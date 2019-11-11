#include "duty.h"

int Pidcalc_start_cnt = 1;
extern int bullet_cnt_1 ;
extern int bullet_cnt_2;
int bullet_value_1_H , bullet_value_1_T , bullet_value_1_G;
int bullet_value_2_H , bullet_value_2_T , bullet_value_2_G;
void Loop()
{
	//0.8ms任务：检测任务
	if(Tim_circle_flag_1ms >= 8) 
	{
		Tim_circle_flag_1ms = 1;
		
		pon_detect_circle();
		guangdian_detect_circle();
		
		bullet_value_1_H = bullet_cnt_1 /100;
		bullet_value_1_T = bullet_cnt_1 / 10;
		bullet_value_1_G = bullet_cnt_1 - (bullet_cnt_1 / 10) * 10;
		if(bullet_cnt_1 == 100)
		{
			bullet_value_1_H = 1;
			bullet_value_1_T = 0;
			bullet_value_1_G = 0;
		}
		if(bullet_cnt_1 < 100)
		{
			bullet_value_1_H = No_Display_bit;
		}
		if(bullet_cnt_1 < 10)
		{
			bullet_value_1_H = No_Display_bit;
			bullet_value_1_T = No_Display_bit;
		}
		//////
		bullet_value_2_H = bullet_cnt_2 /100;
		bullet_value_2_T = bullet_cnt_2 / 10;
		bullet_value_2_G = bullet_cnt_2 - (bullet_cnt_2 / 10) * 10;
		if(bullet_cnt_2 == 100)
		{
			bullet_value_2_H = 1;
			bullet_value_2_T = 0;
			bullet_value_2_G = 0;
		}
		if(bullet_cnt_2 < 100)
		{
			bullet_value_2_H = No_Display_bit;
		}
		if(bullet_cnt_2 < 10)
		{
			bullet_value_2_H = No_Display_bit;
			bullet_value_2_T = No_Display_bit;
		}

		display_left( bullet_value_1_H  , bullet_value_1_T , bullet_value_1_G);
		display_right(bullet_value_2_H  , bullet_value_2_T , bullet_value_2_G);
		
		if(Pidcalc_start_cnt != PIDcalc_start)//计数到了PIDcalc_start，开始PID计算
		{
      Pidcalc_start_cnt++;
		}
	}
	
	//1ms任务：电机PID计算，位置环和速度环
	if(Tim_circle_flag_3ms >= 10 && Pidcalc_start_cnt == PIDcalc_start)
	{
		Tim_circle_flag_3ms = 1;

    motor_pid_task();
		infantry_supply();
		engineer_to_hero_supply();
	}
}












