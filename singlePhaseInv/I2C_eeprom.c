//
// FILE:    I2c_eeprom.c
// Project : singlePhase inverter
// ASSUMPTIONS:
//    This program requires an external I2C EEPROM connected to
//    the I2C bus at address 0x51.
//

#include	<header.h>
#include	<extern.h>

void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CSAR = I2C_EEPROM_SLAVE_ADDR;		// Slave address - EEPROM control code

	I2caRegs.I2CPSC.all = 6;	    // Prescaler - need 7-12 Mhz on module clk (75M/750 = 0.1MHz)

//   I2caRegs.I2CCLKL = 5;			// NOTE: must be non zero
//   I2caRegs.I2CCLKH = 3;			// NOTE: must be non zero
   I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero

	I2caRegs.I2CIER.all = 0x0;		// disable all i2c irq 2008.05.11

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
   									// Stop I2C when suspended
   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,
}

Uint16 I2CA_WriteData(int iSlaveAddr,int iMemAddr,int iData)
{
    int i;
    BACKUP_ENABLE;
    DSP28x_usDelay(50);
    I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
	I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;	 
	I2caRegs.I2CCNT = 3;
    I2caRegs.I2CSAR = iSlaveAddr;
  	I2caRegs.I2CDXR = (iMemAddr >> 8) & 0x00ff;
  	I2caRegs.I2CDXR = iMemAddr & 0x00ff;
	I2caRegs.I2CDXR = iData;		// byte write
  	I2caRegs.I2CMDR.all = 0x6E20;			
	for( i =0 ; i < 20 ; i ++ ){
	    DSP28x_usDelay(1000);
	}
//	while(I2caRegs.I2CSTR.bit.SCD == 0); 
	BACKUP_DISABLE;
	return I2C_SUCCESS;
}

Uint16 I2CA_ReadData(int iSlaveAddr, int iMemAddr, int * data)
{
    int i;
    I2caRegs.I2CSAR = iSlaveAddr;
   I2caRegs.I2CCNT = 2;
   I2caRegs.I2CDXR = (iMemAddr>>8) & 0x00ff;
   I2caRegs.I2CDXR = iMemAddr & 0x00ff;
//   I2caRegs.I2CMDR.all = 0x6620;			
   I2caRegs.I2CMDR.all = 0x2620;			
    for( i =0 ; i < 20 ; i ++ ){
        DSP28x_usDelay(1000);
    }
	// 
//	while(I2caRegs.I2CSTR.bit.ARDY == 0);  // test jsk 

	I2caRegs.I2CFFRX.bit.RXFFRST = 0;		// RXFIFO Operation disable	 
	I2caRegs.I2CFFRX.bit.RXFFINT = 1;		// RXFIFO Operation disable	 

   I2caRegs.I2CSAR = iSlaveAddr;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CMDR.all = 0x6C20;			// Send restart as master receiver stop

   for( i =0 ; i < 20 ; i ++ ){
       DSP28x_usDelay(1000);
   }
//	while(I2caRegs.I2CSTR.bit.SCD == 0);  // test jsk
	
 	* data = I2caRegs.I2CDRR;
 	return I2C_SUCCESS;
}

int get_eprom_address( int code_address)
{
	return code_address % 100 * 4;
}		

void write_code_2_eeprom(int address,UNION32 data)
{
	int eprom_addr;

	eprom_addr = get_eprom_address(address);

	I2CA_WriteData(ADDR_24LC32,eprom_addr+0,data.byte.byte0);
	I2CA_WriteData(ADDR_24LC32,eprom_addr+1,data.byte.byte1);
	I2CA_WriteData(ADDR_24LC32,eprom_addr+2,data.byte.byte2);
	I2CA_WriteData(ADDR_24LC32,eprom_addr+3,data.byte.byte3);
}

void read_eprom_data(int address, UNION32 * u32data)
{
	int eprom_addr,iTemp;

	eprom_addr = get_eprom_address(address);
	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+0,&iTemp); (u32data->byte).byte0 = iTemp;	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+1,&iTemp); (u32data->byte).byte1 = iTemp;	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+2,&iTemp); (u32data->byte).byte2 = iTemp;	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+3,&iTemp); (u32data->byte).byte3 = iTemp;	
}

