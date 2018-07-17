#include	<header.h>
#include	<extern.h>

void estim_ReqLeq_pwm()
{
	double	del_Vs_Coeff;

	if( gfRunTime < 0.01){
		GainUpdateTimer = 0.0;
		LPF_Is = 0.0;
		LPF_Is_Square = 0.0;
		LPF_Vs_Square = 0.0;
		LPF_Re_Power = 0.0;
		Vs_Coeff_Leq_Req = 0.0;
		theta = 0.0;
	}

	Freq_ref = AT_Freq_Leq_Req;				//
	we = fabs(PI_2*Freq_ref);	
	Vs_max = Vs_rat;				        //
	theta += we*Ts;

	if (theta>PI)	theta-=PI_2;
	else if (theta<-PI)	theta+=PI_2;			
	
	LPF1(Ts,(0.05*we),fabs(Is_dq[ds]),&LPF_Is);

	Is_Leq_Req=LPF_Is*PI_1_2;					//

	GainUpdateTimer+=Ts;
	
	if (GainUpdateTimer>0.05)					//
	{
		GainUpdateTimer-=0.05;
		if (Is_Leq_Req<(0.3*AT_Is_Coeff_Leq_Req*Is_rat))
			del_Vs_Coeff=0.030;
		else if (Is_Leq_Req<(0.5*AT_Is_Coeff_Leq_Req*Is_rat))	
			del_Vs_Coeff=0.020;
		else if (Is_Leq_Req<(0.7*AT_Is_Coeff_Leq_Req*Is_rat))	
			del_Vs_Coeff=0.015;
		else if (Is_Leq_Req<(0.8*AT_Is_Coeff_Leq_Req*Is_rat))	
			del_Vs_Coeff=0.010;	
		else if (Is_Leq_Req<(0.9*AT_Is_Coeff_Leq_Req*Is_rat))	
			del_Vs_Coeff=0.005;
		else	del_Vs_Coeff=0.002;	
			
		if (Is_Leq_Req<(AT_Is_Coeff_Leq_Req*Is_rat-0.01*Is_rat))
			Vs_Coeff_Leq_Req+=del_Vs_Coeff;				//
		else if (Is_Leq_Req>(AT_Is_Coeff_Leq_Req*Is_rat+0.01*Is_rat))	
			Vs_Coeff_Leq_Req-=del_Vs_Coeff;	
	}	

	Vs_ref=Vs_Coeff_Leq_Req*(Freq_ref*inv_motor_rate_hz)*Vs_max;
	
	CosDeltaTheta=cos(we*Ts);
	SinDeltaTheta=sin(we*Ts);
	Us_dq[ds]=Vs_dq[ds]*CosDeltaTheta + Vs_dq[qs]*SinDeltaTheta;
	Us_dq[qs]=-Vs_dq[ds]*SinDeltaTheta + Vs_dq[qs]*CosDeltaTheta;
	Vs_dq[ds]=Us_dq[ds];
	Vs_dq[qs]=Us_dq[qs];
	
	LPF1(Ts,(0.5*we),Vs_dq[ds]*Is_dq[ds],&LPF_Re_Power);
	LPF1(Ts,(0.5*we),(2.0*Is_dq[ds]*Is_dq[ds]),&LPF_Is_Square);
	LPF1(Ts,(0.5*we),(Vs_dq[ds]-Req*Is_dq[ds])*(Vs_dq[ds]-Req*Is_dq[ds]),&LPF_Vs_Square);
	
	if ( Is_Leq_Req>(0.5*AT_Is_Coeff_Leq_Req*Is_rat) )	//
	{
		if (gfRunTime<(AT_Time_Leq_Req-0.5)){
			LPF1(Ts,(0.05*we),sqrt(2.0*LPF_Vs_Square/LPF_Is_Square)/we,&Leq);
			LPF1(Ts,(0.05*we), 2.0*(LPF_Re_Power)/LPF_Is_Square,&Req);	
		} else {
			LPF1(Ts,(0.01*we),sqrt(2.0*LPF_Vs_Square/LPF_Is_Square)/we,&Leq);
			LPF1(Ts,(0.01*we), 2.0*(LPF_Re_Power)/LPF_Is_Square,&Req);	
		}	
	}
	Vs_dq_ref[ds]=Vs_ref*cos(theta);	
	Vs_dq_ref[qs]=0.0;		
}	

