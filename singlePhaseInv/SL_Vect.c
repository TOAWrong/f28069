#include	<header.h>
#include	<extern.h>

void SL_SpeedCntl_SFRF()
{
	double 	IntegralLimit;
	
	wr_ref=wr_rat * reference_out;
	
	wr_CycleIndex++;
	wr_Cycle+=Ts;
	if (wr_CycleIndex >= wr_CntlPeriodIndex)
	{
		wr_err = wr_ref-wr; 
		wr_ErrInt += Ki_wr*wr_err*inv_P_pair*wr_Cycle;
		IntegralLimit = Kp_wr*fabs(K_Damp_wr*wr_ref-wr)*inv_P_pair + Is_DQ_max[QS];

		if (wr_ErrInt>IntegralLimit) 		wr_ErrInt=IntegralLimit;
		else if (wr_ErrInt<-IntegralLimit)	wr_ErrInt=-IntegralLimit;

		Is_DQ_ref[QS]=Kp_wr*(K_Damp_wr*wr_ref-wr)*inv_P_pair+wr_ErrInt;

		if (gfRunTime<0.05)		wr_ErrInt=0.0;
		wr_Cycle=0.0;
		wr_CycleIndex=0;
	}	
	SL_VectCntl_SFRF();	
}

void SL_TorqueCntl_SFRF()
{

    Te_ref=Te_rat*reference_out;
	inv_Fs_ref=1.0/Fs_ref;
	Is_DQ_ref[QS]=inv_Kt*Te_ref*inv_Fs_ref;
	SL_VectCntl_SFRF();
}

