//**************************************************************************
//
// FILE:    DS1307.c
//
// TITLE:   Eunwho Inverter 
//
// ASSUMPTIONS:
//
//    This program requires an external I2C EEPROM connected to
//    the I2C bus at address 0x51.
//**************************************************************************
#include	<header.h>
#include	<extern.h>

#define 	ADDR_DS1307			0x0068
#define DS1307_RW_DELAY		5
void DS1307WriteData(int iMemAddr,int iData)
{
	I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset

	I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;	 
	I2caRegs.I2CCNT = 2;
   I2caRegs.I2CSAR = ADDR_DS1307;					// DS1307 Slave Address 
  	I2caRegs.I2CDXR = iMemAddr & 0x00ff;	// 하위 바이트 
	I2caRegs.I2CDXR = iData;		// byte write 만 된다. 
  	I2caRegs.I2CMDR.all = 0x6E20;			
	Nop();
	Nop();

	delay_msecs(DS1307_RW_DELAY);
	Nop();
	Nop();
	while(I2caRegs.I2CSTR.bit.SCD == 0); 
}

void DS1307ReadData(int iMemAddr, int * data)
{
	// no stop 
   I2caRegs.I2CSAR = ADDR_DS1307;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CDXR = iMemAddr & 0x00ff;
   I2caRegs.I2CMDR.all = 0x6620;			
	Nop();
	delay_msecs(DS1307_RW_DELAY);

//	while(I2caRegs.I2CSTR.bit.ARDY == 0);    // jsk

	I2caRegs.I2CFFRX.bit.RXFFRST = 0;		// RXFIFO Operation disable	 
//	I2caRegs.I2CFFRX.bit.RXFFINT = 1;		// RXFIFO Operation disable	 
	I2caRegs.I2CFFRX.bit.RXFFINT = 0;		// RXFIFO Operation disable	 

   I2caRegs.I2CSAR = ADDR_DS1307;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CMDR.all = 0x6C20;			// Send restart as master receiver stop
	delay_msecs(DS1307_RW_DELAY);
	while(I2caRegs.I2CSTR.bit.SCD == 0); 
 	* data = I2caRegs.I2CDRR;
}

void GetTimeAndDateStr(char * StrIn)
{
	int Temp;
	char str[25];

	str[ 0] = '2';
	str[ 1] = '0';

// year
	DS1307ReadData(6, &Temp);
	str[ 2] =((Temp>>4) & 0x000f) + '0';
	str[ 3] =((Temp	) & 0x000f) + '0';
	str[ 4] = ':';

// month
	DS1307ReadData(5, &Temp);
	str[ 5] =((Temp>>4) & 0x0001) + '0';
	str[ 6] =((Temp	) & 0x000f) + '0';
	str[ 7] = ':';

// date
	DS1307ReadData(4, &Temp);
	str[ 8] =((Temp>>4) & 0x0003) + '0';
	str[ 9] =((Temp	) & 0x000f) + '0';

	str[10] = ' ';
	str[11] = ' ';

// hour
	DS1307ReadData(2, &Temp);
	str[12] =((Temp>>4) & 0x0003) + '0';
	str[13] =((Temp	) & 0x000f) + '0';
	str[14] = ':';

// minute
	DS1307ReadData(1, &Temp);
	str[15] =((Temp>>4) & 0x0007) + '0';
	str[16] =((Temp	) & 0x000f) + '0';
	str[17] = ':';

// seccond
	DS1307ReadData(0, &Temp);
	str[18] =((Temp>>4) & 0x0007) + '0';
	str[19] =((Temp   ) & 0x000f) + '0';

	str[20] = '\0';

	strncpy(StrIn, str, 20);
	Nop();

}

// "012345678901");
// "YYMMDDHHMMSS");

#define 	ADDR_YEAR	6
#define 	ADDR_MONTH	5
#define 	ADDR_DATE	4
#define 	ADDR_HOUR	2
#define 	ADDR_MIN		1
#define 	ADDR_SEC		0

void WriteTimeToDS1307(char * str )
 {
	int Temp;

// year
	Temp = ( *(str+0) - '0')*16 + ( *(str+1) - '0'); 
	DS1307WriteData(ADDR_YEAR,Temp);	

// month
	Temp = ( *(str+2) - '0')*16 + (*(str+3) - '0'); 
	DS1307WriteData(ADDR_MONTH,Temp);

// date
	Temp = (*(str+4) - '0')*16 + (*(str+5) - '0'); 
	DS1307WriteData(ADDR_DATE,Temp);

// hour
	Temp = (*(str+6) - '0')*16 + (*(str+7) - '0'); 
	DS1307WriteData(ADDR_HOUR,Temp);

// min
	Temp = (*(str+8) - '0')*16 + (*(str+9) - '0'); 
	DS1307WriteData(ADDR_MIN,Temp);

// sec
	Temp = (*(str+10) - '0')*16 + (*(str+11) - '0'); 
	DS1307WriteData(ADDR_SEC,Temp);
}

//===========================================================================
// No more.
//===========================================================================