void estim_Rs_pwm()
{
	double	Is_ref;
	
	Is_ref=AT_Is_Coeff_Rs*Is_rat;	// AT_Is_Coeff_Rs = 1.0
	we=0.0;

	Is_dq_ref[ds]=Is_ref;						// DC ����
	Is_dq_ref[qs]=0.0;
	
	Vs_max=0.57735*Vdc;
	PI_Damp_Controller(Vs_max,Ts,K_Damp_Is,codeKpIs,codeKiIs,Is_dq_ref[ds],Is_dq[ds],&Is_dq_ErrInt[ds],&Vs_dq_ref[ds]);
	PI_Damp_Controller(Vs_max,Ts,K_Damp_Is,codeKpIs,codeKiIs,Is_dq_ref[qs],Is_dq[qs],&Is_dq_ErrInt[qs],&Vs_dq_ref[qs]);

	if ( (Is_mag>0.1*Is_rat) && (gfRunTime>0.1) ) {
		Re_Power=Vs_dq[ds]*Is_dq[ds]+Vs_dq[qs]*Is_dq[qs];
		if (gfRunTime<0.2)	Rs=0.0;
		else if (gfRunTime<(AT_Time_Rs-1.0)) LPF1(Ts,10.0,Re_Power/(Is_mag*Is_mag),&Rs);
		else	LPF1(Ts,1.0,Re_Power/(Is_mag*Is_mag),&Rs);
	}
}

void estim_Ls_pwm()
{
	double	IncFreq;
	double	Es_m, sgn_freq, Det_emf, Det_slip, Ls_in;
	
	CosDeltaTheta=cos(we*Ts); SinDeltaTheta=sin(we*Ts);
	Us_dq[ds]=Vs_dq[ds]*CosDeltaTheta + Vs_dq[qs]*SinDeltaTheta;
	Us_dq[qs]=-Vs_dq[ds]*SinDeltaTheta + Vs_dq[qs]*CosDeltaTheta;
	Vs_dq[ds]=Us_dq[ds];  Vs_dq[qs]=Us_dq[qs];
	
	Vs_max=Vs_rat;	
	if (gfRunTime < 0.2 )	// debug
	{
		Freq_ref = Freq_set = Freq_out=0.0;
		we = 0.0;
		theta=0.0;
        SinTheta=0.0;
		CosTheta=1.0;
		Vs_ref=Rs*Is_rat;
	}
	else 
	{
		IncFreq=(Ts/AT_Ls_Vs_RAMP)*AT_Freq_Ls;
		if ( gfRunTime < (ExcitationTime+AT_Ls_Vs_RAMP+AT_Time_Ls))
				Freq_ref=AT_Freq_Ls;
		else	Freq_ref=0.0;
			
		if (Freq_set>(Freq_ref+IncFreq))	
			Freq_set-=IncFreq;
		else if (Freq_set<(Freq_ref-IncFreq))	
			Freq_set+=IncFreq;
	
		if (Freq_set>=0.0) 	sgn_freq = 1.0;
		else				sgn_freq =-1.0;
				

		Slip=fabs(Freq_slip * inv_motor_rate_hz);
		
		Power_core_rat = codeRatePower*(1.0-codeRateEffiency/(1.0-S_rat))-1.5*Is_rat*Is_rat*Rs;
		Power_core = 0.5*( (1.0+Slip)/(1+S_rat)*(Freq_out*inv_motor_rate_hz) + (1.0+Slip*Slip)/(1.0+S_rat*S_rat)*(Freq_out*inv_motor_rate_hz)*(Freq_out*inv_motor_rate_hz) )*Power_core_rat;
		LPF1(Ts,VF_Slip_Comp_FilterPole,1.5*(Vs_dq[ds]*Is_dq[ds]+Vs_dq[qs]*Is_dq[qs] - (VF_Rs_ThermalCoeff*Rs)*Is_mag*Is_mag)-Power_core,&Power_gap);	
		Det_slip=Freq_ref*Freq_ref + S_lin*Power_gap;
		if (Det_slip<0.0)
			LPF1(Ts,VF_Slip_Comp_FilterPole,-0.5*sqrt(fabs(S_lin*Power_gap)),&Freq_slip);
		else	LPF1(Ts,VF_Slip_Comp_FilterPole,0.5*(sqrt(Det_slip)-fabs(Freq_ref)),&Freq_slip);
		Freq_out=Freq_set + sgn_freq*Freq_slip;
	
		Freq_out=Freq_set;
		
		we=fabs(PI_2*Freq_out);				// ������ ����� ���ļ� 
		theta+=we*Ts;

		if (theta>PI)				theta-=PI_2;
		else if (theta<-PI)		theta+=PI_2;	

		SinTheta=sin(theta);		CosTheta=cos(theta);	
		
		Vs_max=0.57735*Vdc;

		Es_m = Base_Flux_Coeff*fabs(Freq_out)*inv_motor_rate_hz*Vs_rat;
		if (Es_m>Vs_max)	Es_m=Vs_max;
	
		Is_DQ[DS]= CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
		Is_DQ[QS]=-SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];
		Det_emf=(Es_m*Es_m)-(Rs*Is_DQ[QS])*(Rs*Is_DQ[QS]);  //sqrt���� ������������
		if ( (Det_emf>0.0)&&(fabs(Freq_out)>VF_Freq_TrqBoost) )
				LPF1(Ts,VF_IR_Comp_FilterPole,Rs*Is_DQ[DS]+sqrt(Det_emf)-Es_m,&Vs_IR_comp);		
		else	LPF1(Ts,VF_IR_Comp_FilterPole,VF_Vs_Coeff_TrqBoost*Vs_rat,&Vs_IR_comp);	
	
		// ���� ���ѱ�
		if (Is_mag > Is_max)
		{
			del_Vs_comp=(2.0*Vs_rat*inv_Is_rat)*(Is_mag-Is_max);
			if (del_Vs_comp>0.1*Vs_rat)	
				del_Vs_comp=0.1*Vs_rat;
			else if (del_Vs_comp<-0.1*Vs_rat)	
				del_Vs_comp=-0.1*Vs_rat;
		}	
		else	del_Vs_comp=0.0;
	
		// ���� ���� ���
		Vs_ref = Es_m + Vs_IR_comp - del_Vs_comp;		// IR���, ����ũ�� ���� 
		if (Vs_ref>Vs_max)
			Vs_ref=Vs_max;
	}	

	Vs_dq_ref[ds]=Vs_ref*CosTheta + AT_DeadTimeGain*(Vs_dq_ref[ds]-Vs_dq[ds]);
	Vs_dq_ref[qs]=Vs_ref*SinTheta + AT_DeadTimeGain*(Vs_dq_ref[qs]-Vs_dq[qs]);
	
	LPF1(Ts,100.0,Vs_dq[qs]*Is_dq[ds] - Vs_dq[ds]*Is_dq[qs],&Im_Power);				// ��ȿ����
	LPF1(Ts,100.0,(Vs_dq[ds]*Is_dq[ds] + Vs_dq[qs]*Is_dq[qs]) - Rs*(Is_mag*Is_mag),&Re_Power);	// ��ȿ����

	if ( (gfRunTime>ExcitationTime) && (Is_mag>(0.1*Is_rat)) && (Is_mag<(0.9*Is_rat)) )
	{
		if (gfRunTime<(ExcitationTime+AT_Ls_Vs_RAMP*AT_Freq_Ls*inv_motor_rate_hz+AT_Time_Ls-0.1))
		{
			if (Ls>(5.0*Leq))
			{
				Lr=Ls;							// ȸ���� �δ��Ͻ��� ������ �δ��Ͻ��� ���� �����Ƿ� ������ ������ ���� �ʴ´�.
				Rr=(Req-Rs)*(Lr*Lr)/((Lr-0.5*Leq)*(Lr-0.5*Leq));			// Rr ~ (Req-Rs)*(Lr/Lm)^2
				sigma_Ls=Leq-(Rr*Rr)*(Lr-0.5*Leq)*(Lr-0.5*Leq)/(Lr*Lr*Lr)/(PI_2*AT_Freq_Leq_Req*PI_2*AT_Freq_Leq_Req);
				sigma=sigma_Ls/Ls;
			}
			else
			{
				sigma=0.1;
				sigma_Ls=Leq;
			}	
			Ls_in=2.0*(Re_Power*Re_Power+Im_Power*Im_Power)/( Im_Power+sqrt(fabs(Im_Power*Im_Power - (4*sigma/sigma*sigma) * (Re_Power*Re_Power+Im_Power*Im_Power))) )/(we*Is_mag*Is_mag) - sigma_Ls;
			if (Ls_in>30.0*Leq)	
				Ls_in=30.0*Leq;
			else if (Ls_in<3.0*Leq)
				Ls_in=3.0*Leq;
			if (gfRunTime<(AT_Ls_Vs_RAMP+AT_Time_Ls+ExcitationTime-1.0))
					LPF1(Ts,(0.05*we),Ls_in,&Ls);
			else	LPF1(Ts,(0.01*we),Ls_in,&Ls);	
		}
	}
}

