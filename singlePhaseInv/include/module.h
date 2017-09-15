#ifndef		__FUNCTION_MODULE_DEFINITION_
#define		__FUNCTION_MODULE_DEFINITION_

// analog.c
extern void ADC_SOC_CNF( );
extern void analog_input_proc( float * analog_referenc);
extern void analog_out_proc( );
extern int check_sensor_trip();
__interrupt void adcIsr(void);
// code_proc.c
extern int get_code_information(int address,int cmd , CODE_INFO *  codes);
extern void set_code_default(float min, float max, float defaults, float value,int open_level, CODE_INFO * codes );
extern int get_code_group8(int addr ,int cmd, CODE_INFO * codes );
extern int check_backup_data();
extern void save_backup_data();
extern void backup_data_load();
extern int init_eprom_data();
extern int Check_Eeprom_Error();
extern float CheckSum();
// common_module.c
extern void LPF_COEFF_CAL(float cut_freq, float * coeff1, float * coeff2);
extern void LPF_V(float *LPF_out, float *LPF_feed, float LPF_in);
extern void LPF_I(float *LPF_out, float *LPF_feed, float LPF_in);
extern float linear_eq(float x1, float x2, float y1, float y2, float x );
extern int periodic_check(unsigned long  msec);
extern  void    PI_Damp_Controller(float limit,float Ts,float damp_factor,float Kp,float Ki,float ref,float feedback,float *integral,float *output);
// digital_inout.c
extern void digital_out_proc();
extern void digital_input_proc( int * cmd, float * ref);
extern void input_ext_fault_a_proc();
extern void serial_com_proc( int * sci_cmd, float * sci_reference );
extern void load_sci_tx_mail_box(char *st);
// f28069GpioSetup.c
extern void ePwmPortOff();
extern void ePwmEnable();
extern void InitGpio(void);
// low_pass_filter.c
extern void lpf2nd(float * x,float * y, float * K);
extern void lpf2ndCoeffInit( float cutoff_freq, float T_sample, float *x, float *y, float *k);
// MonitorProc.c
extern void monitor_proc();     // need_edit
// ParameterSet.c
extern void VariInit();
extern int HardwareParameterVerification();
// RefFunc.c
extern void ramp_proc(  float set_ref, float * out_ref);
// scia.c
extern void scia_cmd_proc(int * scic_cmd, float * scic_ref);
extern interrupt void sciaTxFifoIsr(void);
extern interrupt void sciaRxFifoIsr(void);
extern void scia_fifo_init(void);
extern void load_scia_tx_mail_box(char *st);
// set_dac_point.c
extern void set_dac_point();

// File : "svm.c"
extern  void SpaceVectorModulation(float *Vs_dq );
extern  void VoltageEstimation();
// switching_irq.c
extern void PLL(void);
extern void Converter_Ctrl(void);
extern void Inverter_Ctrl(void);
extern void fIn_SpaceVectorPWM(void); 
extern void fOut_SpaceVectorPWM(void); 
extern void fault_check(void);
extern void convert_var_init();
extern void MotorControlProc( );
// test_run.c
extern int test_run();
// vector_control.c
extern int vector_control();
extern int vector_control_init();
extern void sl_vector_variable_init();
extern int pwm_regenerat_convert();
// vf_control.c
extern int vf_loop_control(float);
extern int vf_frequency_control();
extern void vf_simple_control();
extern void slip_comp_scalar_ctrl();
extern int SaveDataProc(int addr, float data);
interrupt void cpu_timer0_isr(void);

interrupt void MainPWM(void);
interrupt void wakeint_isr(void);

// File : ""SL_Vect.c""
extern	void 	SL_VectCntl_SFRF();
extern	void 	SL_SpeedCntl_SFRF();
extern	void 	DirTorqueLimitSpeedCntl_SFRF();
extern	void 	SL_TorqueCntl_SFRF();
extern int SL_SPEED_CNTL_Parameter();	

// File : "RefFunc.c"
extern void GetAnaMonitCount(unsigned int * piChA, unsigned * piChB);

// File : "auto_tuning.c"
extern void estim_ReqLeq_pwm();
extern void estim_Rs_pwm();
extern void	estim_Ls_pwm( );
extern void estim_Jm_pwm();
// SCI.C
extern void GetInputMark(char * str);
// main.c
extern void InitEPwm_ACIM_Inverter();
extern void Start_CheckSum();
// EwInv.C
extern void Nop();
extern void SetSensorOffset();
extern void PowerOnReset();
extern unsigned long ulGetTime_mSec(unsigned long Start_mSec);
extern unsigned long ulGetNow_mSec( );
extern void delay_msecs( unsigned long ulmSec);
extern void GetSensorValue( );
// refunc.c
extern void RefFunc( float CommandRef,float * OutRef);

// I2C_eeprom.c
extern int check_code_data(int address, UNION32 u32data );
// extern int check_code_data(UNION32 u32data,CODE_INFO CodeInfo );
extern void I2CA_Init(void);

extern void write_code_2_eeprom(int address,UNION32 data);
extern void read_eprom_data(int address, UNION32 * u32data);

extern Uint16 I2CA_ReadData(int iSlaveAddr, int iMemAddr, int * data);
extern Uint16 I2CA_WriteData(int iSlaveAddr,int iMemAddr,int iData);
extern int load_code2ram();

//*****************************************
// DS1307.c

extern void DS1307WriteData(int iMemAddr,int iData);
extern void DS1307ReadData(int iMemAddr, int * data);
extern void GetTimeAndDateStr(char * StrIn);
extern void WriteTimeToDS1307( );


// interrupt void i2c_int1a_isr(void);

// CommandProc.c
extern void get_command(int * command, float * ref );

//TripProc.c
extern void trip_recording(int trip_code,float trip_data,char * st);
extern void GetTripInfo(int Point, TRIP_INFO * TripData );
extern void WriteTripString(int StartAddr, char * str);
extern void ReadTripString(int StartAddr, char * str);
extern void SaveTripDataToEeprom();
extern void ClearTripDataToEeprom();

extern int CheckOverCurrent( );
extern int chk_invt_OC();
extern int chk_convt_OC();
extern int CheckOverVolt( );
extern int CheckUndeVolt( );
extern int CheckOverSpeed( );
extern int CheckIGBTFault( );
extern int CheckOverHeat( );

extern int trip_check();
extern void tripProc( );
extern void TripRecorder();

// hyd_unit.c
extern int hyd_unit_loop_proc();
extern void hyd_unit_control( );

#endif


