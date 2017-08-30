#ifndef		__VARIABLES_
#define		__VARIABLES_

extern float Pole_pair;
extern float Wrm_det;

extern float Wrm_det_flt;
extern float Wr;
extern float Wrpm_det;
extern float Wrpm_max;

//--- low_pass_filter.c 
extern float LPF_zeta;
//--- DC link Voltage Low Pass
extern float LPF_Vdc_cutoff_freq;
extern float LPF_Vdc_in[3];
extern float LPF_Vdc_out[3];
extern float LPF_Vdc_K[4];

//--- AC Current Low Pass
extern float LPF_I_uvw_cutoff_freq ;

extern float LPF_I_u_in[3], LPF_I_v_in[3], LPF_I_w_in[3];
extern float LPF_I_u_out[3], LPF_I_v_out[3], LPF_I_w_out[3];
extern float LPF_I_u_K[4], LPF_I_v_K[4],LPF_I_w_K[4];


extern float  ADC_Vdc;

extern float  ADC_V_rs;
extern float  ADC_V_st;
extern float  ADC_V_tr;

extern float  ADC_I_r;
extern float  ADC_I_s;

extern float  ADC_I_u;
extern float  ADC_I_v;

extern unsigned int Fault_Code;

extern int init_charge_flag;

extern int giAdcAI_I1;
extern int giAdcAI_V1;
extern int giAdcAI_I2;
extern int giAdcAI_V2;
extern int giAdcTemp;

extern char TimeInput[13]; // ="101020123000";

extern int scib_rx_msg_flag;
extern int scic_rx_msg_flag;

extern float analog_ref_a;
extern float analog_ref_b;

//*******************************************************
// ���� ���� 
//*******************************************************
extern float y1_data[GRAPH_NUMBER];
extern float y2_data[GRAPH_NUMBER];

extern float Vdc_factor;			// 2010 01 13
extern float Vdc_calc_offset;		// 2010 01 13 for Vdc calc

extern float ref_time;	// 2009.10.28

extern CODE_INFO code_inform;
extern union PROTECT_FLAG protect_reg;

// codes
// --- digital_inout.h
extern union DIGITAL_OUT_FUNC relay_flag;
extern union DIGITAL_FUNCTION func_flag;	// ������ �Է��� ����� �����Ѵ�.

extern int scic_rx_start_addr;
extern int scic_rx_end_addr;

extern int scic_tx_start_addr;
extern int scic_tx_end_addr;

//-- use in udd_timer_irq
extern int terminal_input_state;
extern char TripMessage[25];
// PWM
extern float	DutyRatio[3];
extern Uint16 DutyCount[3];

// �ð� �� �ε���
extern float 	gfRunTime;
extern float	Ts;
extern float	inv_Ts;
extern int timer0_count;
extern float inv_MAX_PWM_CNT;

// Ref.
extern float	reference_in;
extern float	reference_out;

// ���� �� ���ļ�

extern float	we_in;
extern float	we;
extern float	we0;

extern float	frequency;
extern float	theta;
extern float	SinTheta;
extern float	CosTheta;
extern float  CosDeltaTheta;
extern float  SinDeltaTheta;

extern float	wr_m;			// ���ڴ��� ���� ���� �ӵ�
extern float	wr_m0;			// ���� �ӵ��� ���͸� ��
extern float	wr;
extern float	wr_ref;
extern float	wr_ref0;
extern float	wr_err;
extern float	wr_ErrInt;
extern float	w_sl;
extern float	w_sl0;
extern float	we_FW;				// ����� ���� ���� ���ļ�
extern float	we_FW1;				// ����� �������� 2 ���� ���ļ�
extern float	rpm;
extern float	rpm_m;
extern float	rpm_ref;
extern float	rpm_err;

// ����
extern float Is_R;
extern float Is_S;
extern float Is_T;

extern float	Is_abc[3];
extern float	Is_dq[2];

extern float RMS_Ia;
extern float RMS_Ib;

extern float	Is_mag;
extern float	Is_mag_rms;

extern float I_r;
extern float I_s;
extern float I_t;

extern float	sgn_Is[3];
extern float	Is_DQ[2];
extern float	Is_DQ_max[2];
extern float	Is_DQ_ref[2];
extern float	prev_I_QS;				// --> ���� ���
extern float	Is_DQ_ErrInt[2];
extern float	Is_dq_ref[2];
extern float	Is_dq_ErrInt[2];