void estim_Jm_pwm()
{
    double	t0,t1,t2;
	double	ts0,ts1,ts2,ts3;
	
	t0=ExcitationTime + AT_Ls_DMB_OpenTime;
	t1=ExcitationTime + AT_Ls_DMB_OpenTime + 0.45*AT_Time_Jm;
	t2=ExcitationTime + AT_Ls_DMB_OpenTime + 0.90*AT_Time_Jm;

	if (gfRunTime<=t0)
	{
		Is_DQ_ref[QS]=0.0;	
		Jm=0.0e-6;
		Jm_ID_wr[0]=Jm_ID_wr[1]=Jm_ID_wr[2]=Jm_ID_wr[3]=0.0;
		Jm_ID_Te[0]=Jm_ID_Te[1]=Jm_ID_Te[2]=Jm_ID_Te[3]=0.0;
		Jm_ID_t[0]=Jm_ID_t[1]=Jm_ID_t[2]=Jm_ID_t[3]=0.0;
	}
	else if (gfRunTime<=t1)	
			Is_DQ_ref[QS]=(AT_Te_Coeff_Jm*Te_rat)*(inv_Kt*inv_Fs_B);
	else if (gfRunTime<=t2)	
			Is_DQ_ref[QS]=-(AT_Te_Coeff_Jm*Te_rat)*(inv_Kt*inv_Fs_B);
	else	Is_DQ_ref[QS]=0.0;		

	SL_VectCntl_SFRF();

	ts0=ExcitationTime + AT_Ls_DMB_OpenTime + 0.05*AT_Time_Jm;
	ts1=ExcitationTime + AT_Ls_DMB_OpenTime + 0.45*AT_Time_Jm;
	ts2=ExcitationTime + AT_Ls_DMB_OpenTime + 0.55*AT_Time_Jm;
	ts3=ExcitationTime + AT_Ls_DMB_OpenTime + 0.95*AT_Time_Jm;

	if (gfRunTime<=ts0)		// Sampling 1
	{	
		Jm_ID_wr[0]=wr*inv_P_pair;
		Jm_ID_Te[0]=Te;
		Jm_ID_t[0]=gfRunTime;
	} 
	else if (gfRunTime<=ts1)	// Sampling 2
	{	
		Jm_ID_wr[1]=wr*inv_P_pair;
		Jm_ID_Te[1]=Te;
		Jm_ID_t[1]=gfRunTime;
	}
	else if (gfRunTime<=ts2) 	// Sampling 3
	{	
		Jm_ID_wr[2]=wr*inv_P_pair;
		Jm_ID_Te[2]=Te;
		Jm_ID_t[2]=gfRunTime;
	}
	else if (gfRunTime<=ts3) 	// Sampling 4	
	{	
		Jm_ID_wr[3]=wr*inv_P_pair;
		Jm_ID_Te[3]=Te;
		Jm_ID_t[3]=gfRunTime;
	}	
}

