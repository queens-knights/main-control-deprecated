/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
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
/** @file chassis_task.c
 *  @version 1.1
 *  @date June 2017
 *
 *  @brief chassis control task
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */

#include "chassis_task.h"
#include "gimbal_task.h"
#include "detect_task.h"
#include "comm_task.h"
#include "modeswitch_task.h"
#include "info_get_task.h"
#include "info_interactive.h"
#include "infantry_info.h"
#include "judgement_info.h"
#include "remote_ctrl.h"
#include "keyboard.h"
#include "pid.h"
#include "sys_config.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "cmsis_os.h"

/* chassis twist angle (degree)*/
#define TWIST_ANGLE    40
/* twist period time (ms) */
#define TWIST_PERIOD   1500
/* warning surplus energy */
#define Threshold 3333.3f //(mA)

UBaseType_t chassis_stack_surplus;

/* chassis task global parameter */
chassis_t chassis;

uint32_t chassis_time_last;
int chassis_time_ms;
extern TaskHandle_t can_msg_send_task_t;
void chassis_task(void const *argu)
{
  chassis_time_ms = HAL_GetTick() - chassis_time_last;
  chassis_time_last = HAL_GetTick();
  
//    get_chassis_info();
//    get_chassis_mode();
	if(rc.sw2 == RC_UP){
		chassis_twist_handler();
	}else
		follow_gimbal_handler();
  

  mecanum_calc(chassis.vx, chassis.vy, chassis.vw, chassis.wheel_spd_ref);

  for (int i = 0; i < 4; i++)
  {
    chassis.current[i] = pid_calc(&pid_spd[i], chassis.wheel_spd_fdb[i], chassis.wheel_spd_ref[i]);
  }
  
  if (!chassis_is_controllable())
  {
    memset(chassis.current, 0, sizeof(chassis.current));
  }
  
	power_limit_handler();
	
  memcpy(glb_cur.chassis_cur, chassis.current, sizeof(chassis.current));
  osSignalSet(can_msg_send_task_t, CHASSIS_MOTOR_MSG_SEND);
  
  chassis_stack_surplus = uxTaskGetStackHighWaterMark(NULL);
}


void chassis_stop_handler(void)
{
  chassis.vy = 0;
  chassis.vx = 0;
  chassis.vw = 0;
}

uint32_t twist_count;
static void chassis_twist_handler(void)
{
  static int16_t twist_period = TWIST_PERIOD/CHASSIS_PERIOD;
  static int16_t twist_angle  = TWIST_ANGLE;
  twist_count++;
  chassis.position_ref = twist_angle*sin(2*PI/twist_period*twist_count);
  chassis.vw = -pid_calc(&pid_chassis_angle, gim.sensor.yaw_relative_angle, chassis.position_ref);
}
void separate_gimbal_handler(void)
{
  chassis.vy = rm.vy * CHASSIS_RC_MOVE_RATIO_Y + km.vy * CHASSIS_KB_MOVE_RATIO_Y;
  chassis.vx = rm.vx * CHASSIS_RC_MOVE_RATIO_X + km.vx * CHASSIS_KB_MOVE_RATIO_X;
  chassis.vw = rm.vw * CHASSIS_RC_MOVE_RATIO_R;
}
void follow_gimbal_handler(void)
{
  chassis.position_ref = 0;
  
  chassis.vy = rm.vy * CHASSIS_RC_MOVE_RATIO_Y + km.vy * CHASSIS_KB_MOVE_RATIO_Y;
  chassis.vx = rm.vx * CHASSIS_RC_MOVE_RATIO_X + km.vx * CHASSIS_KB_MOVE_RATIO_X;

  if (chassis.follow_gimbal)
    chassis.vw = -pid_calc(&pid_chassis_angle, gim.sensor.yaw_relative_angle, chassis.position_ref);
  else
    chassis.vw = 0;
}

/**
  * @brief mecanum chassis velocity decomposition
  * @param input : ↑=+vx(mm/s)  ←=+vy(mm/s)  ccw=+vw(deg/s)
  *        output: every wheel speed(rpm)
  * @note  1=FR 2=FL 3=BL 4=BR
  */
