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

#include "chassis.h"
#include "drv_io.h"
#include "referee_system.h"
#include "dbus.h"

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
float mAlimit = 10000.0f;
float Motor_limit = 10000.0f;
float new_current;
float control_ratio;
float B_power;
#define Threshold 800.3f //(mA)

static int32_t motor_pid_input_convert(struct controller *ctrl, void *input);
float wheel_1_rpm;
int modulefeedback[4];
float wheel_1_out;
float eco;
float totaleco;
float buffer_eco;
float buffer_percent = 0.1;
float stop_ratio;
int threshold = 0;
float speed = 6000;
int motor_mode = 0;
int ran_sum = 0;
int current_target = 0;
int next_target = 0;
int motor_current0;
int motor_current1;
int control_out0;
int control_out1;
int state;

int32_t chassis_pid_register(struct chassis *chassis, const char *name, enum device_can can)
{
  char motor_name[4][OBJECT_NAME_MAX_LEN] = {0};
  uint8_t name_len;

  int32_t err;

  if (chassis == NULL)
    return -RM_INVAL;
  if (chassis_find(name) != NULL)
    return -RM_EXISTED;

  object_init(&(chassis->parent), Object_Class_Chassis, name);

  name_len = strlen(name);

  if (name_len > OBJECT_NAME_MAX_LEN / 2)
  {
    name_len = OBJECT_NAME_MAX_LEN / 2;
  }

  for (int i = 0; i < 4; i++)
  {
    memcpy(&motor_name[i], name, name_len);
    chassis->motor[i].can_periph = can;
    chassis->motor[i].can_id = 0x201 + i;
    chassis->motor[i].init_offset_f = 1;

    chassis->ctrl[i].convert_feedback = motor_pid_input_convert;
    pid_struct_init(&chassis->motor_pid[i], 15000, 500, 6.5f, 0.1, 0);
  }

  chassis->mecanum.param.wheel_perimeter = PERIMETER;
  chassis->mecanum.param.wheeltrack = WHEELTRACK;
  chassis->mecanum.param.wheelbase = WHEELBASE;
  chassis->mecanum.param.rotate_x_offset = ROTATE_X_OFFSET;
  chassis->mecanum.param.rotate_y_offset = ROTATE_Y_OFFSET;

  memcpy(&motor_name[0][name_len], "_FR\0", 4);
  memcpy(&motor_name[1][name_len], "_FL\0", 4);
  memcpy(&motor_name[2][name_len], "_BL\0", 4);
  memcpy(&motor_name[3][name_len], "_BR\0", 4);

  for (int i = 0; i < 4; i++)
  {
    err = motor_device_register(&(chassis->motor[i]), motor_name[i], 0);
    if (err !=  RM_OK)
      goto end;
  }

  memcpy(&motor_name[0][name_len], "_CTLFR\0", 7);
  memcpy(&motor_name[1][name_len], "_CTLFL\0", 7);
  memcpy(&motor_name[2][name_len], "_CTLBL\0", 7);
  memcpy(&motor_name[3][name_len], "_CTLBR\0", 7);

  for (int i = 0; i < 4; i++)
  {
    err = pid_controller_register(&(chassis->ctrl[i]), motor_name[i], &(chassis->motor_pid[i]), &(chassis->motor_feedback[i]), 1);
    if (err != RM_OK)
      goto end;
  }

  return RM_OK;
end:
  object_detach(&(chassis->parent));

  return err;
}

