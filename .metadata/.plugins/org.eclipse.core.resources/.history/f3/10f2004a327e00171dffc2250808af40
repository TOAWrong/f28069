// EwInv File $Revision: /main/2 $
// Checkin $Date: May 13, 2008   21:50:** $
//###########################################################################
//
// FILE:	io_define.h
//
// Project:	EwInv F28335  _080413
// TITLE:	s.

#ifndef		__DIGITAL_INOUT_H_
#define		__DIGITAL_INOUT_H_
     // Set Output High

#define J8_1_SET			(GpioDataRegs.GPASET.bit.GPIO15 = 1) 
#define J8_1_CLEAR			(GpioDataRegs.GPACLEAR.bit.GPIO15 = 1) 

#define J8_2_SET			(GpioDataRegs.GPASET.bit.GPIO16 = 1) 
#define J8_2_CLEAR			(GpioDataRegs.GPACLEAR.bit.GPIO16 = 1) 

#define digital_out0_on()	(GpioDataRegs.GPBSET.bit.GPIO60 = 1)	// 
#define digital_out0_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1)	// 

#define digital_out1_on()	(GpioDataRegs.GPBSET.bit.GPIO61 = 1)	// run/stop
#define digital_out1_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1)	//

#define TRIP_OUT_ON		(digital_out1_on())
#define TRIP_OUT_OFF	(digital_out1_off())

#define RUN_OUT_ON		(digital_out0_on())
#define RUN_OUT_OFF		(digital_out0_off())

#define MAIN_CHARGE_OFF		(GpioDataRegs.GPACLEAR.bit.GPIO14 = 1)
#define MAIN_CHARGE_ON		(GpioDataRegs.GPASET.bit.GPIO14   = 1)

// out put 확장을 위하여 남겨 놓음  

#define digital_out3_on()	Nop()	// GPIO.1
#define digital_out3_off()	Nop()	// GPIO.1

#define digital_out4_on()	Nop()	// GPIO.2
#define digital_out4_off()	Nop()	// GPIO.2

#define digital_out5_on()	Nop()	// GPIO.3
#define digital_out5_off()	Nop()	// GPIO.3

#define digital_out6_on()	Nop()	// GPIO.4
#define digital_out6_off()	Nop()	// GPIO.4

#define digital_out7_on()	Nop()	// GPIO.5
#define digital_out7_off()	Nop()	// GPIO.5

struct DIGIT_FUNCTION_BITS {      
	Uint16 DRIVE_ENABLE:1;      // 
	Uint16 MULTI_STEP_BIT0:1;	// 
	Uint16 MULTI_STEP_BIT1:1;	// 
	Uint16 MULTI_STEP_BIT2:1;	// 
	Uint16 MULTI_STEP_BIT3:1;	// 
	Uint16 FAULT_RESET:1;		// 
	Uint16 JOG:1;				//
	Uint16 AI_REF_ACTIVE:1;		//
	Uint16 AI_LOCAL_REMOTE:1;	//
	Uint16 EXT_FAULT_A:1;		//
	Uint16 EXT_FAULT_B:1;		//
	Uint16 MOTOR_SELECT:1;		//
	Uint16 MB_BRAKE_STATE:1;	//
	Uint16 ACCEL_DECEL_SWITCH:1;	//
	Uint16 REF_TUNING_INC:1;	//
	Uint16 REF_TUNING_DEC:1;	//
	Uint16 ACC_DEC_BYP:1;		//
	Uint16 PID_CNTL_ENABLE:1;	//
	Uint16 AUTO_PID_MODE:1;		//
	Uint16 PID_GAIN_SEL:1;		//
	Uint16 PID_I_RESET:1;		//
	Uint16 TRQ_REF_OPT_BYP:1;	//
	Uint16 TRQ_SIGN:1;			//
	Uint16 TRQ_OUT_ZERO:1;		//
	Uint16 TIMER_RUN_ENABLE:1;	//
	Uint16 SLAVE_RUN_STATUS:1;	//
	Uint16 SYNC_CTRL_OPT_BPY:1;	//
	Uint16 FLYING_START:1;		//
	Uint16 DISABLE_PROFIBUS:1;	//
	Uint16 INVERT_DIR:1;		//
	Uint16 INVERT_RUN:1;		//
};

struct DIGITAL_OUT_BITS{
	Uint16 DRIVE_READY:1;	// driver ready
	Uint16 FAULT_OUT_A:1;
	Uint16 FAULT_OUT_B:1;
	Uint16 MOTOR_BRAKE:1;
	Uint16 RUN_STOP:1;
	Uint16 WARNING:1;
	Uint16 DIRECTION:1;
	Uint16 JOG_INPUT:1;
	Uint16 VC_LIMIT:1;
	Uint16 FREE:1;
};

union DIGITAL_OUT_FUNC{
	Uint16	all;
	struct DIGITAL_OUT_BITS bit;
};

union DIGITAL_FUNCTION
{
   Uint32               	  all;
   struct DIGIT_FUNCTION_BITS  bit;
} ;

//----------------------------------------
//Input Define
//----------------------------------------

#define PWM_FAULT 		(GpioDataRegs.GPADAT.bit.GPIO12)
#define DB_FAULT		(GpioDataRegs.GPADAT.bit.GPIO17)

//----------------------------------------
// Output Define
//----------------------------------------
#define RESET_DRIVER_SET	(GpioDataRegs.GPASET.bit.GPIO12 = 1)  
#define RESET_DRIVER_CLEAR	(GpioDataRegs.GPACLEAR.bit.GPIO12= 1)  

#define BACKUP_ENABLE		(GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1)
#define BACKUP_DISABLE		(GpioDataRegs.GPBSET.bit.GPIO48   = 1)

#define EX_OUT_RELAY0_CLEAR	(GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1)	// EX-OUT-RELAY0
#define EX_OUT_RELAY0_SET	(GpioDataRegs.GPBSET.bit.GPIO60   = 1)

#define EX_OUT_RELAY1_CLEAR	(GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1)	// EX-OUT-RELAY0
#define EX_OUT_RELAY1_SET	(GpioDataRegs.GPBSET.bit.GPIO61   = 1)

#define INVERTER_RUN_CLEAR	(GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1)	// EX-OUT-RELAY1
#define INVERTER_RUN_SET	(GpioDataRegs.GPBSET.bit.GPIO59   = 1)

// 2011.06.25
#define INIT_CHARGE_CLEAR	(GpioDataRegs.GPACLEAR.bit.GPIO13 = 1)
#define INIT_CHARGE_SET		(GpioDataRegs.GPASET.bit.GPIO13   = 1)

#endif
//===================================================================
// No more.
//===================================================================
