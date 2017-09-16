//
// filename 	: trip_proc.c 
// projectname 	: F28035 inverter
// 					PCB --> pag.ls.0503  
// data			; start 2012.11.28 ~		
//					by cheoung soon gil  
// 
#include	<header.h>
#include	<extern.h>
int CheckOverCurrent( )
{
	if(( protect_reg.bit.OVER_I_ADC)&&( abs(adcIm) > 3500)){
		return ERR_OVER_CURRENT_U_PHASE;
	}
	if(( protect_reg.bit.OVER_I_ADC)&&( abs(adcIm) < 500)){
		return ERR_OVER_CURRENT_U_PHASE;
	}
	if(( protect_reg.bit.OVER_I_ADC)&&( abs(adcIa) > 3500)){
		return ERR_OVER_CURRENT_V_PHASE;
	}
	if(( protect_reg.bit.OVER_I_ADC)&&( abs(adcIa) < 500)){
		return ERR_OVER_CURRENT_V_PHASE;
	}
	return 	0; 
}
#define CODE_OC_level 		301
float code_over_volt_set = 380.0;
int CheckOverVolt( )
{
	static int OverVoltCount = 0;

	if( protect_reg.bit.OVER_VOLT == 0 ) return 0;

	if (lpfVdc > code_over_volt_set ) OverVoltCount++;
	else if( OverVoltCount > 0) OverVoltCount --;

	if (OverVoltCount > 5 )
	{
		OverVoltCount = 6;
		return CODE_OC_level;
	}
	return 0;
}

#define code_under_volt_set     180.0
int CheckUndeVolt( )
{
	static int UnderVoltCount = 0;

	if( protect_reg.bit.UNVER_VOLT == 0 ) return 0;

	if (lpfVdc < code_under_volt_set) 	UnderVoltCount++;
	else if( UnderVoltCount > 0) 	UnderVoltCount--;

	if (UnderVoltCount > 5 )
	{
		UnderVoltCount = 6;
		return CODE_under_volt_set;
	}
	return 0;
}

int CheckIGBTFault( )
{
	if( GATE_DRIVER_FAULT == 0)	return ERR_PWM;
	return 0;
}

int CheckOverHeat( )
{
	static int OverHeatCount = 0;

	if( protect_reg.bit.OVER_HEAT == 0 ) return 0;
	if( adcIgbtTemperature < 1000 )		OverHeatCount++;
	else if( OverHeatCount > 0) 	    OverHeatCount--;

	if( OverHeatCount > 10 ){	// debug// Low --> High
		OverHeatCount = 11;
		return ERR_OVER_HEAT;
	}
	return 0 ;
}

int trip_check()
{
	int TripCode;
	TripCode = 0;
	if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;	// debug
	if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;	// ���������� ������ �Ѵ�. 
	if( ( TripCode = CheckOverHeat()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckIGBTFault()  ) != 0 ) return TripCode ;
	return TripCode;
}

void trip_recording(int trip_code,float trip_data,char * st)
{

	TripInfoNow.CODE	= trip_code;
	TripInfoNow.DATA	= trip_data;
	strncpy( TripInfoNow.MSG,st,30) ;

	gMachineState 		= STATE_TRIP;
	TripInfoNow.CURRENT	= rmsIm;
	TripInfoNow.VDC 	= lpfVdc;
	TripInfoNow.RPM		= codeRateRpm * reference_out;

	if(gRunFlag)    gTripSaveFlag = 1;
    else            gTripSaveFlag = 0;
}	