//---------------------------------------------------
// auto tunning loop control
//---------------------------------------------------

int estim_req_leq_loop( )
{
	int iTemp,iTripCode;
	int iCommand;
	int LoopCtrl;

	unsigned long count_msec=0;

	double fReference;

//	INIT_CHARGE_CLEAR;
//	MAIN_CHARGE_SET;
//	TRIP_OUT_CLEAR;
	commonVariableInit();
	if( (iTripCode = HardwareParameterVerification()) !=0 ){
		Nop();
		return iTripCode;
	}

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	Leq=0.0;	Req=0.0;		
	LPF_Is = 0.0;
	LPF_Is_Square = 0.0;
	LPF_Vs_Square =0.0;
	LPF_Re_Power = 0.0;

	AutoTuningFlag = ID_AT_LEQ_REQ;
	gfRunTime = 0.0 ;
	LoopCtrl = 1;		

	while(LoopCtrl == 1)
	{
		if( gfRunTime < 0.3 )	gMachineState = STATE_INIT_RUN;
		else					gMachineState = STATE_RUN; 

		if(gfRunTime >= (AT_Time_Leq_Req + 4.0)) LoopCtrl = 0;
		if( gPWMTripCode != 0 ) 	LoopCtrl = 0;
		get_command(&iCommand,&fReference);
		if ( iCommand == CMD_STOP)	{LoopCtrl = 0; gMachineState = STATE_READY;}

		if( ulGetTime_mSec(count_msec) > 500 ){
			count_msec = ulGetNow_mSec( );
			snprintf(gStr1,25,"IsLeqReq=%10.2e : ", Is_Leq_Req);
			load_sci_tx_mail_box( gStr1) ;

			snprintf(gStr1,25,"ReP= %10.3e : ",LPF_Re_Power);
			load_sci_tx_mail_box( gStr1) ;

            snprintf(gStr1,25,"lpfI= %10.3e : ",LPF_Is);
            load_sci_tx_mail_box( gStr1) ;

            snprintf(gStr1,25,"Isq= %10.3e : ",LPF_Is_Square);
            load_sci_tx_mail_box( gStr1) ;

            snprintf(gStr1,25,"Vsq= %10.3e \r\n",LPF_Vs_Square);
            load_sci_tx_mail_box( gStr1) ;
		}
	}

	Nop();
	if( gfRunTime < (AT_Time_Leq_Req + 4.0) ){

		if		(gPWMTripCode != 0) iTemp = gPWMTripCode;
		else 	iTemp = 0;
		return iTemp;
	}	
		
	gMachineState = STATE_READY;

	if (Req<=1.0e-3){	
		trip_recording( ERR_Req_Under,Req,"ERR ReqUnder0.001");
		return	ERR_Req_Under;			// Req <= 1m Ohm
	}

	if (Req>=20.0){
		trip_recording( ERR_Req_Over,Req,"ERR Req Over 20.0");
		return	ERR_Req_Over;			// Req >= 10.0 Ohm
	}
	if (Leq<=0.1e-3){
		trip_recording( ERR_Leq_Under0,Leq,"ERRLeqUnder0.0001");
		return	ERR_Leq_Under0;			// Leq <= 100 uH
	}
	if (Leq>=200.0e-3){
		trip_recording( ERR_Leq_Over0,Leq,"ERR Leq Over 0.2");
		return	ERR_Leq_Over0;			// Leq <= 100 uH
	}

	codeKiIs = codeKiIs;
    codeKpIs = codeKpIs;

	return AT_SUCCESS; 
}

