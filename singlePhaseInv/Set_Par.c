#include	<header.h>
#include	<extern.h>

int HardwareParameterVerification()
{
	if ( codeRatePower >(0.99*sqrt(3.0) * codeRateVolt * codeRateCurrent)){
		trip_recording( CODE_rate_power, codeRatePower,"POWER FACTOR OVER");
		return	CODE_rate_power;
	}	

	if (codeRatePower<(0.2*sqrt(3.0)* codeRateVolt * codeRateCurrent)){
		trip_recording( CODE_rate_power, codeRatePower,"POWER FACTOR UNDER");
		return	CODE_rate_power;
	}

	if (codeRateRpm < (0.85*120.0 * codeRateHz / codeMotorPole)){
		trip_recording( CODE_rate_rpm, codeRateRpm,"RATE RPM UNDER");
		return	CODE_rate_rpm;
	}
	Vs_rat=sqrt(2.0)/sqrt(3.0)* codeRateVolt;			// �������� ��ũ ��

	Is_rat=sqrt(2.0)*codeRateCurrent;

	inv_Is_rat=1.0/Is_rat;
	Freq_rat = codeRateHz;
	we_rat=PI_2*Freq_rat;

	inv_Freq_rat=1.0/Freq_rat;

	inv_motor_rate_hz = 1.0 / codeRateHz; //   csk_check 2009.10.30
	wr_rat=PI_2*codeMotorPole*codeRateRpm/120.0;			// rpm -> rad/sec
	wm_rat=wr_rat*(2.0/codeMotorPole);
	Te_rat= codeRatePower/wm_rat;

	inv_Te_rat=1.0/Te_rat;
	Fs_rat=Vs_rat/we_rat;

	Kt=(3.0/2.0)*(codeMotorPole/2.0);
	inv_Kt=1.0/Kt;
	P_pair=(codeMotorPole/2.0);
	inv_P_pair=1.0/P_pair;
	rpm_Coeff=60.0*inv_P_pair/PI_2;
	
	S_rat=(we_rat-wr_rat)/we_rat;
	S_lin=(codeMotorPole/PI)*(S_rat*Freq_rat)/Te_rat;
	Freq_slip_rat=S_rat*Freq_rat;

	inv_Ts = codePwmFreq;
	Ts = 1.0 / codePwmFreq;	// debug

	Is_max = Is_rat * Is_Max_Coeff ;	// added 2009.11.01	
	OverCurLimit = Is_max *2;			// added 2009.11.01  _debug

	return	0;	
}	

int COMMON_VECT_CNTL_ParameterVerification()
{
	double	In;

    if ( Lm > 0.985*Ls ){ trip_recording( CODE_Lm, Lm," Lm > 0.985xLs"); return  CODE_Lm;}
    if ( Lm > 0.985*Lr ){ trip_recording( CODE_Lm, Lm," Lm > 0.985xLr"); return  CODE_Lm;}

    In=Vs_rat/(we_rat*Ls);
    if ( In < 0.1*Is_rat ){ trip_recording( CODE_Ls, Ls," Vs/wLs < 0.1xIs"); return  CODE_Ls;}
    if ( In > 0.8*Is_rat ){ trip_recording( CODE_Ls, Ls," Vs/wLs > 0.8xIs"); return  CODE_Ls;}

    if ( (Lr<(0.9*Ls)) || (Lr>(1.1*Ls)) ){ trip_recording( CODE_Lr, Lr," Lr<> 0.9Ls"); return  CODE_Lr;}
	
	Tr=Lr/Rr;
    if ( Tr < 0.02 ){ trip_recording( ERR_Tr_Over, Tr," Tr(Lr/Rr) < 0.02"); return  ERR_Tr_Over;}
    if ( Tr > 2.0  ){ trip_recording( ERR_Tr_Over, Tr," Tr(Lr/Rr) > 2.0"); return  ERR_Tr_Over;}

    if ( Rs < 0.5*Rr ){ trip_recording( CODE_Rs, Rs," Rs < 0.5 x Rr"); return  CODE_Rs;}
    if ( Rs > 20.0*Rr  ){ trip_recording( CODE_Rs, Rs," Rs > 20 x Rr"); return  CODE_Rs;}

    sigma_Ls=Ls-(Lm*Lm)/Lr;
	sigma=sigma_Ls/Ls;

    if ( sigma < 0.02 ){ trip_recording( ERR_sigma_Under, sigma," (Ls - (Lm*Lm)/Lr)/Ls < 0.02"); return  ERR_sigma_Under;}
    if ( sigma > 0.2 ){ trip_recording( ERR_sigma_Over, sigma," (Ls - (Lm*Lm)/Lr)/Ls > 0.2"); return  ERR_sigma_Over;}
	
	inv_Tr=1.0/Tr;
	inv_Ls=1.0/Ls;
//	inv_Lm=1.0/Lm;
	SlipCoeff=Ls/Tr;
	sigma_Tr=sigma*Tr;
	inv_sigma_Tr=1.0/sigma_Tr;
	sigma_minus_1_div_sigma_Ls=(sigma-1.0)/sigma_Ls;
	inv_sigma_Ls=1.0/sigma_Ls;
	inv_Ls_plus_sigma_Ls=1.0/(sigma_Ls+Ls);
	sigma_Ls_div_1_plus_sigma=sigma_Ls/(1.0+sigma);
	Lm_div_Lr=Lm/Lr;
	Lr_div_Lm=Lr/Lm;
	return	0;	
}	

int COMMON_SL_VECT_CNTL_ParameterVerification()
{
	int ErrCode;

	ErrCode=COMMON_VECT_CNTL_ParameterVerification();	
	if (ErrCode!=0)				return	ErrCode;		
		
	Fs_B=Base_Flux_Coeff*Fs_rat;
	inv_Fs_B=1.0/Fs_B;	
	Fs_ref=Fs_B;	

	I_QS_rat=(2.0/3.0)*inv_P_pair*Te_rat/Fs_B;
//	inv_I_QS_rat=1.0/I_QS_rat;
	inv_Te_rat=1.0/Te_rat;
	
	wr_FilterPole=Default_wr_FilterPole;				//
	wn_wr=wr_FilterPole/10.0;							//
	if (wn_wr>Max_wn_wr)	wn_wr=Max_wn_wr;			//

	return	0;	
}	

int SL_TORQUE_CNTL_Parameter()
{
	int ErrCode;
	
	ErrCode=COMMON_SL_VECT_CNTL_ParameterVerification();
	if (ErrCode!=0)
		return	ErrCode;
	
	wr_FilterPole=Default_wr_FilterPole;
	
	return	0;
}

int SL_SPEED_CNTL_Parameter()	
{
	int ErrCode;
	ErrCode=COMMON_SL_VECT_CNTL_ParameterVerification();
	if (ErrCode!=0) 	return	ErrCode;

	I_QS_rat=(2.0/3.0)*inv_P_pair*Te_rat/Fs_rat;
	inv_Te_rat=1.0/Te_rat;
	
	wn_wr=wn_wr_Coeff*( (P_pair*Te_rat/wr_rat)/Jm );
	if (wn_wr>Max_wn_wr)	wn_wr=Max_wn_wr;

	wr_FilterPole=wr_FilterPoleCoeff*wn_wr;
	Kp_wr=(Jm*2.0*wr_DampingRatio*wn_wr)*(inv_Kt/Fs_B);
	Ki_wr=(Jm*wn_wr*wn_wr)*(inv_Kt/Fs_B);
	return	0;
}
