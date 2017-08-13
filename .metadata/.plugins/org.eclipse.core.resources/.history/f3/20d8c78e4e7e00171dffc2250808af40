#include	<header.h>
#include	<extern.h>

#if USE_DAC_OUT
void dac8412_out( )
{
	unsigned int dac_data[4];

	dac_data[0] = (unsigned int )(( * (dac_point[code_dac_select_ch1]) - code_dac_offset_ch1 ) * inv_code_dac_scale_ch1 * 204.8 + 2047); 
	dac_data[1] = (unsigned int )(( * (dac_point[code_dac_select_ch2]) - code_dac_offset_ch2 ) * inv_code_dac_scale_ch2 * 204.8 + 2047); 
	dac_data[2] = (unsigned int )(( * (dac_point[code_dac_select_ch3]) - code_dac_offset_ch3 ) * inv_code_dac_scale_ch3 * 204.8 + 2047); 
	dac_data[3] = (unsigned int )(( * (dac_point[code_dac_select_ch4]) - code_dac_offset_ch4 ) * inv_code_dac_scale_ch4 * 204.8 + 2047); 

	ZONE7_BUF[0x60] = 7;
	ZONE7_BUF[0x60] = 3;
	ZONE7_BUF[0x30] = dac_data[0] ;
	ZONE7_BUF[0x32] = dac_data[1];
	ZONE7_BUF[0x34] = dac_data[2];
	ZONE7_BUF[0x36] = dac_data[3];
	ZONE7_BUF[0x60] = 1;
	ZONE7_BUF[0x60] = 7;
}
#else
void dac8412_out( )
{
	unsigned int dac_data[4];
	double scale1,scale2,scale3,scale4;

	ZONE7_BUF[0x60] = 7;
	Nop();
	ZONE7_BUF[0x60] = 3;
	Nop();
	Nop();

    scale1 = 1/50.0;
    scale2 = 1/50.0;
    scale3 = 1/1.0;
	scale4 = 1/1.0;

	dac_data[0] = (unsigned int )(( Uan - 0.0 ) * scale1 * 204.8 + 2047); 
	dac_data[1] = (unsigned int )(( fIn_Va_ref - 0.0 ) * scale2 * 204.8 + 2047); 
	dac_data[2] = (unsigned int )(( theta_pll - 0.0 ) * scale3  * 204.8 + 2047); 
	dac_data[3] = (unsigned int )(( theta_pll - 0.0 ) * scale4  * 204.8 + 2047); 

	dac_data[0] = dac_data0; 
	dac_data[1] = dac_data1; 
	dac_data[2] = dac_data2; 
	dac_data[3] = dac_data3; 

	ZONE7_BUF[0x30] = dac_data[0] ;
	Nop();
	Nop();
	ZONE7_BUF[0x32] = dac_data[1];
	Nop();
	Nop();
	ZONE7_BUF[0x34] = dac_data[2];
	Nop();
	Nop();
	ZONE7_BUF[0x36] = dac_data[3];
	Nop();
	Nop();
	ZONE7_BUF[0x60] = 1;
	Nop();
	Nop();
	Nop();
	Nop();
	ZONE7_BUF[0x60] = 7;
}
#endif

//===========================================================================
// End of file.
//===========================================================================