void GetTripInfo(int Point,TRIP_INFO * TripData )
{
	int TripDataPoint;
	int TripBaseAddr;
	int iTemp;
	char str[30]={0};
	UNION32 u32data;

	strncpy(TripData->MSG ,NULL,41);

	if( Point == 0){
//		* TripData = &TripInfoNow;
		TripData->CURRENT 	= TripInfoNow.CURRENT;
		TripData->DATA 		= TripInfoNow.DATA;
		TripData->RPM 		= TripInfoNow.RPM;
		TripData->CODE 		= TripInfoNow.CODE;
		TripData->VDC 		= TripInfoNow.VDC;
		strncpy(TripData->MSG  ,TripInfoNow.MSG,20);
		return ;
	}

	I2CA_ReadData(ADDR_24LC32,EPROM_ADDR_TRIP_POINT,&TripDataPoint);
	if( ( 1 > Point ) || ( Point > 10) || (TripDataPoint == 0x00ff))
	{
		TripData->CURRENT = 0.0;
		TripData->DATA = 0.0;
		TripData->RPM = 0.0;
		TripData->CODE = 0.0;
		TripData->VDC = 0.0;

		if( TripDataPoint == 0x00ff) strncpy(TripData->MSG  ," NO TRIP DATA       ",20);
		else  strncpy(TripData->MSG  ," Invalid Trip Code  ",20);

		return ;
	}

	if( (TripDataPoint<1)||(TripDataPoint>10)){
		I2CA_WriteData(ADDR_24LC32, EPROM_ADDR_TRIP_POINT,1);
		TripDataPoint = 1;
	}
	EepromSaveFlag = 1;
	iTemp = TripDataPoint - Point + 1;		// iPoint = 1~10;
	if( iTemp <= 0 ) iTemp += 10;
	TripBaseAddr = TRIP_BACKUP_ADDR + iTemp * 100;
	read_eprom_data( TripBaseAddr+ 0, & u32data);
		TripData->CODE =  u32data.dword;

	// Data
	read_eprom_data( TripBaseAddr+ 4, & u32data);
		TripData->CURRENT =  u32data.dword;

	// Current
	read_eprom_data( TripBaseAddr+ 8, & u32data);
	TripData->CURRENT =  u32data.dword;

	// HZ
	read_eprom_data( TripBaseAddr+ 12, & u32data);
	TripData->RPM =  u32data.dword;

	// VDC
	read_eprom_data( TripBaseAddr+16, & u32data);
	TripData->VDC =  u32data.dword;

	// Time
	ReadTripString( TripBaseAddr+20,str);

	ReadTripString( TripBaseAddr+40,str);
	strncpy(TripData->MSG,str,20);

	EepromSaveFlag = 0;
}

void WriteTripString(int StartAddr, char * str)
{
	int i;
	int Addr;
	int string[21]={0};
	
	for(i=0;i<20;i++) string[i] = (int)(*(str ++));

	Addr = StartAddr;

	for(i=0;i<20;i++) I2CA_WriteData(ADDR_24LC32,Addr+i,string[i]);
}

void ReadTripString(int StartAddr, char * str)
{
	int i;
	int Addr;
	int iTemp;	
	char StrBuf[30];

	Addr = StartAddr;

	for(i=0;i<20;i++){
		I2CA_ReadData(ADDR_24LC32,Addr+i,&iTemp);
		StrBuf[i] = (char)(iTemp);
	}
	StrBuf[20] =0;
	strncpy(str,StrBuf,20);
}

void SaveTripDataToEeprom()
{
	int TripDataPoint,TripBaseAddr;
	char str[30];
	UNION32 u32data;

	I2CA_ReadData(ADDR_24LC32,EPROM_ADDR_TRIP_POINT,&TripDataPoint);

	if( TripDataPoint == 0x00FF) TripDataPoint = 1;
	else TripDataPoint ++;

	if( TripDataPoint > 10 ) TripDataPoint = 1;
	
	I2CA_WriteData(ADDR_24LC32, EPROM_ADDR_TRIP_POINT, TripDataPoint);			
	 
	TripBaseAddr = TRIP_BACKUP_ADDR + TripDataPoint * 100;

	EepromSaveFlag = 1;
// Code
	u32data.dword = TripInfoNow.CODE;
	write_code_2_eeprom( TripBaseAddr+ 0, u32data);

// Data
	u32data.dword = TripInfoNow.DATA;
	write_code_2_eeprom( TripBaseAddr+ 4, u32data);

// Current
	u32data.dword = TripInfoNow.CURRENT;
	write_code_2_eeprom( TripBaseAddr+ 8, u32data);

// RPM
	u32data.dword = TripInfoNow.RPM;
	write_code_2_eeprom( TripBaseAddr+ 12, u32data);

// VDC
	u32data.dword = TripInfoNow.VDC;
	write_code_2_eeprom( TripBaseAddr+16, u32data);

// Msg
	strncpy(str,TripInfoNow.MSG,20);
	WriteTripString( TripBaseAddr+40,str);

	EepromSaveFlag = 0;
}

