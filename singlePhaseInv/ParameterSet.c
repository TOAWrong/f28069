#include	<header.h>
#include	<extern.h>

void VariInit()
{
	double x1,x2,y1,y2;
// for Vdc calc 
	x1 = code_adc_vdc_low;		y1 = code_Vdc_calc_low;
	x2 = code_adc_vdc_high;		y2 = code_Vdc_calc_high;
	Vdc_factor = ( y2-y1) / ( x2 - x1 );
	Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

	C_ce_nF=(3.5-0.8)/(1000.0-100.0)*(2.0*Is_rat-100.0)+0.8;

	C_ce=1.0e-9*C_ce_nF;
	inv_C_ce=1.0/C_ce;

	// 시간 및 인덱스
	gfRunTime=0.0;

	// reference
	reference0=0.0;
	reference1=0.0;
	reference_in=0.0;
	reference_out=0.0;	// new
	
	// 각도, 주파수, 속도
	frequency=0.0;
	theta=0.0;
	SinTheta=0.0;
	CosTheta=1.0;

	we_in=0.0;
	we=0.0;
	we0=0.0;

	rpm=0.0;
	rpm_ref=0.0;
	
	// 전류
	RMS_Ia = 0.0;
	RMS_Ib = 0.0;

	Is_dq[ds]=Is_dq[qs]=0.0;
	Is_mag=0.0;
	Is_mag_rms=0.0;
	
	Is_DQ[DS]=Is_DQ[QS]=0.0;
	

	// 전압
	Vs_max=0.0;	

	// 토크
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

	inv_Jm = 1.0 / Jm;		

}	

//-----------------------------------
//  End of ParameterSect.c
//-----------------------------------

