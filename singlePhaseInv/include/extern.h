#ifndef     __VARIABLES_
#define     __VARIABLES_

// control and flag
extern CODE_INFO code_inform;
extern union PROTECT_FLAG protect_reg;
extern union DIGITAL_FUNCTION func_flag;
extern union DIGITAL_OUT_FUNC relay_flag;
extern TRIP_INFO TripInfo;
extern TRIP_INFO TripInfoNow;
extern int terminal_input_state;
extern char MonitorMsg[25];

// flag
extern int init_charge_flag;
extern int gRunFlag;
extern int gTripFlag;
extern int gTripSaveFlag;
extern int gTripSavePoint;
extern int gPWMTripCode;
extern int Flag_TripDataBackup;
extern int EepromSaveFlag;

extern int gMachineState;
extern int gControlMode;
extern int gDeChargeFlag;

extern int sendAdcDataFlag;
extern int graphCount;
extern UNION16 adcData[4][GRAPH_NUMBER+1];

// reference
extern double  reference_in;
extern double  reference_out;
extern double  analog_ref;
extern double  AnaCmdReference;
extern double  IncScanRef;
extern double  IncRef;
extern double  DecRef;

// count and time

extern int     timer0_count;
extern Uint16  MAX_PWM_CNT;
extern double  inv_MAX_PWM_CNT;
extern Uint16  DutyCount[3];
extern double  DutyRatio[3];
extern double  GainUpdateTimer;

extern double  Ts;
extern double  inv_Ts;
extern double  gfRunTime;
extern double  ref_time;
extern unsigned long   gulStartCount;
extern unsigned int    gStartInitFinish;

// frequency
extern double  P_pair;
extern double  inv_P_pair;

extern double  Freq_rat;
extern double  inv_Freq_rat;
extern double  inv_motor_rate_hz;
extern double  Freq_ref;
extern double  Freq_set;
extern double  frequency;
extern double  Freq_out;

extern double  Freq_slip_rat;
extern double  Freq_slip;

extern double  rpmOut;
extern double  rpm;
extern double  rpm_ref;
extern double  rpm_err;
extern double  rpm_Coeff;
extern double  rpm_m;

// angle
extern double  we_rat;
extern double  we;
extern double  we0;
extern double  we_in;
extern double  we_FW;
extern double  we_FW1;

extern int     wr_ctrl_index;
extern int     wr_CycleIndex;
extern double  wr;
extern double  wr_rat;
extern double  wr_ref;
extern double  wr_ref0;
extern double  wr_err;
extern double  wr_ErrInt;

extern double  wr_Cycle;
extern double  w_sl;
extern double  w_sl0;
extern double  Delta_wr;
extern double  Delta_wr_Filter_Pole;

extern double  wm_rat;
extern double  wr_m;
extern double  wr_m0;

extern double  theta;
extern double  theta_m;
extern double  SinTheta;
extern double  CosTheta;
extern double  SinTheta1;
extern double  CosTheta1;
extern double  SinDeltaTheta;
extern double  CosDeltaTheta;
extern double  SinCosDeltaTheta;
extern double  inv_SinCosDeltaTheta;
extern double  DeltaLambda;
extern double  DeltaTheta;

// Current
extern double  OverCurLimit;
extern double  Is_rat;
extern double  inv_Is_rat;
extern double  Is_max;
extern double  Is_mag;
extern double  Is_mag_rms;
extern double  sgn_Is[3];
extern double  sgn_I_QS;

extern double  Is_abc[3];
extern double  Is_dq[2];
extern double  Is_dq_ref[2];
extern double  Is_dq_ErrInt[2];

extern double  Is_DQ[2];
extern double  Is_DQ_ref[2];
extern double  Is_DQ_max[2];
extern double  Is_DQ_ErrInt[2];
extern double  prev_I_QS;
extern double  I_DS0;
extern double  I_DS0_0;
extern double  I_DS_err;
extern double  Is_Leq_Req;

// Voltage
extern double  Vs_rat;
extern double  Vdc;
extern double  Vs_ref;
extern double  sensVdc;
extern double  Vdc_factor;          // 2010 01 13
extern double  Vdc_calc_offset;     // 2010 01 13 for Vdc calc
extern double  Vs_Coeff_Leq_Req;

extern double  Vs_abc_ref[3];
extern double  Vs_abc[3];
extern double  Us_dq[2];
extern double  Vs_dq[2];
extern double  Vs_DQ[2];

extern double  Vs_max;
extern double  Vs_abc[3];
extern double  Vs_abc_ref[3];
extern double  Vs_dq[2];
extern double  Vs_dq_ref[2];
extern double  Vo;                 // zero sequence
extern double  Us_dq[2];
extern double  Vs_DQ[2];
extern double  Vs_DQ_max[2];
extern double  Vs_DQ_ref[2];
extern double  Vs_DQ_comp[2];
extern double  Vs_max_FW;
extern double  Vs_DQ_ref_P[2];
extern double  Vs_DQ_ref_PI[2];
extern double  Vs_IR_comp;
extern double  del_Vs_comp;

