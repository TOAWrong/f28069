//
//--- single phase space vector modulation
#include	<header.h>
#include	<extern.h>
// space vector pwm
// Input    :  Vs_dq[ds], Vs_dq[qs]
// Output   : DutyRatio[u], DutyRatio[v], DutyRatio[w]
#define Vdc_MIN                     10.0
#define inv_Vdc_MIN                 0.1

void SpaceVectorModulation( double * Vs_dqIn )
{
    unsigned sector;
    double  Vx,Vy;
    double  Dx,Dy,Dxy,Dz;
    double  inv_Vdc;
    Uint16 temp;

    if (Vs_dqIn[qs]>=0) {
        if (fabs(0.57735*Vs_dqIn[qs])<fabs(Vs_dqIn[ds])){
            if (Vs_dqIn[ds]>=0){
                sector=1; Vx=Vs_dqIn[ds]-0.57735*Vs_dqIn[qs];   Vy=1.154701*Vs_dqIn[qs];
            }
            else{
                sector=3; Vx=1.154701*Vs_dqIn[qs]; Vy=-(Vs_dqIn[ds]+0.57735*Vs_dqIn[qs]);
            }
        }
        else{
                sector=2; Vx=Vs_dqIn[ds]+0.57735*Vs_dqIn[qs]; Vy=-Vs_dqIn[ds]+0.57735*Vs_dqIn[qs];
        }
    }
    else
    {
        if  (fabs(0.57735*Vs_dqIn[qs])<fabs(Vs_dqIn[ds]))
        {
            if (Vs_dqIn[ds]>=0){
                sector=6;   Vx=-1.154701*Vs_dqIn[qs]; Vy=Vs_dqIn[ds]+0.57735*Vs_dqIn[qs];
            } else{
                sector=4; Vx=0.57735*Vs_dqIn[qs]-Vs_dqIn[ds]; Vy=-1.154701*Vs_dqIn[qs];
            }
        } else{
                sector=5; Vx=-Vs_dqIn[ds]-0.57735*Vs_dqIn[qs]; Vy=Vs_dqIn[ds]-0.57735*Vs_dqIn[qs];
        }
    }

    if (Vdc>Vdc_MIN){
        inv_Vdc = 1.0 / Vdc;
        Dx = 1.5* Vx * inv_Vdc;     // Maximum available voltage = 2.0*Vdc/3.0
        Dy = 1.5 *Vy * inv_Vdc;
        Dxy= Dx+Dy;
    }else {
        Dx=1.5*Vx*inv_Vdc_MIN;      // Maximum available voltage = 2.0*Vdc/3.0
        Dy=1.5*Vy*inv_Vdc_MIN;
        Dxy=Dx+Dy;
    }

    if (Dxy>=1.0) {
        if (Dx>Dy)  { Dx=Dx/Dxy; Dy=1.0-Dx; }
        else        { Dy=Dy/Dxy; Dx=1.0-Dy; }
        Dxy=1.0;    Dz=0;
    } else    Dz=0.5*(1.0-Dxy);

    switch (sector) {
        case 1 :    DutyRatio[u]=Dxy+Dz;    DutyRatio[v]=Dy+Dz;     DutyRatio[w]=Dz;        break;
        case 2 :    DutyRatio[u]=Dx+Dz;     DutyRatio[v]=Dxy+Dz;    DutyRatio[w]=Dz;        break;
        case 3 :    DutyRatio[u]=Dz;        DutyRatio[v]=Dxy+Dz;    DutyRatio[w]=Dy+Dz;     break;
        case 4 :    DutyRatio[u]=Dz;        DutyRatio[v]=Dx+Dz;     DutyRatio[w]=Dxy+Dz;    break;
        case 5 :    DutyRatio[u]=Dy+Dz;     DutyRatio[v]=Dz;        DutyRatio[w]=Dxy+Dz;    break;
        case 6 :    DutyRatio[u]=Dxy+Dz;    DutyRatio[v]=Dz;        DutyRatio[w]=Dx+Dz;     break;
    }

    temp = (Uint16)(MAX_PWM_CNT * DutyRatio[u] );
    DutyCount[u] = ( temp < DEAD_TIME_COUNT) ? 0 : temp ;
    DutyCount[u] = ( (MAX_PWM_CNT -temp ) < DEAD_TIME_COUNT) ? MAX_PWM_CNT : temp;

    temp = (Uint16)(MAX_PWM_CNT * DutyRatio[v] );
    DutyCount[v] = ( temp < DEAD_TIME_COUNT) ? 0 : temp ;
    DutyCount[v] = ( (MAX_PWM_CNT -temp ) < DEAD_TIME_COUNT) ? MAX_PWM_CNT : temp;

    temp = (Uint16)(MAX_PWM_CNT * DutyRatio[w] );
    DutyCount[w] = ( temp < DEAD_TIME_COUNT) ? 0 : temp ;
    DutyCount[w] = ( (MAX_PWM_CNT -temp ) < DEAD_TIME_COUNT) ? MAX_PWM_CNT : temp;
}

