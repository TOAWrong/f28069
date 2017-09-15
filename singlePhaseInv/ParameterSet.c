#include	<header.h>
#include	<extern.h>

void VariInit()
{
	float x1,x2,y1,y2;
// for Vdc calc 

    code_adc_vdc_low    = 100;
    code_Vdc_calc_low   = 10;
    code_adc_vdc_high   = 2500;
    code_Vdc_calc_high  = 300;

	x1 = code_adc_vdc_low;		y1 = code_Vdc_calc_low;
	x2 = code_adc_vdc_high;		y2 = code_Vdc_calc_high;
	Vdc_factor = ( y2-y1) / ( x2 - x1 );
	Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

	C_ce_nF=(3.5-0.8)/(1000.0-100.0)*(2.0*Is_rat-100.0)+0.8;

	C_ce=1.0e-9*C_ce_nF;
	inv_C_ce=1.0/C_ce;

	//
	gfRunTime=0.0;

	// reference
	reference_in=0.0;
	reference_out=0.0;	// new
	
	//
	frequency=0.0;
	theta=0.0;

	we_in=0.0;
	we=0.0;
	rpm=0.0;
	rpm_ref=0.0;

	Vs_max=0.0;	
	//
	Te_max=0.0;
	Te_ref=0.0;
	Te=0.0;
	LPF_Te=0.0;
	
	// VVVF-Control
	Vs_ref=0.0;
	Freq_ref=0.0;
	Freq_slip=0.0;
	Freq_out=0.0;
	Slip=0.0;
	Power_core=0.0;
	Power_core_rat=0.0;
	Power_gap=0.0;
	Vs_IR_comp=0.0;
	del_Vs_comp=0.0;
}	

int HardwareParameterVerification()
{
    if ( codeRatePower >(0.99*sqrt(3.0) * codeRateVolt * codeRateCurrent)){
        trip_recording( CODE_rate_power, codeRatePower,"PW FACTOR OVER"); // POWER FACTOR OVER
        return  CODE_rate_power;
    }
    //
    if (codeRatePower<(0.2*sqrt(3.0)*codeRateVolt * codeRateCurrent)){
        trip_recording( CODE_rate_power, codeRatePower,"PW FACTOR UNDER"); // POWER FACTOR UNDER
        return  CODE_rate_power;
    }
    //
    if ( codeRateRpm < (0.85*120.0 * codeRateHz / codeMotorPole)){
        trip_recording( CODE_rate_rpm, codeRateRpm,"RATE RPM UNDER");
        return  CODE_rate_rpm;
    }
    return  0;
}

//-----------------------------------
//  End of ParameterSect.c
//-----------------------------------

