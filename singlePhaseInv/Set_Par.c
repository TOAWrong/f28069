#include	<header.h>
#include	<extern.h>

int HardwareParameterVerification()
{
	if ( codeMotorRatePower >(0.99*sqrt(3.0) * codeMotorRateVolt * codeMotorRateCurrent)){
		trip_recording( CODE_motor_rate_power, codeMotorRatePower,"PW FACTOR OVER"); // POWER FACTOR OVER
		return	CODE_motor_rate_power;
	}	
	//
	if (codeMotorRatePower<(0.2*sqrt(3.0)*codeMotorRateVolt * codeMotorRateCurrent)){
		trip_recording( CODE_motor_rate_power, codeMotorRatePower,"PW FACTOR UNDER"); // POWER FACTOR UNDER
		return	CODE_motor_rate_power;
	}
	//
	if ( codeMotorRateRpm < (0.85*120.0 * codeMotorRateHz / codeMotorPole)){
		trip_recording( CODE_motor_rate_rpm, codeMotorRateRpm,"RATE RPM UNDER");
		return	CODE_motor_rate_rpm;
	}
	return	0;	
}	
// end of Set_Par.c
	
