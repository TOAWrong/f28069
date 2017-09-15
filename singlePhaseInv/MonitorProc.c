#include	<header.h>
#include	<extern.h>

void monitor_proc()		// need_edit
{
    static int monitorCount=0;
    int temp;
    float ftemp;
	char str[50]= {0};

	Uint32 RunTimeMsec=0 ;
	static unsigned long StartTimeMsec = 0 ;

	RunTimeMsec = ulGetTime_mSec( StartTimeMsec);
	if(RunTimeMsec < 500) return;	// 500msec ���� �ѹ��� 
	StartTimeMsec = ulGetNow_mSec( );

	if( gMachineState == STATE_POWER_ON ){
		temp = (int)(floor(Vdc +0.5));
		snprintf( gStr1,10," VDC =%4d",temp);
		load_sci_tx_mail_box(gStr1);delay_msecs(20);
        snprintf( str,19,"No%d adc=%4d",monitorCount,adc_result[monitorCount]);
        load_scia_tx_mail_box(str); delay_msecs(10);
        monitorCount++;
        if(monitorCount>5) monitorCount = 0;
	}
    else if( gMachineState == STATE_TRIP ){
        if( monitorCount == 0 ){
            load_scia_tx_mail_box("TRIP");
       }
        else if( monitorCount == 1 ){
            load_scia_tx_mail_box(TripInfoNow.MSG);
        }
        else if( monitorCount == 2 ){
            snprintf( str,20,"CODE=%d",TripInfoNow.CODE); load_scia_tx_mail_box(str);
        }
        else if( monitorCount == 3 ){
            //snprintf( str,25,"Trip DATA= %.2f",TripInfoNow.DATA); load_scia_tx_mail_box(str);
            sprintf( str,"DATA=%e",TripInfoNow.DATA); load_scia_tx_mail_box(str);
        }
        else if( monitorCount == 4 ){
            //snprintf( str,25,"Trip DATA= %.2f",TripInfoNow.CURRENT); load_scia_tx_mail_box(str);
            ftemp = (floor(TripInfoNow.CURRENT +0.5));
            sprintf( str,"Irms=%e",ftemp); load_scia_tx_mail_box(str);
        }
        else if( monitorCount == 5 ){
            // snprintf( str,20,"Trip Vdc= %.2f",TripInfoNow.RPM); load_scia_tx_mail_box(str);
            sprintf( str,"RPM =%e",TripInfoNow.RPM); load_scia_tx_mail_box(str);
        }
        else if( monitorCount == 6 ){
            // snprintf( str,20,"Trip Vdc= %.2f",TripInfoNow.RPM); load_scia_tx_mail_box(str);
            sprintf( str,"VDC =%e",TripInfoNow.VDC); load_scia_tx_mail_box(str);
        }
        else{
            monitorCount = 0;
        }
        monitorCount ++;
        if(monitorCount>6) monitorCount = 0;
    }
    else {
        if( monitorCount == 0 ){
            load_scia_tx_mail_box(MonitorMsg);
       }
        else if( monitorCount == 1 ){
            temp = (int)(floor(rmsIm * 10 + 0.5));
            snprintf( str,10,"Im  =%2d.%d ",temp/10, temp%10); load_scia_tx_mail_box(str);
        }
        else if( monitorCount == 2 ){
            temp = (int)(floor(rmsIa * 10 + 0.5));
            snprintf( str,10,"Ia  =%2d.%d ",temp/10, temp%10); load_scia_tx_mail_box(str);
        }
        else if( monitorCount == 3 ){
            temp = (int)(floor(lpfVdc  + 0.5));
            snprintf( str,10,"Vdc =%4d",temp); load_scia_tx_mail_box(str);
        }
        else{
            monitorCount = 0;
        }
        monitorCount ++;
        if(monitorCount>3) monitorCount = 0;
	}
}

void GetInputMark(char * str)
{
	strncpy(str,"xxxx",20);			// debug

/*
	char str2[30]= "TEST";
	str2[0] = 'I';
	str2[1] = 'N';
	str2[2] = 'P';
	str2[3] = 'U';
	str2[4] = 'T';
	str2[5] = '[';

	if(terminal_input_state & 0x0001 ) 	str2[6] = 'I';
	else								str2[6] = 'O';

	if(terminal_input_state & 0x0002 ) 	str2[7] = 'I';
	else								str2[7] = 'O';

	if(terminal_input_state & 0x0004 ) 	str2[8] = 'I';
	else								str2[8] = 'O';

	if(terminal_input_state & 0x0008 ) 	str2[9] = 'I';
	else								str2[9] = 'O';

	if(terminal_input_state & 0x0010 ) 	str2[10] = 'I';
	else								str2[10] = 'O';

	if(terminal_input_state & 0x0020 ) 	str2[11] = 'I';
	else								str2[11] = 'O';

	if(terminal_input_state & 0x0040 ) 	str2[12] = 'I';
	else								str2[12] = 'O';

	if(terminal_input_state & 0x0080 ) 	str2[13] = 'I';
	else								str2[13] = 'O';

	str2[18] = ']';
	str2[19] = '_'; 
	str2[20] = 0; 
	strncpy(str,str2,20);
*/
}

//==================================
// End of file.
//==================================