int32_t chassis_execute(struct chassis *chassis, int Control_mode)
{
  float motor_out;
  struct motor_data *pdata;
  struct mecanum_motor_fdb wheel_fdb[4];

  static uint8_t init_f = 0;
  static float last_time, period;

	flag = 0;
	
	
  if (chassis == NULL)
    return -RM_INVAL;
	
	period  = get_time_ms_us() - last_time;

  if(!init_f)
  {
    period = 0;
		last_time = get_time_ms_us();
    init_f = 1;
  }
  else
  {
    last_time = get_time_ms_us();

    chassis->mecanum.speed.vx += chassis->acc.ax/1000.0f*period;
    chassis->mecanum.speed.vy += chassis->acc.ay/1000.0f*period;
    chassis->mecanum.speed.vw += chassis->acc.wz/1000.0f*period;
  }

  mecanum_calculate(&(chassis->mecanum));

  for (int i = 0; i < 2; i++)
  {
    pdata = motor_device_get_data(&(chassis->motor[i]));

    wheel_fdb[i].total_ecd = pdata->total_ecd;
    wheel_fdb[i].speed_rpm = pdata->speed_rpm;
		
		buffer_eco = (buffer_percent)*threshold;
	
    //controller_set_input(&chassis->ctrl[i], chassis->mecanum.wheel_rpm[i]);
		if(Control_mode == 0){
			if(motor_mode == 0){
				if(totaleco <= (int)buffer_eco){ //start up
				stop_ratio = totaleco/buffer_eco;
				if(stop_ratio < 0.05)
					stop_ratio = 0.05;
				controller_set_input(&chassis->ctrl[0], speed*stop_ratio);
				controller_set_input(&chassis->ctrl[1], -speed*stop_ratio);
				state = 1;
				}else if(totaleco >= (int)(threshold - buffer_eco)){
				stop_ratio = (threshold-totaleco)/(buffer_eco);
				controller_set_input(&chassis->ctrl[0], speed*stop_ratio);
				controller_set_input(&chassis->ctrl[1], -speed*stop_ratio);
				if(stop_ratio < 0.05)
					motor_mode = 1;
				state = 2;
				}else{
				controller_set_input(&chassis->ctrl[0], speed);
				controller_set_input(&chassis->ctrl[1], -speed);
				state = 3;
				}			
			}else if(motor_mode  == 1){
				if(totaleco <= (int)buffer_eco){ //stop
				stop_ratio = totaleco/buffer_eco;
				controller_set_input(&chassis->ctrl[0], -speed*stop_ratio);
				controller_set_input(&chassis->ctrl[1], speed*stop_ratio);
				if(stop_ratio < 0.05)
					motor_mode = 0;
				state = 4;
				}else if(totaleco >= (int)(threshold - buffer_eco)){
				stop_ratio = (threshold-totaleco)/(buffer_eco);
			  if(stop_ratio < 0.05)
					stop_ratio = 0.05;
				controller_set_input(&chassis->ctrl[0], -speed*stop_ratio);
				controller_set_input(&chassis->ctrl[1], speed*stop_ratio);
				state = 5;
				}else{
				controller_set_input(&chassis->ctrl[0], -speed);
				controller_set_input(&chassis->ctrl[1], speed);
				state = 6;
				}
			}				
		}else if(Control_mode == 2){
			controller_set_input(&chassis->ctrl[0], speed*(chassis->ratio));
			controller_set_input(&chassis->ctrl[1], -speed*(chassis->ratio));
			threshold = 0;
			motor_mode = 0;
			ran_sum = 0;
			current_target = 0;
			next_target = 0;
		}else if(Control_mode == 1){
			threshold = totaleco;
		}
    controller_execute(&chassis->ctrl[i], (void *)pdata);
    controller_get_output(&chassis->ctrl[i], &motor_out);
		
		modulefeedback[i]=chassis->ctrl[i].input;
		
		//motor_device_set_current(&chassis->motor[i], (int16_t)motor_out);
		
		if( i == 0)
			motor_current0 = motor_out;
		else if(i == 1)
			motor_current1 = motor_out;

  }
	
	//power limit 
	control_ratio = Motor_limit/mAlimit;
	
	B_power = judge_rece_mesg.power_heat.chassis_power_buffer;
	
	total_cur1 = (float)(abs(motor_current0) + abs(motor_current1));
	
	total_cur2 = total_cur1/control_ratio;
	
	if (total_cur2 > Threshold && B_power < 30)
  {
	
		c0 = ((float)motor_current0 / total_cur1) * Threshold;
    c1 = ((float)motor_current1 / total_cur1) * Threshold;
		motor_current0 = c0 * control_ratio;
		motor_current1 = c1 * control_ratio;
		flag = 1;
  }
	
	after_current1 = (float)(abs(motor_current0) + abs(motor_current1));
	after_current = judge_rece_mesg.power_heat.chassis_current;
	limit = total_cur_limit;
	current_power = judge_rece_mesg.power_heat.chassis_power;
	
	motor_device_set_current(&chassis->motor[0], (int16_t)motor_current0);
	motor_device_set_current(&chassis->motor[1], (int16_t)motor_current1);
	
	
	
//	ran_sum = ran_sum + (int)(0.571*threshold);
//	
//	while(ran_sum > threshold){
//		ran_sum = ran_sum - (int)(0.733*threshold);
//	}
//	
//	while(ran_sum < 0){
//		ran_sum = ran_sum + (int)(0.733*threshold);
//	}
	
//	if(motor_mode == 0){
//		if(ran_sum < current_target & ((current_target - ran_sum) > 0.3*threshold)){
//			next_target = ran_sum;
//		}
//		if(totaleco > current_target){
//			current_target = next_target;
//			motor_mode = 1;
//		}
//	}else if(motor_mode == 1){
//		if(ran_sum > current_target & ((ran_sum - current_target) > 0.3*threshold)){
//			next_target = ran_sum;
//		}
//		if(totaleco < current_target){
//			current_target = next_target;
//			motor_mode = 0;
//		}
//	}
	
	wheel_1_out = chassis->motor[0].current;
	
	eco = chassis->motor[0].data.ecd;
	
	totaleco = chassis->motor[0].data.total_ecd;
//	
//	if(totaleco >= 0.995*threshold ){
//		motor_mode = 1;
//	}else if(totaleco <= 0.005*threshold){
//		motor_mode = 0;
//	}
	

	
	
	//wheel_1_rpm = 5000*(chassis->ratio);
	
	motor_device_can_output(DEVICE_CAN1);
	
  mecanum_position_measure(&(chassis->mecanum), wheel_fdb);

  return RM_OK;
}

