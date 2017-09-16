#include	"header.h"
#include	"extern.h"

int get_code_information(int address,int cmd , CODE_INFO *  codes)
{	
	switch(address)
	{
    case CODE_motor_direction_change:
        strncpy(codes->disp, "Rotate CW ON",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorDirection = codes->code_value;
        set_code_default(0,1,0,codeMotorDirection,0,codes);
        break;

    case CODE_accel_time1:
        strncpy(codes->disp, "accel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeAccelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeAccelTime1,0,codes);
        break;

    case CODE_decel_time1:
        strncpy(codes->disp, "decel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeDecelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeDecelTime1,0,codes);
        break;

    case CODE_motor_ctrl_mode:  //
        strncpy(codes->disp, "motor_ctrl_mode",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorCtrlMode = codes->code_value;
        set_code_default(0,7,0,codeMotorCtrlMode,0,codes);
        break;

    case CODE_speed1:
		strncpy(codes->disp, "speed1 (p.u)",20);
		if( cmd == CMD_WRITE_RAM ) codeSpeed1 = codes->code_value;
		set_code_default(0.0,0.9,0.25,codeSpeed1,0,codes);
		break;

	case CODE_speed2:		
		strncpy(codes->disp, "speed2 (p.u)",20);
		if( cmd == CMD_WRITE_RAM ) codeSpeed2 = codes->code_value;
		set_code_default(0.0,1.2,0.25,codeSpeed2,0,codes);
		break;

    case CODE_set_vdc:
        strncpy(codes->disp, "set Vdc 300.0",20);
        if( cmd == CMD_WRITE_RAM ) codeSetVdc = codes->code_value;
        set_code_default(0,1,0,codeSetVdc,0,codes);
        break;

    case CODE_protect_off:
        strncpy(codes->disp, "Protect Off",20);
        if( cmd == CMD_WRITE_RAM ) codeProtectOff = codes->code_value;
        set_code_default(0,1,1,codeProtectOff,0,codes);
        break;

    case CODE_rate_power:
        strncpy(codes->disp, "Rate_power",20);
        if( cmd == CMD_WRITE_RAM ) codeRatePower = codes->code_value;
        set_code_default(100,2.0e+6,400,codeRatePower,0,codes);
        break;

    case CODE_rate_volt:
        strncpy(codes->disp, "Rate Volt (Vrms)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateVolt = codes->code_value;
        set_code_default(100.0,500.0,220.0,codeRateVolt,0,codes);
        break;

    case CODE_rate_current:
        strncpy(codes->disp, "Rate Current(A)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateCurrent = codes->code_value;
        set_code_default(1.0,2000.0,2.3,codeRateCurrent,0,codes);
        break;

    case CODE_rate_hz:
        strncpy(codes->disp, "Rate hz",20);
        if( cmd == CMD_WRITE_RAM ) codeRateHz = codes->code_value;
        set_code_default(30.0,120.0,60.0,codeRateHz,0,codes);
        break;

    case CODE_rate_rpm:
        strncpy(codes->disp, "Rate RPM",20);
        if( cmd == CMD_WRITE_RAM ) codeRateRpm = codes->code_value;
        set_code_default(500,8000.0,1680.0,codeRateRpm,0,codes);
        break;

    case CODE_motor_pole:
        strncpy(codes->disp, "Motor Pole ",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorPole = codes->code_value;
        set_code_default(2,20,4,codeMotorPole,0,codes);
        break;

    case CODE_rate_effiency:
        strncpy(codes->disp, "Motor Effiency",20);
        if( cmd == CMD_WRITE_RAM ) codeRateEffiency = codes->code_value;
        set_code_default(0.2,0.99,0.65,codeRateEffiency,0,codes);
        break;
/*
    case CODE_pwm_freq:
        strncpy(codes->disp, "PWM Freq",20);
        if( cmd == CMD_WRITE_RAM ) codePwmFreq = codes->code_value;
        set_code_default(500.0,10000.0,8000.0,codePwmFreq,0,codes);
        break;
*/
	case CODE_END:
		return -2;
			
	default:
		return -1;
	}
	return 0;
}

void set_code_default(float min, float max, float defaults, float value,int open_level, CODE_INFO * codes )
{
	codes->type 		= TYPE_float;
	codes->open_level 	= open_level;
	codes->code_min		= min;
	codes->code_max		= max;
	codes->code_default	= defaults;
	codes->code_value 	= value;
}

int check_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0 ; address <= CODE_END; address++){	 // code group �� 6��
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            check = check_code_data(address, data );	// check min and max boundary
            if(check)  return -1;
        }
    }
	return 0;
}


void save_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
	for( address = 0 ; address <= CODE_END ; address++){
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 1;
            write_code_2_eeprom( address,data);
            Flag_TripDataBackup = 0;
        }
	}
}

void backup_data_load()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0; address <= CODE_END ;address++)
    {
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            write_code_2_eeprom( address,data);
            code_inform.code_value = data.dword;
            cmd = CMD_WRITE_RAM;
            check = get_code_information( address,cmd, & code_inform);
        }
	}
}
float CheckSum()
{

}