// ����
extern float Vs_R;
extern float Vs_S;
extern float Vs_T;

extern float	Vdc;
extern float	Vs_max;
extern float	Vs_abc[3];
extern float	Vs_abc_ref[3];
extern float	Vs_dq_ref[2];

extern float	Vo;					// zero sequence
extern float	Us_dq[2];
extern float	Vs_DQ[2];
extern float	Vs_DQ_max[2];
extern float	Vs_DQ_ref[2];
extern float	Vs_DQ_comp[2];
extern float	Vs_max_FW;
extern float	Vs_DQ_ref_P[2];
extern float	Vs_DQ_ref_PI[2];

// ��ũ
extern float	Te_max;
extern float	Te_ref;
extern float	Te;
extern float	LPF_Te;
extern float	Max_Trq_Coeff;

// Flux
extern float	Fs_ref0;
extern float	Fs_ref;
extern float	inv_Fs_ref;
extern float	Fs_dq[2];
extern float	Fs;
extern float	Fs1;
extern float	inv_Fs;

extern float	Fr_ref;
extern float	Fr_ref0;
extern float	inv_Fr_ref;
extern float	Fr;
extern float	inv_Fr;
extern float	Fr_Err;
extern float	Fr_ErrInt;

extern float	theta_m;		// ��谢


// VVVF-Control
extern float	Vs_ref;
extern float	Freq_ref;
extern float	Freq_slip;
extern float	Freq_out;
extern float	Slip;
extern float	Power_core;
extern float	Power_core_rat;
extern float	Power_gap;
extern float	Vs_IR_comp;
extern float	del_Vs_comp;

// �������� ��������

// Reference Func.
extern float 	IncScanRef;
extern float	IncRef;
extern float	DecRef;

// Dead Time ���� 
extern float 	C_ce_nF;
extern float 	C_ce;
extern float 	inv_C_ce;

// Motor Name Plate Parameter
extern float	Vs_rat;
extern float	Is_rat;
extern float	inv_Is_rat;
extern float	we_rat;
extern float	inv_motor_rate_hz;
extern float	wm_rat;
extern float	Te_rat;
extern float	inv_Te_rat;
extern float	Fr_rat;
extern float	Kt;
extern float	inv_Kt;
extern float	P_pair;
extern float	inv_P_pair;

// �ι��� �Ķ����
extern float	Is_max;					// �ִ� �������
	
// V/F �����
extern float	S_rat;
extern float	S_lin;
extern float	Freq_slip_rat;
	
extern unsigned long gulStartCount;
extern unsigned int gStartInitFinish; 

// Sci.c

extern char gStr1[50];
extern char gStr2[10];

extern int gSciInFlag;
extern int scia_rx_msg_flag;

extern char gSciaRxBuf[NUM_SCI_RX_BUF+1];
extern char gSciaTxBuf[NUM_SCI_TX_BUF+1];

extern int	gSciaTxInPoint;
extern int	gSciaTxOutPoint;
extern int	gSciaTxEndFlag;

extern int giSciCmdFunction;
extern int giSciCmdAddr;
extern float gdouSciCmdData;

extern int gMachineState;

extern int gAutoTuningSelect;		// �޴���� ���� ���� ���� �ϴ� �� 

extern int gControlMode;

extern unsigned long gulExcitTimeMsec;		// �ʱ� ���� �ð� 0.25�� 

	// Ref. Func

extern int gDeChargeFlag;
extern int	gPWMTripCode;

extern int gTripSavePoint;		// Ʈ���� ������ ������

extern int adc_result[16];
extern int adcIuPhase;
extern int adcIvPhase;
extern int adcVdc;
extern int adcIgbtTemperature;
extern int adcExSensor;

extern TRIP_INFO TripInfo;
extern TRIP_INFO TripInfoNow;

extern int gTripFlag;
extern float AnaCmdReference;
extern Uint16	MAX_PWM_CNT;
extern char MonitorMsg[30];
extern int gRunFlag;
extern int gTripSaveFlag;
extern float OverCurLimit;
extern int EepromSaveFlag;
extern int Flag_TripDataBackup;


extern float	inv_code_dac_scale_ch1;
extern float	inv_code_dac_scale_ch2;
extern float	inv_code_dac_scale_ch3;
extern float	inv_code_dac_scale_ch4;

