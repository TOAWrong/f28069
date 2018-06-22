//
// analog.c
// 2012.04.12
// Eunwho Power Electronics
// by Cheoung Soon Gil
// revision :
#include	<header.h>
#include	<extern.h>


// included in F2806x_Adc.c
// InitAdc();
// AdcOffsetSelfCal();

void ADC_SOC_CNF( )
{

    extern void DSP28x_usDelay(Uint32 Count);

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1; // Enable non-overlap mode
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;        // enable ADC interrupt 1
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0; // set ADCInterrupt 1 to auto clr

    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;      // IntChSel causes ADCInterrupt 1

    AdcRegs.ADCSOC0CTL.bit.CHSEL= 0;        // I_u
    AdcRegs.ADCSOC1CTL.bit.CHSEL= 1;        // I_v
    AdcRegs.ADCSOC2CTL.bit.CHSEL= 8;        // Vdc
    AdcRegs.ADCSOC3CTL.bit.CHSEL= 9;        // IGBT_Temp
    AdcRegs.ADCSOC4CTL.bit.CHSEL= 3;        // Ex_sensor
    AdcRegs.ADCSOC5CTL.bit.CHSEL= 5;        // Ex_sensor

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 5;

    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC2CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC3CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC4CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC5CTL.bit.ACQPS = 6;
//    AdcRegs.ADCSAMPLEMODE.all = 0;      // Simultaneous sample mode
    EDIS;
}

// 3.3Volt --> 4096 1 Volt --> 1/3.3 * 4096 = 1241.2
#define I_RATIO   0.004          //
interrupt void adcIsr(void)
{
    DIGIT1_SET;

    adc_result[0] = adcIa   = AdcResult.ADCRESULT0;
    adc_result[1] = adcIb   = AdcResult.ADCRESULT1;
    adc_result[2] = adcVdc  = AdcResult.ADCRESULT2;
    adc_result[3] = adcIgbtTemperature = AdcResult.ADCRESULT3;
    adc_result[4] = adcExSensor = AdcResult.ADCRESULT4;
    adc_result[5] = adcCmdAnalog = AdcResult.ADCRESULT5;

    sensVdc = Vdc_factor * adcVdc + Vdc_calc_offset;
    lpfVdcIn[0] = sensVdc;
    lpf2nd( lpfVdcIn, lpfVdcOut, lpfVdcK);
    Vdc = (codeSetVdc > 0.5 ) ? 300.0 : lpfVdcOut[0];

    lpfIaIn[0] = (double)adcIa;
    lpf2nd( lpfIaIn, lpfIaOut, lpfIrmsK);
    lpfadcIa = (int)(lpfIaOut[0]);

    lpfIbIn[0] = (double)(adcIb);
    lpf2nd( lpfIbIn, lpfIbOut, lpfIrmsK);
    lpfadcIb = (int)(lpfIbOut[0]);

    Is_abc[as] = I_sense_value * ( lpfadcIa - codeIaOffset) * I_RATIO;
    Is_abc[bs] = I_sense_value * ( lpfadcIb - codeIbOffset ) * I_RATIO;
    LPF1(Ts,1.0,fabs(Is_abc[as]),&LPF_Ia);          // debug

    Is_abc[cs]= -(Is_abc[as]+Is_abc[bs]);
    Is_dq[ds] = Is_abc[as];
    Is_dq[qs] = 0.577350 * Is_abc[as] + 1.15470 * Is_abc[bs];
    Is_mag = sqrt( Is_abc[as] *Is_abc[as] + Is_abc[bs] *Is_abc[bs]);           // 전류크기
    Is_mag_rms = 0.707106*Is_mag;

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

    DIGIT1_CLEAR;
    return;
}

void analog_out_proc( )
{
}

int check_sensor_trip()
{
	int TripCode;

	Nop();

	if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;	// debug
	if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;	// ���������� ������ �Ѵ�. 
	return 0;
}
	
// end of file