#define inv_Min_Isw     20
#define Dt_us           4
double  Dd, T_d,delta_Tc;

void VoltageEstimation()
{
    T_d=1.0e-6*Dt_us;
    Dd=T_d*inv_Ts;

//--- U phase
    sgn_Is[as]=Is_abc[as]*inv_Min_Isw;
    sgn_Is[as] = ( sgn_Is[as] > 1.0) ? 1.0 : -1.0;
    Vs_abc_ref[as] = ( DutyRatio[u] - 0.5)*Vdc;
    Vs_abc[as]=Vs_abc_ref[as] - sgn_Is[as]*Dd*Vdc;
//--- V phase
    sgn_Is[bs]=Is_abc[bs]*inv_Min_Isw;
    sgn_Is[bs] = ( sgn_Is[bs] > 1.0) ? 1.0 : -1.0;
    Vs_abc_ref[bs] = ( DutyRatio[v] - 0.5)*Vdc;
    Vs_abc[bs]=Vs_abc_ref[bs] - sgn_Is[bs]*Dd*Vdc;
//--- W phase
    sgn_Is[cs]=Is_abc[cs]*inv_Min_Isw;
    sgn_Is[cs] = ( sgn_Is[cs] > 1.0) ? 1.0 : -1.0;
    Vs_abc_ref[cs] = ( DutyRatio[w] - 0.5)*Vdc;
    Vs_abc[cs]=Vs_abc_ref[cs] - sgn_Is[cs]*Dd*Vdc;

    Vs_dq_ref[ds]=0.66666667*(Vs_abc_ref[as] - 0.5*Vs_abc_ref[bs] - 0.5*Vs_abc_ref[cs]);    // 2/3=0.666666667
    Vs_dq_ref[qs]=0.57735027*(Vs_abc_ref[bs] - Vs_abc_ref[cs]);                             // 1.0/sqrt(3.0)=0.57735027
    Vs_dq[ds]=0.66666667*(Vs_abc[as] - 0.5*Vs_abc[bs] - 0.5*Vs_abc[cs]);                    // 2/3=0.666666667
    Vs_dq[qs]=0.57735027*(Vs_abc[bs] - Vs_abc[cs]);                                         // 1.0/sqrt(3.0)=0.57735027
}

const double pwmCoeff[6][4] = {{1.0   ,ROOT2  ,0.0            ,PI_DIV4    },
                             {1.0   ,ROOT2  ,PI_DIV2        ,PI_DIV4    },
                             {1.0   ,1.0    ,PI_DIV2        ,PI         },
                             {ROOT2 ,1.0    ,PI + PI_DIV4   ,PI         },
                             {ROOT2 ,1.0    ,PI + PI_DIV4   ,PI + PI_DIV2},
                             {1.0   ,1.0    ,0.0            ,PI + PI_DIV2}};
// end of file
