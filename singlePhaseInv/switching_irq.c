// Company 	: Eunwho Power Electonics  
// FILE		: switching_irq.c
// Project 	: KERI back2back inverter
// PCB		: regen_dsp_110513 & regen_sen_110513
// date		: 2011-0105	by Cheoung Soon-Gil
// rev data : 2011.1013  cheoung soon gil

#include        <header.h>
#include        <extern.h>

int dacCount = 0;

interrupt void MainPWM(void)
{
	static int invt_PWM_Port_Set_flag = 0;
	float modulationRatio;

#if TEST_ADC_CENTER
	J8_2_SET;
#endif

	switch(gMachineState)
	{
    case STATE_TRIP:
        invt_PWM_Port_Set_flag = 0;
//      ePwmPortOff(); // converter PWM gate OFF
        break;

    case STATE_READY:
	case STATE_POWER_ON:
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
		break;

	case STATE_INIT_RUN:
		if( invt_PWM_Port_Set_flag == 0 ){
			ePwmEnable();
			invt_PWM_Port_Set_flag = 1;
		}
		else{
			EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
			EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
			EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
		}
		break;

	case STATE_RUN:
	case STATE_GO_STOP:
	case STATE_WAIT_BREAK_OFF:		

	    we = codeRateHz * reference_out;
	    theta += we * Ts;
        while (theta >= PI_2 ){ theta -= PI_2;}
        if (theta < 0.0 ) theta = 0.0;

        modulationRatio = reference_out;
        singlePhaseModulation(modulationRatio, theta, DutyRatio);

        DutyCount[0] = MAX_PWM_CNT * DutyRatio[0];
        DutyCount[1] = MAX_PWM_CNT * DutyRatio[1];
        DutyCount[2] = MAX_PWM_CNT * DutyRatio[2];

        EPwm1Regs.CMPA.half.CMPA = DutyCount[0];
        EPwm2Regs.CMPA.half.CMPA = DutyCount[1];
        EPwm3Regs.CMPA.half.CMPA = DutyCount[2];
        break;

	default: 
		invt_PWM_Port_Set_flag = 0;
		ePwmPortOff(); // converter PWM gate OFF
		break;
	}

	digital_out_proc();
//---
    if( !sendAdcDataFlag ){
        if(graphCount<GRAPH_NUMBER){
            adcData[0][graphCount].INTEGER = adc_result[0];
            adcData[1][graphCount].INTEGER = adc_result[1];
            adcData[2][graphCount].INTEGER = adc_result[2];
            adcData[3][graphCount].INTEGER = adc_result[3];
            graphCount ++;
        }
        else graphCount = 0;
    }

    EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

#if TEST_ADC_CENTER
	J8_2_CLEAR;	// debug
#endif

}

 // end of switching_irq.c 

