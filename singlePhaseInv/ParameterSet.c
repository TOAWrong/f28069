#include	<header.h>
#include	<extern.h>

#define max_I_ratio     1.5

void VariableInitialization()
{
    double x1,x2,y1,y2;

    x1 = code_adc_vdc_low;       y1 = code_Vdc_calc_low;
    x2 = code_adc_vdc_high;       y2 = code_Vdc_calc_high;

    Vdc_factor = ( y2-y1) / ( x2 - x1 );
    Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

    C_ce_nF=(3.5-0.8)/(1000.0-100.0)*(2.0*Is_rat-100.0)+0.8;    // 1000A -> 3.5nF, 100A -> 0.8nF
    C_ce=1.0e-9*C_ce_nF;
    inv_C_ce=1.0/C_ce;

    gfRunTime=0.0;
    wr_Cycle=0.0;
    wr_CycleIndex=0;

    // reference
    reference_in=0.0;
    reference_out=0.0;  // new

    // °¢µµ, ÁÖÆÄ¼ö, ¼Óµµ
    we_in=0.0;
    we=0.0;
    we0=0.0;
    frequency=0.0;
    theta=0.0;
    SinTheta=0.0;
    CosTheta=1.0;
    CosDeltaTheta=0.0;
    SinDeltaTheta=1.0;

    wr_m0=0.0;
    wr_m=0.0;               // ½ÇÁ¦ ¼ÓµµÀÇ ÇÊÅÍ¸µ ÃÊ±â°ª = ½ÇÁ¦ ¼Óµµ
    wr=0.0;
    wr_ref=0.0;
    wr_ref=0.0;
    wr_err=0.0;
    wr_ErrInt=0.0;              // ¼ÓµµÁ¦¾î±âÀÇ ÀûºÐ·®
    w_sl=0.0;
    w_sl0=0.0;
    rpm=0.0;
    rpm_m=0.0;
    theta_m=0.0;
    rpm_ref=0.0;
    rpm_err=0.0;

    // Àü·ù
    Is_dq[ds]=Is_dq[qs]=0.0;
    Is_mag=0.0;
    Is_mag_rms=0.0;
    sgn_Is[as]=sgn_Is[bs]=sgn_Is[cs]=0.0;

    Is_DQ[DS]=Is_DQ[QS]=0.0;
    Is_DQ_max[DS]=Is_DQ_max[QS]=0.0;
    Is_DQ_ref[DS]=Is_DQ_ref[QS]=0.0;

    prev_I_QS=0.0;

    Is_DQ_ErrInt[DS]=Is_DQ_ErrInt[QS]=0.0;          // Àü·ùÁ¦¾î±âÀÇ ÀûºÐ·®

    // Àü¾Ð
    Vs_max=0.0;
    Vs_abc[as]=Vs_abc[bs]=Vs_abc[cs]=0.0;
    Vs_abc_ref[as]=Vs_abc_ref[bs]=Vs_abc_ref[cs]=0.0;
    Vs_dq_ref[ds]=Vs_dq_ref[qs]=0.0;
    Vs_dq[ds]=Vs_dq[qs]=0.0;
    Vo=0.0;
    Us_dq[ds]=Us_dq[qs]=0.0;
    Vs_DQ[DS]=Vs_DQ[QS]=0.0;
    Vs_DQ_max[DS]=Vs_DQ_max[QS]=0.0;
    Vs_DQ_ref[DS]=Vs_DQ_ref[QS]=0.0;
    Vs_DQ_comp[DS]=Vs_DQ_comp[QS]=0.0;
    Vs_max_FW=0.0;
    Vs_DQ_ref_P[DS]=Vs_DQ_ref_P[QS]=0.0;
    Vs_DQ_ref_PI[DS]=Vs_DQ_ref_PI[QS]=0.0;

    // ÅäÅ©
    Te_max=0.0;
    Te_ref=0.0;
    Te=0.0;

    // ÀÚ¼Ó
    Fs_ref0=0.0;
    Fs_ref=0.0;
    inv_Fs_ref=0.0;
    Fs_dq[ds]=Fs_dq[qs]=0.0;
    Fs=0.0;
    inv_Fs=0.0;
    Fr_ref=0.0;
    Fr_ref0=0.0;
    inv_Fr_ref=0.0;
    Fr=0.0;
    inv_Fr=0.0;
    Fr_Err=0.0;
    Fr_ErrInt=0.0;

    // VVVF-Control
    Vs_ref=0.0;
    Freq_ref=0.0;
    Freq_slip=0.0;
    Freq_out=0.0;
    Slip=0.0;
    Power_core=0.0;
    Power_core_rat=0.0;
    Power_gap=0.0;
    Vs_IR_comp=0.0;
    del_Vs_comp=0.0;

    Pf=0.0;
    sgn_I_QS=0.0;
    Delta_wr=0.0;
    I_DS0_0=0.0;
    I_DS0=0.0;
    I_DS_err=0.0;

    GainUpdateTimer=0.0;
    AutoTuningFlag=0;
    LPF_Is_Square=0.0;
    LPF_Is=0.0;
    LPF_Re_Power=0.0;
    LPF_Vs_Square=0.0;
    Vs_Coeff_Leq_Req=0.0;
    Is_dq_ref[ds]=Is_dq_ref[qs]=0.0;
    Is_dq_ErrInt[ds]=Is_dq_ErrInt[qs]=0.0;

    Freq_set=0.0;
    Re_Power=0.0;
    Im_Power=0.0;
    ref_time = 0.0; //new
}
void VariInit()
{
	float x1,x2,y1,y2;
// for Vdc calc 

    code_adc_vdc_low    = 100;
    code_Vdc_calc_low   = 10;
    code_adc_vdc_high   = 2500;
    code_Vdc_calc_high  = 300;

	x1 = code_adc_vdc_low;		y1 = code_Vdc_calc_low;
	x2 = code_adc_vdc_high;		y2 = code_Vdc_calc_high;
	Vdc_factor = ( y2-y1) / ( x2 - x1 );
	Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

    Vs_rat = sqrt(2.0)/sqrt(3.0) * codeRateVolt;         // 상전압의 피크 값
    Is_rat=sqrt(2.0)*codeRateCurrent;

    Is_max = Is_rat * max_I_ratio  / 100.0;
    inv_Is_rat=1.0/Is_rat;

    Kt=(3.0/2.0)*(codeMotorPole/2.0);
    inv_Kt=1.0/Kt;
    P_pair=(codeMotorPole/2.0);
    inv_P_pair=1.0/P_pair;

    Ts = 1.0 / codePwmFreq;  // pwm switching frequency
    inv_Ts = codePwmFreq;
    Freq_rat = codeRateHz;
    inv_Freq_rat=1.0/Freq_rat;
    inv_motor_rate_hz = 1.0 / codeRateHz; //   csk_check 2009.10.30.

	gfRunTime=0.0;

	// reference
	reference_in=0.0;
	reference_out=0.0;	// new
    theta=0.0;
	we=0.0;

    rpm_Coeff=60.0*inv_P_pair/PI_2;             // 회전수/분
}	

