#include	"header.h"
#include	"extern.h"

int get_code_information(int address,int cmd , CODE_INFO *  codes)
{	
    int returnValue=0;

	switch(address)
	{
    case CODE_motor_direction_change:
        strncpy(codes->disp, "motor_direction_change ON(1)/OFF",40);
        if( cmd == CMD_WRITE_RAM ) motor_direction_change = codes->code_value;
        set_code_default_int(0,1,0,motor_direction_change,0,codes);
        break;


    case CODE_accel_time1:
        strncpy(codes->disp, "accel_time1 (sec)",40);
        if( cmd == CMD_WRITE_RAM ) accel_time1 = (codes->code_value).floats;
        code_default_float(0.0,3000.0,5.0,accel_time1,0,codes);
        break;

    case CODE_decel_time1:
        strncpy(codes->disp, "decel_time1 (sec)",40);
        if( cmd == CMD_WRITE_RAM ) decel_time1 = (codes->code_value).floats;
        set_code_default_float(0.0,3000.0,5.0,decel_time1,0,codes);
        break;

    case CODE_motor_ctrl_mode:  //
        strncpy(codes->disp, "motor_ctrl_mode",40);
        if( cmd == CMD_WRITE_RAM ) motor_ctrl_mode = (codes->code_value).ints;
        set_code_default_int(0,7,0,motor_ctrl_mode,0,codes);
        break;

    case CODE_speed1:
		strncpy(codes->disp, "speed1 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_digital_speed2 = (codes->code_value).floats;
		set_code_default_float(0.0,0.9,0.25,code_digital_speed2,0,codes);
		break;

	case CODE_speed2:		
		strncpy(codes->disp, "speed2 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_speed2 = (codes->code_value).floats;
		set_code_default_float(0.0,1.2,0.25,code_speed2,0,codes);
		break;

    case CODE_motor_rate_power:
        strncpy(codes->disp, "motor_rate_power",40);
        if( cmd == CMD_WRITE_RAM ) motor_rate_power = (codes->code_value).floats;
        set_code_default_float(100,2.0e+6,3700,motor_rate_power,0,codes);
        break;

    case CODE_motor_rate_volt:
        strncpy(codes->disp, "motor_rate_volt (Vrms)",40);
        if( cmd == CMD_WRITE_RAM ) motor_rate_volt = (codes->code_value).floats;
        set_code_default_float(100.0,500.0,380.0,motor_rate_volt,0,codes);
        break;

    case CODE_motor_rate_current:
        strncpy(codes->disp, "motor_rate_current (A)",40);
        if( cmd == CMD_WRITE_RAM ) motor_rate_current = (codes->code_value).floats;
        set_code_default_float(1.0,2000.0,7.6,motor_rate_current,0,codes);
        break;

    case CODE_motor_rate_hz:
        strncpy(codes->disp, "motor_rate_hz (Hz)",40);
        if( cmd == CMD_WRITE_RAM ) motor_rate_hz = (codes->code_value).floats;
        set_code_default_float(30.0,120.0,60.0,motor_rate_hz,0,codes);
        break;

    case CODE_motor_rate_rpm:
        strncpy(codes->disp, "motor_rate_rpm",40);
        if( cmd == CMD_WRITE_RAM ) motor_rate_rpm = (codes->code_value).floats;
        set_code_default_float(500,8000.0,1750.0,motor_rate_rpm,0,codes);
        break;

    case CODE_motor_pole:
        strncpy(codes->disp, "motor_pole ",40);
        if( cmd == CMD_WRITE_RAM ) motor_pole = (codes->code_value).ints;
        set_code_default_int(2,20,4,motor_pole,0,codes);
        break;

    case CODE_motor_rate_effiency:
        strncpy(codes->disp, "motor_rate_effiency (p.u)",40);
        if( cmd == CMD_WRITE_RAM ) motor_rate_effiency = (codes->code_value).floats;
        set_code_default_float(0.2,0.99,0.875,motor_rate_effiency,0,codes);
        break;

    case CODE_protect_inhibit_on:
        strncpy(codes->disp, "protect_inhibit_on[1]",40);
        if( cmd == CMD_WRITE_RAM ) code_protect_inhibit_on = (codes->code_value).ints;
        set_code_default_int(0,1,0,code_protect_inhibit_on,0,codes);
        break;

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
	int i,j,check;
	int loop_control,address,cmd,return_value;
	
	data.dword  = 0.0;

	address = return_value = 0;	// start of address

	cmd = CMD_READ_DATA;
	address = 0;

	loop_control =  1;

	while( loop_control )	
	{
		for( i = 0 ; i <= 7 ; i++){	 // code group �� 6�� 
			for( j = 0; j <= 50 ;j++)
			{
				address = i * 100 + j ;
				check = get_code_information( address, cmd , & code_inform);
				if( !check ){
					
					// debug  address �� ��ũ�� �����ϴ� ����� �߰��� �� 
					// 2009.08.30
					Flag_TripDataBackup = 1;
					read_eprom_data( address, & data);
					Flag_TripDataBackup = 0;
					check = check_code_data(address, data );	// check min and max boundary
					if(check){
						loop_control = 0;
						return_value = -1;
					}
				}
			}
		}
		loop_control =  0;
	}
	return return_value;
}


void save_backup_data()
{
	UNION32	data;
	int i,j,check;
	int address,cmd;
	
	data.dword  = 0.0;

	address = 0;	// start of address

	cmd = CMD_READ_DATA;
	address = 0;

	for( i = 0 ; i <= 7 ; i++){	 // code group �� 6�� 
		for( j = 0; j <= 29 ;j++)
		{
			address = i* 100 +j ;
			check = get_code_information( address, cmd , & code_inform);
			if( !check ){
				read_eprom_data( address, & data);
				Flag_TripDataBackup = 1;
				write_code_2_eeprom( address,data);
				Flag_TripDataBackup = 0;
			}
		}
	}
}
// address 1000�� ���Ѵ�.  


void backup_data_load()
{
	UNION32	data;
	int i,j,check;
	int loop_control,address,cmd;
	
	data.dword  = 0.0;

	address = 0;	// start of address

	cmd = CMD_READ_DATA;
	address = 0;
	loop_control =  1;
	while( loop_control )	
	{
		for( i = 0 ; i <= 7 ; i++){	 // code group �� 6�� 

			for( j = 0; j <= 29 ;j++)
			{
				address = i * 100 + j ;
				check = get_code_information( address, cmd , & code_inform);
				if( !check ){
					Flag_TripDataBackup = 1;
					read_eprom_data( address, & data);
					Flag_TripDataBackup = 0;
					write_code_2_eeprom( address,data);

					if( code_inform.type == TYPE_FLOAT)
						code_inform.code_value.floats = data.dword;
					else
						code_inform.code_value.ints = data.word.word0;

					cmd = CMD_WRITE_RAM;
					check = get_code_information( address,cmd, & code_inform);
				}
			}
		}
		loop_control = 0;
	}
}

float CheckSum()
{
	return 0.0;
}
float CheckSum_bk()
{
	UNION32	data;
	UNION32	data2;
	int i,j,check;
	int address,cmd;
	
	data.dword  = 0.0;
	data2.dword  = 0.0;

	address = 0;	// start of address

	cmd = CMD_READ_DATA;

	for( i = 0 ; i <= 7 ; i++){
		for( j = 0; j <= 29 ;j++)
		{
			address = i* 100 +j ;
			check = get_code_information( address, cmd , & code_inform);
			if( !check ){
				read_eprom_data( address, & data);
				data2.dword = data2.dword + data.dword;
			}
		}
	}
	return data2.dword;
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
		case CODE_get_adc_offset:	get_adc_offset();	break;
		case CODE_get_adc_vdc_low:	get_adc_vdc_low();	break;
		case CODE_get_adc_vdc_high:	get_adc_vdc_high();	break;
		default:
			goto _SAVE_ERROR_INVALID_ADDR;
		}
		return return_value;
	}

	if( code_inform.type == TYPE_INTEGER){
		if( (code_inform.code_min.ints)  > (int)data ){
			goto _SAVE_ERROR_DATA_UNDER;
		}
		else if( (code_inform.code_max.ints) < (int)data){
			goto _SAVE_ERROR_DATA_OVER;
		}
		else {
//			u32data.word.word1 = 0;
			u32data.word.word0 = (int)data;
			read_eprom_data( addr, & u32data2);
			if( u32data.word.word0 != u32data2.word.word0 ){
				write_code_2_eeprom( addr, u32data);
				read_eprom_data( addr, & u32data2);				
				if( u32data.word.word0 != u32data2.word.word0 ) goto _EEPROM_WRITE_ERROR;
				code_inform.code_value.ints = (int)data;
				cmd = CMD_WRITE_RAM;
				get_code_information( addr,cmd, & code_inform);

				load_sci_tx_mail_box("OK write success") ;
			}
			else{
				load_sci_tx_mail_box("Equal Data write skipped");
			}
			return 0;
		}	 
	}	
	else {		//  code_inform->Type == TYPE_float
		if( ( code_inform.code_min.floats) > data ){
			goto _SAVE_ERROR_DATA_UNDER;
		}
		else if( ( code_inform.code_max.float) < data ){
			goto _SAVE_ERROR_DATA_OVER;
		}			
		else {
			u32data.dword = data;
			read_eprom_data( addr, & u32data2);
			if( u32data.dword != u32data2.dword ){
				write_code_2_eeprom( addr, u32data);
				read_eprom_data( addr, & u32data2);

				if( u32data.dword != u32data2.dword ) goto _EEPROM_WRITE_ERROR;

				code_inform.code_value.float = data;
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
	int check;
	int address,cmd;
	int return_value;

	data.dword  = 0.0;

	cmd = CMD_READ_DATA;
	address = return_value = 0;
	
	for( address = 0 ; address < CODE_END ; address++ )
		cmd = CMD_READ_DATA;
		check = get_code_information( address, cmd , & code_inform);

		if( check==0 ){
			data.dword = code_inform.code_default;
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword)	write_code_2_eeprom( address,data);
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword)
			{
				return_value = -1;
				load_sci_tx_mail_box("Trip : eeprom write" );
				delay_msecs(100);
				break;
			}	 
			code_inform.code_value = data.dword;
			cmd = CMD_WRITE_RAM;
			check = get_code_information( address,cmd, & code_inform);
		}
		else address ++; 		
	}
	return return_value;
}
//--- end of code_proc.c
