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
#include "referee_system.h"

static float vx, vy, wz;
float speed_vx,speed_vy,speed_wz;
float mouse_x;
float follow_relative_angle;
struct pid pid_follow = {0}; //angle control
float speed_ratio;
float ratio;
int Control_mode = 0;

rc_info_t temp_rc;

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
		temp_rc = prc_info;
  }
  else
  {
  }

  soft_timer_register(chassis_push_info, (void *)pchassis, 10);

  pid_struct_init(&pid_follow, MAX_CHASSIS_VW_SPEED, 50, 8.0f, 0.0f, 2.0f);
  while (1)
  {
		//ws: FB
		//ad: parallel LR
//    if (rc_device_get_state(prc_dev, RC_S2_MID) == RM_OK)
//      {
				offline_check("aaa");
				ratio = (float)prc_info->ch2 / 660;

				vx = 0;
				vy = 0;
				wz = 0;
				
		if(rc_device_get_state(prc_dev, RC_S2_MID) == RM_OK){
			Control_mode = 1;
		}else if(rc_device_get_state(prc_dev, RC_S2_UP) == RM_OK){
			Control_mode = 2;
			if(judge_rece_mesg.game_status.game_process == 0x04)
				Control_mode = 0 ;
		}else{
				Control_mode = 0; 
		}
		
    chassis_set_offset(pchassis, 0, 0);
		chassis_set_speed(pchassis,vx,vy,wz);
    chassis_set_ratio(pchassis, ratio);
    chassis_set_acc(pchassis, 0, 0, 0);
    chassis_execute(pchassis, Control_mode);
    osDelayUntil(&period, 2);
		}
  }

int32_t chassis_set_relative_angle(float angle)
{
  follow_relative_angle = angle;
  return 0;
}