void ClearTripDataToEeprom()
{
	int TripBaseAddr = 0;
	int TripDataPoint;
	int TripPointCount;
	char str[30];
	UNION32 u32data;

	EepromSaveFlag = 1;

	u32data.dword = 0.0;

	load_sci_tx_mail_box("WAIT FOR CLEAR DATA!");

	for(TripPointCount = 1; TripPointCount <= 10; TripPointCount++)
	{
		I2CA_ReadData(ADDR_24LC32,EPROM_ADDR_TRIP_POINT,&TripDataPoint);

		if( TripDataPoint == 0x00FF) TripDataPoint = 1;
		else TripDataPoint ++;
		if( TripDataPoint > 10 ) TripDataPoint = 1;
	
		I2CA_WriteData(ADDR_24LC32, EPROM_ADDR_TRIP_POINT, TripDataPoint);
		TripBaseAddr = TRIP_BACKUP_ADDR + TripDataPoint * 100;
		write_code_2_eeprom( TripBaseAddr+ 0, u32data);
		write_code_2_eeprom( TripBaseAddr+ 4, u32data);
		write_code_2_eeprom( TripBaseAddr+ 8, u32data);
		write_code_2_eeprom( TripBaseAddr+ 12, u32data);
		write_code_2_eeprom( TripBaseAddr+16, u32data);
		strncpy(str," NO TRIP DATA       ",20);
		WriteTripString( TripBaseAddr+40,str);
	}
	EepromSaveFlag = 0;
	load_sci_tx_mail_box("CLEAR COMPLETE !!   ");
}

void tripProc()
{
    int cmd;
    float ref_in0;

    gMachineState = STATE_TRIP;
	GATE_DRIVER_CLEAR;
	MAIN_CHARGE_OFF;
	ePwmPortOff();
    load_scia_tx_mail_box("TRIP"); delay_msecs(20);
    load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(20);
    sprintf( gStr1,"CODE=%d",TripInfoNow.CODE)    ; load_scia_tx_mail_box(gStr1);delay_msecs(20);
    sprintf( gStr1,"DATA=%e",TripInfoNow.DATA)    ; load_scia_tx_mail_box(gStr1);delay_msecs(20);
    sprintf( gStr1,"Irms=%e",TripInfoNow.CURRENT) ; load_scia_tx_mail_box(gStr1);delay_msecs(20);
    sprintf( gStr1,"RPM =%e",TripInfoNow.RPM)     ; load_scia_tx_mail_box(gStr1);delay_msecs(20);
    sprintf( gStr1,"VDC =%e",TripInfoNow.VDC)     ; load_scia_tx_mail_box(gStr1);delay_msecs(20);
	/*
// start input 이 되어 있는 상태에서 트립이 발생한다. 일반적으로
// - 이때 다시 스톱을 하고 시작을
// 다시 스톱 하면 리셋이 된다.
// 리셋이 되고 있다는 신호를 줘야 한다.
// - 초기 충전 릴레이?
//	트립과 동시에 충전 릴레이는 off가 된다.
// 리모트 리셋도 가능하다.
*/
	while( RUN_INPUT == 0 ){
        get_command( & cmd, & ref_in0);
        monitor_proc();
	    Nop();
	}
	delay_msecs(100);
	while( RUN_INPUT){
        get_command( & cmd, & ref_in0);
        monitor_proc();
	    Nop();
	}
	while( RUN_INPUT==0){
        get_command( & cmd, & ref_in0);
        monitor_proc();
	    Nop();
	}

	gMachineState = STATE_POWER_ON; Nop();
    asm (" .ref _c_int00");     // Branch to start of boot.asm in RTS library
    asm (" LB _c_int00");       // Branch to start of boot.asm in RTS library
}
//--- end of Trip_proc.c
