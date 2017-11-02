#include	<header.h>
#include	<extern.h>
// include <scia,h>

#if	USE_UART_A

#define CPU_FREQ    90E6
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ    115200
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

#define UARTA_BAUD_RATE          SCI_PRD     // 115200

#define SCIA_RX_BUF_MAX		30
#define SCIA_TX_BUF_MAX		50

int scia_rx_start_addr=0;
int scia_rx_end_addr=0;
int sciRxPoint=0;

int scia_tx_start_addr=0;
int scia_tx_end_addr=0;
int scia_rx_msg_flag = 0;

char msg_box[20]={0};
char sciaRxIrqBox[SCIA_RX_BUF_MAX] = {0};
char scia_rx_msg_box[SCIA_RX_BUF_MAX] = {0};
char scia_tx_msg_box[SCIA_TX_BUF_MAX] = {0};

void scia_fifo_init()
{
	SciaRegs.SCICCR.all =0x0007;   // 1stopbit,No parity,8 char bits, async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.bit.TXINTENA 	=1;	// debug
//	SciaRegs.SCICTL2.bit.RXBKINTENA     =0;
	SciaRegs.SCICTL2.bit.RXBKINTENA     = 1;    // 2017
	SciaRegs.SCIHBAUD = 0x0000;
	SciaRegs.SCILBAUD = UARTA_BAUD_RATE;
	SciaRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
	SciaRegs.SCIFFTX.all=0xC020; // 2011.
    // SciaRegs.SCIFFTX.all=0xC022;        // 2017.09.01

    // SciaRegs.SCIFFRX.all=0xC020;    // 2017.09.01 mal function
    SciaRegs.SCIFFRX.all=0x0021;    // 2017.09.01

    SciaRegs.SCIFFCT.all=0x00;          // 2017.09.01
    SciaRegs.SCIFFTX.bit.TXFFIL = 0;    // irq 15 byte receive
    SciaRegs.SCIFFCT.all=0x00;

    SciaRegs.SCICTL1.all =0x0023;       // Relinquish SCI from Reset
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

//---
    SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag
	SciaRegs.SCIFFTX.bit.SCIFFENA=1;

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block 2017.09.03
	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // SCI_RX_INT_A --> PIE Group 9, INT1
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // SCI_TX_INT_A --> PIE Group 9, INT1
	//PieCtrlRegs.PIEIER9.bit.INTx2=0;     // SCI_TX_INT_A --> PIE Group 9, INT1
	IER |= M_INT9;		// M == 0x0100 scia irq
}

void load_scia_tx_mail_box( char * st)
{
	int i;
	char * str;

	str = st;

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	for( i = 0 ; i < 30 ; i++){
 		scia_tx_msg_box[scia_tx_end_addr++] = * str++;
 		if(scia_tx_end_addr >= SCIA_TX_BUF_MAX ) scia_tx_end_addr = 0;
		if(scia_tx_end_addr == scia_tx_start_addr){
		    scia_tx_start_addr++;
			if(scia_tx_start_addr >= (SCIA_TX_BUF_MAX-1)) scia_tx_start_addr = 0;
		}
		if( *str == '\0')  break;
	}
	SciaRegs.SCIFFTX.bit.TXFFIENA = 1;	// Clear SCI Interrupt flag
}
		
