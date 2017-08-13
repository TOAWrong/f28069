#include	<header.h>
#include	<extern.h>

int HardwareParameterVerification()
{
	if ( motor_rate_power >(0.99*sqrt(3.0) * motor_rate_volt * motor_rate_current)){
		trip_recording( CODE_motor_rate_power, motor_rate_power,"PW FACTOR OVER"); // POWER FACTOR OVER
		return	CODE_motor_rate_power;
	}	
	// 역률이 20%이하로 설정되었을 경우 
	if (motor_rate_power<(0.2*sqrt(3.0)*motor_rate_volt*motor_rate_current)){
		trip_recording( CODE_motor_rate_power, motor_rate_power,"PW FACTOR UNDER"); // POWER FACTOR UNDER
		return	CODE_motor_rate_power;
	}
	// 정격 슬립이 15%이상으로 설정된 경우 : 대체로 2% 
	if (motor_rate_rpm < (0.85*120.0 * motor_rate_hz / motor_pole)){
		trip_recording( CODE_motor_rate_rpm, motor_rate_rpm,"RATE RPM UNDER");
		return	CODE_motor_rate_rpm;
	}

	Vs_rat=sqrt(2.0)/sqrt(3.0)*motor_rate_volt;			// 상전압의 피크 값

	Is_rat=sqrt(2.0)*motor_rate_current;

	inv_Is_rat=1.0/Is_rat;
	Freq_rat = motor_rate_hz;

	we_rat= PI_2 * Freq_rat;
	inv_Freq_rat=1.0/Freq_rat;

	inv_motor_rate_hz = 1.0 / motor_rate_hz; //   csk_check 2009.10.30.
	wr_rat=PI_2*motor_pole*motor_rate_rpm/120.0;			// rpm -> rad/sec
	wm_rat=wr_rat*(2.0/motor_pole);
	Te_rat=motor_rate_power/wm_rat;

	inv_Te_rat=1.0/Te_rat;
	Fs_rat=Vs_rat/we_rat;

	Kt=(3.0/2.0)*(motor_pole/2.0);
	inv_Kt=1.0/Kt;
	P_pair=(motor_pole/2.0);
	inv_P_pair=1.0/P_pair;
	rpm_Coeff=60.0*inv_P_pair/PI_2;				// 회전수/분
	
	// V/F 제에의 슬립 보상
	S_rat=(we_rat-wr_rat)/we_rat;
	S_lin=(motor_pole/PI)*(S_rat*Freq_rat)/Te_rat;				// ==> V/f 제어 : 슬립 보상
	Freq_slip_rat=S_rat*Freq_rat;

	//-------------------------------------------------
	inv_Ts = igbt_pwm_freq;
	Ts = 1.0 / igbt_pwm_freq;	// debug

	Is_max = Is_rat * Is_Max_Coeff ;	// added 2009.11.01	
	OverCurLimit = Is_max * 2.0;			// added 2009.11.01  _debug

	return	0;	
}	
// end of Set_Par.c
	