int rotation_center_gimbal = 0;
void mecanum_calc(float vx, float vy, float vw, int16_t speed[])
{
  static float rotate_ratio_fr;
  static float rotate_ratio_fl;
  static float rotate_ratio_bl;
  static float rotate_ratio_br;
  static float wheel_rpm_ratio;
  
  taskENTER_CRITICAL();
  if(chassis.ctrl_mode == DODGE_MODE)
  {
    chassis.rotate_x_offset = GIMBAL_X_OFFSET;
    chassis.rotate_y_offset = 0;
  }
  else
  {
    if (rotation_center_gimbal)
    {
      chassis.rotate_x_offset = glb_struct.gimbal_x_offset;
      chassis.rotate_y_offset = glb_struct.gimbal_y_offset;
    }
    else
    {
      chassis.rotate_x_offset = 0;
      chassis.rotate_y_offset = 0;
    }
  }
  
  rotate_ratio_fr = ((glb_struct.wheel_base+glb_struct.wheel_track)/2.0f \
                      - chassis.rotate_x_offset + chassis.rotate_y_offset)/RADIAN_COEF;
  rotate_ratio_fl = ((glb_struct.wheel_base+glb_struct.wheel_track)/2.0f \
                      - chassis.rotate_x_offset - chassis.rotate_y_offset)/RADIAN_COEF;
  rotate_ratio_bl = ((glb_struct.wheel_base+glb_struct.wheel_track)/2.0f \
                      + chassis.rotate_x_offset - chassis.rotate_y_offset)/RADIAN_COEF;
  rotate_ratio_br = ((glb_struct.wheel_base+glb_struct.wheel_track)/2.0f \
                      + chassis.rotate_x_offset + chassis.rotate_y_offset)/RADIAN_COEF;

  wheel_rpm_ratio = 60.0f/(glb_struct.wheel_perimeter*CHASSIS_DECELE_RATIO);
  taskEXIT_CRITICAL();
  
  
  VAL_LIMIT(vx, -MAX_CHASSIS_VX_SPEED, MAX_CHASSIS_VX_SPEED);  //mm/s
  VAL_LIMIT(vy, -MAX_CHASSIS_VY_SPEED, MAX_CHASSIS_VY_SPEED);  //mm/s
  VAL_LIMIT(vw, -MAX_CHASSIS_VR_SPEED, MAX_CHASSIS_VR_SPEED);  //deg/s
  
  int16_t wheel_rpm[4];
  float   max = 0;
  
  wheel_rpm[0] = (-vx - vy - vw * rotate_ratio_fr) * wheel_rpm_ratio;
  wheel_rpm[1] = ( vx - vy - vw * rotate_ratio_fl) * wheel_rpm_ratio;
  wheel_rpm[2] = ( vx + vy - vw * rotate_ratio_bl) * wheel_rpm_ratio;
  wheel_rpm[3] = (-vx + vy - vw * rotate_ratio_br) * wheel_rpm_ratio;

  //find max item
  for (uint8_t i = 0; i < 4; i++)
  {
    if (abs(wheel_rpm[i]) > max)
      max = abs(wheel_rpm[i]);
  }
  //equal proportion
  if (max > MAX_WHEEL_RPM)
  {
    float rate = MAX_WHEEL_RPM / max;
    for (uint8_t i = 0; i < 4; i++)
      wheel_rpm[i] *= rate;
  }
  memcpy(speed, wheel_rpm, 4*sizeof(int16_t));
}



/**
  * @brief  nitialize chassis motor pid parameter
  * @usage  before chassis loop use this function
  */
void chassis_param_init(void)
{
  memset(&chassis, 0, sizeof(chassis_t));
  
  chassis.ctrl_mode      = CHASSIS_STOP;
  chassis.last_ctrl_mode = CHASSIS_RELAX;
  
#ifdef CHASSIS_EC60
  for (int k = 0; k < 4; k++)
  {
    PID_struct_init(&pid_spd[k], POSITI ON_PID, 10000, 2500, 25, 1.2, 0);
  }
#else
  for (int k = 0; k < 4; k++)
  {
    PID_struct_init(&pid_spd[k], POSITION_PID, 10000, 1000, 3.0f, 0, 0);
  }
#endif
  
  PID_struct_init(&pid_chassis_angle, POSITION_PID, MAX_CHASSIS_VR_SPEED, 50, 14.0f, 0.0f, 50.0f);
  
  glb_struct.chassis_config = NO_CONFIG;
  glb_struct.gimbal_config  = NO_CONFIG;
  
  memset(&pc_recv_mesg.structure_data, 0, sizeof(pc_recv_mesg.structure_data));
}

int32_t total_cur_limit;
int32_t total_cur;
float limit;
float total_cur1;
float total_cur2;
float current_power;
float current_current;
float current_voltage;
float c0, c1, c2, c3;
float after_current;
float after_current1;
int flag = 0;
float mAlimit = 20000.0f;
float Motor_limit = 16384.0f;
float new_current;
float control_ratio;
float B_power;
void power_limit_handler(void)
{
	//Threshold is in mA
	
	
	control_ratio = Motor_limit/mAlimit;
	
	B_power = judge_rece_mesg.power_heat.chassis_power_buffer;
	
	total_cur1 = (float)(abs(chassis.current[0]) + abs(chassis.current[1]) + abs(chassis.current[2]) + abs(chassis.current[3]));
  
	total_cur2 = total_cur1/control_ratio;
	
  if (total_cur2 > Threshold && B_power < 30)
  {
		
    c0 = ((float)chassis.current[0] / total_cur1) * Threshold;
    c1 = ((float)chassis.current[1] / total_cur1) * Threshold;
    c2 = ((float)chassis.current[2] / total_cur1) * Threshold;
    c3 = ((float)chassis.current[3] / total_cur1) * Threshold;
		chassis.current[0] = c0 * control_ratio;
		chassis.current[1] = c1 * control_ratio;
		chassis.current[2] = c2 * control_ratio;
		chassis.current[3] = c3 * control_ratio;
		flag = 1;
  }

	after_current1 = (float)(abs(chassis.current[0]) + abs(chassis.current[1]) + abs(chassis.current[2]) + abs(chassis.current[3]));
	after_current = judge_rece_mesg.power_heat.chassis_current;
	limit = total_cur_limit;
	current_power = judge_rece_mesg.power_heat.chassis_power;
	
}

