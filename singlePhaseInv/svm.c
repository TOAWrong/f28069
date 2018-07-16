//
//--- single phase space vector modulation
#include	<header.h>
#include	<extern.h>

#define	Vdc_MIN						10.0
#define	inv_Vdc_MIN					0.1

const double pwmCoeff[6][4] = {{1.0   ,ROOT2  ,0.0            ,PI_DIV4    },
                             {1.0   ,ROOT2  ,PI_DIV2        ,PI_DIV4    },
                             {1.0   ,1.0    ,PI_DIV2        ,PI         },
                             {ROOT2 ,1.0    ,PI + PI_DIV4   ,PI         },
                             {ROOT2 ,1.0    ,PI + PI_DIV4   ,PI + PI_DIV2},
                             {1.0   ,1.0    ,0.0            ,PI + PI_DIV2}};

void singlePhaseModulation( double m, double thetaIn, double dutyRatio[3])
{
    int sector;
    double vectorDuty[3];

    if     ( thetaIn < PI_DIV4    )   sector = 0;
    else if( thetaIn < PI_DIV2    )   sector = 1;
    else if( thetaIn < PI         )   sector = 2;
    else if( thetaIn < PI+PI_DIV4 )   sector = 3;
    else if( thetaIn < PI+PI_DIV2 )   sector = 4;
    else                            sector = 5;

    vectorDuty[1] = m * sin(pwmCoeff[sector][3] - thetaIn) / ( pwmCoeff[sector][0] * sin(pwmCoeff[sector][3] - pwmCoeff[sector][2]));
    vectorDuty[2] = m * sin(thetaIn - pwmCoeff[sector][2] ) / ( pwmCoeff[sector][1] * sin(pwmCoeff[sector][3] - pwmCoeff[sector][2]));
    vectorDuty[0] = 1.0 - (vectorDuty[1] + vectorDuty[2]);

    switch(sector){
    case 0:
        dutyRatio[0] = vectorDuty[0]*0.5 + vectorDuty[1] + vectorDuty[2];
        dutyRatio[1] = vectorDuty[0]*0.5;
        dutyRatio[2] = vectorDuty[0]*0.5 + vectorDuty[2];
        break;
    case 1:
        dutyRatio[0] = vectorDuty[0]*0.5 + vectorDuty[2];
        dutyRatio[1] = vectorDuty[0]*0.5;
        dutyRatio[2] = vectorDuty[0]*0.5 + vectorDuty[1]+ vectorDuty[2];
        break;
    case 2:
        dutyRatio[0] = vectorDuty[0]*0.5;
        dutyRatio[1] = vectorDuty[0]*0.5 + vectorDuty[2];
        dutyRatio[2] = vectorDuty[0]*0.5 + vectorDuty[1] + vectorDuty[2];
        break;
    case 3:
        dutyRatio[0] = vectorDuty[0]*0.5;
        dutyRatio[1] = vectorDuty[0]*0.5 + vectorDuty[1] + vectorDuty[2];
        dutyRatio[2] = vectorDuty[0]*0.5 + vectorDuty[2];
        break;
    case 4:
        dutyRatio[0] = vectorDuty[0]*0.5 + vectorDuty[2];
        dutyRatio[1] = vectorDuty[0]*0.5 + vectorDuty[1] + vectorDuty[2];
        dutyRatio[2] = vectorDuty[0]*0.5;
        break;
    case 5:
        dutyRatio[0] = vectorDuty[0]*0.5 + vectorDuty[1] + vectorDuty[2];
        dutyRatio[1] = vectorDuty[0]*0.5 + vectorDuty[2];
        dutyRatio[2] = vectorDuty[0]*0.5;
        break;
    }
}
//========================
// end of file
//========================