// power and torque
extern double Te_rat;
extern double inv_Te_rat;
extern double Kt;
extern double inv_Kt;
extern double S_lin;
extern double S_rat;
extern double  Pf;
extern double  Slip;
extern double  Power_core;
extern double  Power_core_rat;
extern double  Power_gap;

extern double  Re_Power;
extern double  Im_Power;
extern double  Te_max;
extern double  Te_ref;
extern double  Te;
extern double  LPF_Te;
extern double  Max_Trq_Coeff;


// Flux
extern double  Fs_rat;
extern double  Fs_ref;
extern double  Fs_ref0;
extern double  inv_Fs_ref;
extern double  Fs;
extern double  inv_Fs;
extern double  Fs_dq[2];
extern double  Fs1;

extern double  Fr;
extern double  inv_Fr;
extern double  Fr_ref;
extern double  inv_Fr_ref;
extern double  Fr_ref0;
extern double  Fr_Err;
extern double  Fr_ErrInt;

// Dead Time
extern double  C_ce_nF;
extern double  C_ce;
extern double  inv_C_ce;

// Motor Name Plate Parameter

extern double  inv_motor_rat_hz;
extern double  wr_rat;
extern double  wm_rat;
extern double  Te_rat;
extern double  inv_Te_rat;
extern double  Fs_rat;
extern double  Fr_rat;
extern double  Kt;
extern double  inv_Kt;
extern double  P_pair;
extern double  inv_P_pair;
extern double  rpm_Coeff;

// Machine Parameter
extern double  sigma;
extern double  sigma_Ls;
extern double  SlipCoeff;
extern double  inv_sigma_Tr;
extern double  sigma_Tr;
extern double  sigma_minus_1_div_sigma_Ls;
extern double  inv_sigma_Ls;
extern double  inv_Ls;
extern double  Tr;
extern double  inv_Tr;
extern double  inv_Ls_plus_sigma_Ls;
extern double  sigma_Ls_div_1_plus_sigma;
extern double  Lm_div_Lr;                      // Lm/Lr
extern double  Lr_div_Lm;                      // Lr/Lm

// Vector Control with/out sensor
extern double  wn_wr;
extern double  I_QS_rat;
extern double inv_I_QS_rat;

// V/F
extern double  S_rat;
extern double  S_lin;
extern double  Freq_slip_rat;

//
extern double  Kp_wr;
extern double  Ki_wr;

extern double  Fs_B;
extern double  inv_Fs_B;

extern double  inv_GM_Is_square_minus_1;
extern double  inv_GM_Is;
extern double  wp_Is_Coeff;
extern double  Kp_Is_Coeff;
extern double  wp_Is;
extern double  Ki_Is;
extern double  Kp_Is;

extern double  wr_FilterPole;
extern unsigned AutoTuningFlag;
extern double  Jm_SampleData[2];
extern double  Jm_ID_wr[4];
extern double  Jm_ID_Te[4];
extern double  Jm_ID_t[4];

extern double  Req;
extern double  Leq;

extern double  GainUpdateTimer;
extern double  Vs_Coeff_Leq_Req;

extern double LPF_Is;
extern double LPF_Is_Square;
extern double LPF_Vs_Square;
extern double LPF_Re_Power;

extern double  Is_Leq_Req;
extern double Freq_rat;
extern double inv_Freq_rat;

// Sci.c
extern int scib_rx_msg_flag;
extern int scic_rx_msg_flag;

extern int scia_tx_start_addr;
extern int scia_tx_end_addr;
extern int scia_rx_msg_flag;

extern char gStr1[50];
extern char gStr2[10];

extern int gSciInFlag;

extern char gSciaRxBuf[NUM_SCI_RX_BUF+1];
extern char gSciaTxBuf[NUM_SCI_TX_BUF+1];

extern int gSciaTxInPoint;
extern int gSciaTxOutPoint;
extern int gSciaTxEndFlag;

extern int giSciCmdFunction;
extern int giSciCmdAddr;
extern double gdouSciCmdData;

// analog to digital converter
extern int adc_result[6];
extern int adcIa;
extern int adcIb;
extern int adcVdc;
extern int adcIgbtTemperature;
extern int adcExSensor;
extern int adcCmdAnalog;

//filter
extern double lpfIa;
extern double lpfIb;

extern double lpfIrmsCutOffRreq;
extern double lpfIaIn[3];
extern double lpfIaOut[3];
extern double lpfIrmsK[4];
//double lpfIrmsCutOffRreq = 1.0;
extern double lpfIbIn[3];
extern double lpfIbOut[3];

