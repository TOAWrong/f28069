#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	


#define TYPE_INTEGER		0
#define TYPE_float			1

//======================================
// Code address
//======================================
#define CODE_motor_direction_change		1
#define CODE_accel_time1				2
#define CODE_decel_time1				3
#define CODE_MotorCtrMode               4
#define CODE_speed1						5
#define CODE_speed2						6
#define CODE_set_vdc                    7
#define CODE_protect_off                8
#define CODE_pwm_freq                   9

#define CODE_rate_power			        10
#define CODE_rate_current               11
#define CODE_rate_rpm                   12
#define CODE_rate_effiency              13
#define CODE_rate_hz				    14
#define CODE_rate_volt                  15
#define CODE_motor_pole					16

#define CODE_IaOffset                   20
#define CODE_IbOffset                   21

#define CODE_I_sense_value              22
#define CODE_u_phase_I_sense_span       23
#define CODE_v_phase_I_sense_span       24
#define CODE_vdc_sense_zero             25
#define CODE_vdc_sense_span             26

#define CODE_Rs                         30
#define CODE_Rr                         31
#define CODE_Ls                         32
#define CODE_Lr                         33
#define CODE_Lm                         34
#define CODE_Jm                         35

#define CODE_VF_DeadTimeGain            40
#define CODE_VF_ExcitationTime          41
#define CODE_VF_Fs_Coeff                42
#define CODE_VF_Freq_TrqBoost           43
#define CODE_VF_Vs_Coeff_TrqBoost       44
#define CODE_VF_Rs_ThermalCoeff         45
#define CODE_VF_IR_Comp_FilterPole      46
#define CODE_VF_Slip_Comp_FilterPole    47
#define CODE_VF_Rs                      48

#define CODE_AT_Freq_Leq_Req            50
#define CODE_AT_Time_Leq_Req            51
#define CODE_AT_Is_Coeff_Leq_Req        52

#define CODE_AT_Is_Coeff_Rs             53
#define CODE_AT_Time_Rs                 54

#define CODE_AT_DeadTimeGain            55
#define CODE_AT_Ls_Vs_RAMP              56
#define CODE_AT_Freq_Ls                 57
#define CODE_AT_Time_Ls                 58
#define CODE_AT_Ls_DMB_OpenTime         59

#define CODE_AT_Te_Coeff_Jm             60
#define CODE_AT_Time_Jm                 61
#define CODE_Jm_ID_ENABLE               62
#define CODE_posi_duration_time         63
#define CODE_zero_duration_time         64
#define CODE_nega_duration_time         65
#define CODE_test_accel_time            66
#define CODE_test_decel_time            67
#define CODE_RampTest                   68

#define CODE_wr_FilterPoleCoeff         70
#define CODE_wn_wr_Coeff                71
#define CODE_Max_wn_wr                  72
#define CODE_K_Damp_wr                  73
#define CODE_wr_DampingRatio            74
#define CODE_wr_CntlPeriodIndex         75
// ÀÚ¼Ó Á¦¾î
#define CODE_FW_VoltageCoeff            76
#define CODE_Base_Flux_Coeff            77
#define CODE_ExcitationTime             78
#define CODE_K_Damp_Fr                  79
#define CODE_GM_Fr                      80
#define CODE_PM_Fr                      81

#define CODE_K_Damp_Is                  82
//#define CODE_GM_Is                      83
//#define CODE_PM_Is                      84
#define CODE_KpIs                      83
#define CODE_KiIs                      84

#define CODE_Default_wr_FilterPole      85
#define CODE_SlipCompCoeff              86
#define CODE_GammaLambda                87
#define CODE_GammaLambda_R_Constant     88
#define CODE_Max_DeltaLambda            89
#define CODE_GammaTheta_M               90
#define CODE_GammaTheta_R               91
#define CODE_Max_DeltaTheta             92
#define CODE_Delta_wr_FilterPoleCoeff_L 93
#define CODE_Delta_wr_FilterPoleCoeff_U 94

#define CODE_END                        95

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
	double	code_min ;
	double   code_max ;
	double   code_default;
	double   code_value;
	char   disp[40];
};
typedef struct CODE_INFO_DEFINE CODE_INFO;

#endif
