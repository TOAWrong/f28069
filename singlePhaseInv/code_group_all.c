// code_proc.c
//   header file : code_proc.h
//

#include	"header.h"
#include	"extern.h"


int get_code_group0(int addr ,int cmd, CODE_INFO * codes)
{

	switch(addr)
	{
	case CODE_run_input_select:	
		strncpy(codes->disp, "run_input_select",40);
		if( cmd == CMD_WRITE_RAM ) run_input_select = (codes->code_value).ints;
		set_code_default_int(0,4,2,run_input_select,0,codes);
		break;
	
	case CODE_motor_ctrl_mode:	// 
		strncpy(codes->disp, "motor_ctrl_mode",40);
		if( cmd == CMD_WRITE_RAM ) motor_ctrl_mode = (codes->code_value).ints;
		set_code_default_int(0,7,0,motor_ctrl_mode,0,codes);
		break;
	
	case CODE_motor_direction_change:	
		strncpy(codes->disp, "motor_direction_change ON(1)/OFF",40);
		if( cmd == CMD_WRITE_RAM ) motor_direction_change = (codes->code_value).ints;
		set_code_default_int(0,1,0,motor_direction_change,0,codes);
		break;
	
	case CODE_ramp_func_mode:
		strncpy(codes->disp, "ramp_func_mode",40);
		if( cmd == CMD_WRITE_RAM ) ramp_func_mode = (codes->code_value).ints;
		set_code_default_int(0,3,0,ramp_func_mode,0,codes);
		break;
	
	case CODE_accel_time1:	
		strncpy(codes->disp, "accel_time1 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) accel_time1 = (codes->code_value).doubles;
		set_code_default_double(0.0,3000.0,5.0,accel_time1,0,codes);
		break;
	
	case CODE_decel_time1:
		strncpy(codes->disp, "decel_time1 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) decel_time1 = (codes->code_value).doubles;
		set_code_default_double(0.0,3000.0,5.0,decel_time1,0,codes);
		break;

	case CODE_btn_start_ref:	
		strncpy(codes->disp, "btn_start_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) btn_start_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.5,btn_start_ref,0,codes);
		break;
	
	case CODE_jog_speed:	
		strncpy(codes->disp, "jog_speed (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) jog_speed = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.05,jog_speed,0,codes);
		break;
	
	case CODE_min_vf_ref:	
		strncpy(codes->disp, "min_vf_ref (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) min_vf_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.5,0.01,min_vf_ref,0,codes);
		break;


	//--- protect inhibit set

	case CODE_protect_inhibit_on:	
		strncpy(codes->disp, "protect_inhibit_on[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_inhibit_on = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_inhibit_on,0,codes);
		break;

	case CODE_protect_under_volt_off:	
		strncpy(codes->disp, "protect under volt off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_uv_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_uv_off,0,codes);
		break;

	case CODE_protect_over_volt_off:	
		strncpy(codes->disp, "protect over volt off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_ov_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_ov_off,0,codes);
		break;

	case CODE_protect_I_adc_off:	
		strncpy(codes->disp, "protect over I adc off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_Iadc_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_Iadc_off,0,codes);
		break;

	case CODE_protect_over_I_off:	
		strncpy(codes->disp, "protect over I off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_over_I_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_over_I_off,0,codes);
		break;

	case CODE_protect_IGBT_off:	
		strncpy(codes->disp, "protect IGBT off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_IGBT_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_IGBT_off,0,codes);
		break;

	case CODE_protect_ex_trip_off:	
		strncpy(codes->disp, "protect EX_TRIP off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_ex_trip_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_ex_trip_off,0,codes);
		break;
	
	case CODE_protect_IGBT2_off:	
		strncpy(codes->disp, "protect IGBT2 off[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_IGBT2_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_IGBT2_off,1,codes);
		break;

	case CODE_protect_CONVT_adc_off:	
		strncpy(codes->disp, "convt I adc chk[1]",40);
		if( cmd == CMD_WRITE_RAM ) code_protect_CONV_adc_off = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_protect_CONV_adc_off,0,codes);
		break;

	case CODE_GROUP0_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

int get_code_group1(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{
	case CODE_use_binary_input:	
		strncpy(codes->disp, "use_binary_input ON",40);
		if( cmd == CMD_WRITE_RAM ) code_use_binary_input = (codes->code_value).ints;
		set_code_default_int(0,1,0,code_use_binary_input,0,codes);
		break;
	
	case CODE_speed1:	
		strncpy(codes->disp, "speed1 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_speed1 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.9,0.25,code_speed1,0,codes);
		break;

	case CODE_speed2:	// 110	
		strncpy(codes->disp, "110 speed2 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_speed2 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.2,0.25,code_speed2,0,codes);
		break;

	case CODE_speed3:	// 111	
		strncpy(codes->disp, "111 speed3 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_speed3 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.2,0.5,code_speed3,0,codes);
		break;

	case CODE_speed4:	// 112	
		strncpy(codes->disp, "112 speed4 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_speed4 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.2,0.75,code_speed4,0,codes);
		break;

	case CODE_speed5:	// 113	
		strncpy(codes->disp, "113 speed5 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) code_speed5 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.2,0.95,code_speed5,0,codes);
		break;

	case CODE_GROUP1_END:
		return -2;
			
	default:
		return -1;
	}
	return 0;
}

int get_code_group2(int addr ,int cmd, CODE_INFO * codes )
{
	
	switch(addr)
	{
	case CODE_analog_cmd_in_zero1:	
		strncpy(codes->disp, "Analog Cmd1 in Zero",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_zero1 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,analog_cmd_in_zero1,0,codes);
		break;

	case CODE_analog_cmd_in_span1:	
		strncpy(codes->disp, "Analog Cmd1 in Span",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_span1 = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.0,analog_cmd_in_span1,0,codes);
		break;

	case CODE_analog_cmd_in_zero2:	
		strncpy(codes->disp, "Analog Cmd2 in Zero",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_zero2 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,analog_cmd_in_zero2,0,codes);
		break;

	case CODE_analog_cmd_in_span2:	
		strncpy(codes->disp, "Analog Cmd2 in Span",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_span2 = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.0,analog_cmd_in_span2,0,codes);
		break;

	case CODE_GROUP2_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

// Inverter protection 
int get_code_group3(int addr ,int cmd, CODE_INFO * codes)
{

	switch(addr)
	{
	case CODE_over_current_level:	
		strncpy(codes->disp, "over_currebt_level(%)",40);
		if( cmd == CMD_WRITE_RAM ) over_current_level = (codes->code_value).doubles;
		set_code_default_double(20.0,200.0,120.0,over_current_level,0,codes);
		break;
		
	case CODE_over_volt_set:	
		strncpy(codes->disp, "over_volt_set (V)",40);
		if( cmd == CMD_WRITE_RAM ) over_volt_set = (codes->code_value).doubles;
		set_code_default_double(100.0,780.0,370.0,over_volt_set,0,codes);
		break;
		
	case CODE_under_volt_set:	
		strncpy(codes->disp, "under_volt_set(V)",40);
		if( cmd == CMD_WRITE_RAM ) under_volt_set = (codes->code_value).doubles;
		set_code_default_double(50.0,780.0,240.0,under_volt_set,0,codes);
		break;
		
	case CODE_over_speed_level:	
		strncpy(codes->disp, "over_speed_level(%)",40);
		if( cmd == CMD_WRITE_RAM ) over_speed_level = (codes->code_value).doubles;
		set_code_default_double(20.0,200.0,120.0,over_speed_level,0,codes);
		break;
		
	case CODE_e_thermal_level:	
		strncpy(codes->disp, "e_thermal_level (%)",40);
		if( cmd == CMD_WRITE_RAM ) e_thermal_level = (codes->code_value).doubles;
		set_code_default_double(20.0,200.0,120.0,e_thermal_level,0,codes);
		break;
		
	case CODE_pre_charge_time:	
		strncpy(codes->disp, "pre_charge_time",40);
		if( cmd == CMD_WRITE_RAM ) pre_charge_time = (codes->code_value).doubles;
		set_code_default_double(3.0,30.0,5.0,pre_charge_time,0,codes);
		break;
		
	case CODE_Is_Max_Coeff:	
		strncpy(codes->disp, "Is_Max_Coeff (pu)",40);
		if( cmd == CMD_WRITE_RAM ) Is_Max_Coeff = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.5,Is_Max_Coeff,0,codes);
		break;

	case CODE_over_I_time:	
		strncpy(codes->disp, "over_I_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) over_I_time = (codes->code_value).doubles;
		set_code_default_double(0.5,600.0,60.0,over_I_time,0,codes);
		break;
/*
//--- Vdc sense 
	case CODE_Vdc_scaler:  // 308	
		strncpy(codes->disp, " Vdc_Scaler (pu)",40);
		if( cmd == CMD_WRITE_RAM ) code_Vdc_scaler = (codes->code_value).doubles;
		set_code_default_double(0.2,5.0,1.0,code_Vdc_scaler,0,codes);
		break;

	case CODE_Vdc_offseter:	// 309
		strncpy(codes->disp, "Vdc_offseter (V)",40);
		if( cmd == CMD_WRITE_RAM ) code_Vdc_offseter = (codes->code_value).doubles;
		set_code_default_double(-400.0,400.0,0.0,code_Vdc_offseter,0,codes);
		break;
*/
	case CODE_adc_vdc_low:	
		strncpy(codes->disp, "adc_vdc_low (sec)",40);
		if( cmd == CMD_WRITE_RAM ) code_adc_vdc_low = (codes->code_value).doubles;
		set_code_default_double(0.0,4095.0,1820.0,code_adc_vdc_low,0,codes);	// 500.0, 2000.0, 965.0
		break;

	case CODE_adc_vdc_high:	
		strncpy(codes->disp, "adc_vdc_high (sec)",40);
		if( cmd == CMD_WRITE_RAM ) code_adc_vdc_high = (codes->code_value).doubles;
		set_code_default_double(0.0,4010.0,2716.0,code_adc_vdc_high,0,codes);
		break;

	case CODE_Vdc_calc_low:	
		strncpy(codes->disp, "vdc_calc low (Vdc)",40);
		if( cmd == CMD_WRITE_RAM ) code_Vdc_calc_low = (codes->code_value).doubles;
		set_code_default_double(100.0,1.0e3,400.0,code_Vdc_calc_low,0,codes);
		break;

	case CODE_Vdc_calc_high:	
		strncpy(codes->disp, "vdc_calc high (Vdc)",40);
		if( cmd == CMD_WRITE_RAM ) code_Vdc_calc_high = (codes->code_value).doubles;
		set_code_default_double(200.0,1.0e3,600.0,code_Vdc_calc_high,0,codes);
		break;


	case CODE_GROUP3_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

// Motor Parameter

int get_code_group4(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{

	case CODE_motor_rate_power:	
		strncpy(codes->disp, "motor_rate_power",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_power = (codes->code_value).doubles;
		set_code_default_double(100,2.0e+6,3700,motor_rate_power,0,codes);
		break;
		
	case CODE_motor_rate_volt:	
		strncpy(codes->disp, "motor_rate_volt (Vrms)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_volt = (codes->code_value).doubles;
		set_code_default_double(100.0,500.0,380.0,motor_rate_volt,0,codes);
		break;
		
	case CODE_motor_rate_current:	
		strncpy(codes->disp, "motor_rate_current (A)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_current = (codes->code_value).doubles;
		set_code_default_double(1.0,2000.0,7.6,motor_rate_current,0,codes);
		break;
		
	case CODE_motor_rate_hz:	
		strncpy(codes->disp, "motor_rate_hz (Hz)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_hz = (codes->code_value).doubles;
		set_code_default_double(30.0,120.0,60.0,motor_rate_hz,0,codes);
		break;
		
	case CODE_motor_rate_rpm:	
		strncpy(codes->disp, "motor_rate_rpm",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_rpm = (codes->code_value).doubles;
		set_code_default_double(500,8000.0,1750.0,motor_rate_rpm,0,codes);
		break;
		
	case CODE_motor_pole:	
		strncpy(codes->disp, "motor_pole ",40);
		if( cmd == CMD_WRITE_RAM ) motor_pole = (codes->code_value).ints;
		set_code_default_int(2,20,4,motor_pole,0,codes);
		break;
	
	case CODE_motor_rate_effiency:	
		strncpy(codes->disp, "motor_rate_effiency (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_effiency = (codes->code_value).doubles;
		set_code_default_double(0.2,0.99,0.875,motor_rate_effiency,0,codes);
		break;

	case CODE_GROUP4_END:
		return -2;
		
	default:
		return -1;
	}
	return 0;
}

int get_code_group5(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{
	case CODE_I_sense_value:	
		strncpy(codes->disp, "I_sense_value (A)",40);
		if( cmd == CMD_WRITE_RAM ) I_sense_value = (codes->code_value).doubles;
		set_code_default_double(5.0,2000.0,40.0,I_sense_value ,0,codes);
		break;
		
	case CODE_u_phase_I_sense_span:	
		strncpy(codes->disp, "u_phase_I_sense_span (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) u_phase_I_sense_span = (codes->code_value).doubles;
		set_code_default_double(0.5,1.5,1.0,u_phase_I_sense_span,0,codes);
		break;
		
	case CODE_v_phase_I_sense_span:	
		strncpy(codes->disp, "v_phase_I_sense_span (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) v_phase_I_sense_span = (codes->code_value).doubles;
		set_code_default_double(0.5,1.5,1.0,v_phase_I_sense_span,0,codes);
		break;
				
	case CODE_vdc_sense_zero:	
		strncpy(codes->disp, "vdc_sense_zero (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) vdc_sense_zero = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,vdc_sense_zero,0,codes);
		break;
		
	case CODE_vdc_sense_span:	
		strncpy(codes->disp, "vdc_sense_span (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) vdc_sense_span = (codes->code_value).doubles;
		set_code_default_double(0.5,1.5,1.0,vdc_sense_span,0,codes);
		break;
		
	case CODE_igbt_pwm_freq:	
		strncpy(codes->disp, "igbt_pwm_freq (Hz)",40);
		if( cmd == CMD_WRITE_RAM ) igbt_pwm_freq = (codes->code_value).doubles;
		set_code_default_double(500.0,10000.0,2500.0,igbt_pwm_freq,0,codes);
		break;

	case CODE_adc_u_offset:	
		strncpy(codes->disp, "adc_u_offset",40);
		if( cmd == CMD_WRITE_RAM ) adc_u_offset = (codes->code_value).ints;
		set_code_default_int(1700,2700,2550,adc_u_offset,0,codes);
		break;
	
	case CODE_adc_v_offset:	
		strncpy(codes->disp, "adc_v_offset",40);
		if( cmd == CMD_WRITE_RAM ) adc_v_offset = (codes->code_value).ints;
		set_code_default_int(1700,2700,2550,adc_v_offset,0,codes);
		break;

	case CODE_adc_R_offset:	
		strncpy(codes->disp, "adc_R_offset",40);
		if( cmd == CMD_WRITE_RAM ) adc_R_offset = (codes->code_value).ints;
		set_code_default_int(1700,2700,2550,adc_R_offset,0,codes);
		break;
	
	case CODE_GROUP5_END:
		return -2;
		
	default:
		return -1;
	}
	return 0;
}

int get_code_group6(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{

	case CODE_VF_DeadTimeGain:	
		strncpy(codes->disp, "VF_DeadTimeGain",40);
		if( cmd == CMD_WRITE_RAM ) VF_DeadTimeGain = (codes->code_value).doubles;
		set_code_default_double(0.0,2.0,1.0,VF_DeadTimeGain,0,codes);
		break;
		
	case CODE_VF_ExcitationTime:	
		strncpy(codes->disp, "VF_ExcitationTime",40);
		if( cmd == CMD_WRITE_RAM ) VF_ExcitationTime = (codes->code_value).doubles;
		set_code_default_double(0.0,3.5,1.0,VF_ExcitationTime,0,codes);
		break;
		
	case CODE_VF_Fs_Coeff:	
		strncpy(codes->disp, "VF_Fs_Coeff (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) VF_Fs_Coeff = (codes->code_value).doubles;
		set_code_default_double(0.3,3.0,1.0,VF_Fs_Coeff,0,codes);
		break;
		
	case CODE_VF_Freq_TrqBoost:	
		strncpy(codes->disp, "VF_Freq_TrqBoost",40);
		if( cmd == CMD_WRITE_RAM ) VF_Freq_TrqBoost = (codes->code_value).doubles;
		set_code_default_double(0.0,10.0,1.5, VF_Freq_TrqBoost ,0,codes);
		break;

	case CODE_VF_Vs_Coeff_TrqBoost:	
		strncpy(codes->disp, "VF_Vs_Coeff_TrqBoost",40);
		if( cmd == CMD_WRITE_RAM ) VF_Vs_Coeff_TrqBoost = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.1, VF_Vs_Coeff_TrqBoost ,0,codes);
		break;

	case CODE_VF_Rs_ThermalCoeff:	
		strncpy(codes->disp, "VF_Rs_ThermalCoeff",40);
		if( cmd == CMD_WRITE_RAM ) VF_Rs_ThermalCoeff = (codes->code_value).doubles;
		set_code_default_double(0.8,3.0,1.05, VF_Rs_ThermalCoeff ,0,codes);
		break;

	case CODE_VF_IR_Comp_FilterPole:	
		strncpy(codes->disp, "VF_IR_Comp_FilterPole",40);
		if( cmd == CMD_WRITE_RAM ) VF_IR_Comp_FilterPole = (codes->code_value).doubles;
		set_code_default_double(5.0,1000.0,100.0, VF_IR_Comp_FilterPole ,0,codes);
		break;

	case CODE_VF_Slip_Comp_FilterPole:	
		strncpy(codes->disp, "VF_Slip_Comp_FilterPole",40);
		if( cmd == CMD_WRITE_RAM ) VF_Slip_Comp_FilterPole = (codes->code_value).doubles;
		set_code_default_double(5.0,1000.0,20.0, VF_Slip_Comp_FilterPole ,0,codes);
		break;

	case CODE_VF_Rs:	
		strncpy(codes->disp, "VF_Rs",40);
		if( cmd == CMD_WRITE_RAM ) VF_Rs = (codes->code_value).doubles;
		set_code_default_double(0.0,50.0,0.0, VF_Rs ,0,codes);
		break;

	case CODE_GROUP6_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}


int get_code_group8(int addr ,int cmd, CODE_INFO * codes)
{	
	switch(addr)
	{
	case CODE_Data_Check:	
		strncpy(codes->disp, "Backup Data Check",40);
		break;

	case CODE_Data_Backup:	
		strncpy(codes->disp, "Code Data Backup",40);
		break;

	case CODE_Data_Load:	
		strncpy(codes->disp, "Backup Data Load",40);
		break;

	case CODE_Data_Init:	
		strncpy(codes->disp, "Backup Data Init",40);
		break;

	case CODE_get_adc_offset:	
		strncpy(codes->disp, "get_adc_offset",40);
		break;

	case CODE_get_adc_vdc_low:	
		strncpy(codes->disp, "get_adc_vdc_low",40);
		break;

	case CODE_get_adc_vdc_high:	
		strncpy(codes->disp, "get_adc_vdc_high",40);
		break;

	case CODE_GROUP8_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

// end of file
