#ifndef		__GLOBAL_VARIABLES_
#define		__GLOBAL_VARIABLES_

//double theta;
double rpmOut;

int sendAdcDataFlag;
int graphCount=0;
UNION16 adcData[4][GRAPH_NUMBER+1];

double Vdc;
double Is_max;

double sensVdc;
double sensIm;
double sensIa;

double lpfVdc;
double lpfIm;

double Is_abc[3];
double Is_dq[2];

double lpfIa;
double rmsIm;
double rmsIa;
double Is_mag;
double Is_mag_rms;


double lpfVdcCutoffFreq = 1000.0;
double lpfVdcIn[3];
double lpfVdcOut[3];
double lpfVdcK[4];

double lpfIrmsCutOffRreq = 1.0;
double lpfImIn[3];
double lpfImOut[3];
double lpfIrmsK[4];
//double lpfIrmsCutOffRreq = 1.0;
double lpfIaIn[3];
double lpfIaOut[3];

int init_charge_flag = 0;

int scib_rx_msg_flag = 0;
int scic_rx_msg_flag = 0;

double analog_ref_a;
double analog_ref_b;

double Vdc_factor;			// 2010 01 13
double Vdc_calc_offset;		// 2010 01 13 for Vdc calc

double ref_time;

CODE_INFO code_inform = {0,0,0,0,0,0,{0}};

union PROTECT_FLAG protect_reg;

int terminal_input_state;

// PWM
double	DutyRatio[3];
Uint16 DutyCount[3];

// �ð� �� �ε���
double	Ts;
double	inv_Ts;
double 	gfRunTime=0;
int timer0_count;
double inv_MAX_PWM_CNT;


//=============================================

double	Freq_set=0.0;
double	Re_Power=0.0;
double	Im_Power=0.0;

double	Vs_rat;
double	Is_rat;
double	inv_Is_rat;
double	we_rat;
double inv_motor_rate_hz;

double	Vs_max=0.0;

double	Freq_out=0.0;
double	rpm=0.0;

double	reference_in=0.0;
double	reference_out=0.0;

// ���� �� ���ļ�

double	we_in=0.0;
double	we=0.0;
double	we0=0.0;

double	frequency=0.0;
double	theta=0.0;
double	SinTheta=0.0;
double	CosTheta=1.0;
double  CosDeltaTheta;
double  SinDeltaTheta;

double	Vs_dq_ref[2]={0.0,0.0};


// ��ũ
double	Te_max=0.0;
double	Te_ref=0.0;
double	Te=0.0;
double	LPF_Te=0.0;
double	Max_Trq_Coeff=0.0;


// VVVF-Control
double	Vs_ref=0.0;
double	Freq_ref=0.0;
double	Freq_slip=0.0;
double	Slip=0.0;
double	Power_core=0.0;
double	Power_core_rat=0.0;
double	Power_gap=0.0;
double	Vs_IR_comp=0.0;
double	del_Vs_comp=0.0;


// �ʱ�����	

// Dead Time ���� 
double 	C_ce_nF;
double 	C_ce;
double 	inv_C_ce;

double	Freq_slip_rat;
	
//====================================
// F28335 
// EwInv ���� ����
//====================================

unsigned long gulStartCount;

unsigned int gStartInitFinish; 

// Sci.c

int scia_tx_start_addr=0;
int scia_tx_end_addr=0;
int scia_rx_msg_flag = 0;

char gStr1[50] = {0};
char gStr2[10] = {0};

int gSciInFlag;

char gSciaRxBuf[NUM_SCI_RX_BUF+1];
char gSciaTxBuf[NUM_SCI_TX_BUF+1];

int	gSciaTxInPoint;
int	gSciaTxOutPoint;
int	gSciaTxEndFlag;

int giSciCmdFunction;
int giSciCmdAddr;
double gdouSciCmdData;

int gMachineState=0;

int gAutoTuningSelect;		// �޴����� ���� ���� ���� �ϴ� �� 

int gControlMode;

// Ref. Func
int gDeChargeFlag;
int	gPWMTripCode;

int gTripSavePoint;     //

// analog to digital converter
int adc_result[6]={0};

int adcIm;
int adcIa;
int adcVdc;
int adcIgbtTemperature;
int adcExSensor;
int adcCmdAnalog;

union DIGITAL_FUNCTION func_flag;	// ������ �Է��� ����� �����Ѵ�.

union DIGITAL_OUT_FUNC relay_flag;

TRIP_INFO TripInfo = {0,0,0,0,0," No Trip Data       "};

//TRIP_INFO TripInfoNow={0,0,0,0,0,"01234567890123456789","01234567890123456789"};
TRIP_INFO TripInfoNow = {0,0,0,0,0," No Trip Data       "};

