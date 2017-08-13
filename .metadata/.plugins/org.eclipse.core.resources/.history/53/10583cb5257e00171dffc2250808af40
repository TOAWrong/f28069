// EwInv File $Revision: /main/2 $
// Checkin $Date: July 06, 2009   21:50:** $
//###########################################################################
//
// FILE:	EwInvF283X_Gpio.c
//
// Project:	EwInv F28335 _090706
// TITLE:	DSP280x General Purpose I/O Initialization & Support Functions.
//

#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

void InitGpio(void)
{
		EALLOW;

	//--------------------------------------------------------------------
	//		GPIO INIT FOR PWM
	//--------------------------------------------------------------------

	// Enable PWM1A				// UT
	GpioCtrlRegs.GPAPUD.bit.GPIO0		= 1;	// Enable pullup on GPIO0
	GpioDataRegs.GPACLEAR.bit.GPIO0		= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO0		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO0		= 0;	// GPIO0 = PWM1A

	// Enable PWM1B				// UB
	GpioCtrlRegs.GPAPUD.bit.GPIO1 		= 1;	// Enable pullup on GPIO1
	GpioDataRegs.GPACLEAR.bit.GPIO1 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO1 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 		= 0;	// GPIO0 = PWM1B

	// Enable PWM2A				// VT
	GpioCtrlRegs.GPAPUD.bit.GPIO2 		= 1;	// Enable pullup on GPIO2
	GpioDataRegs.GPACLEAR.bit.GPIO2 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO2 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 		= 0;	// GPIO0 = PWM2A

	// Enable PWM2B				// VB
	GpioCtrlRegs.GPAPUD.bit.GPIO3 		= 1;	// Enable pullup on GPIO3
	GpioDataRegs.GPACLEAR.bit.GPIO3 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO3 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 		= 0;	// GPIO0 = PWM2B

	// Enable PWM3A				// WT
	GpioCtrlRegs.GPAPUD.bit.GPIO4 		= 1;	// Enable pullup on GPIO4
	GpioDataRegs.GPACLEAR.bit.GPIO4 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO4 		= 1;	// GPIO0 = Outpu3
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 		= 0;	// GPIO0 = PWM3A

	// Enable PWM3B				// WB
	GpioCtrlRegs.GPAPUD.bit.GPIO5 		= 1;	// Enable pullup on GPIO5
	GpioDataRegs.GPACLEAR.bit.GPIO5 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO5 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 		= 0;	// GPIO0 = PWM3B

	// Enable PWM4A				// PWM_R+
	GpioCtrlRegs.GPAPUD.bit.GPIO6 		= 1;	// Enable pullup on GPIO0
	GpioDataRegs.GPACLEAR.bit.GPIO6 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO6 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 		= 0;	// GPIO0 = PWM4A

	// Enable PWM4B				// PWM_R-
	GpioCtrlRegs.GPAPUD.bit.GPIO7 		= 1;	// Enable pullup on GPIO1
	GpioDataRegs.GPACLEAR.bit.GPIO7 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO7 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 		= 0;	// GPIO0 = PWM4B

	// Enable PWM5A				// PWM_S+
	GpioCtrlRegs.GPAPUD.bit.GPIO8 		= 1;	// Enable pullup on GPIO2
	GpioDataRegs.GPACLEAR.bit.GPIO8 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO8 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 		= 0;	// GPIO0 = PWM5A

	// Enable PWM5B				// PWM_S-
	GpioCtrlRegs.GPAPUD.bit.GPIO9 		= 1;	// Enable pullup on GPIO3
	GpioDataRegs.GPACLEAR.bit.GPIO9 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO9 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 		= 0;	// GPIO0 = PWM5B

	// Enable PWM6A				// PWM_T+
	GpioCtrlRegs.GPAPUD.bit.GPIO10 		= 1;	// Enable pullup on GPIO4
	GpioDataRegs.GPACLEAR.bit.GPIO10 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO10 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO10		= 0;	// GPIO0 = PWM6A

	// Enable PWM6B				// PWM_T-
	GpioCtrlRegs.GPAPUD.bit.GPIO11 		= 1;	// Enable pullup on GPIO5
	GpioDataRegs.GPACLEAR.bit.GPIO11 	= 1;	// Set Output
	GpioCtrlRegs.GPADIR.bit.GPIO11 		= 1;	// GPIO0 = Output
	GpioCtrlRegs.GPAMUX1.bit.GPIO11		= 0;	// GPIO0 = PWM6B

	//--------------------------------------------------------------------
	//		RST.DRIVER
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPAPUD.bit.GPIO12		= 1;	// Enable pullup on GPIO12
	GpioCtrlRegs.GPAMUX1.bit.GPIO12		= 0;	// GPIO12 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO12		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		INIT CHARGE
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPAPUD.bit.GPIO13		= 1;	// Enable pullup on GPIO13
	GpioCtrlRegs.GPAMUX1.bit.GPIO13		= 0;	// GPIO13 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO13		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 MAIN CHARGE
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPAPUD.bit.GPIO14		= 1;	// Enable pullup on GPIO14
	GpioCtrlRegs.GPAMUX1.bit.GPIO14		= 0;	// GPIO14 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO14		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 OPT-GPIO
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPAPUD.bit.GPIO15		= 1;	// Enable pullup on GPIO15
	GpioCtrlRegs.GPAMUX1.bit.GPIO15		= 0;	// GPIO15 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO15		= 1;	// OUTPUT

	GpioCtrlRegs.GPAPUD.bit.GPIO16		= 1;	// Enable pullup on GPIO16
	GpioCtrlRegs.GPAMUX2.bit.GPIO16		= 0;	// GPIO16 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO16		= 1;	// OUTPUT

	GpioCtrlRegs.GPAPUD.bit.GPIO17		= 1;	// Enable pullup on GPIO17
	GpioCtrlRegs.GPAMUX2.bit.GPIO17		= 0;	// GPIO17 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO17		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 SERIAL PORT SET
	//--------------------------------------------------------------------
	// GPIO18 = SCITXB
	GpioCtrlRegs.GPAPUD.bit.GPIO18 		= 1;	// Enable pullup on GPIO18     
	GpioCtrlRegs.GPAMUX2.bit.GPIO18		= 2;	// GPIO18 = SCITXB
 
	// GPIO19 = SCIRXDB
	GpioCtrlRegs.GPAPUD.bit.GPIO19		= 0;	// Disable pullup on GPIO19     
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19	= 3;	// Asynch Input         
	GpioCtrlRegs.GPAMUX2.bit.GPIO19		= 2;	// GPIO19 = SCIRXB

//---
/*
	//-------------------------------------------------------------------
	//		EQEP1
	//-------------------------------------------------------------------
	// GPIO20 EQEP1A
	GpioCtrlRegs.GPAQSEL2.bit.GPIO20	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO20		= 1;	// EQEP1A
	GpioCtrlRegs.GPADIR.bit.GPIO20		= 0;	// INPUT

	// GPIO21 EQEP1B
	GpioCtrlRegs.GPAQSEL2.bit.GPIO21 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 	= 1;	// EQEP1B
	GpioCtrlRegs.GPADIR.bit.GPIO21 		= 0;	// INPUT

	// GPIO22 EQEP1S
	GpioCtrlRegs.GPAQSEL2.bit.GPIO22 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 	= 1;	// EQEP1S
	GpioCtrlRegs.GPADIR.bit.GPIO22 		= 0;	// Input

	// GPIO23 EQEP1I
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 	= 1;	// EQEP1I
	GpioCtrlRegs.GPADIR.bit.GPIO23 		= 0;	// Input

	//-------------------------------------------------------------------
	//		EQEP2
	//-------------------------------------------------------------------
	// GPIO24 EQEP2A
	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 	= 2;	// EQEP2A
	GpioCtrlRegs.GPADIR.bit.GPIO24 		= 0;	// INPUT

	// GPIO25 EQEP2B
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 	= 2;	// EQEP2B
	GpioCtrlRegs.GPADIR.bit.GPIO25 		= 0;	// INPUT

	// GPIO26 EQEP2I
	GpioCtrlRegs.GPAQSEL2.bit.GPIO26	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 	= 2;	// EQEP2I
	GpioCtrlRegs.GPADIR.bit.GPIO26 		= 0;	// INPUT

	// GPIO27 EQEP2S
	GpioCtrlRegs.GPAQSEL2.bit.GPIO27	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 	= 2;	// EQEP2S
	GpioCtrlRegs.GPADIR.bit.GPIO27 		= 0;	// INPUT
*/

	//-------------------------------------------------------------------
	//		EQEP1
	//-------------------------------------------------------------------
	// GPIO20 EQEP1A
	GpioCtrlRegs.GPAQSEL2.bit.GPIO20	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO20		= 0;	// EQEP1A
	GpioCtrlRegs.GPADIR.bit.GPIO20		= 0;	// INPUT

	// GPIO21 EQEP1B
	GpioCtrlRegs.GPAQSEL2.bit.GPIO21 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 	= 0;	// EQEP1B
	GpioCtrlRegs.GPADIR.bit.GPIO21 		= 0;	// INPUT

	// GPIO22 EQEP1S
	GpioCtrlRegs.GPAQSEL2.bit.GPIO22 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 	= 0;	// EQEP1S
	GpioCtrlRegs.GPADIR.bit.GPIO22 		= 0;	// Input

	// GPIO23 EQEP1I
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 	= 0;	// EQEP1I
	GpioCtrlRegs.GPADIR.bit.GPIO23 		= 0;	// Input

	//-------------------------------------------------------------------
	//		EQEP2
	//-------------------------------------------------------------------
	// GPIO24 EQEP2A
	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 	= 0;	// EQEP2A
	GpioCtrlRegs.GPADIR.bit.GPIO24 		= 0;	// INPUT

	// GPIO25 EQEP2B
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 	= 0;	// EQEP2B
	GpioCtrlRegs.GPADIR.bit.GPIO25 		= 0;	// INPUT

	// GPIO26 EQEP2I
	GpioCtrlRegs.GPAQSEL2.bit.GPIO26	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 	= 0;	// EQEP2I
	GpioCtrlRegs.GPADIR.bit.GPIO26 		= 0;	// INPUT

	// GPIO27 EQEP2S
	GpioCtrlRegs.GPAQSEL2.bit.GPIO27	= 1;	// using 3 Sample
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 	= 0;	// EQEP2S
	GpioCtrlRegs.GPADIR.bit.GPIO27 		= 0;	// INPUT

//--- endcoder test end 2011.1124

	//--------------------------------------------------------------------
	//		 OPT-GPIO
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPAPUD.bit.GPIO28		= 1;	// Enable pullup on GPIO28
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 	= 0;	// GPIO28 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO28		= 1;	// OUTPUT

	GpioCtrlRegs.GPAPUD.bit.GPIO29		= 1;	// Enable pullup on GPIO29
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 	= 0;	// GPIO29 = GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO29		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 CAN
	//--------------------------------------------------------------------
	// GPIO30 CANRXA
	GpioCtrlRegs.GPAMUX2.bit.GPIO30		= 1;	// CANRXA
	GpioCtrlRegs.GPADIR.bit.GPIO30		= 0;	// INPUT

	// GPIO31 CANTXA
	GpioCtrlRegs.GPAMUX2.bit.GPIO31		= 1;	// CANTXA
	GpioCtrlRegs.GPADIR.bit.GPIO31		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		I2C
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBQSEL1.bit.GPIO32	= 1;	// Asynch Input                        
	GpioCtrlRegs.GPBMUX1.bit.GPIO32		= 1;	// GPIO32 = I2C_SDAA

	GpioCtrlRegs.GPBQSEL1.bit.GPIO33	= 1;	// Asynch Input               
	GpioCtrlRegs.GPBMUX1.bit.GPIO33		= 1;	// GPIO33 = I2C_SCLA

	//--------------------------------------------------------------------
	//		No Connect
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 	= 2;	// XREADY

	//--------------------------------------------------------------------
	//		XR/W
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 	= 2;	// XR/W
	GpioCtrlRegs.GPBDIR.bit.GPIO35 		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		XZCS0
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 	= 3;	// /XZCS0
	GpioCtrlRegs.GPBDIR.bit.GPIO36 		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		XZCS7
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO37 	= 3;	// /XZCS7
	GpioCtrlRegs.GPBDIR.bit.GPIO37 		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		XWE0
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO38 	= 3;	// /XWE0
	GpioCtrlRegs.GPBDIR.bit.GPIO38 		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 OPT-GPIO
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 	= 0;	// GPIO39 = GPIO 
	GpioCtrlRegs.GPBDIR.bit.GPIO39		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 External Address Bus
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX1.bit.GPIO40		= 3;	// XA0/XWE1n
	GpioCtrlRegs.GPBMUX1.bit.GPIO41		= 3;	// XA1
	GpioCtrlRegs.GPBMUX1.bit.GPIO42		= 3;	// XA2
	GpioCtrlRegs.GPBMUX1.bit.GPIO43		= 3;	// XA3
	GpioCtrlRegs.GPBMUX1.bit.GPIO44		= 3;	// XA4
	GpioCtrlRegs.GPBMUX1.bit.GPIO45		= 3;	// XA5
	GpioCtrlRegs.GPBMUX1.bit.GPIO46		= 3;	// XA6
	GpioCtrlRegs.GPBMUX1.bit.GPIO47 	= 3;	// XA7
	GpioCtrlRegs.GPCMUX2.bit.GPIO80 	= 3;	// XA8
	GpioCtrlRegs.GPCMUX2.bit.GPIO81 	= 3;	// XA9
	GpioCtrlRegs.GPCMUX2.bit.GPIO82 	= 3;	// XA10
	GpioCtrlRegs.GPCMUX2.bit.GPIO83 	= 3;	// XA11
	GpioCtrlRegs.GPCMUX2.bit.GPIO84 	= 3;	// XA12
	GpioCtrlRegs.GPCMUX2.bit.GPIO85 	= 3;	// XA13
	GpioCtrlRegs.GPCMUX2.bit.GPIO86 	= 3;	// XA14
	GpioCtrlRegs.GPCMUX2.bit.GPIO87 	= 3;	// XA15

	GpioCtrlRegs.GPCMUX1.bit.GPIO64 	= 3;	// XD15
	GpioCtrlRegs.GPCMUX1.bit.GPIO65 	= 3;	// XD14
	GpioCtrlRegs.GPCMUX1.bit.GPIO66 	= 3;	// XD13
	GpioCtrlRegs.GPCMUX1.bit.GPIO67 	= 3;	// XD12
	GpioCtrlRegs.GPCMUX1.bit.GPIO68 	= 3;	// XD11
	GpioCtrlRegs.GPCMUX1.bit.GPIO69 	= 3;	// XD10
	GpioCtrlRegs.GPCMUX1.bit.GPIO70 	= 3;	// XD19
	GpioCtrlRegs.GPCMUX1.bit.GPIO71 	= 3;	// XD8
	GpioCtrlRegs.GPCMUX1.bit.GPIO72 	= 3;	// XD7
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 	= 3;	// XD6
	GpioCtrlRegs.GPCMUX1.bit.GPIO74 	= 3;	// XD5
	GpioCtrlRegs.GPCMUX1.bit.GPIO75 	= 3;	// XD4
	GpioCtrlRegs.GPCMUX1.bit.GPIO76 	= 3;	// XD3
	GpioCtrlRegs.GPCMUX1.bit.GPIO77 	= 3;	// XD2
	GpioCtrlRegs.GPCMUX1.bit.GPIO78 	= 3;	// XD1
	GpioCtrlRegs.GPCMUX1.bit.GPIO79 	= 3;	// XD0

	//--------------------------------------------------------------------
	//		 I_OUT
	//--------------------------------------------------------------------
	// A01
	GpioCtrlRegs.GPBMUX2.bit.GPIO48 	= 0;	// GPIO48 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO48		= 1;	// OUTPUT

	// A02
	GpioCtrlRegs.GPBMUX2.bit.GPIO49 	= 0;	// GPIO49 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO49		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 24LC32_PROTECT
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX2.bit.GPIO50 	= 0;	// GPIO50 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO50		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 OPT-GPIO
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX2.bit.GPIO51 	= 0;	// GPIO51 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO51		= 1;	// OUTPUT 

	GpioCtrlRegs.GPBMUX2.bit.GPIO52 	= 0;	// GPIO52 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO52		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 RS485_TX_ENABLE
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX2.bit.GPIO53 	= 0;	// GPIO53 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO53		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 SPI
	//--------------------------------------------------------------------
	// GPIO54 SPISIMOA
	GpioCtrlRegs.GPBMUX2.bit.GPIO54 	= 1;	// SPI-A Slave In Mast Out  
	GpioCtrlRegs.GPBDIR.bit.GPIO54 		= 1;	// OUTPUT

	// GPIO55 SPISOMIA
	GpioCtrlRegs.GPBMUX2.bit.GPIO55 	= 1;	// SPI-A Slave Out Mast In 

	// GPIO56 SPICLKA
	GpioCtrlRegs.GPBMUX2.bit.GPIO56 	= 1;	// SPI-A clock  
	GpioCtrlRegs.GPBDIR.bit.GPIO56 		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		 OPT-GPIO
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 	= 0;	// GPIO57 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO57 		= 1;	// OUTPUT

	GpioCtrlRegs.GPBMUX2.bit.GPIO58 	= 0;	// GPIO58 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO58 		= 1;	// OUTPUT

	GpioCtrlRegs.GPBMUX2.bit.GPIO59 	= 0;	// GPIO59 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO59 		= 1;	// OUTPUT

	//--------------------------------------------------------------------
	//		  EX_OUT_RELAY
	//--------------------------------------------------------------------
	GpioDataRegs.GPBCLEAR.bit.GPIO60	= 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO60 	= 0;	// GPIO57 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO60 		= 1;	// OUTPUT // EX_OUT_RELAY0

	GpioDataRegs.GPBCLEAR.bit.GPIO61	= 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 	= 0;	// GPIO57 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO61 		= 1;	// OUTPUT // EX_OUT_RELAY1

	//--------------------------------------------------------------------
	//		  OPTION_SCI
	//--------------------------------------------------------------------
	GpioCtrlRegs.GPBMUX2.bit.GPIO62 	= 1;	// GPIO62 OPTION_SCI_RXD_C

	GpioCtrlRegs.GPBMUX2.bit.GPIO63 	= 1;	// GPIO62 OPTION_SCI_RXD_C
	GpioCtrlRegs.GPBDIR.bit.GPIO63		= 1; 


	EDIS;  
}
void InitXintf(void)
{
    // This shows how to write to the XINTF registers.  The
    // values used here are the default state after reset.
    // Different hardware will require a different configuration.

    // For an example of an XINTF configuration used with the
    // F28335 eZdsp, refer to the examples/run_from_xintf project.

    // Any changes to XINTF timing should only be made by code
    // running outside of the XINTF.

    // All Zones---------------------------------
    // Timing for all zones based on XTIMCLK = 1/2 SYSCLKOUT
    EALLOW;
    XintfRegs.XINTCNF2.bit.XTIMCLK = 1;
    // No write buffering
    XintfRegs.XINTCNF2.bit.WRBUFF = 0;
    // XCLKOUT is enabled
    XintfRegs.XINTCNF2.bit.CLKOFF = 0;
    // XCLKOUT = XTIMCLK/2
    XintfRegs.XINTCNF2.bit.CLKMODE = 1;


    // Zone 0------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING0.bit.XWRLEAD = 3;
    XintfRegs.XTIMING0.bit.XWRACTIVE = 7;
    XintfRegs.XTIMING0.bit.XWRTRAIL = 3;
    // Zone read timing
    XintfRegs.XTIMING0.bit.XRDLEAD = 3;
    XintfRegs.XTIMING0.bit.XRDACTIVE = 7;
    XintfRegs.XTIMING0.bit.XRDTRAIL = 3;

    // double all Zone read/write lead/active/trail timing
    XintfRegs.XTIMING0.bit.X2TIMING = 1;

    // Zone will sample XREADY signal
//    XintfRegs.XTIMING0.bit.USEREADY = 1;
    XintfRegs.XTIMING0.bit.USEREADY = 0;
    XintfRegs.XTIMING0.bit.READYMODE = 1;  // sample asynchronous

    // Size must be either:
    // 0,1 = x32 or
    // 1,1 = x16 other values are reserved
    XintfRegs.XTIMING0.bit.XSIZE = 3;

    // Zone 6------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING6.bit.XWRLEAD = 3;
    XintfRegs.XTIMING6.bit.XWRACTIVE = 7;
    XintfRegs.XTIMING6.bit.XWRTRAIL = 3;
    // Zone read timing
    XintfRegs.XTIMING6.bit.XRDLEAD = 3;
    XintfRegs.XTIMING6.bit.XRDACTIVE = 7;
    XintfRegs.XTIMING6.bit.XRDTRAIL = 3;

    // double all Zone read/write lead/active/trail timing
    XintfRegs.XTIMING6.bit.X2TIMING = 1;

    // Zone will sample XREADY signal
 //   XintfRegs.XTIMING6.bit.USEREADY = 1;
	XintfRegs.XTIMING6.bit.USEREADY = 0;	// 090617
    XintfRegs.XTIMING6.bit.READYMODE = 0;  // sample asynchronous

    // Size must be either:
    // 0,1 = x32 or
    // 1,1 = x16 other values are reserved
    XintfRegs.XTIMING6.bit.XSIZE = 3;


    // Zone 7------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING7.bit.XWRLEAD = 3;
    XintfRegs.XTIMING7.bit.XWRACTIVE = 7;
    XintfRegs.XTIMING7.bit.XWRTRAIL = 3;
    // Zone read timing
    XintfRegs.XTIMING7.bit.XRDLEAD = 3;
    XintfRegs.XTIMING7.bit.XRDACTIVE = 7;
    XintfRegs.XTIMING7.bit.XRDTRAIL = 3;

    // double all Zone read/write lead/active/trail timing
    XintfRegs.XTIMING7.bit.X2TIMING = 1;

    // Zone will sample XREADY signal
    XintfRegs.XTIMING7.bit.USEREADY = 0;
    XintfRegs.XTIMING7.bit.READYMODE = 0;  // sample asynchronous

    // Size must be either:
    // 0,1 = x32 or
    // 1,1 = x16 other values are reserved
    XintfRegs.XTIMING7.bit.XSIZE = 3;

    // Bank switching
    // Assume Zone 7 is slow, so add additional BCYC cycles
    // when ever switching from Zone 7 to another Zone.
    // This will help avoid bus contention.
    XintfRegs.XBANK.bit.BANK = 7;
    XintfRegs.XBANK.bit.BCYC = 7;
    EDIS;
   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.

//   InitXintf16Gpio();			// 090617 eunwho
// InitXintf32Gpio();

   asm(" RPT #7 || NOP");

}
//===========================================================================
// No more.
//===========================================================================
