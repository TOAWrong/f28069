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

    ServiceDog();
    CpuTimer0.InterruptCount++;

    if( ref_time < 1.0e+30) ref_time += 0.001;
    if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
