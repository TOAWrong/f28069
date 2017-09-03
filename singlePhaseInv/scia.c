#include	<header.h>
#include	<extern.h>
// include <scia,h>

#if	USE_UART_A

#define CPU_FREQ    90E6
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ    115200
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

#define UARTA_BAUD_RATE          SCI_PRD     // 38400

#define SCIA_RX_BUF_MAX		20
#define SCIA_TX_BUF_MAX		48

int scia_rx_start_addr=0;
int scia_rx_end_addr=0;

int scia_tx_start_addr=0;
int scia_tx_end_addr=0;
int scia_rx_msg_flag = 0;

char scia_rx_msg_box[SCIA_RX_BUF_MAX] = {0};
char scia_tx_msg_box[SCIA_TX_BUF_MAX] = {0};

void scia_fifo_init()
{
	SciaRegs.SCICCR.all =0x0007;   // 1stopbit,No parity,8 char bits, async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.bit.TXINTENA 	=1;	// debug
	SciaRegs.SCICTL2.bit.RXBKINTENA 	=0;
	SciaRegs.SCIHBAUD = 0x0000;
	SciaRegs.SCILBAUD = UARTA_BAUD_RATE;
	SciaRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
	SciaRegs.SCIFFTX.all=0xC020; // 2011.
    // SciaRegs.SCIFFTX.all=0xC022;        // 2017.09.01
//    SciaRegs.SCIFFRX.all=0xC022;
    SciaRegs.SCIFFCT.all=0x00;          // 2017.09.01
    SciaRegs.SCIFFTX.bit.TXFFIL = 0;    // irq 15 byte receive
    SciaRegs.SCIFFCT.all=0x00;
    SciaRegs.SCICTL1.all =0x0023;       // Relinquish SCI from Reset
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag
	SciaRegs.SCIFFTX.bit.SCIFFENA=1;

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block 2017.09.03
	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // SCI_RX_INT_A --> PIE Group 9, INT1
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // SCI_TX_INT_A --> PIE Group 9, INT1
	//PieCtrlRegs.PIEIER9.bit.INTx2=0;     // SCI_TX_INT_A --> PIE Group 9, INT1
	IER |= M_INT9;		// M == 0x0100 scia irq
}

/*
void scia_tx_msg( char * st)
{
    int i =0;

    for(i = 0 ; i < 16 ; i++ ){
        SciaRegs.SCITXBUF= st[i];     // Send data
    }
}
*/

void load_scia_tx_mail_box( char * st)
{
	int loop_ctrl = 1;
	char * str;

	str = st;

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	while(loop_ctrl){
 		scia_tx_msg_box[scia_tx_end_addr] = * str++;
		
		if(scia_tx_end_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_end_addr ++;
		else										scia_tx_end_addr = 0;

		if(scia_tx_end_addr == scia_tx_start_addr){
			if(scia_tx_end_addr < (SCIA_TX_BUF_MAX-1)) scia_tx_start_addr++;
			else										scia_tx_start_addr = 0;
		}
		if( *str == '\0') loop_ctrl = 0;
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
		if( i > 4 ) break;
	}

	if(scia_tx_end_addr == scia_tx_start_addr) SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

interrupt void sciaRxFifoIsr(void)
{
	int i;

	for( i =0 ; i< 13 ; i++){ 
		scia_rx_msg_box[i] = SciaRegs.SCIRXBUF.all;	 // Read data
	}
	
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

	scia_rx_msg_flag = 1;

	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

// read data format  "X40001.234e-3"
// write data format  "X60001.234e-3"
void scia_cmd_proc( int * sci_cmd, float * sci_ref)
{
	float data;
	int addr,check;
	 
	* sci_cmd = CMD_NULL;
	* sci_ref = 0.0;

	if( scia_rx_msg_flag == 0) return;

	scia_rx_msg_flag = 0;

	if ( scia_rx_msg_box[0] != 'X') return;
	
	addr =  (scia_rx_msg_box[2]- '0')* 100 +(scia_rx_msg_box[2]- '0')*10 + (scia_rx_msg_box[2]- '0');
	data =  atof( & scia_rx_msg_box[4]);
	
	// regist write function decoding
	if( scia_rx_msg_box[1] == '6'){
		if( addr == 900 ){ * sci_cmd = CMD_START; * sci_ref = data;}
		else if( addr == 901 ){ * sci_cmd = CMD_STOP;  * sci_ref = 0.0;}
		else{
			// registor_write_proc(addr,data);

			check = SaveDataProc(addr, data);
		}
	}
	else if(scia_rx_msg_box[1] == '4'){
		check = get_code_information( addr, CMD_READ_DATA , & code_inform);
		if( check != 0 ){
			data = code_inform.code_value;
			snprintf( gStr1,20,"read data =10.3%e \n",data);
			load_scia_tx_mail_box(gStr1);		
		}
		else{
			load_scia_tx_mail_box("Error Invalid Address");		
		}
	}
}
#endif

//==================================
// End of file.
//==================================