int SaveDataProc(int addr, float data)
{
	int cmd,i,return_value;
	char SciBuf[30]={0};
	char str[30];
	UNION32 u32data,u32data2;

	return_value = 0;

	cmd = CMD_READ_DATA;

	i = get_code_information( addr,cmd,&code_inform); 

	if( i != 0 ) goto _SAVE_ERROR_INVALID_ADDR;   

	if( addr >= 800 ){

		if( data < 1.22 ) goto _SAVE_ERROR_INVALID_DATA; 
		if( data > 1.24 ) goto _SAVE_ERROR_INVALID_DATA; 
		switch(addr)
		{
		case CODE_Data_Check: 	return_value = check_backup_data();	break;
		case CODE_Data_Backup:
			strncpy(str,"Wait for Data Backup",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			save_backup_data();
			strncpy(str,"Wait for Error Check",20);
			load_sci_tx_mail_box(str);  delay_msecs(20);

			break;
		case CODE_Data_Load:
			strncpy(str,"Wait for Data Load !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);	
			backup_data_load();
			break;
		case CODE_Data_Init:
			strncpy(str,"Wait For Data Init !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			init_eprom_data();
			strncpy(str,"Data Init OK !      ",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			break;

		default:
			goto _SAVE_ERROR_INVALID_ADDR;
		}
		return return_value;
	}

    if( code_inform.code_min > data ){
        goto _SAVE_ERROR_DATA_UNDER;
    }
    else if( code_inform.code_max < data ){
        goto _SAVE_ERROR_DATA_OVER;
    }
    else {
        u32data.dword = data;
        read_eprom_data( addr, & u32data2);
        if( u32data.dword != u32data2.dword ){
            write_code_2_eeprom( addr, u32data);
            read_eprom_data( addr, & u32data2);

            if( u32data.dword != u32data2.dword ) goto _EEPROM_WRITE_ERROR;

            code_inform.code_value = data;
            cmd = CMD_WRITE_RAM;
            get_code_information( addr,cmd, & code_inform);

            // CheckSum Save
            u32data.dword = CheckSum();
            EepromSaveFlag = 1;
            write_code_2_eeprom(EPROM_ADDR_CHECKSUM, u32data);
            EepromSaveFlag = 0;

            load_sci_tx_mail_box("OK write success") ;
        }
        else{
            load_sci_tx_mail_box("Equal Data write skipped");
        }
        return 0;
    }
_SAVE_ERROR_INVALID_ADDR:
//	strcpy(SciBuf, "ADDR");
	strcpy(SciBuf,"Invalid Address" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_UNDER:

//	strcpy(SciBuf, "UNDE");

	strcpy(SciBuf,"Input data under" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_OVER:
//	strcpy(SciBuf, "OVER");
	strcpy(SciBuf,"Input data over" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_INVALID_DATA:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Invalid data " );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_EEPROM_WRITE_ERROR:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Eeprom write error" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;
}


int init_eprom_data()
{
	UNION32	data,data2;
	int check,address,cmd;

	data.dword  = 0.0;

	cmd = CMD_READ_DATA;
	for( address = 0 ; address < CODE_END ; address++ )
	{
		cmd = CMD_READ_DATA;
		check = get_code_information( address, cmd , & code_inform);
		if( check==0 ){
			data.dword = code_inform.code_default;
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword)	write_code_2_eeprom( address,data);
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword){
				load_sci_tx_mail_box("Trip : eeprom write" );
				delay_msecs(100);
				return -1;
			}	 
			else{
			    code_inform.code_value = data.dword;
			    cmd = CMD_WRITE_RAM;
			    check = get_code_information( address,cmd, & code_inform);
			}
		}
    }
	return 0;
}
//--- end of code_proc.c
