#ifndef		__FUNCTION_MODULE_DEFINITION_
#define		__FUNCTION_MODULE_DEFINITION_

// analog.c
extern void ADC_SOC_CNF( );
extern void analog_input_proc( double * analog_referenc);
extern void analog_out_proc( );
extern int check_sensor_trip();
extern interrupt void adcIsr(void);

// auto_tuning.c
void estim_ReqLeq_pwm();
void estim_Rs_pwm();
void estim_Ls_pwm();
void estim_Jm_pwm();

int estim_req_leq_loop( );
int estim_Rs_loop();
int estim_Ls_loop();
int estim_Jm_loop();
int parameter_estimation( );

// code_proc.c
extern void loadSciaTxMailBox( char * st);
extern int get_code_information(int address,int cmd , CODE_INFO *  codes);
extern void set_code_default(double min, double max, double defaults, double value,int open_level, CODE_INFO * codes );
extern int check_backup_data();
extern void save_backup_data();
extern void backup_data_load();
extern int init_eprom_data();
extern double CheckSum();
extern void readAllCodes();
// common_module.c
extern void LPF1(double Ts,double pole,double in,double *out);
extern double linear_eq(double x1, double x2, double y1, double y2, double x );
extern int periodic_check(unsigned long  msec);
extern  void    PI_Damp_Controller(double limit,double Ts,double damp_factor,double Kp,double Ki,double ref,double feedback,double *integral,double *output);
extern void get_command(int * command, double * ref );

// digital_inout.c
extern void digital_out_proc();
extern void digital_input_proc( int * cmd, double * ref);
extern void input_ext_fault_a_proc();
extern void serial_com_proc( int * sci_cmd, double * sci_reference );
extern void load_sci_tx_mail_box(char *st);
// EwInv.C
extern void Nop();
extern void SetSensorOffset();
extern void PowerOnReset();
extern unsigned long ulGetTime_mSec(unsigned long Start_mSec);
extern unsigned long ulGetNow_mSec( );
extern void delay_msecs( unsigned long ulmSec);
// f28069GpioSetup.c
extern void ePwmPortOff();
extern void ePwmEnable();
extern void InitGpio(void);
// I2C_eeprom.c
extern int check_code_data(int address, UNION32 u32data );
extern void I2CA_Init(void);
extern void write_code_2_eeprom(int address,UNION32 data);
extern void read_eprom_data(int address, UNION32 * u32data);
extern Uint16 I2CA_ReadData(int iSlaveAddr, int iMemAddr, int * data);
extern Uint16 I2CA_WriteData(int iSlaveAddr,int iMemAddr,int iData);
extern int load_code2ram();
// low_pass_filter.c
extern void lpf2nd(double * x,double * y, double * K);
extern void lpf2ndCoeffInit( double cutoff_freq, double T_sample, double *x, double *y, double *k);
// main.c
extern void InitEPwm_ACIM_Inverter();
// MonitorProc.c
extern void monitor_proc();     // need_edit
// ParameterSet.c
extern void VariableInitialization();
extern void VariInit();
// RefFunc.c
extern void ramp_proc(  double set_ref, double * out_ref);
// SCI.C
extern void GetInputMark(char * str);
// scia.c
extern void scia_cmd_proc(int * scic_cmd, double * scic_ref);
extern interrupt void sciaTxFifoIsr(void);
extern interrupt void sciaRxFifoIsr(void);
extern void scia_fifo_init(void);
extern void load_scia_tx_mail_box(char *st);

//set_Par.c
extern int HardwareParameterVerification();
extern int VF_Cntl_Parameter();
extern int COMMON_VECT_CNTL_ParameterVerification();
extern int COMMON_SL_VECT_CNTL_ParameterVerification();
extern int SL_TORQUE_CNTL_Parameter();
extern int SL_SPEED_CNTL_Parameter();
extern int AUTO_TUNING_Parameter();

//SL_Vect.c
void SL_SpeedCntl_SFRF();
void SL_TorqueCntl_SFRF();
void SL_VectCntl_SFRF();

// svm.c
extern  void SpaceVectorModulation(double *Vs_dq );
extern  void VoltageEstimation();
extern void singlePhaseModulation( double m, double theta, double dutyRatio[3]);
// switching_irq.c
extern void MotorControlProc( );
extern interrupt void MainPWM(void);
//TripProc.c
extern void trip_recording(int trip_code,double trip_data,char * st);
extern void GetTripInfo(int Point, TRIP_INFO * TripData );
extern void WriteTripString(int StartAddr, char * str);
extern void ReadTripString(int StartAddr, char * str);
extern void SaveTripDataToEeprom();
extern void ClearTripDataToEeprom();
extern int CheckOverCurrent( );
extern int CheckOverVolt( );
extern int CheckUndeVolt( );
extern int CheckIGBTFault( );
extern int CheckOverHeat( );
extern int trip_check();
extern void tripProc( );

//vectorCtrl.c
int vectorCtrlLoop();


// vf_control.c
extern void vf_simple_control();
extern void slip_comp_scalar_ctrl();

extern int vf_loop_control(double);
extern int SaveDataProc(int addr, double data);
interrupt void cpu_timer0_isr(void);
interrupt void MainPWM(void);
interrupt void wakeint_isr(void);
#endif