//============================================
//   CODE variable 
//============================================
extern float   codeMotorDirection;     //
extern float   codeAccelTime1;         //
extern float   codeDecelTime1;         //
extern float   codeMotorCtrlMode;      //
extern float   codeSpeed1;             // 5
extern float   codeSpeed2;             // 6
extern float   codeProtectOff;         // 7

extern float   codeMotorRatePower;     // 10
extern float   codeMotorRateVolt;      // 11
extern float   codeMotorRateCurrent;   // 12
extern float   codeMotorRateHz;        // 13
extern float   codeMotorRateRpm;       // 14
extern float   codeMotorPole;          // 15
extern float   codeMotorRateEffiency;  // 16

///////////////////////////////////
// extern int code_protect_inhibit_on;		// 30
extern int code_protect_uv_off;			// 31
extern int code_protect_ov_off;			// 32
extern int code_protect_Iadc_off;		// 33
extern int code_protect_over_I_off;		// 34
extern int code_protect_IGBT_off;		// 35
extern int code_protect_ex_trip_off;	// 36
extern int code_protect_IGBT2_off;		// 37
extern int code_protect_CONV_adc_off;	// 38
///////////////////////////////////

// group 1
extern int code_use_binary_input;
extern float code_speed1;			//
extern float code_speed2;			//
extern float code_speed3;			//
extern float code_speed4;			//
extern float code_speed5;			//

// group2

extern float analog_cmd_in_zero1;		// 200
extern float analog_cmd_in_span1;		// 201
extern float analog_cmd_in_zero2;		// 202
extern float analog_cmd_in_span2;		// 203
extern float analog_out_select1;		// 204

extern int code_dac_select_ch1;		// 213	
extern float code_dac_scale_ch1;		//214
extern float code_dac_offset_ch1;		// 215

extern int code_dac_select_ch2;		// 216
extern float code_dac_scale_ch2;		//217
extern float code_dac_offset_ch2;		//218

extern int code_dac_select_ch3;		// 219
extern float code_dac_scale_ch3;		// 220
extern float code_dac_offset_ch3;		// 221

extern int code_dac_select_ch4;		// 222
extern float code_dac_scale_ch4;		// 223
extern float code_dac_offset_ch4;		// 224

// group3
extern float over_current_level;		// 300
extern float over_volt_set;			// 301
extern float under_volt_set;			// 302
extern float over_speed_level;		// 303
extern float e_thermal_level;			// 304
extern float pre_charge_time;			// 305
extern float Is_Max_Coeff;			// 306
extern float over_I_time;				// 307

extern float code_Vdc_scaler;			// 308  2011.0613
extern float code_Vdc_offseter;		// 309

extern float code_adc_vdc_low;			// 310
extern float code_adc_vdc_high;		// 311

extern float code_Vdc_calc_low;		// 312
extern float code_Vdc_calc_high;		// 313

// group5
extern float I_sense_value;			// 500
extern float u_phase_I_sense_span;		// 502
extern float v_phase_I_sense_span;		// 504
extern float vdc_sense_zero;			// 505
extern float vdc_sense_span;			// 506

extern int adc_u_offset;				// 510
extern int adc_v_offset;				// 511
extern int adc_R_offset;				// 512
extern int adc_S_offset;				// 513

extern float R_phase_I_sense_span;		// 515
extern float S_phase_I_sense_span;		// 517

// group6
extern float VF_DeadTimeGain;
extern float VF_ExcitationTime;
extern float VF_Fs_Coeff;
extern float VF_Freq_TrqBoost;
extern float VF_Vs_Coeff_TrqBoost;
extern float VF_Rs_ThermalCoeff;
extern float VF_IR_Comp_FilterPole;
extern float VF_Slip_Comp_FilterPole;
extern float VF_Rs;

extern float Freq_rat;
extern float inv_Freq_rat;

extern float Vs_abc_ref[3];
extern float Vs_abc[3];
extern float Us_dq[2];
extern float Vs_dq[2];
extern float Is_dq[2];
extern float Is_DQ[2];

extern float P_pair;
extern float inv_P_pair;
extern float Kt;
extern float inv_Kt;
extern float Te_rat;
extern float inv_Te_rat;
extern float S_lin;
extern float S_rat;
extern float Fs_rat;

extern float rpm_ref;
extern float wr_rat;
extern float rpm_Coeff;

#endif

