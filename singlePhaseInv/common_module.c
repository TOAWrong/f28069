#include	<header.h>
#include	<extern.h>

/*
void LPF_V(double *LPF_out, double *LPF_feed, double LPF_in)
{
	*LPF_out = (pCoeff_V2 * (LPF_in + *LPF_feed)) - ( pCoeff_V1 * (*LPF_out));
	*LPF_feed = LPF_in;
}

void LPF_I(double *LPF_out, double *LPF_feed, double LPF_in)
{

	
// 1000 Hz cut off at 2.5 kH switching
//	pCoeff_I1 = -0.081;
//	pCoeff_I2 =  0.919*0.5;

	
// 2000 Hz cut off  at 2.5 kH switching
	pCoeff_I1 = -0.006561;
	pCoeff_I2 =  0.9934*0.5;

	*LPF_out = (pCoeff_I2 * (LPF_in + *LPF_feed)) - ( pCoeff_I1 * (*LPF_out));
	*LPF_feed = LPF_in;
}
*/

double linear_eq(double x1, double x2, double y1, double y2, double x )
{
	double y;

	y = (( y2-y1) / ( x2 - x1 )) * x  + (( y1 * x2 - y2 * x1 )/ (x2- x1));
	return y;
}

void LPF1(double Ts,double pole,double in,double *out)
{
	*out+=pole*(in-*out)*Ts;
}

void Nop()
{
  asm ("      nop");
}
void PI_Damp_Controller(double limit,double Ts, double damp_factor, double Kp,double Ki,double ref,double feedback,double *integral,double *output)
{
	*integral+=Ki*(ref-feedback)*Ts;
	if (*integral>fabs(limit))			*integral=fabs(limit);
	else if (*integral<-fabs(limit))	*integral=-fabs(limit);
	*output=Kp*(damp_factor*ref-feedback)+*integral;
}

void SetSensorOffset()
{
}

void PowerOnReset()
{

}

unsigned long ulGetTime_mSec(unsigned long Start_mSec)
{
	unsigned long Temp;
	 
	if( CpuTimer0.InterruptCount < Start_mSec){
		Temp = ((unsigned long )(0xFFFFFFFF) - Start_mSec) + CpuTimer0.InterruptCount; 		
	}
	else{
		Temp = CpuTimer0.InterruptCount - Start_mSec ;
	}
	return Temp;
}

unsigned long ulGetNow_mSec( )
{
	return CpuTimer0.InterruptCount;

}

void delay_msecs( unsigned long ulmSec)
{
	unsigned long Start_mSec,ulTemp;

	ulTemp =0;
	Start_mSec = ulGetNow_mSec( );

	while( ulTemp < ulmSec)
	{
		ulTemp = ulGetTime_mSec( Start_mSec );
	}
}

int periodic_check(unsigned long  msec)
{
	static unsigned long count_msec=0;

	if( ulGetTime_mSec(count_msec) > msec ){
		count_msec = ulGetNow_mSec( );
		return 0;
	}
	return -1;				
}

int iGetAinCmd(int * piCommand, double * pfReference)
{
	int iTemp;
	iTemp = 0;

	* piCommand =  CMD_NULL;
	* pfReference = 0.0;
	return iTemp;
}

void analog_cmd_proc(double * ana_ref)
{
	* ana_ref = analog_ref_a * analog_cmd_in_span1;		// debug
}
//------------------------------
//
//------------------------------

void get_command( int * command, double * ref )
{
	int digital_cmd,sci_cmd;
	double digital_reference,sci_ref,ana_ref;

	digital_input_proc( & digital_cmd, & digital_reference);
	serial_com_proc( & sci_cmd, & sci_ref );
	analog_cmd_proc( & ana_ref);
//	KeyInputProc(&button_cmd,&button_ref);

// button�� ���� ������ �ɼǰ� ������� ������ ������ �ȴ�.
	switch( run_input_select )
	{
	case 1: // ������ �Է¿� ���� �õ��� ���� 
		* command = digital_cmd;
		* ref = digital_reference;
		break;

	case 2: //  ��ſ� ���� �õ��� ��
		* command = sci_cmd;
		* ref = sci_ref;
		break;

	case 3: // �Ƴ��α� �Է�����

		* command = digital_cmd;
		if( digital_cmd == CMD_START ){
			if( analog_ref_a < 0.01 )	* command = CMD_STOP;
			else 						* ref = ana_ref;
		}
		break;

	default:
		* command = CMD_STOP;
		* ref = 0.0; 
		break;
	}

	// ��ſ� ���� ������ �ֿ켱���� ó���Ѵ�. 
	if( sci_cmd == CMD_SAVE){
		* command = sci_cmd ;
	}
}