int gTripFlag = 0;
double AnaCmdReference=0;

Uint16	MAX_PWM_CNT;

char MonitorMsg[25]={0};

int gRunFlag=0;
int gTripSaveFlag=0;
int EepromSaveFlag = 0;
int Flag_TripDataBackup = 0;

double OverCurLimit;


//============================================
//   CODE variable 
//============================================
double   codeMotorDirection;     //
double   codeAccelTime1;         //
double   codeDecelTime1;         //
double   codeMotorCtrlMode;      //
double   codeSpeed1;             // 5
double   codeSpeed2;             // 6
double   codeSetVdc;             // 7
double   codeProtectOff;         // 8

double   codeRatePower;          // 10
double   codeRateVolt;           // 11
double   codeRateCurrent;        // 12
double   codeRateHz;             // 13
double   codeRateRpm;            // 14
double   codeMotorPole;          // 15
double   codeRateEffiency;       // 16
double   codePwmFreq;            // 17

double   codeIaOffset;           // 20
double   codeIbOffset;           // 21

// #define CODE_END                22

///////////////////////////
//int code_protect_inhibit_on;	// 30
int code_protect_uv_off;		// 31
int code_protect_ov_off;		// 32
int code_protect_Iadc_off;		// 33
int code_protect_over_I_off;	// 34
int code_protect_IGBT_off;		// 35
int code_protect_ex_trip_off;	// 36
int code_protect_IGBT2_off;		// 37
int code_protect_CONV_adc_off;	// 38
///////////////////////////
double analog_cmd_in_zero1;		// 200
double analog_cmd_in_span1;		// 201
double analog_cmd_in_zero2;		// 202
double analog_cmd_in_span2;		// 203

int code_dac_select_ch1;		// 213	
double code_dac_scale_ch1;		//214
double code_dac_offset_ch1;		// 215

int code_dac_select_ch2;		// 216
double code_dac_scale_ch2;		//217
double code_dac_offset_ch2;		//218

int code_dac_select_ch3;		// 219
double code_dac_scale_ch3;		// 220
double code_dac_offset_ch3;		// 221

int code_dac_select_ch4;		// 222
double code_dac_scale_ch4;		// 223
double code_dac_offset_ch4;		// 224

// group3
double over_current_level;		// 300
double over_volt_set;			// 301
double under_volt_set;			// 302
double over_speed_level;		// 303
double e_thermal_level;			// 304
double pre_charge_time;			// 305
double Is_Max_Coeff;			// 306
double over_I_time;				// 307

double code_Vdc_scaler;			// 308  2011.0613
double code_Vdc_offseter;		// 309
double code_adc_vdc_low;		// 310
double code_adc_vdc_high;		// 311
double code_Vdc_calc_low;		// 312
double code_Vdc_calc_high;		// 313


//group 4
double motor_rate_power;		// 400
double motor_rate_volt;			// 401
double motor_rate_current;		// 402
double motor_rate_hz;			// 403
double motor_rate_rpm;			// 404
double motor_pole;				// 405
double motor_rate_effiency;		// 406

// group5
double I_sense_value;			// 500
double u_phase_I_sense_span;	// 502
double v_phase_I_sense_span;	// 504
double vdc_sense_zero;			// 505
double vdc_sense_span;			// 506

int adc_u_offset;				// 510
int adc_v_offset;				// 511

int adc_R_offset;				// 512
int adc_S_offset;				// 513

double R_phase_I_sense_span;	// 515
double S_phase_I_sense_span;	// 517

// group6

double VF_DeadTimeGain;
double VF_ExcitationTime;
double VF_Fs_Coeff;
double VF_Freq_TrqBoost;
double VF_Vs_Coeff_TrqBoost;
double VF_Rs_ThermalCoeff;
double VF_IR_Comp_FilterPole;
double VF_Slip_Comp_FilterPole;
double VF_Rs;


double Data_Check;				// 800
double Data_Backup;				// 801
double Data_Load;				// 802
double Data_Init;				// 803

//=====================================================

double	GainUpdateTimer;
double	Vs_Coeff_Leq_Req;

double	Is_Leq_Req;

int wr_ctrl_index			= 1;

double Freq_rat;
double inv_Freq_rat;

double Vs_abc_ref[3];
double Vs_abc[3];
double Us_dq[2];
double Vs_dq[2];
double Vs_DQ[2];

double Is_DQ[2];
double P_pair;
double inv_P_pair;
double Kt;
double inv_Kt;
double Te_rat;
double inv_Te_rat;
double S_lin;
double S_rat;
double Fs_rat;

double rpm_ref;
double wr_rat;
double rpm_Coeff;
double wm_rat;
double sgn_Is[3];
#endif



