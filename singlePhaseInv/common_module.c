#include	<header.h>
#include	<extern.h>

float linear_eq(float x1, float x2, float y1, float y2, float x )
{
	float y;

	y = (( y2-y1) / ( x2 - x1 )) * x  + (( y1 * x2 - y2 * x1 )/ (x2- x1));
	return y;
}

void LPF1(float Ts,float pole,float in,float *out)
{
	*out+=pole*(in-*out)*Ts;
}

void Nop()
{
  asm ("      nop");
}
void PI_Damp_Controller(float limit,float Ts, float damp_factor, float Kp,float Ki,float ref,float feedback,float *integral,float *output)
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

int iGetAinCmd(int * piCommand, float * pfReference)
{
	int iTemp;
	iTemp = 0;

	* piCommand =  CMD_NULL;
	* pfReference = 0.0;
	return iTemp;
}

void analog_cmd_proc(float * ana_ref)
{
	* ana_ref = analog_ref_a * analog_cmd_in_span1;		// debug
}

//
void get_command( int * command, float * ref )
{
	int digital_cmd,sci_cmd;
	float digital_reference,sci_ref,ana_ref;

	digital_input_proc( & digital_cmd, & digital_reference);
//	serial_com_proc( & sci_cmd, & sci_ref );
	analog_cmd_proc( & ana_ref);

	* command = digital_cmd;
    if( digital_cmd == CMD_START ){
        if( analog_ref_a < 0.01 )   * command = CMD_STOP;
        else                        * ref = ana_ref;
    }
}

//---------------------------------
// end of file
//----------------------------------