void get_adc_offset()
{
	int LoopCtrl;

	Uint32 RunTimeMsec,StartTimeMsec;
	double u_offset_in, v_offset_in;
	double u_offset_out, v_offset_out;
	
	UNION32 u32data;

	load_sci_tx_mail_box( "\n***********************"); delay_msecs(10);
	load_sci_tx_mail_box( "\n Start ADC Offset Calc "); delay_msecs(10);
	load_sci_tx_mail_box( "\n***********************"); delay_msecs(10);

	gfRunTime=0.0;
	LoopCtrl = 1;
	gMachineState = STATE_READY;

	while(LoopCtrl == 1)
	{
		if( gfRunTime >= 5.0 ) LoopCtrl = 0;
//		get_command(&cmd,&ref0);	// Command�� �Է� ���� 
//		if( gPWMTripCode != 0 ) 	LoopCtrl = 0;
//		if ( cmd == CMD_STOP)	LoopCtrl = 0; 

		RunTimeMsec = ulGetTime_mSec( StartTimeMsec);
		if(RunTimeMsec > 1){
			StartTimeMsec = ulGetNow_mSec( );
			u_offset_in = (double)adcIuPhase;
			v_offset_in = (double)adcIvPhase;
			LPF1(0.002,10.0,u_offset_in, & u_offset_out);
			LPF1(0.002,10.0,v_offset_in, & v_offset_out);
		}
	}

	if( gfRunTime >= 5.0 ){
		adc_u_offset = (int)u_offset_out;
		adc_v_offset = (int)v_offset_out;

		u32data.word.word0 = adc_u_offset; write_code_2_eeprom(CODE_adc_u_offset,u32data);
		u32data.word.word0 = adc_v_offset; write_code_2_eeprom(CODE_adc_v_offset,u32data);
				
		load_sci_tx_mail_box("\n*********************");delay_msecs(10);		
		load_sci_tx_mail_box("\n OK Adc offset Saved ");delay_msecs(10);		
		load_sci_tx_mail_box("\n*********************");delay_msecs(10);		
	}
}

void get_adc_vdc_low()
{
	int LoopCtrl;

	Uint32 RunTimeMsec,StartTimeMsec;
	double adc_Vdc_in, adc_Vdc_out;
	
	UNION32 u32data;

	load_sci_tx_mail_box( "Start ADC at Vdc low"); delay_msecs(10);

	gfRunTime=0.0;
	LoopCtrl = 1;
	gMachineState = STATE_READY;

	while(LoopCtrl == 1)
	{
		if( gfRunTime >= 1.0 ) LoopCtrl = 0;

		RunTimeMsec = ulGetTime_mSec( StartTimeMsec);
		if(RunTimeMsec > 1){
			StartTimeMsec = ulGetNow_mSec( );
			adc_Vdc_in = (double)adcVdc;			// VDC ����
			LPF1(0.002,10.0,adc_Vdc_in, & adc_Vdc_out);
		}
	}

	if( gfRunTime >= 1.0 ){

		code_adc_vdc_low = adc_Vdc_out;
		u32data.dword = code_adc_vdc_low; write_code_2_eeprom(CODE_adc_vdc_low,u32data);
					
		load_sci_tx_mail_box("OK adc_vdc_low Saved");delay_msecs(10);				
	}
}

void get_adc_vdc_high()
{
	int LoopCtrl;

	Uint32 RunTimeMsec,StartTimeMsec;
	double adc_Vdc_in, adc_Vdc_out;
	
	UNION32 u32data;

	load_sci_tx_mail_box( "Start ADC at Vdc high"); delay_msecs(10);

	gfRunTime=0.0;
	LoopCtrl = 1;
	gMachineState = STATE_READY;

	while(LoopCtrl == 1)
	{
		if( gfRunTime >= 1.0 ) LoopCtrl = 0;

		RunTimeMsec = ulGetTime_mSec( StartTimeMsec);
		if(RunTimeMsec > 1){
			StartTimeMsec = ulGetNow_mSec( );
			adc_Vdc_in = (double)adcVdc;
			LPF1(0.002,10.0,adc_Vdc_in, & adc_Vdc_out);
		}
	}

	if( gfRunTime >= 1.0 ){

		code_adc_vdc_high = adc_Vdc_out;
		u32data.dword = code_adc_vdc_high; write_code_2_eeprom(CODE_adc_vdc_high,u32data);
						
		load_sci_tx_mail_box("OK adc_vdc_high Saved");delay_msecs(10);				
	}
}

//---------------------------------
// end of file
//----------------------------------

