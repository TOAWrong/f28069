#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	

#define SWITCH_FREQ			8000

#define TYPE_INTEGER		0
#define TYPE_float			1

//======================================
// Code address
//======================================
#define CODE_motor_direction_change		1
#define CODE_accel_time1				2
#define CODE_decel_time1				3
#define CODE_motor_ctrl_mode            4
#define CODE_speed1						5
#define CODE_speed2						6
#define CODE_protect_inhibit_on         7

#define CODE_motor_rate_power			10
#define CODE_motor_rate_volt			11
#define CODE_motor_rate_current			12
#define CODE_motor_rate_hz				13
#define CODE_motor_rate_rpm				14
#define CODE_motor_pole					15
#define CODE_motor_rate_effiency		16
#define CODE_END                        17

#define CODE_Data_Check						800
#define CODE_Data_Backup					801
#define CODE_Data_Load						802
#define CODE_Data_Init						803
#define CODE_get_adc_offset					804

#define CODE_get_adc_vdc_low				805
#define CODE_get_adc_vdc_high				806

//--- end of code address

struct CODE_INFO_DEFINE {
	int		type;	
	int	  	open_level	;
	float	code_min ;
	float   code_max ;
	float   code_default;
	float   code_value;
	char   disp[40];
};
typedef struct CODE_INFO_DEFINE CODE_INFO;

#endif
