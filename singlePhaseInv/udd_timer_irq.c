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
//	CpuTimer0.InterruptCount++;

	Nop();
	ServiceDog();

	INIT_CHARGE_CLEAR;
	if(timer0_count > 4)		timer0_count = 4;
	else if(timer0_count > 1 ) 	timer0_count--;
	else{						timer0_count = 4;
		CpuTimer0.InterruptCount++;
		if( ref_time < 1.0e+30) ref_time += 0.001;
		if( gfRunTime < 1.0e+30 ) gfRunTime += 0.001;		

		if((gMachineState == STATE_POWER_ON )&&(init_charge_flag == 1)){
			INIT_CHARGE_SET;
		}
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