extern double lpfVdc;
extern double lpfVdcCutoffFreq;
extern double lpfVdcIn[3];
extern double lpfVdcOut[3];
extern double lpfVdcK[4];

//============================================
//   CODE variable 
//============================================
extern double   codeMotorDirection;     // 1
extern double   codeAccelTime1;         // 2
extern double   codeDecelTime1;         // 3
extern double   codeMotorCtrlMode;      // 4
extern double   codeSpeed1;             // 5
extern double   codeSpeed2;             // 6
extern double   codeSetVdc;             // 7
extern double   codeProtectOff;         // 8
extern double   codePwmFreq;            // 9

extern double   codeRatePower;          // 10
extern double   codeRateCurrent;        // 11
extern double   codeRateRpm;            // 12
extern double   codeRateVolt;           // 13
extern double   codeRateEffiency;       // 14
extern double   codeRateHz;             // 15
extern double   codeMotorPole;          // 16

extern double   codeIaOffset;           // 20
extern double   codeIbOffset;           // 21

extern double I_sense_value;           // 22
extern double u_phase_I_sense_span;    // 23
extern double v_phase_I_sense_span;    // 24
extern double vdc_sense_zero;          // 25
extern double vdc_sense_span;          // 26

extern double Rs;                      // 30
extern double Rr;                      // 31
extern double Ls;                      // 32
extern double Lr;                      // 33
extern double Lm;                      // 34
extern double Jm;                      // 35

extern double VF_DeadTimeGain;         // 40
extern double VF_ExcitationTime;       // 41
extern double VF_Fs_Coeff;             // 42
extern double VF_Freq_TrqBoost;        // 43
extern double VF_Vs_Coeff_TrqBoost;    // 44
extern double VF_Rs_ThermalCoeff;      // 45
extern double VF_IR_Comp_FilterPole;   // 46
extern double VF_Slip_Comp_FilterPole; // 47
extern double VF_Rs;                   // 48

extern double AT_Freq_Leq_Req;         // 50
extern double AT_Time_Leq_Req;         // 51
extern double AT_Is_Coeff_Leq_Req;     // 52
extern double AT_Is_Coeff_Rs;          // 53
extern double AT_Time_Rs;              // 54
extern double AT_DeadTimeGain;         // 55
extern double AT_Ls_Vs_RAMP;           // 56
extern double AT_Freq_Ls;              // 57
extern double AT_Time_Ls;              // 58
extern double AT_Ls_DMB_OpenTime;      // 59

extern double AT_Te_Coeff_Jm;          // 60
extern double AT_Time_Jm;              // 61
extern double Jm_ID_ENABLE;            // 62

extern double posi_duration_time;      // 63
extern double zero_duration_time;      // 64
extern double nega_duration_time;      // 65
extern double test_accel_time;         // 66
extern double test_decel_time;         // 67

// group 7 advance control vaiable

extern double wr_FilterPoleCoeff;      // 70
extern double wn_wr_Coeff;             // 71
extern double Max_wn_wr;               // 72
extern double K_Damp_wr;               // 73
extern double wr_DampingRatio;         // 74
extern double wr_CntlPeriodIndex;         // 75

extern double FW_VoltageCoeff;         // 76
extern double Base_Flux_Coeff;         // 77
extern double ExcitationTime;          // 78
extern double K_Damp_Fr;               // 79
extern double GM_Fr;                   // 80
extern double PM_Fr;                   // 81
extern double K_Damp_Is;               // 82
extern double GM_Is;                   // 83
extern double PM_Is;                   // 84

extern double Default_wr_FilterPole;   // 85
extern double SlipCompCoeff;           // 86
extern double GammaLambda;             // 87
extern double GammaLambda_R_Constant;  // 88
extern double Max_DeltaLambda;         // 89
extern double GammaTheta_M;            // 90
extern double GammaTheta_R;            // 91
extern double Max_DeltaTheta;          // 92
extern double Delta_wr_FilterPoleCoeff_L; // 93
extern double Delta_wr_FilterPoleCoeff_U; //94

// end of code
extern double under_volt_set;          // 302
extern double over_speed_level;        // 303
extern double e_thermal_level;         // 304
extern double pre_charge_time;         // 305
extern double over_I_time;             // 307

extern double code_Vdc_scaler;         // 308  2011.0613
extern double code_Vdc_offseter;       // 309
extern double code_adc_vdc_low;        // 310
extern double code_adc_vdc_high;       // 311
extern double code_Vdc_calc_low;       // 312
extern double code_Vdc_calc_high;      // 313

extern double Data_Check;              // 800
extern double Data_Backup;             // 801
extern double Data_Load;               // 802
extern double Data_Init;               // 803
#endif
