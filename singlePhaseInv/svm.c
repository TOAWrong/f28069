#include	<header.h>
#include	<extern.h>

#define	Vdc_MIN						10.0
#define	inv_Vdc_MIN					0.1

void SpaceVectorModulation( float *Vs_dq)
{

    unsigned sector;
	float	Vx,Vy;
	float 	Dx,Dy,Dxy,Dz;
	float	inv_Vdc;

	Vdc = 300.0;
	if (Vs_dq[qs]>=0) {
		if (fabs(0.57735*Vs_dq[qs])<fabs(Vs_dq[ds])){
			if (Vs_dq[ds]>=0){ sector=1; Vx=Vs_dq[ds]-0.57735*Vs_dq[qs];	Vy=1.154701*Vs_dq[qs];}
			else{ 				sector=3; Vx=1.154701*Vs_dq[qs]; Vy=-(Vs_dq[ds]+0.57735*Vs_dq[qs]);}		
		}
		else{ sector=2; Vx=Vs_dq[ds]+0.57735*Vs_dq[qs]; Vy=-Vs_dq[ds]+0.57735*Vs_dq[qs];
		}
	}
	else{
		if  (fabs(0.57735*Vs_dq[qs])<fabs(Vs_dq[ds])){
			if (Vs_dq[ds]>=0){ sector=6;	Vx=-1.154701*Vs_dq[qs];	Vy=Vs_dq[ds]+0.57735*Vs_dq[qs];	}
			else{				sector=4; Vx=0.57735*Vs_dq[qs]-Vs_dq[ds]; Vy=-1.154701*Vs_dq[qs];	}
		}
		else{ sector=5; Vx=-Vs_dq[ds]-0.57735*Vs_dq[qs]; Vy=Vs_dq[ds]-0.57735*Vs_dq[qs];
		}
	}
	if (Vdc>Vdc_MIN){
		inv_Vdc = 1.0 / Vdc;
		Dx = 1.5* Vx * inv_Vdc;		// Maximum available voltage = 2.0*Vdc/3.0 
		Dy = 1.5 *Vy * inv_Vdc;						
		Dxy= Dx+Dy;
	}
	else{
		Dx=1.5*Vx*inv_Vdc_MIN;		// Maximum available voltage = 2.0*Vdc/3.0 
		Dy=1.5*Vy*inv_Vdc_MIN;						
		Dxy=Dx+Dy;
	}

	if (Dxy>=1.0){
		if (Dx>Dy)	{ Dx=Dx/Dxy; Dy=1.0-Dx; }
		else		{ Dy=Dy/Dxy; Dx=1.0-Dy;	}
		Dxy=1.0;	Dz=0;
	}
	else 	Dz=0.5*(1.0-Dxy);

	switch (sector)
	{
		case 1 :	DutyRatio[u]=Dxy+Dz;	DutyRatio[v]=Dy+Dz; 	DutyRatio[w]=Dz;		break;
		case 2 :	DutyRatio[u]=Dx+Dz; 	DutyRatio[v]=Dxy+Dz; 	DutyRatio[w]=Dz;		break;
		case 3 :	DutyRatio[u]=Dz; 		DutyRatio[v]=Dxy+Dz; 	DutyRatio[w]=Dy+Dz; 	break;
		case 4 :	DutyRatio[u]=Dz; 		DutyRatio[v]=Dx+Dz; 	DutyRatio[w]=Dxy+Dz;	break;
		case 5 :	DutyRatio[u]=Dy+Dz; 	DutyRatio[v]=Dz; 		DutyRatio[w]=Dxy+Dz;	break;
		case 6 :	DutyRatio[u]=Dxy+Dz; 	DutyRatio[v]=Dz; 		DutyRatio[w]=Dx+Dz;		break;
	}

	DutyCount[u] = (Uint16)(MAX_PWM_CNT * (1-DutyRatio[u]) );
	DutyCount[v] = (Uint16)(MAX_PWM_CNT * (1-DutyRatio[v]) );
	DutyCount[w] = (Uint16)(MAX_PWM_CNT * (1-DutyRatio[w]) );
}  

#define Dt_us						4
float 	Dd;
float 	T_d;
float 	delta_Tc;
#define inv_Min_Isw 				20

