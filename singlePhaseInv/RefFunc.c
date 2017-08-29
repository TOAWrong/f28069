#include	<header.h>
#include	<extern.h>

void RefFunc( float SetRef,float * pOutRef)
{
	static unsigned long ulCount;

	float OutRef;
	float accel_time,decel_time;
	
	OutRef = * pOutRef;

 	if( ulGetNow_mSec( )== ulCount ) return;
	
	ulCount = ulGetNow_mSec( );

	if(accel_time1 <= 0.0) accel_time1 = 0.01;			// debug
	if(decel_time1 <= 0.0) decel_time1 = 0.01;			// debug
	if(accel_time2 <= 0.01) accel_time2 = accel_time1;	// debug
	if(decel_time2 <= 0.01) decel_time2 = decel_time1;	// debug

	if( fabs(OutRef) <= code_speed2 )	{ accel_time = accel_time1; decel_time = decel_time1; }
	else 								{ accel_time = accel_time2; decel_time = decel_time2; }

//-- �������� ����� ��� 
	if( OutRef >= 0 )
	{
		if (SetRef > OutRef){ 
			OutRef += 0.001 / accel_time; 
			if( OutRef > SetRef ) OutRef = SetRef;
		}
		else if (SetRef < OutRef){
			OutRef -=  0.001 / decel_time ;
			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
//-- �������� ������ ��� 
	else{
		if (SetRef > OutRef){
			OutRef += 0.001 / decel_time ;
			if( OutRef > SetRef ) OutRef = SetRef;
		}
		else if (SetRef < OutRef){
			OutRef -= 0.001 / accel_time ;
			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
	* pOutRef = OutRef; 
}	


void ramp_proc( float set_ref, float * out_ref)
{
	switch(ramp_func_mode){
	
	case 0:	RefFunc( set_ref, out_ref ); break;
	
//	case 1:	test_ref_func( set_ref, out_ref ); break;	// debugs 2010.06.23
	
	default:RefFunc( set_ref, out_ref ); break;
	}
}

//----------------------------------
// End of File
//----------------------------------
