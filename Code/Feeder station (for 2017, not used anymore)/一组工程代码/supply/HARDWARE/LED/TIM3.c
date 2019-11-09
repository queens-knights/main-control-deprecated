#include "TIM3.h"


void Tim3_Configuration(void)
{
		TIM_TimeBaseInitTypeDef  tim;
	  NVIC_InitTypeDef         nvic;
		
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    nvic.NVIC_IRQChannel = TIM3_IRQn;
	  nvic.NVIC_IRQChannelPreemptionPriority = 3;
   	nvic.NVIC_IRQChannelSubPriority = 3;
  	nvic.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&nvic);	
	
		tim.TIM_Prescaler = 168 - 1;                             
	  tim.TIM_Period = 100;	 				
	  tim.TIM_ClockDivision = 0;
	  tim.TIM_CounterMode = TIM_CounterMode_Up;
	  TIM_TimeBaseInit(TIM3 , &tim);
	
	  TIM_ARRPreloadConfig(TIM3, ENABLE);
  	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	  TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3, ENABLE);	
}

extern int rm2006_fanzhuan_flag1 , rm2006_fanzhuan_flag2;
int rm2006_fanzhuan_cnt1 = 0 , rm2006_fanzhuan_cnt2 = 0;
/////
extern int supply_box_uping_flag ;
float supply_box_uping_cnt = 0 , waving_flag = 0;
/////
extern int box_down_and_close_flag;
float box_down_cnt = 0;
////////
//TIM3专门用作电机PID计算
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) 
	{
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		
		Tim_circle_flag_1ms++;
		Tim_circle_flag_2ms++;
		Tim_circle_flag_3ms++;
 
		//拨弹电机反转计时:
		if(rm2006_fanzhuan_flag1)
		{
			rm2006_fanzhuan_cnt1++;
			if(rm2006_fanzhuan_cnt1 >= 10000)
			{
				rm2006_fanzhuan_cnt1 = 0;
				rm2006_fanzhuan_flag1 = 0;
				speed_set_1 = 0;
			}
		}
		if(rm2006_fanzhuan_flag2)
		{
			rm2006_fanzhuan_cnt2++;
			if(rm2006_fanzhuan_cnt2 >= 10000)
			{
				rm2006_fanzhuan_cnt2 = 0;
				rm2006_fanzhuan_flag2 = 0;
				speed_set_3 = 0;
			}
		}
		
		
		
		////////////////////////
		///////英雄补弹：
		if(supply_box_uping_flag == 1)
		{
			supply_box_uping_cnt++;
			if(supply_box_uping_cnt <= 100)
			{
			  TIM4->CCR3 = 2200;//
			}
			if(supply_box_uping_cnt >= 6000 && waving_flag == 0)
			{
        TIM4->CCR3 = 2200;//上
				waving_flag = 1;
			}
			else if(supply_box_uping_cnt >= 12000 && waving_flag == 1)
			{
        TIM4->CCR3 = 1000;//下
				waving_flag = 2;
			}
			else if(supply_box_uping_cnt >= 18000 && waving_flag == 2)
			{
        TIM4->CCR3 = 2200;//上
				waving_flag = 3;
			}
			else if(supply_box_uping_cnt >= 24000 && waving_flag == 3)
			{
        TIM4->CCR3 = 1000;//下
				waving_flag = 4;
			}
			else if(supply_box_uping_cnt >= 30000 && waving_flag == 4)
			{
        TIM4->CCR3 = 2200;//上
				waving_flag = 5;
			}
			else if(supply_box_uping_cnt >= 36000 && waving_flag == 5)
			{
        TIM4->CCR3 = 1000;//下
				waving_flag = 6;
			}
			else if(supply_box_uping_cnt >= 42000 && waving_flag == 6)
			{
        TIM4->CCR3 = 2200;//上
				waving_flag = 7;
			}
			else if(supply_box_uping_cnt >= 48000 && waving_flag == 7)
			{
        TIM4->CCR3 = 1000;//下
				waving_flag = 8;
			}
			else if(supply_box_uping_cnt >= 54000 && waving_flag == 8)
			{
        TIM4->CCR3 = 2200;//上
				waving_flag = 9;
			}
			else if(supply_box_uping_cnt >= 60000 && waving_flag == 9)
			{
        TIM4->CCR3 = 1000;//下
				waving_flag = 10;
			}
			else if(supply_box_uping_cnt >= 66000 && waving_flag == 10)
			{
        TIM4->CCR3 = 2200;//上
				waving_flag = 11;
			}
			else if(supply_box_uping_cnt >= 72000 && waving_flag == 11)
			{
        TIM4->CCR3 = 1000;//下
				waving_flag = 12;
			}
			else if(supply_box_uping_cnt >= 78000 && waving_flag == 12)
			{
        TIM4->CCR3 = 2200;//上
			}
			//////////
			if(supply_box_uping_cnt >= 80000)
			{
				TIM4->CCR3 = 1000;//下
				waving_flag = 0;
				supply_box_uping_cnt = 0;
				supply_box_uping_flag = 2;
			}
		}
		///////////////////////
		if(box_down_and_close_flag == 1)
		{
			box_down_cnt++;
			if(box_down_cnt >= 13000)
			{
				TIM4->CCR3 = 1000;
			}
			if(box_down_cnt >= 150000)
			{
				box_down_cnt = 0;
				box_down_and_close_flag = 0;
				//盒子下降并关闭
				open_or_close_motorlocationset = 0;
				box_motor_locationset = 0;
				TIM4->CCR3 = 1000;
			}
		}
			
	}
 
}



