#include	<header.h>
#include	<extern.h>

void RefFunc( double SetRef,double * pOutRef)
{
	static unsigned long ulCount;
	double OutRef;
	double accel_time,decel_time;
	
	OutRef = * pOutRef;
 	if( ulGetNow_mSec( )== ulCount ) return;
	
 	ulCount = ulGetNow_mSec( );
	if(codeAccelTime1 <= 0.0) codeAccelTime1 = 0.01;			// debug
	if(codeDecelTime1 <= 0.0) codeDecelTime1 = 0.01;			// debug
/*
	if( fabs(OutRef) <= digital_speed2 )	{ accel_time = accel_time1; decel_time = decel_time1; }
	else 								{ accel_time = accel_time2; decel_time = decel_time2; }
*/
    accel_time = codeAccelTime1; decel_time = codeDecelTime1;
    if( OutRef >= 0 )
	{
		if (SetRef > OutRef){ 
			OutRef += 0.001 / accel_time; 
			if( OutRef > SetRef ) OutRef = SetRef;
		}else if (SetRef < OutRef){
			OutRef -=  0.001 / decel_time ;
			if( OutRef < SetRef ) OutRef = SetRef;
		}
	} else{
		if (SetRef > OutRef){
			OutRef += 0.001 / decel_time ;
			if( OutRef > SetRef ) OutRef = SetRef;
		} else if (SetRef < OutRef){
			OutRef -= 0.001 / accel_time ;
			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
	* pOutRef = OutRef; 
}	

void test_ramp_proc( double SetRef,double * pOutRef)
{
	double OutRef;

	OutRef = * pOutRef;

	if( OutRef >= 0 )
	{
		if (SetRef > OutRef){ 

			if( test_accel_time > 0.01 ) OutRef += 0.001 / test_accel_time; 
			else 						 OutRef = SetRef;

			if( OutRef > SetRef ) OutRef = SetRef;
		}
		else if (SetRef < OutRef){
			if( test_decel_time > 0.01 ) OutRef -=  0.001 / test_decel_time ;
			else						 OutRef = SetRef;

			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
	else{
		if (SetRef > OutRef){
			if( test_decel_time > 0.01 )  OutRef += 0.001 / test_decel_time ;
			else							OutRef = SetRef;

			if( OutRef > SetRef ) OutRef = SetRef;
		}
		else if (SetRef < OutRef){
			if( test_accel_time > 0.01 ) OutRef -= 0.001 / test_accel_time ;
			else 						 OutRef = SetRef;

			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
	* pOutRef = OutRef; 
}	

void test_ref_func( double ref_in, double * ref_out )
{
	static unsigned long one_count=0;

 	if( ulGetNow_mSec( )== one_count ) return;    	
 	one_count = ulGetNow_mSec( );

	if ( ref_time <  posi_duration_time ){	
		if( test_accel_time == 0) * ref_out = ref_in;	
		else test_ramp_proc( ref_in, ref_out);
	}											// Positive Command					
	else if ( ref_time < (posi_duration_time+zero_duration_time)){
		if( test_decel_time == 0) * ref_out = 0.0;							
		else test_ramp_proc( 0.0, ref_out);
	}					
	else if ( ref_time < (posi_duration_time+zero_duration_time+nega_duration_time)){
		if( test_accel_time == 0) * ref_out = -ref_in;
		else test_ramp_proc( -ref_in, ref_out);
	}
	else if (ref_time < (posi_duration_time+(zero_duration_time*2.0)+ nega_duration_time) ){
		if( test_decel_time == 0 ) * ref_out = 0.0;											// Zero Command
		else test_ramp_proc( 0.0, ref_out);
	}
	else  ref_time = 0.0;
}

void ramp_proc( double set_ref, double * out_ref)
{
	if(codeRampTest < 0.5 )	RefFunc( set_ref, out_ref );
	else                    test_ref_func( set_ref, out_ref );
}

//----------------------------------
// End of File
//----------------------------------
