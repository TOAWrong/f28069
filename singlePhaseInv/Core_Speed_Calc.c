
#include	<header.h>
#include	<extern.h>

// Wrpm_mt Wrpm_est Wrm_det -> 변수 확인 
#define 	PPR			1024
#define		SPD1		52.359877559
#define		SPD2		1.0471975511
#define CPU_CLOCK            (150.e+6)   
#define   TSAMP_SPD      (800.e-6)
//#define SPEED_CALC_PRD      (CPU_CLOCK*TSAMP_SPD)       // EQEP Timer Period
#define SPEED_CALC_PRD      120000					      // EQEP Timer Period
//#define SPEED_OB_GAIN      (1000.*200.e-6/TSAMP_SPD)   // Speed Observer 
#define SPEED_OB_GAIN      250.0   // Speed Observer 
//	Pulse2Thetarm = (2.*PI)/(4.*PPR);
#define	Pulse2Thetarm 0.0015339807
//		Kt = (3./2.)*Pole_pair*Lm/Lr*LAMdre_ref;
#define Kt		1.3154935116


double Ls=0.2543;
double Lr=0.2543;
double Lm=0.2478;
double Jm=4.085e-2;

double L3_sp_est = 0.0;
double L3_sp_tmp;
double Pole_pair = 2.0;
double LAMdre_ref = 0.45;

//double Iqse_ref;
double inv_Jm;

double L2_sp_est = 0.0;
double L1_sp_est = 0.0;
// RPM2WRM

double Wrm_det = 0.0;

double Wrm_det_flt = 0.0;
double Wr = 0.0;
double Wrpm_det = 0.0;
double Wrpm_max = 0.0;
// Flag" is undefined


void  EQEP_Initialization(void)
{										// 0~59999
	EQep1Regs.QUPRD=SPEED_CALC_PRD-1;	// Unit Timer 
	EQep1Regs.QDECCTL.bit.QSRC=00;		// QEP quadrature count mode
		
	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
	EQep1Regs.QEPCTL.bit.PCRM=00;		// PCRM=00 mode - QPOSCNT reset on index event
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on QPOSCNT :0, unit time out :1
	EQep1Regs.QPOSMAX=0xffffffff;
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable
		
	EQep1Regs.QCAPCTL.bit.UPPS=0;   	// 1/1 for unit position
	EQep1Regs.QCAPCTL.bit.CCPS=0;		// 1/1 for CAP clock
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable
	
	EQep1Regs.QPOSCNT=0;
	EQep1Regs.QCTMR=0;
	EQep1Regs.QPOSLAT=0;
	EQep1Regs.QCTMRLAT=0;
	EQep1Regs.QCPRD=0xffff;
	EQep1Regs.QPOSLAT= 0;

}

double MT_Time, a;
double K_Wrm= 0.,K_Wrm1= 0., K_Wrm2= 0.;
double Thetarm_enc= 0.; 
double Te_tmp=0., Wrm_tmp=0., Thetarm_tmp=0., err_tmp=0., Tl_tmp=0.; 
long pls, mt, pulse_num, i;
long Pulse_Counter_MT= 0., Pulse_Counter_est=0.; 
long Dir_mt=1, Dir_est=1;
long	MT_Timer= 0.,  Overflow_num=0., Flag_first_MT= 0.;
double Tl_est= 0.;
double Wrm_mt= 0., Wrm_mt_flt= 0., Wrm_mt_old= 0.;
double Wrm_est= 0., Wrm_est_flt= 0., Wrm_est_old= 0.;
double Wrm_det_old= 0.; 
double Thetarm_err= 0., Thetarm_est= 0.; 