int estim_Rs_loop()
{
	int iCommand;
	double fReference;
	int LoopCtrl;
	int iTemp;

	gMachineState = STATE_READY;
//	AutoTuningFlag=0;												// No Action
	commonVariableInit();

	Vs_dq_ref[ds] = Vs_dq_ref[qs] = 0.0;
	Is_dq_ErrInt[ds] = Is_dq_ErrInt[qs] = 0.0;

	Rs=0.0;												// Rs �ʱ�ȭ
	AutoTuningFlag = ID_AT_RS;

	gfRunTime=0.0;
	LoopCtrl = 1;
	gMachineState = STATE_RUN;

	while(LoopCtrl == 1)
	{
		if( gfRunTime >= AT_Time_Rs ) LoopCtrl = 0;
		get_command(&iCommand,&fReference);
//		if ( EXT_TRIP == 1) 			LoopCtrl = 0; 
		if( gPWMTripCode != 0 ) 	LoopCtrl = 0;
		if ( iCommand == CMD_STOP)	{LoopCtrl = 0; gMachineState = STATE_READY;}
	}

	gMachineState = STATE_READY;

	if( gfRunTime < AT_Time_Rs ){
		if		(gPWMTripCode != 0){
			gMachineState = STATE_TRIP;
			iTemp = gPWMTripCode;
		}
		else{
			gMachineState = STATE_READY;
		 	iTemp = 0;
		}
		return iTemp;
	}	

	if (Rs<=1.0e-3){
		trip_recording( ERR_Rs_Under,Rs,"ERR  Rs <= 0.001    ");
		return	ERR_Rs_Under;			// Leq <= 100 uH
	}
	if (Rs>=0.99*Req){
		trip_recording( ERR_Rs_Over,Rs,"ERR Rs >= 0.99*Req  ");
		return	ERR_Rs_Over;			// Leq <= 100 uH
	}
	return AT_SUCCESS; 
}