// Direct Stator Flux Oriented Sensorless Vector Control
void SL_VectCntl_SFRF()
{
	CosDeltaTheta=cos(we*Ts);
	SinDeltaTheta=sin(we*Ts);
	
	Us_dq[ds]=Vs_dq[ds]*CosDeltaTheta + Vs_dq[qs]*SinDeltaTheta;
	Us_dq[qs]=-Vs_dq[ds]*SinDeltaTheta + Vs_dq[qs]*CosDeltaTheta;
	
	Vs_dq[ds]=Us_dq[ds];
	Vs_dq[qs]=Us_dq[qs];
	
	Fs_dq[ds] += (Vs_dq[ds]-Rs*Is_dq[ds])*Ts;
	Fs_dq[qs] += (Vs_dq[qs]-Rs*Is_dq[qs])*Ts;
	
	Fs=sqrt(Fs_dq[ds]*Fs_dq[ds] + Fs_dq[qs]*Fs_dq[qs]);

	if ( gfRunTime >0.05){
		inv_Fs=1.0/Fs;
		CosTheta=Fs_dq[ds]*inv_Fs; SinTheta=Fs_dq[qs]*inv_Fs;
	}else {
		 inv_Fs=0.0; 
		 SinTheta=0.0;  CosTheta=1.0;
	 }

	Is_DQ[DS] = CosTheta*Is_dq[ds] + SinTheta*Is_dq[qs];
	Is_DQ[QS] = -SinTheta*Is_dq[ds] + CosTheta*Is_dq[qs];

//	Vs_DQ[DS] = CosTheta*Vs_dq[ds] + SinTheta*Vs_dq[qs];
	Vs_DQ[QS] = -SinTheta*Vs_dq[ds] + CosTheta*Vs_dq[qs];

	we_in=(Vs_DQ[QS] - Rs*Is_DQ[QS])*inv_Fs;
	we+=(0.5*wr_FilterPole)*(we_in - we)*Ts;	

	Vs_max=0.57735*Vdc;		// 1.0/sqrt(3.0)=0.57735027
	Vs_max_FW+=20.0*(FW_VoltageCoeff*(Vs_max-Rs*Is_max) - Vs_max_FW)*Ts;

	if (gfRunTime <0.05){ Vs_max_FW = Vs_max;	Fs_ref=Fs_B; }

	we_FW=(sqrt(fabs((Vs_max_FW*Vs_max_FW)-(Rs*0.707*Is_max)*(Rs*0.707*Is_max)))- Rs*Is_max)*inv_Fs_B;

	Fs_ref0 = (fabs(we)<we_FW) ? Fs_B : Fs_B*(we_FW/fabs(we));
	if (Fs_ref0>Fs_B) Fs_ref0=Fs_B;
	Fs_ref += 50.0*(Fs_ref0-Fs_ref)*Ts;

	if (gfRunTime>0.05){
		w_sl=(sigma_Ls*(Is_DQ[QS] - prev_I_QS)*inv_Ts + SlipCoeff*Is_DQ[QS])/(Fs - sigma_Ls*Is_DQ[DS]);
		prev_I_QS=Is_DQ[QS];
		w_sl+=0.5*SlipCompCoeff*Pf*Delta_wr;
	} else {
		we=0.0;
		we_in=0.0;
		w_sl=0.0;
		prev_I_QS=Is_DQ[QS];
	}	

	Pf = ((Is_DQ[QS]*(Vs_DQ[QS] - Rs*Is_DQ[QS])) >= 0.0) ? 1.0 : -1.0;
	sgn_I_QS = (Is_DQ[QS]>=0.0) ?  1.0 : -1.0;

	I_DS0_0 += (inv_sigma_Tr)*( ((sigma_Tr*w_sl*Is_DQ[QS]) + (sigma_minus_1_div_sigma_Ls*Fs)) - I_DS0_0)*Ts;		
	I_DS0 = I_DS0_0 + inv_sigma_Ls*Fs;

	I_DS_err=Is_DQ[DS] - I_DS0;
	if (gfRunTime < 0.05){
		Pf=1.0;
		DeltaLambda=GammaLambda*sigma_Ls*I_DS_err; 
		DeltaTheta=0.0; 
	}else{
		if (Pf>=0.0){
			DeltaTheta=GammaTheta_M*(sgn_I_QS*inv_Is_rat)*I_DS_err;
			DeltaLambda=GammaLambda*sigma_Ls*I_DS_err;
		} else {
			DeltaTheta=-GammaTheta_R*(sgn_I_QS*inv_Is_rat)*I_DS_err;
			if (fabs(Is_DQ[QS])<(0.05*I_QS_rat))	
					DeltaLambda=GammaLambda*sigma_Ls*I_DS_err;
			else	DeltaLambda=GammaLambda*sigma_Ls*I_DS_err*I_QS_rat/(I_QS_rat+GammaLambda_R_Constant*(fabs(Is_DQ[QS])-0.05*I_QS_rat));
		}
	}
		
	if (DeltaLambda>Max_DeltaLambda)		DeltaLambda = Max_DeltaLambda;
	else if (DeltaLambda<-Max_DeltaLambda)	DeltaLambda =-Max_DeltaLambda;
	if (DeltaTheta>Max_DeltaTheta)			DeltaTheta  = Max_DeltaTheta;
	else if (DeltaTheta<-Max_DeltaTheta)	DeltaTheta  =-Max_DeltaTheta;

	SinCosDeltaTheta=sqrt(1.0-2.0*DeltaTheta+2.0*DeltaTheta*DeltaTheta);	
	inv_SinCosDeltaTheta=1.0/SinCosDeltaTheta;
	CosDeltaTheta=(1.0-DeltaTheta)*inv_SinCosDeltaTheta;
	SinDeltaTheta=DeltaTheta*inv_SinCosDeltaTheta;
	SinTheta1=SinTheta*CosDeltaTheta + CosTheta*SinDeltaTheta;
	CosTheta1=CosTheta*CosDeltaTheta - SinTheta*SinDeltaTheta;

	Fs+=DeltaLambda;
	Fs_dq[ds]=Fs*CosTheta1;
	Fs_dq[qs]=Fs*SinTheta1;

	Is_DQ_ref[DS]=I_DS0_0 + inv_sigma_Ls*Fs_ref;

	if (gfRunTime > ExcitationTime){	
		Is_DQ_max[DS] = 0.9 * Is_max;
	} else {
		Is_DQ_max[DS]=(ExcitationTime+Tr)/(ExcitationTime+sigma*Tr)*(Fs_B*inv_Ls);
		if (Is_DQ_max[DS]<(Fs_B*inv_Ls)) 	Is_DQ_max[DS]=Fs_B*inv_Ls;
		else if (Is_DQ_max[DS]>0.9*Is_max)	Is_DQ_max[DS]=0.9*Is_max;	
	}	
	
	if (Is_DQ_ref[DS]>=Is_DQ_max[DS]) Is_DQ_ref[DS]=Is_DQ_max[DS];
	else if (Is_DQ_ref[DS]<(0.5*inv_Ls*Fs_ref))	Is_DQ_ref[DS]=0.5*inv_Ls*Fs_ref;

	Vs_DQ_max[DS] = Vs_max;		// 0.8165=sqrt(2/3) => Vs_rat=0.8165*Vs_LL_rms= phase peak voltage		
	Is_DQ_ErrInt[DS] += Ki_Is*(Is_DQ_ref[DS] - Is_DQ[DS])*Ts;
	if (Is_DQ_ErrInt[DS]>Vs_DQ_max[DS])	        Is_DQ_ErrInt[DS] =  Vs_DQ_max[DS];
	else if (Is_DQ_ErrInt[DS]<-Vs_DQ_max[DS])   Is_DQ_ErrInt[DS] = -Vs_DQ_max[DS];

	Vs_DQ_ref_PI[DS]=Kp_Is*(K_Damp_Is*Is_DQ_ref[DS] - Is_DQ[DS]) + Is_DQ_ErrInt[DS];
	
	Is_DQ_max[QS]=sqrt( fabs(Is_max*Is_max - Is_DQ_ref[DS]*Is_DQ_ref[DS]) );	// Q-�� ���� ���� ��
	if (Is_DQ_ref[QS]>Is_DQ_max[QS])		
		Is_DQ_ref[QS]=Is_DQ_max[QS];
	else if (Is_DQ_ref[QS]<-Is_DQ_max[QS])	
		Is_DQ_ref[QS]=-Is_DQ_max[QS];	
	
	Vs_DQ_max[QS]=2.0*Vs_max;					// 2.0/3.0=0.666667, 1.0/sqrt(3.0)=0.57735, (0.57735+0.666667)/2.0=0.6220 
	Is_DQ_ErrInt[QS] += Ki_Is*(Is_DQ_ref[QS] - Is_DQ[QS])*Ts;
	if (Is_DQ_ErrInt[QS]>Vs_DQ_max[QS])			
		Is_DQ_ErrInt[QS] = Vs_DQ_max[QS];
	else if (Is_DQ_ErrInt[QS]<-Vs_DQ_max[QS])		
		Is_DQ_ErrInt[QS] = -Vs_DQ_max[QS];
	Vs_DQ_ref_PI[QS] = Kp_Is*(K_Damp_Is*Is_DQ_ref[QS] - Is_DQ[QS]) + Is_DQ_ErrInt[QS];
	
	Vs_DQ_comp[DS]+=100.0*(Fs_ref*inv_Tr - Vs_DQ_comp[DS])*Ts;
	Vs_DQ_comp[QS]+=100.0*(wr*Fs_ref - Vs_DQ_comp[QS])*Ts;
	Vs_DQ_ref[DS] = Vs_DQ_ref_PI[DS] - Vs_DQ_comp[DS];
	Vs_DQ_ref[QS] = Vs_DQ_ref_PI[QS] + Vs_DQ_comp[QS];

	Vs_dq_ref[ds] = (CosTheta*Vs_DQ_ref[DS] - SinTheta*Vs_DQ_ref[QS]) +  (Vs_dq_ref[ds]-Vs_dq[ds]);
	Vs_dq_ref[qs] = (SinTheta*Vs_DQ_ref[DS] + CosTheta*Vs_DQ_ref[QS]) + (Vs_dq_ref[qs]-Vs_dq[qs]);

	if (gfRunTime<0.05) { Delta_wr=0.0; wr=0.0; we=0.0; }
	else {
		Delta_wr_Filter_Pole=1.0*wn_wr;
		Delta_wr += Delta_wr_Filter_Pole*(DeltaTheta*inv_Ts - Delta_wr)*Ts;
		wr += (wr_FilterPole)*( (we_in + Delta_wr - w_sl)  - wr)*Ts;
	}
	
	Freq_out = we * inv_PI_2;
	rpm = rpm_Coeff * wr;	
	Te=Kt*Fs*Is_DQ[QS];	
}