void Speed_Calculation()
{
/*
	long pls, mt, pulse_num, i;	
	double MT_Time, a;
	double K_Wrm= 0.,K_Wrm1= 0., K_Wrm2= 0.;
	double Pulse2Thetarm= 0., Thetarm_enc= 0.; 
	double Te_tmp=0., Wrm_tmp=0., Thetarm_tmp=0., err_tmp=0., Tl_tmp=0.; 
	static long Pulse_Counter_MT= 0., Pulse_Counter_est=0.; 
	static long Dir_mt=1, Dir_est=1;
	static long	MT_Timer= 0.,  Overflow_num=0., Flag_first_MT= 0.;
	static double Tl_est= 0.;
	static double Wrm_mt= 0., Wrm_mt_flt= 0., Wrm_mt_old= 0.;
	static double Wrm_est= 0., Wrm_est_flt= 0., Wrm_est_old= 0.;
	static double Wrm_det_old= 0.; 
	static double Thetarm_err= 0., Thetarm_est= 0.; 
//	static double Wrpm_mt=0., Wrpm_est=0., Theta_rm_mt=0.;
*/
	if(EQep1Regs.QFLG.bit.UTO==1) // If unit timeout (one 2500Hz period)
	{ 	
	/*----------------------------------------------*/
	/*					 MT							*/
	/*----------------------------------------------*/
		
//		if (Flag.ETC.bit.FAULT_RESET)
//			Flag.Fault.bit.SPEED_DETECTION= 0;		
		/* to inititial routine */

		if(Flag_first_MT==0) 
		{
			Flag_first_MT=1;
			Pulse_Counter_est = Pulse_Counter_MT = (EQep1Regs.QPOSLAT)&(0xffff);
			MT_Timer = (EQep1Regs.QCTMRLAT)&(0xffff);
		}
		else 
		{
			pls = (EQep1Regs.QPOSLAT)&(0xffff);
			mt = (EQep1Regs.QCTMRLAT)&(0xffff);

	
			/* MT Rountine */
			if(pls!=Pulse_Counter_MT) 
			{
				i = pls - Pulse_Counter_MT;
				if(i>(32768))		pulse_num = i - (65536);
				else if(i<-(32768))	pulse_num = i + (65536);
				else				pulse_num = i;
				Pulse_Counter_MT=pls;

   				/* Dir_mt : 1(positive) -1(negative) */		
				a = pulse_num;
				if(pulse_num*Dir_mt<0) 
				{
					a +=Dir_mt/2.;
					Dir_mt*=-1;
				} 

				MT_Time = TSAMP_SPD*(Overflow_num + 1)+ (1./CPU_CLOCK)*(float)(MT_Timer-mt);
				MT_Timer = mt;
//				Theta_rm_mt=Pulse2Thetarm*a;
				Wrm_mt = Pulse2Thetarm*a/MT_Time; 

				Overflow_num =0;
			}
			else 
			{
				Overflow_num ++;
//				Theta_rm_mt=0;
				a = TSAMP_SPD*Overflow_num + (1./CPU_CLOCK)*(float)(MT_Timer);
				if( (a>50.e-3) )	Wrm_mt=0.;
				else 
				{
					a = Pulse2Thetarm*Dir_mt/a;
					if( fabs(Wrm_mt)>fabs(a) )
						Wrm_mt = a;
				}
			}
		}

	/*----------------------------------------------*/
	/*		      Speed Observer					*/
	/*----------------------------------------------*/
		L1_sp_est= 3*SPEED_OB_GAIN;
		L2_sp_est= 3*SPEED_OB_GAIN*SPEED_OB_GAIN;
		L3_sp_est= -(SPEED_OB_GAIN*SPEED_OB_GAIN*SPEED_OB_GAIN)*Jm;
//		L3_sp_est= L3_sp_tmp*Jm; 
	
		pls = (EQep1Regs.QPOSLAT)&(0xffff);
		i = pls - Pulse_Counter_est;
		if(i>(32768))		pulse_num = i - (65536);
		else if(i<-(32768))	pulse_num = i + (65536);
		else				pulse_num = i;
		Pulse_Counter_est=pls;

		/* Direction */
		a = pulse_num;
   		if(pulse_num*Dir_est<0) {
			a +=Dir_est/2.;
			Dir_est*=-1;
		}  

		/* Thetarm_enc */
		Thetarm_enc = Pulse2Thetarm*a;

		/* Calculate torque */
//		Kt = (3./2.)*Pole_pair*Lm/Lr*LAMdre_ref;
//		Te_tmp = Kt*Iqse_ref;  // Iqse_ref = Is_dq[qs];
		Te_tmp = Kt*Is_dq[qs];

		/* Open Loop Estimation */
		Wrm_tmp = Wrm_est + (Te-Tl_est)*(TSAMP_SPD*inv_Jm);
		Thetarm_tmp = Thetarm_est + (TSAMP_SPD/2.)*(Wrm_est+Wrm_tmp);

		/* Closed Loop Estimation */
		err_tmp = Thetarm_enc-Thetarm_tmp;		
		a = Thetarm_err + err_tmp;
 		Tl_tmp = Tl_est + (L3_sp_est*a)*(TSAMP_SPD/2.);
  		Wrm_tmp = Wrm_est + (TSAMP_SPD/2.) 
  			* ( (Te+Te_tmp-Tl_est-Tl_tmp)*inv_Jm + L2_sp_est*a );
		Thetarm_tmp = Thetarm_est + TSAMP_SPD/2.*( (Wrm_est+Wrm_tmp) + L1_sp_est*a );

		/* Updating States */
		Thetarm_err = err_tmp;
		Thetarm_est = Thetarm_tmp - Thetarm_enc;
		Wrm_est = Wrm_tmp;
		Tl_est = Tl_tmp;
		Te = Te_tmp;

		Wrm_est_flt = 0.5*(Wrm_est+Wrm_est_old);
		Wrm_est_old = Wrm_est;

		Wrm_mt_flt = 0.5*(Wrm_mt+Wrm_mt_old);
		Wrm_mt_old = Wrm_mt;	

		a = fabs(Wrm_mt_flt);
		if(a>=(2.*SPD1))  	K_Wrm1=0.;
		else if(a<=SPD1) 	K_Wrm1=1.;
		else				K_Wrm1=2.-a/SPD1;

		a = fabs(Wrm_est_flt - Wrm_mt_flt);
		if( a < SPD2 ) {
			K_Wrm2 = -a*a/(2.*SPD2*SPD2)+1.;
		}
		else if ( a < (2.*SPD2) ) {
			a = a - (2.*SPD2);
			K_Wrm2 = a*a/(2.*SPD2*SPD2);
		}
		else	K_Wrm2 = 0.;
		K_Wrm = K_Wrm1*K_Wrm2; 
//		K_Wrm = 0.;
	
		Wrm_det = (1.-K_Wrm)*Wrm_mt_flt + K_Wrm*Wrm_est_flt;
		Wrm_det_flt = 0.5*(Wrm_det+Wrm_det_old);		// Wc = 2/T = 2/100u = 20,000 rad/s
		Wrm_det_old = Wrm_det;
		Wr = Wrm_det_flt*Pole_pair;
		Wrpm_det = (60./(2.*PI))*Wrm_det; 
		

//		if (fabs(Wrpm_det)>Wrpm_max)	Flag.Fault.bit.OVER_SPEED= 1; 

		// QEP initialization
		EQep1Regs.QCLR.bit.UTO=1;  // Clear Unit Timer Flag
  		EQep1Regs.QEPSTS.all=0x00; // Clear All flag
								   
	}
	else // 속도 측정 하지 않으면  Fault 발생
	{
//		Flag.Fault.bit.SPEED_DETECTION= 1.;
	}

}