int estim_Ls_loop()
{
	int iCommand;
	int iTripCode = 0;
    int LoopCtrl;
	unsigned long Ls_count_msec=0;

	double fReference;
	double TuningTime;
	double In;

	gMachineState = STATE_READY;
	commonVariableInit();

	Ls=0.0;													// Ls �ʱ�ȭ
	gfRunTime=0.0;
	TuningTime	=	AT_Time_Ls + AT_Ls_Vs_RAMP + 0.2;

	AutoTuningFlag = ID_AT_LS;							

	load_sci_tx_mail_box( "AT LS loop Start \n") ;
	delay_msecs(10);

	gMachineState = STATE_RUN;

	LoopCtrl = 1;

	while(LoopCtrl == 1)
	{
		if(gPWMTripCode != 0){
			LoopCtrl = 0; 
			iTripCode = gPWMTripCode;
			gMachineState = STATE_TRIP;
			load_sci_tx_mail_box( "Ls Trip End \n") ;
		}

		get_command(&iCommand,&fReference);	// Command�� �Է� ���� 
		if ( iCommand == CMD_STOP){
			LoopCtrl = 0;
			iTripCode = 0;
			gMachineState = STATE_READY;
			load_sci_tx_mail_box( "LS Stop End \n") ;
		}

		if( gfRunTime >= TuningTime ){
			LoopCtrl = 0;
			iTripCode = 0;
			gMachineState = STATE_READY;
			load_sci_tx_mail_box( "LS Time End \n") ;
		}

		if ( gfRunTime >  AT_Ls_DMB_OpenTime )		RUN_OUT_ON;

		if( ulGetTime_mSec(Ls_count_msec) > 500 ){
			Ls_count_msec = ulGetNow_mSec( );
			snprintf(gStr1,25,"\n Im=%10.1e :: ", Im_Power);
			load_sci_tx_mail_box( gStr1) ;
			snprintf(gStr1,25,"Re=%10.1e \n", Re_Power);
			load_sci_tx_mail_box( gStr1) ;
		}
	}

	if( gfRunTime < TuningTime ) return iTripCode;

	gMachineState = STATE_READY;
	load_sci_tx_mail_box( "Start Ls Check \n") ;
	delay_msecs(5);

	if (Ls>1.0){
		trip_recording( ERR_Ls_Over0,Ls,"ERR Ls >= 1.0       ");
		return	ERR_Ls_Over0;			// Leq <= 100 uH
	}
	else if (Ls<0.001){
		trip_recording( ERR_Ls_Under0,Ls,"ERR Ls <= 0.001     ");
		return	ERR_Ls_Under0;			// Leq <= 100 uH
	}

	In = Vs_rat/(we_rat*Ls);

	if (In>0.80*Is_rat){
		trip_recording( ERR_Ls_Under1,In,"ERR I_nl > 0.8*Irat ");
		return	ERR_Ls_Under1;			// Leq <= 100 uH
	}
	else if (In<0.1*Is_rat)	{
		trip_recording( ERR_Ls_Over1,In,"ERR I_nl < 0.1*Irat ");
		return	ERR_Ls_Over1;			// Leq <= 100 uH
	}
	if (Leq>0.75*Ls){
		trip_recording( ERR_Leq_Over1,Leq,"ERR Leq< 0.75 * Ls  ");
		return	ERR_Leq_Over1;			// Leq <= 100 uH
	}

	Lr=Ls;
	Rr=(Req-Rs)*(Lr*Lr)/((Lr-0.5*Leq)*(Lr-0.5*Leq));	// Rr ~ (Req-Rs)*(Lr/Lm)^2
	sigma_Ls=Leq-(Rr*Rr)*(Lr-0.5*Leq)*(Lr-0.5*Leq) /(Lr*Lr*Lr)/(PI_2*AT_Freq_Leq_Req*PI_2*AT_Freq_Leq_Req);
	sigma=sigma_Ls/Ls;
	if (sigma<0.02)		
	{
		trip_recording( ERR_sigma_Under,sigma,"ERR sigma < 0.02    ");
		return	ERR_sigma_Under;			// Leq <= 100 uH
	}
	else if (sigma>0.2)	{
		trip_recording( ERR_sigma_Over,sigma,"ERR sigma > 0.2     ");
		return	ERR_sigma_Over;			// Leq <= 100 uH
	}
	
	Lm=sqrt((1.0-sigma)*Ls*Lr);
	if (Lm>0.985*Ls){
		trip_recording( ERR_sigma_Under,Lm,"ERR Lm > 0.985*Ls   ");
		return	ERR_sigma_Under;			// Leq <= 100 uH
	}
	
	Lr=Ls;
	Rr=(Req-Rs)*(Lr*Lr)/(Lm*Lm);
	Tr=Lr/Rr;
	
	if (Tr>2.0){
		trip_recording( ERR_Tr_Over,Tr,"ERR Tr > 2.0   ");
		return	ERR_Tr_Over;			// Leq <= 100 uH
	}
	else if (Tr<0.02){
		trip_recording( ERR_Tr_Under,Tr,"ERR Tr < 0.02   ");
		return	ERR_Tr_Under;			// Leq <= 100 uH
	}
	
	sigma_Ls=Leq-(Rr*Rr)*(Lm*Lm)/(Lr*Lr*Lr)/(PI_2*AT_Freq_Leq_Req*PI_2*AT_Freq_Leq_Req);
	sigma=sigma_Ls/Ls;
	
	if (sigma<0.02){
		trip_recording( ERR_sigma_Under,sigma,"ERR sigma < 0.02   ");
		return	ERR_sigma_Under;			// Leq <= 100 uH
	}else if (sigma>0.2){
		trip_recording( ERR_sigma_Over,sigma,"ERR sigma > 0.2   ");
		return	ERR_sigma_Over;			// Leq <= 100 uH
	}
	
	Lm=sqrt((1.0-sigma)*Ls*Lr);
	if (Lm>0.985*Ls){
		trip_recording( ERR_sigma_Under,sigma,"ERR Lm > 0.985 * Ls ");
		return	ERR_sigma_Under;			// Leq <= 100 uH
	}
	return AT_SUCCESS; 
}								
	
