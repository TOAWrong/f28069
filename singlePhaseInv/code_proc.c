#include	"header.h"
#include	"extern.h"

int get_code_information(int address,int cmd , CODE_INFO *  codes)
{	
	switch(address)
	{
    case CODE_motor_direction_change:
        strncpy(codes->disp, "Rotate CW ON",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorDirection = codes->code_value;
        set_code_default(0,1,0,codeMotorDirection,0,codes);
        break;

    case CODE_accel_time1:
        strncpy(codes->disp, "accel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeAccelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeAccelTime1,0,codes);
        break;

    case CODE_decel_time1:
        strncpy(codes->disp, "decel_time1 (sec)",20);
        if( cmd == CMD_WRITE_RAM ) codeDecelTime1 = codes->code_value;
        set_code_default(0.0,3000.0,5.0,codeDecelTime1,0,codes);
        break;

    case CODE_MotorCtrMode:
        strncpy(codes->disp, "select Ctrl Mode",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorCtrlMode = codes->code_value;
        set_code_default(0,9,0,codeMotorCtrlMode,0,codes);
        break;

    case CODE_speed1:
		strncpy(codes->disp, "speed1 (p.u)",20);
		if( cmd == CMD_WRITE_RAM ) codeSpeed1 = codes->code_value;
		set_code_default(0.0,0.9,0.25,codeSpeed1,0,codes);
		break;

	case CODE_speed2:		
		strncpy(codes->disp, "speed2 (p.u)",20);
		if( cmd == CMD_WRITE_RAM ) codeSpeed2 = codes->code_value;
		set_code_default(0.0,1.2,0.25,codeSpeed2,0,codes);
		break;

    case CODE_set_vdc:
        strncpy(codes->disp, "set Vdc 300.0",20);
        if( cmd == CMD_WRITE_RAM ) codeSetVdc = codes->code_value;
        set_code_default(0,1,0,codeSetVdc,0,codes);
        break;

    case CODE_protect_off:
        strncpy(codes->disp, "Protect Off",20);
        if( cmd == CMD_WRITE_RAM ) codeProtectOff = codes->code_value;
        set_code_default(0,1,1,codeProtectOff,0,codes);
        break;

    case CODE_pwm_freq:
        strncpy(codes->disp, "PWM Freq",20);
        if( cmd == CMD_WRITE_RAM ) codePwmFreq = codes->code_value;
        set_code_default(500.0,10000.0,8000.0,codePwmFreq,0,codes);
        break;

    case CODE_rate_power:
        strncpy(codes->disp, "Rate_power",20);
        if( cmd == CMD_WRITE_RAM ) codeRatePower = codes->code_value;
        set_code_default(100,2.0e+6,400,codeRatePower,0,codes);
        break;

    case CODE_rate_current:
        strncpy(codes->disp, "Rate Current(A)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateCurrent = codes->code_value;
        set_code_default(1.0,2000.0,2.3,codeRateCurrent,0,codes);
        break;

    case CODE_rate_rpm:
        strncpy(codes->disp, "Rate RPM",20);
        if( cmd == CMD_WRITE_RAM ) codeRateRpm = codes->code_value;
        set_code_default(500,8000.0,1690.0,codeRateRpm,0,codes);
        break;

    case CODE_rate_effiency:
        strncpy(codes->disp, "Motor Effiency",20);
        if( cmd == CMD_WRITE_RAM ) codeRateEffiency = codes->code_value;
        set_code_default(0.2,0.99,0.65,codeRateEffiency,0,codes);
        break;

    case CODE_rate_hz:
        strncpy(codes->disp, "Rate hz",20);
        if( cmd == CMD_WRITE_RAM ) codeRateHz = codes->code_value;
        set_code_default(30.0,120.0,60.0,codeRateHz,0,codes);
        break;

    case CODE_rate_volt:
        strncpy(codes->disp, "Rate Volt (Vrms)",20);
        if( cmd == CMD_WRITE_RAM ) codeRateVolt = codes->code_value;
        set_code_default(100.0,500.0,220.0,codeRateVolt,0,codes);
        break;

    case CODE_motor_pole:
        strncpy(codes->disp, "Motor Pole ",20);
        if( cmd == CMD_WRITE_RAM ) codeMotorPole = codes->code_value;
        set_code_default(2,20,4,codeMotorPole,0,codes);
        break;

    case CODE_IaOffset:
        strncpy(codes->disp, "Ia Offset",20);
        if( cmd == CMD_WRITE_RAM ) codeIaOffset = codes->code_value;
        set_code_default(2000.0,2600.0,2400.0,codeIaOffset,0,codes);
        break;

    case CODE_IbOffset:
        strncpy(codes->disp, "Ib Offset",20);
        if( cmd == CMD_WRITE_RAM ) codeIbOffset = codes->code_value;
        set_code_default(2000.0,2600.0,2400.0,codeIbOffset,0,codes);
        break;

    case CODE_I_sense_value:
        strncpy(codes->disp, "I_sense_value (A)",20);
        if( cmd == CMD_WRITE_RAM ) I_sense_value = codes->code_value;
        set_code_default(5.0,2000.0, 5.0,I_sense_value ,0,codes);
        break;

    case CODE_u_phase_I_sense_span:
        strncpy(codes->disp, "u I_sense_span ",20);
        if( cmd == CMD_WRITE_RAM ) u_phase_I_sense_span = codes->code_value;
        set_code_default(0.5,1.5,1.0,u_phase_I_sense_span,0,codes);
        break;

    case CODE_v_phase_I_sense_span:
        strncpy(codes->disp, "v_I_sense_span ",20);
        if( cmd == CMD_WRITE_RAM ) v_phase_I_sense_span = codes->code_value;
        set_code_default(0.5,1.5,1.0,v_phase_I_sense_span,0,codes);
        break;

    case CODE_Rs:
        strncpy(codes->disp, "Motor State Rs",20);
        if( cmd == CMD_WRITE_RAM ) Rs = codes->code_value;
        set_code_default(0.002,20.0,5.5453,Rs,0,codes);
        break;

    case CODE_Rr:
        strncpy(codes->disp, "Motor Rotor Rr",20);
        if( cmd == CMD_WRITE_RAM ) Rr = codes->code_value;
        set_code_default(0.002,20.0,5.5453,Rr,0,codes);
        break;

    case CODE_Ls:
        strncpy(codes->disp, "Motor State Ls",20);
        if( cmd == CMD_WRITE_RAM ) Ls = codes->code_value;
        set_code_default(0.002,1.0,0.252,Ls,0,codes);
        break;

    case CODE_Lr:
        strncpy(codes->disp, "Motor State Lr",20);
        if( cmd == CMD_WRITE_RAM ) Lr = codes->code_value;
        set_code_default(0.002,1.0,0.252,Lr,0,codes);
        break;

    case CODE_Lm:
        strncpy(codes->disp, "Motor Mutual Lm",20);
        if( cmd == CMD_WRITE_RAM ) Lm = codes->code_value;
        set_code_default(0.002,1.0,0.232,Lm,0,codes);
        break;

    case CODE_Jm:
        strncpy(codes->disp, "Motor Intertia Jm",20);
        if( cmd == CMD_WRITE_RAM ) Jm = codes->code_value;
        set_code_default(1.0e-4,100.0,5.0,Jm,0,codes);
        break;

    case CODE_VF_DeadTimeGain:
        strncpy(codes->disp, "VF_DeadTimeGain",20);
        if( cmd == CMD_WRITE_RAM ) VF_DeadTimeGain = codes->code_value;
        set_code_default(0.0,2.0,1.0,VF_DeadTimeGain,0,codes);
        break;

    case CODE_VF_ExcitationTime:
        strncpy(codes->disp, "VF_ExcitationTime",20);
        if( cmd == CMD_WRITE_RAM ) VF_ExcitationTime = codes->code_value;
        set_code_default(0.0,3.5,1.0,VF_ExcitationTime,0,codes);
        break;

    case CODE_VF_Fs_Coeff:
        strncpy(codes->disp, "VF_Fs_Coeff (p.u)",20);
        if( cmd == CMD_WRITE_RAM ) VF_Fs_Coeff = codes->code_value;
        set_code_default(0.3,3.0,1.0,VF_Fs_Coeff,0,codes);
        break;

    case CODE_VF_Freq_TrqBoost:
        strncpy(codes->disp, "VF_Freq_TrqBoost",20);
        if( cmd == CMD_WRITE_RAM ) VF_Freq_TrqBoost = codes->code_value;
        set_code_default(0.0,10.0,1.5, VF_Freq_TrqBoost ,0,codes);
        break;

    case CODE_VF_Vs_Coeff_TrqBoost:
        strncpy(codes->disp, "VF_VsCoefTqBoost",20);
        if( cmd == CMD_WRITE_RAM ) VF_Vs_Coeff_TrqBoost = codes->code_value;
        set_code_default(0.0,0.2,0.1, VF_Vs_Coeff_TrqBoost ,0,codes);
        break;

    case CODE_VF_Rs_ThermalCoeff:
        strncpy(codes->disp, "VF_Rs_ThermalCoeff",20);
        if( cmd == CMD_WRITE_RAM ) VF_Rs_ThermalCoeff = codes->code_value;
        set_code_default(0.8,3.0,1.05, VF_Rs_ThermalCoeff ,0,codes);
        break;

    case CODE_VF_IR_Comp_FilterPole:
        strncpy(codes->disp, "vfIRCompFiltPole",20);
        if( cmd == CMD_WRITE_RAM ) VF_IR_Comp_FilterPole = codes->code_value;
        set_code_default(5.0,1000.0,100.0, VF_IR_Comp_FilterPole ,0,codes);
        break;

    case CODE_VF_Slip_Comp_FilterPole:
        strncpy(codes->disp, "vfSlipCompFiltPole",20);
        if( cmd == CMD_WRITE_RAM ) VF_Slip_Comp_FilterPole = codes->code_value;
        set_code_default(5.0,1000.0,20.0, VF_Slip_Comp_FilterPole ,0,codes);
        break;

    case CODE_VF_Rs:
        strncpy(codes->disp, "VF_Rs",20);
        if( cmd == CMD_WRITE_RAM ) VF_Rs = codes->code_value;
        set_code_default(0.0,50.0,0.0, VF_Rs ,0,codes);
        break;

// auto tuning
    case CODE_AT_Freq_Leq_Req:
        strncpy(codes->disp, "Freq LeqReq",20);
        if( cmd == CMD_WRITE_RAM ) AT_Freq_Leq_Req = codes->code_value;
        set_code_default(5.0,30.0,15.0,AT_Freq_Leq_Req,0,codes);
        break;

    case CODE_AT_Time_Leq_Req:
        strncpy(codes->disp, "AT_Time_Leq_Req",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Leq_Req = codes->code_value;
        set_code_default(3.0,30.0,6.0,AT_Time_Leq_Req,0,codes);
        break;

    case CODE_AT_Is_Coeff_Leq_Req:
        strncpy(codes->disp, "AT_Is_Coeff_LeqReq",20);
        if( cmd == CMD_WRITE_RAM ) AT_Is_Coeff_Leq_Req = codes->code_value;
        set_code_default(0.4,1.5,1.0,AT_Is_Coeff_Leq_Req,0,codes);
        break;

    case CODE_AT_Is_Coeff_Rs:
        strncpy(codes->disp, "AT_Is_Coeff_Rs",20);
        if( cmd == CMD_WRITE_RAM ) AT_Is_Coeff_Rs = codes->code_value;
        set_code_default(0.4,1.5,1.0,AT_Is_Coeff_Rs,0,codes);
        break;

    case CODE_AT_Time_Rs:
        strncpy(codes->disp, "AT_Time_Rs",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Rs = codes->code_value;
        set_code_default(3.0,30.0,6.0,AT_Time_Rs,0,codes);
        break;

    case CODE_AT_DeadTimeGain:
        strncpy(codes->disp, "AT_DeadTimeGain",20);
        if( cmd == CMD_WRITE_RAM ) AT_DeadTimeGain = codes->code_value;
        set_code_default(0.0,1.2,1.0,AT_DeadTimeGain,0,codes);
        break;

    case CODE_AT_Ls_Vs_RAMP:
        strncpy(codes->disp, "AT_Ls_Vs_RAMP",20);
        if( cmd == CMD_WRITE_RAM ) AT_Ls_Vs_RAMP = codes->code_value;
        set_code_default(0.5,5.0,0.5,AT_Ls_Vs_RAMP,0,codes);
        break;

    case CODE_AT_Freq_Ls:
        strncpy(codes->disp, "AT_Freq_Ls(Hz)",20);
        if( cmd == CMD_WRITE_RAM ) AT_Freq_Ls = codes->code_value;
        set_code_default(1.5,10.0,4.0,AT_Freq_Ls,0,codes);
        break;

    case CODE_AT_Time_Ls:
        strncpy(codes->disp, "AT_Time_Ls(sec)",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Ls = codes->code_value;
        set_code_default(4.0,30.0,7.0,AT_Time_Ls,0,codes);
        break;

    case CODE_AT_Ls_DMB_OpenTime:
        strncpy(codes->disp, "AT_Ls_DMB_OpenTime",20);
        if( cmd == CMD_WRITE_RAM ) AT_Ls_DMB_OpenTime = codes->code_value;
        set_code_default(0.0,2.0,0.6,AT_Ls_DMB_OpenTime,0,codes);
        break;

    case CODE_AT_Te_Coeff_Jm:
        strncpy(codes->disp, "AT_Te_Coeff_Jm",20);
        if( cmd == CMD_WRITE_RAM ) AT_Te_Coeff_Jm = codes->code_value;
        set_code_default(0.2,1.0,0.5,AT_Te_Coeff_Jm,0,codes);
        break;

    case CODE_AT_Time_Jm:
        strncpy(codes->disp, "AT_Time_Jm(sec)",20);
        if( cmd == CMD_WRITE_RAM ) AT_Time_Jm = codes->code_value;
        set_code_default(0.3,2.0,0.4,AT_Time_Jm,0,codes);
        break;

    case CODE_Jm_ID_ENABLE:
        strncpy(codes->disp, "Estim Jm Enable",20);
        if( cmd == CMD_WRITE_RAM )Jm_ID_ENABLE = codes->code_value;
        set_code_default(0,1,1,Jm_ID_ENABLE,0,codes);
        break;
//--- codes for test
    case CODE_posi_duration_time:
        strncpy(codes->disp, "posi_duration_time",20);
        if( cmd == CMD_WRITE_RAM ) posi_duration_time = codes->code_value;
        set_code_default(0.0,30.0,3.0,posi_duration_time,0,codes);
        break;

    case CODE_zero_duration_time:
        strncpy(codes->disp, "zero_duration_time",20);
        if( cmd == CMD_WRITE_RAM ) zero_duration_time = codes->code_value;
        set_code_default(0.0,30.0,3.0,zero_duration_time,0,codes);
        break;

    case CODE_nega_duration_time:
        strncpy(codes->disp, "nega_duration_time",20);
        if( cmd == CMD_WRITE_RAM ) nega_duration_time = codes->code_value;
        set_code_default(0.0,30.0,3.0,nega_duration_time,0,codes);
        break;

    case CODE_test_accel_time:
        strncpy(codes->disp, "test_accel_time",20);
        if( cmd == CMD_WRITE_RAM ) test_accel_time = codes->code_value;
        set_code_default(0.0,30.0,3.0,test_accel_time,0,codes);
        break;

    case CODE_test_decel_time:
        strncpy(codes->disp, "test_decel_time",20);
        if( cmd == CMD_WRITE_RAM ) test_decel_time = codes->code_value;
        set_code_default(0.0,30.0,3.0,test_decel_time,0,codes);
        break;

//--- vector control
    case CODE_wr_FilterPoleCoeff:
        strncpy(codes->disp, "wr_FilterPoleCoeff",20);
        if( cmd == CMD_WRITE_RAM ) wr_FilterPoleCoeff = codes->code_value;
        set_code_default(5.0,30.0,15.0,wr_FilterPoleCoeff,0,codes);
        break;

    case CODE_wn_wr_Coeff:
        strncpy(codes->disp, "wn_wr_Coeff",20);
        if( cmd == CMD_WRITE_RAM ) wn_wr_Coeff = codes->code_value;
        set_code_default(2.0,30.0,5.0,wn_wr_Coeff,0,codes);
        break;

    case CODE_Max_wn_wr:
        strncpy(codes->disp, "Max_wn_wr",20);
        if( cmd == CMD_WRITE_RAM ) Max_wn_wr = codes->code_value;
        set_code_default(0.3,60,24.0,Max_wn_wr,0,codes);
        break;

    case CODE_K_Damp_wr:
        strncpy(codes->disp, "K_Damp_wr",20);
        if( cmd == CMD_WRITE_RAM ) K_Damp_wr = codes->code_value;
        set_code_default(0.05,1.0,0.45,K_Damp_wr,0,codes);
        break;

    case CODE_wr_DampingRatio:
        strncpy(codes->disp, "wr_DampingRatio",20);
        if( cmd == CMD_WRITE_RAM ) wr_DampingRatio = codes->code_value;
        set_code_default(0.6,1.5,0.8,wr_DampingRatio,0,codes);
        break;

    case CODE_wr_CntlPeriodIndex:
        strncpy(codes->disp, "wr_CntlPeriodIndex",20);
        if( cmd == CMD_WRITE_RAM ) wr_CntlPeriodIndex = codes->code_value;
        set_code_default(1,30,1,wr_CntlPeriodIndex,0,codes);
        break;

    case CODE_FW_VoltageCoeff:
        strncpy(codes->disp, "FW_VoltageCoeff",20);
        if( cmd == CMD_WRITE_RAM ) FW_VoltageCoeff = codes->code_value;
        set_code_default(0.2,1.2,1.0,FW_VoltageCoeff,0,codes);
        break;

    case CODE_Base_Flux_Coeff:
        strncpy(codes->disp, "Base_Flux_Coeff",20);
        if( cmd == CMD_WRITE_RAM ) Base_Flux_Coeff =codes->code_value;
        set_code_default(0.1,2.5,0.92,Base_Flux_Coeff,0,codes);
        break;

    case CODE_ExcitationTime:
        strncpy(codes->disp, "ExcitationTime",20);
        if( cmd == CMD_WRITE_RAM ) ExcitationTime = codes->code_value;
        set_code_default(0.1,3.0,0.25,ExcitationTime,0,codes);
        break;

    case CODE_K_Damp_Fr:
        strncpy(codes->disp, "K_Damp_Fr",20);
        if( cmd == CMD_WRITE_RAM ) K_Damp_Fr = codes->code_value;
        set_code_default(0.0,1.0,0.45,K_Damp_Fr,0,codes);
        break;

    case CODE_GM_Fr:
        strncpy(codes->disp, "GM_Fr",20);
        if( cmd == CMD_WRITE_RAM ) GM_Fr = codes->code_value;
        set_code_default(2.5,25.0,7.0,GM_Fr,0,codes);
        break;

    case CODE_PM_Fr:
        strncpy(codes->disp, "PM_Fr",20);
        if( cmd == CMD_WRITE_RAM ) PM_Fr = codes->code_value;
        set_code_default(0.15,1.3,0.785,PM_Fr,0,codes);
        break;

    case CODE_K_Damp_Is:
        strncpy(codes->disp, "K_Damp_Is",20);
        if( cmd == CMD_WRITE_RAM ) K_Damp_Is = codes->code_value;
        set_code_default(0.1,1.0,0.45,K_Damp_Is,0,codes);
        break;

    case CODE_GM_Is:
        strncpy(codes->disp, "GM_Is",20);
        if( cmd == CMD_WRITE_RAM ) GM_Is = codes->code_value;
        set_code_default(2.5,10.0,7.0,GM_Is,0,codes);
        break;

    case CODE_PM_Is:
        strncpy(codes->disp, "PM_Is",20);
        if( cmd == CMD_WRITE_RAM ) PM_Is = codes->code_value;
        set_code_default(0.15,1.3,0.785,PM_Is,0,codes);
        break;

//--- vector control

    case CODE_Default_wr_FilterPole:
        strncpy(codes->disp, "def_wrFiltPole",20);
        if( cmd == CMD_WRITE_RAM ) Default_wr_FilterPole = codes->code_value;
        set_code_default(20.0,500.0,200.0,Default_wr_FilterPole,0,codes);
        break;

    case CODE_SlipCompCoeff:
        strncpy(codes->disp, "slipCompCoeff",20);
        if( cmd == CMD_WRITE_RAM ) SlipCompCoeff = codes->code_value;
        set_code_default(0.0,1.0,0.2,SlipCompCoeff,0,codes);
        break;

    case CODE_GammaLambda:
        strncpy(codes->disp, "GammaLambda",20);
        if( cmd == CMD_WRITE_RAM ) GammaLambda = codes->code_value;
        set_code_default(0.0,2.0,1.0,GammaLambda,0,codes);
        break;

    case CODE_GammaLambda_R_Constant:
        strncpy(codes->disp, "gammaLambdaRConst",20);
        if( cmd == CMD_WRITE_RAM ) GammaLambda_R_Constant = codes->code_value;
        set_code_default(3.0,100.0,20.0,GammaLambda_R_Constant,0,codes);
        break;

    case CODE_Max_DeltaLambda:
        strncpy(codes->disp, "Max_DeltaLambda",20);
        if( cmd == CMD_WRITE_RAM ) Max_DeltaLambda = codes->code_value;
        set_code_default(0.0,0.2,0.05,Max_DeltaLambda,0,codes);
        break;

    case CODE_GammaTheta_M:
        strncpy(codes->disp, "GammaTheta_M",20);
        if( cmd == CMD_WRITE_RAM ) GammaTheta_M = codes->code_value;
        set_code_default(0.0,1.0,0.2,GammaTheta_M,0,codes);
        break;

    case CODE_GammaTheta_R:
        strncpy(codes->disp, "GammaTheta_R",20);
        if( cmd == CMD_WRITE_RAM ) GammaTheta_R = codes->code_value;
        set_code_default(0.0,3.0,1.0,GammaTheta_R,0,codes);
        break;

    case CODE_Max_DeltaTheta:
        strncpy(codes->disp, "Max_DeltaTheta",20);
        if( cmd == CMD_WRITE_RAM ) Max_DeltaTheta = codes->code_value;
        set_code_default(0.0,0.05,0.015,Max_DeltaTheta,0,codes);
        break;

    case CODE_Delta_wr_FilterPoleCoeff_L:
        strncpy(codes->disp, "d_wr_fltPoleCoefL",20);
        if( cmd == CMD_WRITE_RAM ) Delta_wr_FilterPoleCoeff_L = codes->code_value;
        set_code_default(0.1,20.0,0.5,Delta_wr_FilterPoleCoeff_L,0,codes);
        break;

    case CODE_Delta_wr_FilterPoleCoeff_U:
        strncpy(codes->disp, "d_wr_fltPoleCoefU",20);
        if( cmd == CMD_WRITE_RAM ) Delta_wr_FilterPoleCoeff_U = codes->code_value;
        set_code_default(0.1,20.0,3.0,Delta_wr_FilterPoleCoeff_U,0,codes);
        break;

	case CODE_END:
		return -2;
			
	default:
		return -1;
	}
	return 0;
}

void set_code_default(double min, double max, double defaults, double value,int open_level, CODE_INFO * codes )
{
	codes->type 		= TYPE_float;
	codes->open_level 	= open_level;
	codes->code_min		= min;
	codes->code_max		= max;
	codes->code_default	= defaults;
	codes->code_value 	= value;
}

int check_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0 ; address <= CODE_END; address++){	 // code group �� 6��
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            check = check_code_data(address, data );	// check min and max boundary
            if(check)  return -1;
        }
    }
	return 0;
}


void save_backup_data()
{
	UNION32	data;
	int check,address,cmd;
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
	for( address = 0 ; address <= CODE_END ; address++){
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 1;
            write_code_2_eeprom( address,data);
            Flag_TripDataBackup = 0;
        }
	}
}

void backup_data_load()
{
	UNION32	data;
	int check,address,cmd;
	
	data.dword  = 0.0;
	cmd = CMD_READ_DATA;
    for( address = 0; address <= CODE_END ;address++)
    {
        check = get_code_information( address, cmd , & code_inform);
        if( !check ){
            Flag_TripDataBackup = 1;
            read_eprom_data( address, & data);
            Flag_TripDataBackup = 0;
            write_code_2_eeprom( address,data);
            code_inform.code_value = data.dword;
            cmd = CMD_WRITE_RAM;
            check = get_code_information( address,cmd, & code_inform);
        }
	}
}
double CheckSum()
{
    return 0.0;
}

int SaveDataProc(int addr, double data)
{
	int cmd,i,return_value;
	char SciBuf[30]={0};
	char str[30];
	UNION32 u32data,u32data2;

	return_value = 0;

	cmd = CMD_READ_DATA;

	i = get_code_information( addr,cmd,&code_inform); 

	if( i != 0 ) goto _SAVE_ERROR_INVALID_ADDR;   

	if( addr >= 800 ){

		if( data < 1.22 ) goto _SAVE_ERROR_INVALID_DATA; 
		if( data > 1.24 ) goto _SAVE_ERROR_INVALID_DATA; 
		switch(addr)
		{
		case CODE_Data_Check: 	return_value = check_backup_data();	break;
		case CODE_Data_Backup:
			strncpy(str,"Wait for Data Backup",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			save_backup_data();
			strncpy(str,"Wait for Error Check",20);
			load_sci_tx_mail_box(str);  delay_msecs(20);

			break;
		case CODE_Data_Load:
			strncpy(str,"Wait for Data Load !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);	
			backup_data_load();
			break;
		case CODE_Data_Init:
			strncpy(str,"Wait For Data Init !",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			init_eprom_data();
			strncpy(str,"Data Init OK !      ",20);
			load_sci_tx_mail_box(str); delay_msecs(20);
			break;

		default:
			goto _SAVE_ERROR_INVALID_ADDR;
		}
		return return_value;
	}

    if( code_inform.code_min > data ){
        goto _SAVE_ERROR_DATA_UNDER;
    }
    else if( code_inform.code_max < data ){
        goto _SAVE_ERROR_DATA_OVER;
    }
    else {
        u32data.dword = data;
        read_eprom_data( addr, & u32data2);
        if( u32data.dword != u32data2.dword ){
            write_code_2_eeprom( addr, u32data);
            read_eprom_data( addr, & u32data2);

            if( u32data.dword != u32data2.dword ) goto _EEPROM_WRITE_ERROR;

            code_inform.code_value = data;
            cmd = CMD_WRITE_RAM;
            get_code_information( addr,cmd, & code_inform);

            // CheckSum Save
            u32data.dword = CheckSum();
            EepromSaveFlag = 1;
            write_code_2_eeprom(EPROM_ADDR_CHECKSUM, u32data);
            EepromSaveFlag = 0;

            load_sci_tx_mail_box("OK write success") ;
        }
        else{
            load_sci_tx_mail_box("Equal Data write skipped");
        }
        return 0;
    }
_SAVE_ERROR_INVALID_ADDR:
//	strcpy(SciBuf, "ADDR");
	strcpy(SciBuf,"Invalid Address" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_UNDER:

//	strcpy(SciBuf, "UNDE");

	strcpy(SciBuf,"Input data under" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_OVER:
//	strcpy(SciBuf, "OVER");
	strcpy(SciBuf,"Input data over" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_INVALID_DATA:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Invalid data " );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_EEPROM_WRITE_ERROR:
//	strcpy(SciBuf, "DATA");
	strcpy(SciBuf,"Eeprom write error" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;
}


int init_eprom_data()
{
	UNION32	data,data2;
	int check,address,cmd;

	data.dword  = 0.0;

	cmd = CMD_READ_DATA;
	for( address = 0 ; address < CODE_END ; address++ )
	{
		cmd = CMD_READ_DATA;
		check = get_code_information( address, cmd , & code_inform);
		if( check==0 ){
			data.dword = code_inform.code_default;
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword)	write_code_2_eeprom( address,data);
			read_eprom_data(address, & data2 );
			if( data.dword != data2.dword){
				load_sci_tx_mail_box("Trip : eeprom write" );
				delay_msecs(100);
				return -1;
			}	 
			else{
			    code_inform.code_value = data.dword;
			    cmd = CMD_WRITE_RAM;
			    check = get_code_information( address,cmd, & code_inform);
			}
		}
    }
	return 0;
}
void readAllCodes()
{
    int check;
    int addr,cmd;
    char * str;
    scia_tx_end_addr = 0;
    scia_tx_start_addr = 0;
    loadSciaTxMailBox("//Read code data:");
    loadSciaTxMailBox("code  data  Disc:");
    for( addr = 0 ; addr <= CODE_END ; addr++){
        check = get_code_information( addr, cmd , & code_inform);
        if( !check ){
            snprintf( str, 6 ,"%4d,",addr); load_scia_tx_mail_box(str);
            snprintf( str,20,"%.3e,",code_inform.code_value);load_scia_tx_mail_box(str);
            load_scia_tx_mail_box(code_inform.disp);
            load_scia_tx_mail_box(" : ");
            delay_msecs(10);
        }
    }
    load_scia_tx_mail_box("endOfReadall.\r\n");
}
//--- end of code_proc.c
