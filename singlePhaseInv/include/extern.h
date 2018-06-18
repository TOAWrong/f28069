#ifndef		__VARIABLES_
#define		__VARIABLES_

extern double rpmOut;

extern int sendAdcDataFlag;
extern int graphCount;
extern UNION16 adcData[4][GRAPH_NUMBER+1];

extern double    Is_max;                 // �ִ� �������

extern double sensVdc;
extern double sensIa;
extern double sensIb;

extern double lpfVdc;
extern double lpfIa;
extern double lpfIb;

extern double Is_abc[3];
extern double Is_dq[2];

extern double rmsIa;
extern double rmsIb;
extern double Is_mag;
extern double Is_mag_rms;

//-- low pass filter
extern double lpfVdcCutoffFreq;
extern double lpfVdcIn[3];
extern double lpfVdcOut[3];
extern double lpfVdcK[4];

extern double lpfIrmsCutOffRreq;
extern double lpfIaIn[3];
extern double lpfIaOut[3];
extern double lpfIrmsK[4];
//double lpfIrmsCutOffRreq = 1.0;
extern double lpfIbIn[3];
extern double lpfIbOut[3];

extern double Pole_pair;
extern double Wrm_det;

extern double Wrm_det_flt;
extern double Wr;
extern double Wrpm_det;
extern double Wrpm_max;

//--- low_pass_filter.c 
extern double LPF_zeta;
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

extern double analog_ref_a;
extern double analog_ref_b;

//*******************************************************
// ���� ���� 
//*******************************************************
extern double y1_data[GRAPH_NUMBER];
extern double y2_data[GRAPH_NUMBER];

extern double Vdc_factor;			// 2010 01 13
extern double Vdc_calc_offset;		// 2010 01 13 for Vdc calc

extern double ref_time;	// 2009.10.28

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
extern double	DutyRatio[3];
extern Uint16 DutyCount[3];

// �ð� �� �ε���
extern double 	gfRunTime;
extern double	Ts;
extern double	inv_Ts;
extern int timer0_count;
extern double inv_MAX_PWM_CNT;

// Ref.
extern double	reference_in;
extern double	reference_out;

// ���� �� ���ļ�

extern double	we_in;
extern double	we;
extern double	we0;

extern double	frequency;
extern double	theta;
extern double	SinTheta;
extern double	CosTheta;
extern double  CosDeltaTheta;
extern double  SinDeltaTheta;

extern double	wr_m;			// ���ڴ��� ���� ���� �ӵ�
extern double	wr_m0;			// ���� �ӵ��� ���͸� ��
extern double	wr;
extern double	wr_ref;
extern double	wr_ref0;
extern double	wr_err;
extern double	wr_ErrInt;
extern double	w_sl;
extern double	w_sl0;
extern double	we_FW;				// ����� ���� ���� ���ļ�
extern double	we_FW1;				// ����� �������� 2 ���� ���ļ�
extern double	rpm;
extern double	rpm_m;
extern double	rpm_ref;
extern double	rpm_err;

// ����
extern double Is_R;
extern double Is_S;
extern double Is_T;

extern double	Is_abc[3];
extern double	Is_dq[2];

extern double RMS_Ia;
extern double RMS_Ib;

extern double I_r;
extern double I_s;
extern double I_t;

extern double	sgn_Is[3];
extern double	Is_DQ[2];
extern double	Is_DQ_max[2];
extern double	Is_DQ_ref[2];
extern double	prev_I_QS;				// --> ���� ���
extern double	Is_DQ_ErrInt[2];
extern double	Is_dq_ref[2];
extern double	Is_dq_ErrInt[2];

// ����
extern double Vs_R;
extern double Vs_S;
extern double Vs_T;

extern double	Vdc;
extern double	Vs_max;
extern double	Vs_abc[3];
extern double	Vs_abc_ref[3];
extern double	Vs_dq_ref[2];

extern double	Vo;					// zero sequence
extern double	Us_dq[2];
extern double	Vs_DQ[2];
extern double	Vs_DQ_max[2];
extern double	Vs_DQ_ref[2];
extern double	Vs_DQ_comp[2];
extern double	Vs_max_FW;
extern double	Vs_DQ_ref_P[2];
extern double	Vs_DQ_ref_PI[2];

// ��ũ
extern double	Te_max;
extern double	Te_ref;
extern double	Te;
extern double	LPF_Te;
extern double	Max_Trq_Coeff;

// Flux
extern double	Fs_ref0;
extern double	Fs_ref;
extern double	inv_Fs_ref;
extern double	Fs_dq[2];
extern double	Fs;
extern double	Fs1;
extern double	inv_Fs;

extern double	Fr_ref;
extern double	Fr_ref0;
extern double	inv_Fr_ref;
extern double	Fr;
extern double	inv_Fr;
extern double	Fr_Err;
extern double	Fr_ErrInt;

extern double	theta_m;		// ��谢


// VVVF-Control
extern double	Vs_ref;
extern double	Freq_ref;
extern double	Freq_slip;
extern double	Freq_out;
extern double	Slip;
extern double	Power_core;
extern double	Power_core_rat;
extern double	Power_gap;
extern double	Vs_IR_comp;
extern double	del_Vs_comp;

// �������� ��������

// Reference Func.
extern double 	IncScanRef;
extern double	IncRef;
extern double	DecRef;

// Dead Time ���� 
extern double 	C_ce_nF;
extern double 	C_ce;
extern double 	inv_C_ce;

// Motor Name Plate Parameter
extern double	Vs_rat;
extern double	Is_rat;
extern double	inv_Is_rat;
extern double	we_rat;
extern double	inv_motor_rate_hz;
extern double	wm_rat;
extern double	Te_rat;
extern double	inv_Te_rat;
extern double	Fr_rat;
extern double	Kt;
extern double	inv_Kt;
extern double	P_pair;
extern double	inv_P_pair;