int estim_Jm_loop()
{
	int LoopCtrl, iTripCode,iCommand;

	double fReference, TuningTime;

	gMachineState = STATE_READY;

	inv_sigma_Ls=1.0/sigma_Ls;
	inv_Tr=1.0/Tr;
	inv_Ls=1.0/Ls;
	SlipCoeff=Ls/Tr;
	sigma_Tr=sigma*Tr;
	inv_sigma_Tr=1.0/sigma_Tr;
	sigma_minus_1_div_sigma_Ls=(sigma-1.0)/sigma_Ls;
	inv_Ls_plus_sigma_Ls=1.0/(sigma_Ls+Ls);
	sigma_Ls_div_1_plus_sigma=sigma_Ls/(1.0+sigma);
	Lm_div_Lr=Lm/Lr;
	Lr_div_Lm=Lr/Lm;

	if ( (FW_VoltageCoeff<0.2) || (FW_VoltageCoeff>1.5) )			// ����� ���� ���� ���	
		return	CODE_FW_VoltageCoeff;
	if ( (ExcitationTime<0.1) || (ExcitationTime>3.0) )	
		return	CODE_ExcitationTime;
	
	inv_Fs_B=1.0/Fs_B;	Fs_ref=Fs_B;	

	I_QS_rat=(2.0/3.0)*inv_P_pair*Te_rat/Fs_B;

	wr_FilterPole=Default_wr_FilterPole;				// �ӵ� �������� ���� ��
	wn_wr=wr_FilterPole/10.0;							// �ӵ��� �뿪���� ���� ���� 1/10�� ����
	if (wn_wr>Max_wn_wr)	wn_wr=Max_wn_wr;			// max_wn_wr*10.0 ==> measurement noise cutoff frequency

	gfRunTime=0.0; 

	LoopCtrl = 1;
	while(LoopCtrl == 1)
	{
		get_command(&iCommand,&fReference);	// Command� �Է� ���� 
		if ( iCommand == CMD_STOP){
			LoopCtrl = 0;
			iTripCode = 0;
			gMachineState = STATE_READY;
		}
		if( gfRunTime > 1.0 ) LoopCtrl = 0;
	} 

	commonVariableInit();

	TuningTime = ExcitationTime + AT_Ls_DMB_OpenTime + AT_Time_Jm ;
						  //"01234567890123456789"	
	strncpy(MonitorMsg," 4/4 AT FIND Jm     ",20);

	Jm=0.0;	gfRunTime=0.0; LoopCtrl = 1;
	AutoTuningFlag = ID_AT_JM;	
	gMachineState = STATE_RUN;

	while(LoopCtrl == 1)
	{
		if		(gPWMTripCode != 0){
			LoopCtrl = 0; 
			iTripCode = gPWMTripCode;
			gMachineState = STATE_TRIP;
		}

		get_command(&iCommand,&fReference);	// Command�� �Է� ���� 

		if ( iCommand == CMD_STOP){
			LoopCtrl = 0;
			iTripCode = 0;
			gMachineState = STATE_READY;
		}

		if( gfRunTime >= TuningTime ){
			LoopCtrl = 0;
			iTripCode = 0;
			gMachineState = STATE_READY;
		}
		// �ʱ� ���� �ð� ���Ŀ� �극��ũ ����  debug 080726
		if ( gfRunTime >  ExcitationTime )						
		    RUN_OUT_ON;
	}

//	INVERTER_RUN_CLEAR;

	if( gfRunTime < TuningTime ) return iTripCode;
	
	gMachineState = STATE_READY;

	Jm_SampleData[0]=0.5*(Jm_ID_t[1]-Jm_ID_t[0])/(Jm_ID_wr[1]-Jm_ID_wr[0])*(Jm_ID_Te[0]+Jm_ID_Te[1]);
	Jm_SampleData[1]=0.5*(Jm_ID_t[3]-Jm_ID_t[2])/(Jm_ID_wr[3]-Jm_ID_wr[2])*(Jm_ID_Te[2]+Jm_ID_Te[3]);
//		Jm=0.5*(Jm_SampleData[0]+Jm_SampleData[1]);
	Jm=((Jm_ID_t[1]-Jm_ID_t[0])+(Jm_ID_t[3]-Jm_ID_t[2]))/((Jm_ID_wr[1]-Jm_ID_wr[0])-(Jm_ID_wr[3]-Jm_ID_wr[2]))*((Jm_ID_Te[0]+Jm_ID_Te[1])-(Jm_ID_Te[2]+Jm_ID_Te[3]))/4.0;

	if (Jm<=1.0e-6){
		trip_recording( ERR_Jm_Under,Jm,"ERR Jm < 1.0e-6     ");
		return	ERR_Jm_Under;			
	}
	if (Jm>=1000.0){
		trip_recording( ERR_Jm_Over,Jm,"ERR Jm > 1000.0     ");
		return	ERR_Jm_Over;			
	}
	return AT_SUCCESS; 
}	

