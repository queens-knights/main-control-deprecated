/****************************************************************************
 *  Copyright (C) 2019 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
//Init
#include "dbus.h"
#include "chassis_task.h"
#include "timer_task.h"
#include "infantry_cmd.h"
#include "drv_io.h"
#include "offline_check.h"
#include "rc_light.h"
#include "tim.h"


static float vx, vy, wz;
float speed_vx,speed_vy,speed_wz;

float mouse_x;
float follow_relative_angle;
struct pid pid_follow = {0}; //angle control
float speed_ratio;

void chassis_task(void const *argument)
{

  uint32_t period = osKernelSysTick();
  chassis_t pchassis = NULL;
  rc_device_t prc_dev = NULL;
  rc_info_t prc_info = NULL;
  pchassis = chassis_find("chassis");
  prc_dev = rc_device_find("uart_rc");
		

  if (prc_dev != NULL)
  {
    prc_info = rc_device_get_info(prc_dev);
  }
  else
  {
  }

  soft_timer_register(chassis_push_info, (void *)pchassis, 10);

  pid_struct_init(&pid_follow, MAX_CHASSIS_VW_SPEED, 50, 8.0f, 0.0f, 2.0f);
	printf("hello world");
  while (1)
  {
		//ws: FB
		//ad: parallel LR
//    if (rc_device_get_state(prc_dev, RC_S2_MID) == RM_OK)
//      {
				offline_check("aaa");
				if(rc_device_get_state(prc_dev, RC_S2_DOWN) == RM_OK)
				{
        vx = (float)prc_info->ch2 / 660 * MAX_CHASSIS_VX_SPEED;
				vx = -0.8*vx;
				speed_vx=vx;
        vy = -(float)prc_info->ch1 / 660 * MAX_CHASSIS_VY_SPEED;
				vy = -0.8*vy;
				speed_vy = vy;
        wz = -(float)prc_info->ch3 / 660 * MAX_CHASSIS_VW_SPEED;
				wz = 0.8*wz;
				speed_wz = wz;
				}else if(rc_device_get_state(prc_dev, RC_S2_MID) == RM_OK)
				{
        vx = (float)prc_info->ch2 / 660 * MAX_CHASSIS_VX_SPEED;
				vx = 0.8*vx;
				speed_vx=vx;
        vy = -(float)prc_info->ch1 / 660 * MAX_CHASSIS_VY_SPEED;
				vy = 0.8*vy;
				speed_vy = vy;
				if(htim1.Instance->CCR1 == 1900){
        wz = -(float)prc_info->ch3 / 660 * MAX_CHASSIS_VW_SPEED;
				wz = 0.8*wz;
				speed_wz = wz;
				}else{
        wz = -(float)prc_info->ch3 / 660 * MAX_CHASSIS_VW_SPEED;
				wz = 0.15*wz;
				speed_wz = wz;				
				}
				}else{
        vx = (float)prc_info->ch2 / 660 * MAX_CHASSIS_VX_SPEED;
				vx = 0.2*vx;
				speed_vx=vx;
        vy = -(float)prc_info->ch1 / 660 * MAX_CHASSIS_VY_SPEED;
				vy = 0.2*vy;
				speed_vy = vy;
				wz = 0;
				}
        chassis_set_offset(pchassis, 0, 0);
        chassis_set_speed(pchassis, vx, vy, wz);
				//chassis_set_speed(pchassis, MAX_CHASSIS_VX_SPEED, MAX_CHASSIS_VY_SPEED, MAX_CHASSIS_VW_SPEED);
//    }else if(rc_device_get_state(prc_dev, RC_S2_UP) == RM_OK){
//				
//				if(prc_info->kb.bit.SHIFT){
//					LED_G_ON();
//					LED_R_OFF();
//					speed_ratio = 0.7;
//				}else if(prc_info->kb.bit.CTRL){
//					LED_R_ON();
//					LED_G_OFF();
//					speed_ratio = 0.1;
//				}else{
//					LED_G_ON();
//					LED_R_ON();
//					speed_ratio = 0.5;
//				}
//				
//				//forward and backward
//				if(prc_info->kb.bit.W)
//					vx = speed_ratio*MAX_CHASSIS_VX_SPEED;
//				else if(prc_info->kb.bit.S)
//					vx = -speed_ratio*MAX_CHASSIS_VX_SPEED;
//				else
//					vx = 0.0;
//				
//				//parallel
//				if(prc_info->kb.bit.A)
//					vy = speed_ratio*MAX_CHASSIS_VY_SPEED;
//				else if(prc_info->kb.bit.D)
//					vy = -speed_ratio*MAX_CHASSIS_VY_SPEED;
//				else
//					vy = 0.0;
//				
//				if(prc_info->kb.bit.Q)
//					wz = speed_ratio*MAX_CHASSIS_VW_SPEED;
//				else if(prc_info->kb.bit.E)
//					wz = -speed_ratio*MAX_CHASSIS_VW_SPEED;
//				else
//					wz = 0.0;
//				
//				speed_vx = vx;
//				speed_vy = vy;
//				speed_wz = wz;
//				
//				chassis_set_offset(pchassis, 0, 0);
//        chassis_set_speed(pchassis, vx, vy, wz);

//			}else if (rc_device_get_state(prc_dev, RC_S2_DOWN) == RM_OK)
//      {
//        chassis_set_speed(pchassis, 0, 0, 0);
//      }
    chassis_set_acc(pchassis, 0, 0, 0);
    chassis_execute(pchassis);
    osDelayUntil(&period, 2);
		}
  }

int32_t chassis_set_relative_angle(float angle)
{
  follow_relative_angle = angle;
  return 0;
}
