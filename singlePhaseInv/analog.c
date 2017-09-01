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

__interrupt void adcIsr(void)
{
    GpioDataRegs.GPASET.bit.GPIO7 = 1;
//    GpioDataRegs.GPATOGGLE.bit.GPIO7 = 1;  // CON1.8 GATE_ENABLE

    adcIuPhase = AdcResult.ADCRESULT0;
    adcIvPhase = AdcResult.ADCRESULT1;
    adcVdc       = AdcResult.ADCRESULT2;
    adcIgbtTemperature = AdcResult.ADCRESULT3;
    adcExSensor = AdcResult.ADCRESULT4;
    adcCmdAnalog = AdcResult.ADCRESULT5;


    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

    GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
    return;
}

void analog_input_proc( float * referenc)
{
	* referenc = analog_ref_a * analog_cmd_in_span1 - analog_cmd_in_zero1;
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