/*
void common_variable_init()
{
    Ts = 1.0 / SWITCH_FREQ; // pwm switching frequency
    inv_Ts=1.0/Ts;

    Vs_rat = sqrt(2.0)/sqrt(3.0) * motor_rate_volt;         // 상전압의 피크 값
    Is_rat=sqrt(2.0)*motor_rate_current;

    Is_max = Is_rat * max_I_ratio  / 100.0;
    inv_Is_rat=1.0/Is_rat;

    if( selected_motor ) over_current_level = motor2_I_limit_ratio; // debug
    else                 over_current_level = motor1_I_limit_ratio; // debug

    OverCurLimit = Is_rat * over_current_level / 100.0;

    we_rat=PI_2*motor_rate_hz;
    inv_motor_rate_hz=1.0/motor_rate_hz;
    wr_rat=PI_2*motor_pole*motor_rate_rpm/120.0;            // rpm -> rad/sec
    wm_rat=wr_rat*(2.0/motor_pole);
    Te_rat=motor_rate_power/wm_rat;
    inv_Te_rat=1.0/Te_rat;

    Fs_rat=Vs_rat/we_rat;

    Kt=(3.0/2.0)*(motor_pole/2.0);
    inv_Kt=1.0/Kt;
    P_pair=(motor_pole/2.0);
    inv_P_pair=1.0/P_pair;
    rpm_Coeff=60.0*inv_P_pair/PI_2;             // 회전수/분

    // V/F 제에의 슬립 보상
    S_rat=(we_rat-wr_rat)/we_rat;
    S_lin=(motor_pole/PI)*(S_rat*motor_rate_hz)/Te_rat;             // ==> V/f 제어 : 슬립 보상
    Freq_slip_rat=S_rat*motor_rate_hz;

    PreChargeLevel = 0.85*(1.35*motor_rate_volt);   // 정상 전압의 85%
    C_ce_nF=(3.5-0.8)/(1000.0-100.0)*(2.0*Is_rat-100.0)+0.8;    // 1000A -> 3.5nF, 100A -> 0.8nF
    C_ce=1.0e-9*C_ce_nF;
    inv_C_ce=1.0/C_ce;

    //-----------------------

    Freq_ref=0.0;
    wr_ref=0.0;                                         // 속도 명령 -> 0
    rpm_ref=0.0;

    //------
    // reference
    reference0=0.0;
    reference1=0.0;
    reference_in=0.0;
    reference=0.0;

    we_in=0.0;
    we=0.0;
    we0=0.0;

    wr_m0=0.0;
    wr_m=0.0;               // 실제 속도의 필터링 초기값 = 실제 속도
    wr=0.0;

    wr_ref=0.0;
    wr_err=0.0;
    wr_ErrInt=0.0;              // 속도제어기의 적분량
    w_sl=0.0;
    w_sl0=0.0;

    frequency=0.0;
    rpm=0.0;
    rpm_m=0.0;
    theta_m=0.0;
    rpm_ref=0.0;
    rpm_err=0.0;

    theta=0.0;
    SinTheta=0.0;
    CosTheta=1.0;
    CosDeltaTheta=0.0;
    SinDeltaTheta=1.0;

    // 전류
    Is_dq[ds]=Is_dq[qs]=0.0;
    Is_mag=0.0;
    Is_mag_rms=0.0;
    sgn_Is[as]=sgn_Is[bs]=sgn_Is[cs]=0.0;

    Is_DQ[DS]=Is_DQ[QS]=0.0;
    Is_DQ_max[DS]=Is_DQ_max[QS]=0.0;
    Is_DQ_ref[DS]=Is_DQ_ref[QS]=0.0;

    prev_I_QS=0.0;
    Is_DQ_ErrInt[DS]=Is_DQ_ErrInt[QS]=0.0;          // 전류제어기의 적분량

    // 전압
    Vs_max=0.0;
    Vs_abc[as]=Vs_abc[bs]=Vs_abc[cs]=0.0;
    Vs_abc_ref[as]=Vs_abc_ref[bs]=Vs_abc_ref[cs]=0.0;
    Vs_dq_ref[ds]=Vs_dq_ref[qs]=0.0;
    Vs_dq[ds]=Vs_dq[qs]=0.0;
    Vo=0.0;
    Us_dq[ds]=Us_dq[qs]=0.0;
    Vs_DQ[DS]=Vs_DQ[QS]=0.0;
    Vs_DQ_max[DS]=Vs_DQ_max[QS]=0.0;
    Vs_DQ_ref[DS]=Vs_DQ_ref[QS]=0.0;
    Vs_DQ_comp[DS]=Vs_DQ_comp[QS]=0.0;
    Vs_max_FW=0.0;
    Vs_DQ_ref_P[DS]=Vs_DQ_ref_P[QS]=0.0;
    Vs_DQ_ref_PI[DS]=Vs_DQ_ref_PI[QS]=0.0;

    // 토크
    Te_max=0.0;
    Te_ref=0.0;
    Te=0.0;

    // 자속
    Fs_ref0=0.0;
    Fs_ref=0.0;
    inv_Fs_ref=0.0;
    Fs_dq[ds]=Fs_dq[qs]=0.0;
    Fs=0.0;
    inv_Fs=0.0;
    Fr_ref=0.0;
    Fr_ref0=0.0;
    inv_Fr_ref=0.0;
    Fr=0.0;
    inv_Fr=0.0;
    Fr_Err=0.0;
    Fr_ErrInt=0.0;

    Vs_ref=0.0;
    Freq_ref=0.0;
    Freq_slip=0.0;
    Freq_out=0.0;
    Slip=0.0;
    Power_core=0.0;
    Power_core_rat=0.0;
    Power_gap=0.0;
    Vs_IR_comp=0.0;
    del_Vs_comp=0.0;

    // V/F Control Parameter
    VF_DeadTimeGain=1.0;
    VF_ExcitationTime=2.0;                  // DC여자 시간 = 0.5초
    VF_Fs_Coeff=1.0;
    VF_Freq_TrqBoost=1.5;
    VF_Vs_Coeff_TrqBoost=1.5*(VF_Freq_TrqBoost / motor_rate_hz );
    VF_Rs_ThermalCoeff=1.05;
    VF_IR_Comp_FilterPole=100.0;
    VF_Slip_Comp_FilterPole=20.0;
    VF_Rs=0.0;                              // 디폴트 저항 값 --> 0
    //---------------------------
    gfRunTime = 0.0;
}
*/
int HardwareParameterVerification()
{
    if ( codeRatePower >(0.99*sqrt(3.0) * codeRateVolt * codeRateCurrent)){
        trip_recording( CODE_rate_power, codeRatePower,"PW FACTOR OVER"); // POWER FACTOR OVER
        return  CODE_rate_power;
    }
    //
    if (codeRatePower<(0.2*sqrt(3.0)*codeRateVolt * codeRateCurrent)){
        trip_recording( CODE_rate_power, codeRatePower,"PW FACTOR UNDER"); // POWER FACTOR UNDER
        return  CODE_rate_power;
    }
    //
    if ( codeRateRpm < (0.85*120.0 * codeRateHz / codeMotorPole)){
        trip_recording( CODE_rate_rpm, codeRateRpm,"RATE RPM UNDER");
        return  CODE_rate_rpm;
    }
    return  0;
}

//-----------------------------------
//  End of ParameterSect.c
//-----------------------------------

