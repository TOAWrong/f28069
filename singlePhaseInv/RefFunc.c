#include	<header.h>
#include	<extern.h>

void ramp_proc( float SetRef,float * pOutRef)
{
	static unsigned long ulCount;

	float OutRef;
	
	OutRef = * pOutRef;

 	if( ulGetNow_mSec( )== ulCount ) return;
	
	ulCount = ulGetNow_mSec( );

	if(codeAccelTime1 <= 0.0) codeAccelTime1 = 0.01;			// debug
	if(codeDecelTime1 <= 0.0) codeAccelTime1 = 0.01;			// debug

	if( OutRef >= 0 )
	{
		if (SetRef > OutRef){ 
			OutRef += 0.001 / codeAccelTime1;
			if( OutRef > SetRef ) OutRef = SetRef;
		}
		else if (SetRef < OutRef){
			OutRef -=  0.001 / codeDecelTime1 ;
			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
	else{
		if (SetRef > OutRef){
			OutRef += 0.001 / codeDecelTime1 ;
			if( OutRef > SetRef ) OutRef = SetRef;
		}
		else if (SetRef < OutRef){
			OutRef -= 0.001 / codeAccelTime1 ;
			if( OutRef < SetRef ) OutRef = SetRef;
		}
	}
	* pOutRef = OutRef; 
}	

//----------------------------------
// End of File
//----------------------------------
