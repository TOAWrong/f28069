#include	<header.h>
#include	<extern.h>

void fault_reset()
{
	Nop();
	asm (" .ref _c_int00"); // ;Branch to start of boot.asm in RTS library
	asm (" LB _c_int00"); // ;Branch to start of boot.asm in RTS library
}

void driver_enable_proc(){	Nop();}
void input_ai_ref_active_proc(){	Nop();}
void input_ai_local_remote_proc(){	Nop();}
void input_ext_fault_b_proc(){	Nop();}
void input_motor_select_proc(){	Nop();}
void input_mb_brake_state_proc(){	Nop(); }
void input_acel_decel_switch_proc(){	Nop();}
void input_ref_tunning_inc_proc(){	Nop();}
void input_ref_tunning_dec_proc(){	Nop();}
void input_acc_dec_byp_proc(){	Nop();}

void input_ext_fault_a_proc()
{
	trip_recording( TRIP_EXT_A, gfRunTime,"TRIP EXT A: RT "); //TRIP EXT A: runtime save
	gPWMTripCode = TRIP_EXT_A;
}

void digital_input_proc(int * cmd, double * ref )
{
	if( RUN_INPUT == 0 ){
	 	* cmd = CMD_START; //FWD LOW
		* ref = 1.0;
	}
	else { * cmd = CMD_STOP; * ref = 0.0;}
}

//=====================
// Digital Out Proc
//======================

int digital_port_check( int out_function )
{
	int i;

	i = 0;
	if	   ( ( relay_flag.bit.DRIVE_READY )	&&( out_function == 1 )) i =1;
	else if( ( relay_flag.bit.FAULT_OUT_A ) &&( out_function == 2 )) i =1;
	else if( ( relay_flag.bit.FAULT_OUT_B ) &&( out_function == 3 )) i =1;
	else if( ( relay_flag.bit.MOTOR_BRAKE ) &&( out_function == 4 )) i =1;
	else if( ( relay_flag.bit.RUN_STOP) 	&&( out_function == 5 )) i =1;
	else if( ( relay_flag.bit.WARNING) 		&&( out_function == 6 )) i =1;
	else if( ( relay_flag.bit.DIRECTION) 	&&( out_function == 7 )) i =1;
	else if( ( relay_flag.bit.JOG_INPUT) 	&&( out_function == 8 )) i =1;
	else if( ( relay_flag.bit.VC_LIMIT) 	&&( out_function == 9 )) i =1;
	else if( ( relay_flag.bit.FREE) 		&&( out_function == 10)) i =1;
	else															 i = 0;
	
	return i;
}  	

void digital_out_proc()		// debug
{
    switch(gMachineState)
    {
    case STATE_TRIP:
		MAIN_CHARGE_OFF;		// ���� ���� on 
		RUN_OUT_OFF;
		TRIP_OUT_ON;
		break;

    case STATE_POWER_ON:
        MAIN_CHARGE_OFF;        // ���� ���� on
        RUN_OUT_OFF;
        TRIP_OUT_OFF;
        break;

    case STATE_READY:
        MAIN_CHARGE_ON;     //
        RUN_OUT_OFF;
        TRIP_OUT_OFF;
        break;

    case STATE_INIT_RUN:
    case STATE_RUN:
    case STATE_GO_STOP:
    case STATE_WAIT_BREAK_OFF:
		MAIN_CHARGE_ON;		//
		RUN_OUT_ON;
		TRIP_OUT_OFF;
        break;
    default:
        MAIN_CHARGE_OFF;     //
        RUN_OUT_OFF;
        TRIP_OUT_OFF;
        break;
    }
}
//---------------------------------
// end of file
//----------------------------------