// �ι��� �Ķ����
// V/F �����
extern double	S_rat;
extern double	S_lin;
extern double	Freq_slip_rat;
	
extern unsigned long gulStartCount;
extern unsigned int gStartInitFinish; 

// Sci.c
extern int scia_tx_start_addr;
extern int scia_tx_end_addr;
extern int scia_rx_msg_flag;

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
extern double gdouSciCmdData;

extern int gMachineState;

extern int gAutoTuningSelect;		// �޴���� ���� ���� ���� �ϴ� �� 

extern int gControlMode;

extern unsigned long gulExcitTimeMsec;		// �ʱ� ���� �ð� 0.25�� 

	// Ref. Func

extern int gDeChargeFlag;
extern int	gPWMTripCode;

extern int gTripSavePoint;		// Ʈ���� ������ ������
extern int adc_result[6];

extern int adcIa;
extern int adcIb;
extern int adcVdc;
extern int adcIgbtTemperature;
extern int adcExSensor;
extern int adcCmdAnalog;

extern TRIP_INFO TripInfo;
extern TRIP_INFO TripInfoNow;

extern int gTripFlag;
extern double AnaCmdReference;
extern Uint16	MAX_PWM_CNT;
extern char MonitorMsg[25];
extern int gRunFlag;
extern int gTripSaveFlag;
extern double OverCurLimit;
extern int EepromSaveFlag;
extern int Flag_TripDataBackup;


extern double	inv_code_dac_scale_ch1;
extern double	inv_code_dac_scale_ch2;
extern double	inv_code_dac_scale_ch3;
extern double	inv_code_dac_scale_ch4;

//============================================
//   CODE variable 
//============================================
extern double   codeMotorDirection;     //
extern double   codeAccelTime1;         //
extern double   codeDecelTime1;         //
extern double   codeMotorCtrlMode;      //
extern double   codeSpeed1;             // 5
extern double   codeSpeed2;             // 6
extern double   codeSetVdc;             // 7
extern double   codeProtectOff;         // 8

extern double   codeRatePower;           // 10
extern double   codeRateVolt;            // 11
extern double   codeRateCurrent;         // 12
extern double   codeRateHz;              // 13
extern double   codeRateRpm;             // 14
extern double   codeMotorPole;           // 15
extern double   codeRateEffiency;        // 16
extern double   codePwmFreq;            // 17

extern double   codeIaOffset;           // 20
extern double   codeIbOffset;           // 21

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
extern double code_speed1;			//
extern double code_speed2;			//
extern double code_speed3;			//
extern double code_speed4;			//
extern double code_speed5;			//

// group2

extern double analog_cmd_in_zero1;		// 200
extern double analog_cmd_in_span1;		// 201
extern double analog_cmd_in_zero2;		// 202
extern double analog_cmd_in_span2;		// 203
extern double analog_out_select1;		// 204

extern int code_dac_select_ch1;		// 213	
extern double code_dac_scale_ch1;		//214
extern double code_dac_offset_ch1;		// 215

extern int code_dac_select_ch2;		// 216
extern double code_dac_scale_ch2;		//217
extern double code_dac_offset_ch2;		//218

extern int code_dac_select_ch3;		// 219
extern double code_dac_scale_ch3;		// 220
extern double code_dac_offset_ch3;		// 221

extern int code_dac_select_ch4;		// 222
extern double code_dac_scale_ch4;		// 223
extern double code_dac_offset_ch4;		// 224

// group3
extern double over_current_level;		// 300
extern double over_volt_set;			// 301
extern double under_volt_set;			// 302
extern double over_speed_level;		// 303
extern double e_thermal_level;			// 304
extern double pre_charge_time;			// 305
extern double Is_Max_Coeff;			// 306
extern double over_I_time;				// 307

extern double code_Vdc_scaler;			// 308  2011.0613
extern double code_Vdc_offseter;		// 309

extern double code_adc_vdc_low;			// 310
extern double code_adc_vdc_high;		// 311

extern double code_Vdc_calc_low;		// 312
extern double code_Vdc_calc_high;		// 313

// group5
extern double I_sense_value;			// 500
extern double u_phase_I_sense_span;		// 502
extern double v_phase_I_sense_span;		// 504
extern double vdc_sense_zero;			// 505
extern double vdc_sense_span;			// 506

extern int adc_u_offset;				// 510
extern int adc_v_offset;				// 511
extern int adc_R_offset;				// 512
extern int adc_S_offset;				// 513

extern double R_phase_I_sense_span;		// 515
extern double S_phase_I_sense_span;		// 517

// group6
extern double VF_DeadTimeGain;
extern double VF_ExcitationTime;
extern double VF_Fs_Coeff;
extern double VF_Freq_TrqBoost;
extern double VF_Vs_Coeff_TrqBoost;
extern double VF_Rs_ThermalCoeff;
extern double VF_IR_Comp_FilterPole;
extern double VF_Slip_Comp_FilterPole;
extern double VF_Rs;

extern double Freq_rat;
extern double inv_Freq_rat;

extern double Vs_abc_ref[3];
extern double Vs_abc[3];
extern double Us_dq[2];
extern double Vs_dq[2];
extern double Is_dq[2];
extern double Is_DQ[2];

extern double P_pair;
extern double inv_P_pair;
extern double Kt;
extern double inv_Kt;
extern double Te_rat;
extern double inv_Te_rat;
extern double S_lin;
extern double S_rat;
extern double Fs_rat;

extern double rpm_ref;
extern double wr_rat;
extern double rpm_Coeff;

#endif

