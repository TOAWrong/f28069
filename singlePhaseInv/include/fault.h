// fault.h 2018.0613
// powerPack Eunwho Power Electornics by soonkil jung

#ifndef		_ERROR_CODE_DEFINITION_
#define		_ERROR_CODE_DEFINITION_

#define CODE_under_volt_set             100

#define ERR_PWM_IGBT                        600
#define ERR_IGBT_UH							601
#define ERR_IGBT_UL							602
#define ERR_IGBT_VH							603
#define ERR_IGBT_VL							604
#define ERR_IGBT_WH							605
#define ERR_IGBT_WL							606
#define ERR_IGBT_DB                         608
#define ERR_IGBT_RESET                      609

#define ERR_IGBT_RH							610
#define ERR_IGBT_RL							611
#define ERR_IGBT_SH							612
#define ERR_IGBT_SL							613
#define ERR_IGBT_TH							614
#define ERR_IGBT_TL							615

#define ERR_OVER_CURRENT_U_PHASE			620
#define ERR_OVER_CURRENT_V_PHASE			621

#define ERR_OVER_CURRENT_R_PHASE			623
#define ERR_OVER_CURRENT_S_PHASE			624
#define ERR_OVER_CURRENT_T_PHASE			625

#define ERR_UNKNOWN_ERR						999

#define	ERR_NAME_PLATE_PAR_MISMATCH			910
#define	ERR_PM_Is							844
#define	ERR_GM_Is							845
#define	ERR_K_Damp_Is						846
#define	ERR_Tr_Over							851
#define	ERR_Tr_Under						852
#define	ERR_sigma_Under						853
#define	ERR_sigma_Over						854
#define	ERR_Ki_Is_Under						856
#define	ERR_Kp_Is_Over						857
#define	ERR_Kp_Is_Under						858
#define	ERR_EXCITATION_TIME					859

// SCI 
#define ERR_SCI_CMD_ADDR_GROUP_UNDER		861
#define ERR_SCI_CMD_ADDR_GROUP_OVER			862
#define ERR_SCI_CMD_ADDR_1ST_UNDER			863
#define ERR_SCI_CMD_ADDR_1ST_OVER			864
#define ERR_SCI_CMD_ADDR_2ND_UNDER			865
#define ERR_SCI_CMD_ADDR_2ND_OVER			867

//
#define	ERR_Req_Under						920
#define	ERR_Req_Over						921
#define	ERR_Leq_Under0						923
#define	ERR_Leq_Over0						924
#define	ERR_Rs_Under						925
#define	ERR_Rs_Over							926
#define	ERR_Ls_Over0						927
#define	ERR_Ls_Under0						928	
#define	ERR_Ls_Under1						929
#define	ERR_Ls_Over1						930
#define	ERR_Leq_Over1						931
#define	ERR_Rr_Over							932
#define	ERR_Rr_Under						933
#define	ERR_Jm_Under						934
#define	ERR_Jm_Over							945
#define	ERR_WRONG_INTERRUPT_CMD				950

#define	ERR_PRECHARGING_FAIL				960		// �ʱ� ���� ���� 
#define	ERR_PWM								961
#define	ERR_HOC								962
#define	ERR_HOV								963
#define	ERR_HUV								964
#define	ERR_OVER_HEAT						965

#define	ERR_EXT_TRIP						966
#define	TRIP_EXT_A							967

#define	ERR_PWM_CNT							971		// ����Ī �ֱ��� ī���� �� ���� 

#define	ERR_INV_DISABLE						972		// ������ �ι��� �𽺿��̺� 

struct TRIP_INFO_DEFINE {
	int		CODE;				// 1
	float	CURRENT;			// 5
	float	VDC;				// 6
	float	RPM;				// 7
	float	DATA;				// 4
	char 	MSG[41];			// 2
};

typedef struct TRIP_INFO_DEFINE TRIP_INFO;

struct PROTECT_BITS {      // bits description
	Uint16  OVER_VOLT	:1;	
	Uint16  UNVER_VOLT	:1; 
	Uint16  OVER_I  	:1; 
	Uint16  LOW_I		:1; 
	Uint16  OVER_I_ADC	:1; 
	Uint16  OVER_LOAD	:1; 
	Uint16  LOW_LOAD	:1;
	Uint16  OVER_SPEED	:1; 
	Uint16  LOW_SPEED	:1; 
	Uint16  IGBT_FAULT	:1;
	Uint16  EX_TRIP		:1; 
	Uint16	OVER_HEAT	:1;
};

union PROTECT_FLAG{
   Uint16               all;
   struct PROTECT_BITS  bit;
};  

#endif