interrupt void sciaTxFifoIsr(void)
{
    Uint16 i=0;

	while( scia_tx_end_addr != scia_tx_start_addr){

 		SciaRegs.SCITXBUF = scia_tx_msg_box[scia_tx_start_addr];

		if(scia_tx_start_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_start_addr ++;
		else											scia_tx_start_addr=0;

		if(scia_tx_end_addr == scia_tx_start_addr) break;

		i++;
		if( i > 3 ) break;
	}

	if(scia_tx_end_addr == scia_tx_start_addr) SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

interrupt void sciaRxFifoIsr(void)
{
    static Uint32 modebus_start_time=0;
    static int scia_rx_count=0;
    Nop();
    // .
    if( ulGetTime_mSec(modebus_start_time) > 10 ){
        modebus_start_time = ulGetNow_mSec( );
        msg_box[0] = SciaRegs.SCIRXBUF.all;  // Read data
        scia_rx_count = 0;
        scia_rx_count++;
    }
    else if( scia_rx_count < 15 ){
        msg_box[scia_rx_count] = SciaRegs.SCIRXBUF.all;  // Read data
        scia_rx_count++;
    }
    else if( scia_rx_count == 15 ){
        msg_box[15] = SciaRegs.SCIRXBUF.all;     // Read data
        scia_rx_count = 0;
        scia_rx_msg_flag =1;
    }
    else{
        msg_box[0] = SciaRegs.SCIRXBUF.all;  // Read data
        scia_rx_count++;
    }
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x0100;     // IN9
}

// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"
void scia_cmd_proc( int * sci_cmd, float * sci_ref)
{
	float data,dbtemp;
    int addr,check,temp;
    char str[30]={0};

    TRIP_INFO * TripData;

    * sci_cmd = CMD_NULL;
    * sci_ref = 0.0;
	 
	* sci_cmd = CMD_NULL;
	* sci_ref = 0.0;

	if( scia_rx_msg_flag == 0) return;

	scia_rx_msg_flag = 0;

    strncpy( scia_rx_msg_box,msg_box,16);

    if (( scia_rx_msg_box[0] != '9') && ( scia_rx_msg_box[1] != ':')) return;

    addr =  (scia_rx_msg_box[4]- '0')* 100 +(scia_rx_msg_box[5]- '0')*10 + (scia_rx_msg_box[6]- '0');

    scia_rx_msg_box[16]=0;
    data =  atof( & scia_rx_msg_box[8]);

    if( scia_rx_msg_box[2] == '6'){
         if( addr == 900 ){
             check = (int)data;
             if(check == 10){
                 * sci_cmd = CMD_START;
                 * sci_ref = 0.1;           //code_btn_start_ref;
                 load_scia_tx_mail_box("UART CMD_START");
             }
             else if( check == 20 ){
                 * sci_cmd = CMD_STOP;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("UART CMD_STOP");
             }
             else if( check == 30 ){
                 * sci_cmd = CMD_RESET;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("UART CMD_RESET");
             }
             else if( data == 40 ){
                 * sci_cmd = CMD_SAVE;  * sci_ref = 0.0;
                 load_scia_tx_mail_box("UART CMD_SAVE");
             }
             else{
                 load_scia_tx_mail_box("Illegal CMD data");
             }
         }
         else{
             // registor_write_proc(addr,data);
             check = SaveDataProc(addr, data);
             Nop();
         }
     }

 //==================
 //   read routine
 //====================
     else if(scia_rx_msg_box[2] == '4'){

         if(addr == 900){    //  monitor state
             * sci_cmd = CMD_READ_ALL;  * sci_ref = 0.0;
             load_scia_tx_mail_box("ok! read code all");
             return;
         }
         else if(addr == 901){    //  monitor state
             switch(gMachineState){
                 case STATE_POWER_ON:    load_scia_tx_mail_box("[POWE_ON] "); break;
                 case STATE_READY:       load_scia_tx_mail_box("[READY]   "); break;
                 case STATE_RUN:         load_scia_tx_mail_box("[RUN ]    "); break;
                 case STATE_TRIP:        load_scia_tx_mail_box("[TRIP]    "); break;
                 case STATE_INIT_RUN:    load_scia_tx_mail_box("[INIT]    "); break;
                 case STATE_GO_STOP:     load_scia_tx_mail_box("[GO_STOP] "); break;
                 case STATE_WAIT_BREAK_OFF: load_scia_tx_mail_box("STATE_WAIT_BREAK_OFF"); break;
                 default:                load_scia_tx_mail_box("Unknown State"); break;
             }
             return;
         }
         else if(addr == 902){   // read inverter status
             gMachineState = STATE_POWER_ON;
             Nop();
             asm (" .ref _c_int00"); // ;Branch to start of boot.asm in RTS library
             asm (" LB _c_int00"); // ;Branch to start of boot.asm in RTS library
         }
         else if(addr == 903){   //  EEPROM TRIP DATA
             check = (int)data;

             if( data == 0 ){
                 snprintf( str,4,"%03d:",TripInfoNow.CODE);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 load_scia_tx_mail_box(TripInfoNow.MSG); delay_msecs(220);

                 dbtemp = TripInfoNow.RPM;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"Fq=%3d[hz]",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," VDC =%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"I1  =%4d ",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripInfoNow.DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," DATA=%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);
             }
             else{

                TripData = (TRIP_INFO*)malloc(sizeof(TRIP_INFO));
                GetTripInfo(check + 1,TripData);

                 strncpy(gStr1,TripInfoNow.MSG,20);

                 snprintf( str,4,"%03d:",TripData->CODE);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 load_scia_tx_mail_box(TripData->MSG); delay_msecs(220);

                 dbtemp = TripData->RPM;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"Fq=%3d[hz]",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->VDC;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," VDC =%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->CURRENT;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10,"I1  =%4d ",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 dbtemp = TripData->DATA;
                 temp = (int)(floor(dbtemp +0.5));
                 snprintf( str,10," DATA=%4d",temp);
                 load_scia_tx_mail_box(str); delay_msecs(180);

                 free(TripData);
             }
             return;
         }
         else if(addr == 905){   // RUN & STOP
             check = (int)data;

             switch( check ){
             case 0:
                 * sci_cmd = CMD_START;
                 * sci_ref = 0.1 ; // code_btn_start_ref;
                 break;
             case 1:
                 * sci_cmd = CMD_STOP;
                 * sci_ref = 0.0;
                 break;
             case 2:
                 * sci_cmd = CMD_SPEED_UP;
                 break;
             case 3:
                 * sci_cmd = CMD_SPEED_DOWN;
                 break;
             default:
                 * sci_cmd = CMD_NULL;
                 break;
             }
             return;
         }
         else if (( addr > 979) && ( addr < 996)){
             /*
             check = addr - 980;
             snprintf( str,19,"adc =%4d",adc_result[check]);
             load_scia_tx_mail_box(str);
             delay_msecs(10);
             */
             return;
         }

         check = get_code_information( addr, CMD_READ_DATA , & code_inform);

         if( check == 0 ){
             check = (int)data;

             switch(check)
             {
             case 0:
                 snprintf( str,19,"CODE=%4d/t",addr); load_scia_tx_mail_box(str);
                 snprintf( str,20,"Data =%.3e/t",code_inform.code_value);load_scia_tx_mail_box(str);
                 load_scia_tx_mail_box(code_inform.disp);
                 load_scia_tx_mail_box(" \r\n");delay_msecs(10);
                 break;
             case 1:
                 snprintf( str,19,"CODE=%4d",addr);
                 load_scia_tx_mail_box(str);
                  delay_msecs(10);
                 break;
             case 2:
                 load_scia_tx_mail_box(code_inform.disp);delay_msecs(10);
                 break;
             case 3:
                 snprintf( str,20,"Data =%10.3e",code_inform.code_value);
                 load_scia_tx_mail_box(str); delay_msecs(10);
                 break;
             default:
                 snprintf( str,19,"CODE=%4d/t",addr); load_scia_tx_mail_box(str);
                 snprintf( str,20,"Data =%.3e/t",code_inform.code_value);load_scia_tx_mail_box(str);
                 load_scia_tx_mail_box(code_inform.disp);
                 load_scia_tx_mail_box(" \r\n");delay_msecs(10);
                 break;
             }
         }
         else{
             load_scia_tx_mail_box("Error Invalid Address");delay_msecs(10);
         }
         return;
     }
 }
#endif

//==================================
// End of file.
//==================================