void data_under_proc(int address,int type, UNION32 u32data)
{
	int trip_code;
	double trip_data;
	
	trip_code = address;

	if(type ==TYPE_INTEGER) trip_data = (double) u32data.word.word0;
	else					trip_data = u32data.dword;

	trip_recording( trip_code, trip_data,"Data Under");
}

void data_over_proc(int address,int type, UNION32 u32data)
{
	int trip_code;
	double trip_data;
	
	trip_code = address;

	if(type ==TYPE_INTEGER) trip_data = (double) u32data.word.word0;
	else					trip_data = u32data.dword;

	trip_recording( trip_code, trip_data,"Data Over");
}

void invalid_address_proc(int address )
{
	int trip_code;
	double trip_data;
	
	trip_code = address;
	trip_data = 0.0;
	trip_recording( trip_code, trip_data,"Invalid Address");
}

int check_code_data(int address, UNION32 u32data )
{
	int cmd,check,return_value;

	cmd = CMD_READ_DATA;

	check = get_code_information( address, cmd , & code_inform);
	if( check){
		invalid_address_proc( address );
		return -1;
	}

	if( code_inform.type == TYPE_INTEGER){
		if( (( code_inform.code_min).ints) > u32data.word.word0 ){
			data_under_proc(address, TYPE_INTEGER, u32data);	
			return_value = -1;
		}
		else if( (code_inform.code_max.ints) < u32data.word.word0 ){
			data_over_proc(address, TYPE_INTEGER, u32data);	
			return_value = -1;
		}			
		else {
			code_inform.code_value.ints = u32data.word.word0;
			cmd = CMD_WRITE_RAM;
			check =  get_code_information( address,cmd, & code_inform);
			return_value = 0;
		}	 
	}	
	else {		//  code_inform->Type == TYPE_DOUBLE
		if( ( code_inform.code_min.doubles) > u32data.dword ){
			data_under_proc(address, TYPE_DOUBLE, u32data);	
			return_value = -1;
		}
		else if( ( code_inform.code_max.doubles) < u32data.dword ){
			data_over_proc(address, TYPE_DOUBLE, u32data);	
			return_value = -1;
		}			
		else {
			code_inform.code_value.doubles = u32data.dword;
			cmd = CMD_WRITE_RAM;
			check =  get_code_information( address,cmd, & code_inform);
			return_value = 0;
		}	 
	}	
	return return_value;   
}

int load_code2ram()
{
	UNION32	data;
	int i,j,check;
	int loop_control,address,cmd,return_value;
	
	data.dword  = 0.0;

	address = return_value = 0;	// start of address

	loop_control =  1;
	while( loop_control )	
	{
		cmd = CMD_READ_DATA;
		address = 0;
		for( i = 0 ; i <= CODE_END ; i++){

			for( j = 0; j <= code_group_length[i];j++)
			{
				check = get_code_information( address, cmd , & code_inform);
				if( !check ){
					read_eprom_data( address, & data);
					check = check_code_data(address, data);	// check min and max boundary
					if(check){
						loop_control = 0;
						return_value = -1;
					}
					else{
						if(( code_inform.type)==TYPE_INTEGER) code_inform.code_value.ints = data.word.word0;
						else  							 	  code_inform.code_value.doubles = data.dword;
						
						cmd = CMD_WRITE_RAM;
						check = get_code_information( address,cmd, & code_inform);
					}
				}
				address++;
			}
			address = i*100;
		}
	}
	return return_value;
}

int code_init()
{
	UNION32 datum;

	int i, j,check, cmd, address;
 
	cmd = CMD_READ_DATA;

	address = 0;
	for( i = 0 ; i <= 26 ; i++){	 

		for( j = 0; j <= code_group_length[i];j++){
			check = get_code_information( address, cmd , & code_inform);
			if( !check ){

				if( code_inform.type == TYPE_INTEGER)	datum.word.word0 = code_inform.code_value.ints;
				else									datum.dword 	 = code_inform.code_value.doubles;
				write_code_2_eeprom(address, datum);
			}	 		
			address ++;
		}	
		address = i * 100;
	}
	check = load_code2ram();
	return check;
}		

//===========================================================================
// No more.
//===========================================================================
