// FILE		: switching_irq.c
// Company  : Eunwho Power Electonics
// date		: 2018.0608	by soonkil jung

#include        <header.h>
#include        <extern.h>

int dacCount = 0;

void MotorControlProc( )
{
    int temp;

    temp = (int)(floor(codeMotorCtrlMode+0.5));
    switch( temp )
    {
    case 0: vf_simple_control(); break;
    case 1: slip_comp_scalar_ctrl();break;
    case 3: SL_SpeedCntl_SFRF( );   break;
    case 4: SL_TorqueCntl_SFRF( );  break;
    case 5:
        switch(AutoTuningFlag)
        {
        case 0: Vs_dq_ref[ds] = 0.0; Vs_dq_ref[qs] = 0.0; break;
        case ID_AT_LEQ_REQ: estim_ReqLeq_pwm ( );   break;
        case ID_AT_RS:  estim_Rs_pwm( );            break;
        case ID_AT_LS:  estim_Ls_pwm( );            break;
        case ID_AT_JM:  estim_Jm_pwm( );            break;
        default:    Vs_dq_ref[ds] = 0.0; Vs_dq_ref[qs] = 0.0; break;
        }
        break;
    }
}


interrupt void MainPWM(void)
{
    DIGIT2_SET;
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
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        goto _PWM_TRIP;
    }

    switch(gMachineState)
    {
    case STATE_READY:
    case STATE_POWER_ON:
    case STATE_TRIP:
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        break;

    case STATE_INIT_RUN:
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        break;

    case STATE_RUN:
    case STATE_GO_STOP:
    case STATE_WAIT_BREAK_OFF:
        if(gPWMTripCode !=0){
            gTripSaveFlag = 1; // for Trip History Save to EEPROM in Out irq
            EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
            EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
            EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        } else{
            VoltageEstimation();
            MotorControlProc( );
            SpaceVectorModulation(Vs_dq_ref);
            EPwm3Regs.CMPA.half.CMPA = DutyCount[u];
            EPwm2Regs.CMPA.half.CMPA = DutyCount[v];
            EPwm1Regs.CMPA.half.CMPA = DutyCount[w];
        }
        break;

    default:
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        break;
    }

_PWM_TRIP:
    digital_out_proc();
//---
    if( !sendAdcDataFlag ){
        if(graphCount< GRAPH_NUMBER ){
            adcData[0][graphCount].INTEGER = adc_result[0];
            adcData[1][graphCount].INTEGER = adc_result[1];
            adcData[2][graphCount].INTEGER = lpfadcIa;
            adcData[3][graphCount].INTEGER = lpfadcIb;
//          adcData[0][graphCount].INTEGER = adc_result[0];
//          adcData[1][graphCount].INTEGER = (int)(4095 * DutyRatio[0]);
//          adcData[2][graphCount].INTEGER = (int)(4095 * DutyRatio[1]);
//          adcData[3][graphCount].INTEGER = (int)(4095 * DutyRatio[2]);
            graphCount ++;
        }
        else graphCount = 0;
    }
    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    DIGIT2_CLEAR;
}

 // end of switching_irq.c 

