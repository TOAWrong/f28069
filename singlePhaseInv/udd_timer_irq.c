/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Inverter for 
//	Fiele Name	 	: Timer_Irq_Proc.c
//
//  Start 			: 2009.07.09 sunday
//
///////////////////////////////////////////////////////////////////////////
#include	<header.h>
#include	<extern.h>

interrupt void cpu_timer0_isr(void)
{
    static int timerCount=0;
    static int dacCount=0;

    ServiceDog();
    CpuTimer0.InterruptCount++;

    if( ref_time < 1.0e+30) ref_time += 0.001;
    if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;

    timerCount++;
    if(timerCount > 100){
        timerCount = 0 ;
        if(dacCount<300){
            //       y1_data[dacCount] = DutyRatio[u];
             //       y2_data[dacCount] = DutyRatio[v];
            y1_data[dacCount] = reference_in;
            y2_data[dacCount] = reference_out;
            dacCount ++;
        }
        else dacCount = 0;
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
