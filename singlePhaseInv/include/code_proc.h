#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	

#define SWITCH_FREQ			8000

#define TYPE_INTEGER		0
#define TYPE_DOUBLE			1

//======================================
// Code address
//======================================
// group 0

#define CODE_motor_direction_change		2

#define CODE_accel_time1				10
#define CODE_decel_time1				11
#define CODE_motor_ctrl_mode            1

#define CODE_protect_inhibit_on			30

#define CODE_speed1						101
#define CODE_speed2						102

#define CODE_motor_rate_power			400
#define CODE_motor_rate_volt			401
#define CODE_motor_rate_current			402
#define CODE_motor_rate_hz				403
#define CODE_motor_rate_rpm				404
#define CODE_motor_pole					405
#define CODE_motor_rate_effiency		406	

#define CODE_Rs							407
#define CODE_Rr							408
#define CODE_Ls							409
#define CODE_Lr							410
#define CODE_Lm							411
#define CODE_Jm							412


#define CODE_Data_Check						800
#define CODE_Data_Backup					801
#define CODE_Data_Load						802
#define CODE_Data_Init						803
#define CODE_get_adc_offset					804

#define CODE_get_adc_vdc_low				805
#define CODE_get_adc_vdc_high				806

//--- end of code address


union CODE_MIN{
	int 	ints;
	double 	doubles;
};

union CODE_MAX {
	int 	ints;
	double 	doubles;
};

union CODE_DEFAULT {
	int 	ints;
	double 	doubles;
};

union CODE_VALUE {
	int 	ints;
	double 	doubles;
};

struct CODE_INFO_DEFINE {
	int		type;	
	int	  	open_level	;
	union CODE_MIN 		code_min ;
	union CODE_MAX 		code_max ;
	union CODE_DEFAULT 	code_default;
	union CODE_VALUE	code_value;
	char   disp[40];
};
typedef struct CODE_INFO_DEFINE CODE_INFO;

#endif