int parameter_estimation( )
{
	int cmd, iTripCode, LoopCtrl;
	double ref0;
	char str[51] ={0};

	UNION32 u32data;

	iTripCode = estim_req_leq_loop( );
	if ( iTripCode != AT_SUCCESS ) return iTripCode; 

	iTripCode = estim_Rs_loop();
	if ( iTripCode != AT_SUCCESS ) return iTripCode; 

	snprintf(gStr1,25,"Rs=%10.1e  --> ", Rs); load_sci_tx_mail_box( gStr1) ;
	delay_msecs(5);
	load_sci_tx_mail_box( "\n Success find Rs \n");

	iTripCode = estim_Ls_loop();
	if ( iTripCode != AT_SUCCESS ) return iTripCode; 

	snprintf(gStr1,25,"Ls=%10.1e --> ", Ls);
	load_sci_tx_mail_box( gStr1) ;
	delay_msecs(10);
	load_sci_tx_mail_box( "\n Success find Ls \n");
	delay_msecs(10);

	if(Jm_ID_ENABLE > 0.5) {
	    iTripCode = estim_Jm_loop();
	    if ( iTripCode != AT_SUCCESS ) return iTripCode;

	    load_sci_tx_mail_box( "\n Success find Jm \n");
	    delay_msecs(10);
	} else {
        load_sci_tx_mail_box( "---!!! Skip find Jm --- \r\n");
	}

    u32data.dword = Rs; write_code_2_eeprom(CODE_Rs,u32data);
    u32data.dword = Rr; write_code_2_eeprom(CODE_Rr,u32data);
    u32data.dword = Ls; write_code_2_eeprom(CODE_Ls,u32data);
    u32data.dword = Lr; write_code_2_eeprom(CODE_Lr,u32data);
    u32data.dword = Lm; write_code_2_eeprom(CODE_Lm,u32data);
    u32data.dword = Jm; write_code_2_eeprom(CODE_Jm,u32data);

    if( iTripCode = SaveDataProc(CODE_Rs, Rs) ) return iTripCode ;
    if( iTripCode = SaveDataProc(CODE_Rr, Rr) ) return iTripCode ;
    if( iTripCode = SaveDataProc(CODE_Ls, Ls) ) return iTripCode ;
    if( iTripCode = SaveDataProc(CODE_Lr, Lr) ) return iTripCode ;
    if( iTripCode = SaveDataProc(CODE_Lm, Lm) ) return iTripCode ;

    load_sci_tx_mail_box("\n========================= r\n");delay_msecs(10);
    load_sci_tx_mail_box("AT Result Save \r\n");delay_msecs(10);
    snprintf(str,25,"\n Rs=%10.3e",Rs);load_sci_tx_mail_box(str);delay_msecs(10);
    snprintf(str,25,"\n Rr=%10.3e",Rr);load_sci_tx_mail_box(str);delay_msecs(10);
    snprintf(str,25,"\n Ls=%10.3e",Ls);load_sci_tx_mail_box(str);delay_msecs(10);
    snprintf(str,25,"\n Lr=%10.3e",Lr);load_sci_tx_mail_box(str);delay_msecs(10);
    snprintf(str,25,"\n Lm=%10.3e",Lm);load_sci_tx_mail_box(str);delay_msecs(10);
    snprintf(str,25,"\n Jm=%10.3e",Jm);load_sci_tx_mail_box(str);delay_msecs(10);
    load_sci_tx_mail_box("\n======================== \r\n");

    load_sci_tx_mail_box(" send save command for saving motor parameter !!! ");

	iTripCode = 0;
	LoopCtrl = 1;
	while(LoopCtrl == 1)		
	{
		if(gPWMTripCode != 0) {
			LoopCtrl = 0; iTripCode = gPWMTripCode;
			return iTripCode;
		}
        get_command( & cmd, & ref0);
        switch(cmd)
        {
        case CMD_STOP:
            LoopCtrl = 0;
            break;

        case CMD_SAVE:

            u32data.dword = Rs; write_code_2_eeprom(CODE_Rs,u32data);
            u32data.dword = Rr; write_code_2_eeprom(CODE_Rr,u32data);
            u32data.dword = Ls; write_code_2_eeprom(CODE_Ls,u32data);
            u32data.dword = Lr; write_code_2_eeprom(CODE_Lr,u32data);
            u32data.dword = Lm; write_code_2_eeprom(CODE_Lm,u32data);
            u32data.dword = Jm; write_code_2_eeprom(CODE_Jm,u32data);

            if( iTripCode = SaveDataProc(CODE_Rs, Rs) ) return iTripCode ;
            if( iTripCode = SaveDataProc(CODE_Rr, Rr) ) return iTripCode ;
            if( iTripCode = SaveDataProc(CODE_Ls, Ls) ) return iTripCode ;
            if( iTripCode = SaveDataProc(CODE_Lr, Lr) ) return iTripCode ;
            if( iTripCode = SaveDataProc(CODE_Lm, Lm) ) return iTripCode ;

            load_sci_tx_mail_box("\n**************************** r\n");delay_msecs(10);
            load_sci_tx_mail_box("AT Result Save \r\n");delay_msecs(10);
            snprintf(str,25,"\n Rs=%10.3e",Rs);load_sci_tx_mail_box(str);delay_msecs(10);
            snprintf(str,25,"\n Rr=%10.3e",Rr);load_sci_tx_mail_box(str);delay_msecs(10);
            snprintf(str,25,"\n Ls=%10.3e",Ls);load_sci_tx_mail_box(str);delay_msecs(10);
            snprintf(str,25,"\n Lr=%10.3e",Lr);load_sci_tx_mail_box(str);delay_msecs(10);
            snprintf(str,25,"\n Lm=%10.3e",Lm);load_sci_tx_mail_box(str);delay_msecs(10);
            snprintf(str,25,"\n Jm=%10.3e",Jm);load_sci_tx_mail_box(str);delay_msecs(10);
            load_sci_tx_mail_box("\n**************************** \r\n");
            LoopCtrl = 0;
            break;
        default:
            break;
        }
	}
	return iTripCode;	// debug 2008.07.26 
}

// end of auto_tuning.c

