// FILE		: switching_irq.c
// Project 	: KERI back2back inverter
// PCB		: regen_dsp_110513 & regen_sen_110513
// Company  : Eunwho Power Electonics
// date		: 2018.0608	by soonkil jung

#include        <header.h>
#include        <extern.h>

int dacCount = 0;
void MotorControlProc( )
{
 //   if      (codeMotorCtrlMode < 1.0 ) vf_simple_control();
 //   else if (codeMotorCtrlMode < 2.0 ) slip_comp_scalar_ctrl();
 //   else
    vf_simple_control();
}

interrupt void MainPWM(void)
{
    static int monitorCount = 0;

    if( gMachineState == STATE_RUN )
    {
        if( Vdc > ( over_volt_set - 30.0 ))
            EPwm4Regs.CMPA.half.CMPA = MAX_PWM_CNT >> 2 ;
        else
            EPwm4Regs.CMPA.half.CMPA = MAX_PWM_CNT;
    }
    else
        EPwm4Regs.CMPA.half.CMPA = MAX_PWM_CNT;

    if(gPWMTripCode){
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        goto _PWM_TRIP;
    }

    switch(gMachineState)
    {
    case STATE_READY:
    case STATE_POWER_ON:
    case STATE_TRIP:
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        break;

    case STATE_INIT_RUN:
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        break;

    case STATE_RUN:
    case STATE_GO_STOP:
    case STATE_WAIT_BREAK_OFF:
        if(gPWMTripCode !=0){
            gTripSaveFlag = 1; // for Trip History Save to EEPROM in Out irq
            EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
            EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
            EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        }
        else{
            // VoltageEstimation();
            MotorControlProc( );
            SpaceVectorModulation(Vs_dq_ref);
            EPwm1Regs.CMPA.half.CMPA = DutyCount[u];
            EPwm2Regs.CMPA.half.CMPA = DutyCount[v];
            EPwm3Regs.CMPA.half.CMPA = DutyCount[w];
        }
        break;

    default:
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        break;
    }

_PWM_TRIP:
    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    digital_out_proc();
//---
    if( !sendAdcDataFlag ){
        if( monitorCount < 4 ) monitorCount ++ ;
        else {
            monitorCount = 0;
            if(graphCount< GRAPH_NUMBER ){
    //            adcData[0][graphCount].INTEGER = adc_result[0];
    //            adcData[1][graphCount].INTEGER = adc_result[1];
    //            adcData[2][graphCount].INTEGER = adc_result[2];
    //            adcData[3][graphCount].INTEGER = adc_result[3];

                adcData[0][graphCount].INTEGER = adc_result[0];
                adcData[1][graphCount].INTEGER = (int)(4095 * DutyRatio[0]);
                adcData[2][graphCount].INTEGER = (int)(4095 * DutyRatio[1]);
                adcData[3][graphCount].INTEGER = (int)(4095 * DutyRatio[2]);
                graphCount ++;
            }
            else graphCount = 0;
        }
    }
    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

#if TEST_ADC_CENTER
    J8_2_CLEAR; // debug
#endif
}

 // end of switching_irq.c 