int32_t chassis_gyro_updata(struct chassis *chassis, float yaw_angle, float yaw_rate)
{
  if (chassis == NULL)
    return -RM_INVAL;
  chassis->mecanum.gyro.yaw_gyro_angle = yaw_angle;
  chassis->mecanum.gyro.yaw_gyro_rate = yaw_rate;
  return RM_OK;
}

int32_t chassis_set_speed(struct chassis *chassis, float vx, float vy, float vw)
{
  if (chassis == NULL)
    return -RM_INVAL;
  chassis->mecanum.speed.vx = vx;
  chassis->mecanum.speed.vy = vy;
  chassis->mecanum.speed.vw = vw;
  return RM_OK;
}

int32_t chassis_set_ratio(struct chassis *chassis, float ratio)
{
  if (chassis == NULL)
    return -RM_INVAL;
  chassis->ratio = ratio;
  return RM_OK;
}

int32_t chassis_set_acc(struct chassis *chassis, float ax, float ay, float wz)
{
  if (chassis == NULL)
    return -RM_INVAL;
  chassis->acc.ax = ax;
  chassis->acc.ay = ay;
  chassis->acc.wz = wz;
  return RM_OK;
}

int32_t chassis_set_vw(struct chassis *chassis, float vw)
{
  if (chassis == NULL)
    return -RM_INVAL;
  chassis->mecanum.speed.vw = vw;
  return RM_OK;
}

int32_t chassis_set_vx_vy(struct chassis *chassis, float vx, float vy)
{
  if (chassis == NULL)
    return -RM_INVAL;
  chassis->mecanum.speed.vx = vx;
  chassis->mecanum.speed.vy = vy;
  return RM_OK;
}

int32_t chassis_set_offset(struct chassis *chassis, float offset_x, float offset_y)
{
  if (chassis == NULL)
    return -RM_INVAL;

  chassis->mecanum.param.rotate_x_offset = offset_x;
  chassis->mecanum.param.rotate_y_offset = offset_y;

  return RM_OK;
}

int32_t chassis_get_info(struct chassis *chassis, struct chassis_info *info)
{
  if (chassis == NULL)
    return NULL;

  memcpy(info, &(chassis->mecanum.position), sizeof(struct mecanum_position));
  ANGLE_LIMIT_360(info->angle_deg, chassis->mecanum.position.angle_deg);
  ANGLE_LIMIT_360_TO_180(info->angle_deg);
  ANGLE_LIMIT_360(info->yaw_gyro_angle, chassis->mecanum.gyro.yaw_gyro_angle);
  ANGLE_LIMIT_360_TO_180(info->yaw_gyro_angle);
  info->yaw_gyro_rate = chassis->mecanum.gyro.yaw_gyro_rate;

  for (int i = 0; i < 4; i++)
  {
    info->wheel_rpm[i] = chassis->mecanum.wheel_rpm[i] * MOTOR_DECELE_RATIO;
  }

  return RM_OK;
}

chassis_t chassis_find(const char *name)
{
  struct object *object;

  object = object_find(name, Object_Class_Chassis);

  return (chassis_t)object;
}

int32_t chassis_enable(struct chassis *chassis)
{
  if (chassis == NULL)
    return -RM_INVAL;

  for (int i = 0; i < 4; i++)
  {
    controller_enable(&(chassis->ctrl[i]));
  }

  return RM_OK;
}

int32_t chassis_disable(struct chassis *chassis)
{
  if (chassis == NULL)
    return -RM_INVAL;

  for (int i = 0; i < 4; i++)
  {
    controller_disable(&(chassis->ctrl[i]));
  }

  return RM_OK;
}

static int32_t motor_pid_input_convert(struct controller *ctrl, void *input)
{
  pid_feedback_t pid_fdb = (pid_feedback_t)(ctrl->feedback);
  motor_data_t data = (motor_data_t)input;
  pid_fdb->feedback = data->speed_rpm;

  return RM_OK;
}

//power limit

