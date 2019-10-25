//Init
#include "dbus.h"
#include "chassis_task.h"
#include "timer_task.h"
#include "infantry_cmd.h"
#include "drv_io.h"
#include "rc_light.h"
#include "shoot.h"
#include "test.h"
#include "tim.h"
float chan_1,chan_2,chan_3,chan_4;
int switch_1,switch_2;

int Left, Right;
float mouse_y;
int servo_position,open_pos;
int isBoxOpen, isGripUp, isGripClose, isGripForward;
int tim8_1, tim8_2, tim8_3, tim8_4;
int tim4_2, tim4_3;
int tim1;
int Grip_UD_flag;


void rc_light(void const *argument)
{
  uint32_t period = osKernelSysTick();

  rc_device_t prc_dev = NULL;
  rc_info_t prc_info = NULL;

  shoot_t pshoot = NULL;
  pshoot = shoot_find("shoot");

  prc_dev = rc_device_find("uart_rc");

  if (prc_dev != NULL)
  {
    prc_info = rc_device_get_info(prc_dev);
  }
  else
  {
  }

	Grip_UD_flag = 0;
  while (1)
  {

		chan_1 = prc_info->ch1;
		chan_2 = prc_info->ch2;
		chan_3 = prc_info->ch3;
		chan_4 = prc_info->ch4;

		switch_1 = prc_info->sw1;
		switch_2 = prc_info->sw2;

		LED_R_OFF();
		LED_G_OFF();

		//chan_4: BoxUpDown
		if (rc_device_get_state(prc_dev, RC_S1_UP) == RM_OK)
		{	//11
			LED_G_ON();
			LED_R_ON();
			M1_ON();
			M0_ON();
		}
		else if (rc_device_get_state(prc_dev, RC_S1_MID) == RM_OK)
		{	//10
			LED_G_ON();
			LED_R_OFF();
			M1_ON();
			M0_OFF();
		}
		else if (rc_device_get_state(prc_dev, RC_S1_DOWN) == RM_OK)
		{	//01
			LED_G_OFF();
			LED_R_ON();
			M1_OFF();
			M0_ON();
		}
		
		
		if (rc_device_get_state(prc_dev, RC_S2_DOWN) == RM_OK)
		{		
			//Switch2 DOWN
				//Moving, Grip_up, Flip
				
				//Box FLIP
				//Box forward
				if(chan_4 > 550){
					open_pos = 420;
				}
				//Box backward
				if(chan_4 < -550){
					open_pos = 1482;
				}
				htim1.Instance->CCR4 = open_pos;
				tim1 = htim1.Instance->CCR4;
			}
		else if(rc_device_get_state(prc_dev, RC_S2_MID) == RM_OK)
			{
				
				//Grip_UP_DOWN
				if(chan_4 > 550){
					htim8.Instance->CCR3 = 19998;
					htim8.Instance->CCR4 = 200;
				}else if(chan_4 < -550){
					htim8.Instance->CCR3 = 200;
					htim8.Instance->CCR4 = 19998;
				}else{
					htim8.Instance->CCR4 = 200;
					htim8.Instance->CCR3 = 200;
				}
				tim8_3 = htim8.Instance->CCR3;
				tim8_4 = htim8.Instance->CCR4;
				
			}
		else if(rc_device_get_state(prc_dev, RC_S2_UP) == RM_OK)
			{
				//Switch2 up
				//Grip_Flip, Grip_UP_DOWN, grip_in_out, 
				
				//Grip_FLIP
				//grip forward
				if(chan_4 > 550){
					servo_position = 1000;
					//550
				}
				//grip backward
				if(chan_4 < -550){
					servo_position = 1900;
					//1620
				}
				htim1.Instance->CCR1 = servo_position;
				tim1 = htim1.Instance->CCR1;
				
				
				//grip_in
				if(chan_3 > 550 && servo_position == 1000){
					htim8.Instance->CCR1 = 19998;
					htim8.Instance->CCR2 = 200;
				}
				else if(chan_3 < -550 && servo_position == 1000){
					htim8.Instance->CCR1 = 200;
					htim8.Instance->CCR2 = 19998;
				}else{
					htim8.Instance->CCR1 = 200;
					htim8.Instance->CCR2 = 200;
				}
				tim8_1 = htim8.Instance->CCR1;
				tim8_2 = htim8.Instance->CCR2;
				
			}
  }
}