void VoltageEstimation_bk()
{
   T_d=1.0e-6*Dt_us;
   T_d=0.0;
   Dd=T_d*inv_Ts;   
 
//-- V_as   
   Vs_abc_ref[as]=( DutyRatio[u] - 0.5)*Vdc;
   if (Is_abc[as]>=0.0)      
         sgn_Is[as]=1.0;
   else    sgn_Is[as]=-1.0;

   if (fabs(Is_abc[as])<0.01)
         delta_Tc=T_d;
   else   delta_Tc=Vdc*2*C_ce/fabs(Is_abc[as]);

   if (delta_Tc<T_d)
         Vs_abc[as]=Vs_abc_ref[as]-sgn_Is[as]*(Dd-0.5*delta_Tc*inv_Ts)*Vdc;
   else   Vs_abc[as]=Vs_abc_ref[as]-sgn_Is[as]*0.25*fabs(Is_abc[as])*T_d*Dd*inv_C_ce;     

//V_bs   
   Vs_abc_ref[bs]=( DutyRatio[v] - 0.5)*Vdc;
   if (Is_abc[bs]>=0.0)      
         sgn_Is[bs]=1.0;
   else    sgn_Is[bs]=-1.0;
   if (fabs(Is_abc[bs])<0.01)
         delta_Tc=T_d;
   else   delta_Tc=Vdc*2*C_ce/fabs(Is_abc[bs]);
   if (delta_Tc<T_d)
         Vs_abc[bs]=Vs_abc_ref[bs]-sgn_Is[bs]*(Dd-0.5*delta_Tc*inv_Ts)*Vdc;
   else   Vs_abc[bs]=Vs_abc_ref[bs]-sgn_Is[bs]*0.25*fabs(Is_abc[bs])*T_d*Dd*inv_C_ce;
   
//V_cs   

   Vs_abc_ref[cs]=(DutyRatio[w] - 0.5)*Vdc;
   if (Is_abc[cs]>=0.0)      
         sgn_Is[cs]=1.0;
   else    sgn_Is[cs]=-1.0;
   if (fabs(Is_abc[cs])<0.01)
         delta_Tc=T_d;
   else   delta_Tc=Vdc*2*C_ce/fabs(Is_abc[cs]);
   if (delta_Tc<T_d)
         Vs_abc[cs]=Vs_abc_ref[cs]-sgn_Is[cs]*(Dd-0.5*delta_Tc*inv_Ts)*Vdc;
   else   Vs_abc[cs]=Vs_abc_ref[cs]-sgn_Is[cs]*0.25*fabs(Is_abc[cs])*T_d*Dd*inv_C_ce;

	Vs_dq_ref[ds]=0.66666667*(Vs_abc_ref[as] - 0.5*Vs_abc_ref[bs] - 0.5*Vs_abc_ref[cs]);	// 2/3=0.666666667
	Vs_dq_ref[qs]=0.57735027*(Vs_abc_ref[bs] - Vs_abc_ref[cs]);								// 1.0/sqrt(3.0)=0.57735027
	Vs_dq[ds]=0.66666667*(Vs_abc[as] - 0.5*Vs_abc[bs] - 0.5*Vs_abc[cs]);					// 2/3=0.666666667
	Vs_dq[qs]=0.57735027*(Vs_abc[bs] - Vs_abc[cs]);											// 1.0/sqrt(3.0)=0.57735027
}

void VoltageEstimation()
{

//	T_d=1.0e-6*Dt_us;
	T_d=0.0;
	Dd=T_d*inv_Ts;	
//	Dd=T_d*inv_Ts;	

//--- U phase		
	sgn_Is[as]=Is_abc[as]*inv_Min_Isw;							//������ ũ�⿡ ���� ���� Ÿ�Ӱ��  
	if (sgn_Is[as]>1.0)			sgn_Is[as]=1.0;
	else if (sgn_Is[as]<-1.0)	sgn_Is[as]=-1.0;
	
	Vs_abc_ref[as] = ( DutyRatio[u] - 0.5)*Vdc;
	Vs_abc[as]=Vs_abc_ref[as] - sgn_Is[as]*Dd*Vdc;

//--- V phase	
	sgn_Is[bs]=Is_abc[bs]*inv_Min_Isw;							//������ ũ�⿡ ���� ���� Ÿ�Ӱ��  
	if (sgn_Is[bs]>1.0)			sgn_Is[bs]=1.0;
	else if (sgn_Is[bs]<-1.0)	sgn_Is[bs]=-1.0;

	Vs_abc_ref[bs] = ( DutyRatio[v] - 0.5)*Vdc;
	Vs_abc[bs]=Vs_abc_ref[bs] - sgn_Is[bs]*Dd*Vdc;

//--- W phase	
	sgn_Is[cs]=Is_abc[cs]*inv_Min_Isw;							//������ ũ�⿡ ���� ���� Ÿ�Ӱ��  
	if (sgn_Is[cs]>1.0)			sgn_Is[cs]=1.0;
	else if (sgn_Is[cs]<-1.0)	sgn_Is[cs]=-1.0;

	Vs_abc_ref[cs] = ( DutyRatio[w] - 0.5)*Vdc;
	Vs_abc[cs]=Vs_abc_ref[cs] - sgn_Is[cs]*Dd*Vdc;	

	Vs_dq_ref[ds]=0.66666667*(Vs_abc_ref[as] - 0.5*Vs_abc_ref[bs] - 0.5*Vs_abc_ref[cs]);	// 2/3=0.666666667
	Vs_dq_ref[qs]=0.57735027*(Vs_abc_ref[bs] - Vs_abc_ref[cs]);								// 1.0/sqrt(3.0)=0.57735027
	Vs_dq[ds]=0.66666667*(Vs_abc[as] - 0.5*Vs_abc[bs] - 0.5*Vs_abc[cs]);					// 2/3=0.666666667
	Vs_dq[qs]=0.57735027*(Vs_abc[bs] - Vs_abc[cs]);											// 1.0/sqrt(3.0)=0.57735027
}

//========================
// end of file
//========================
