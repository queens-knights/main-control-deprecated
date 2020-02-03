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

/**
  *********************** (C) COPYRIGHT 2018 DJI **********************
  * @update
  * @history
  * Version     Date              Author           Modification
  * V1.0.0      January-15-2018   ric.luo
  * @verbatim
  *********************** (C) COPYRIGHT 2018 DJI **********************
  */ 
 



/************************************ 用户对发射机构自定义控制 User defined control of shooting system*************************************/
#include "gimbal_task.h"
#include "can_device.h"
#include "pid.h"
#include "sys.h"

/* 拨弹电机期望位置(单位是编码器数值encoder) Drum motor expected location (unit is encoder data)*/
int32_t trigger_moto_position_ref;
/* 拨弹电机期望转速(rpm) Drum motor expected spinning speed (rpm)*/
int16_t trigger_moto_speed_ref;
/* 拨弹电机电流 Drum motor current*/
int16_t trigger_moto_current;

/* 子弹的单发和连发处理 Bullet firing mode (single and automatic)*/
void shoot_custom_control(void)
{
  if (fric_wheel_run)
  {
    /* 如果是单发命令，拨轮旋转60度 if it is single firing, dialwheel turns 60 degrees*/
    if (shoot_cmd)
    {
      trigger_moto_position_ref = moto_trigger.total_ecd + DEGREE_60_TO_ENCODER;
      shoot_cmd = 0;
    }
    /* 闭环计算拨弹电机期望转速 Close loop calculation drum motor expected spinning speed*/
    trigger_moto_speed_ref = pid_calc(&pid_trigger, moto_trigger.total_ecd, trigger_moto_position_ref);
    
    /* 如果是连发模式，将电机转速设定为固定值 If it is automatic mode, and motor spinning speed should set as a fixed value*/
    if (continuous_shoot_cmd)
    {
      trigger_moto_speed_ref = TRIGGER_MOTOR_SPEED;  
    }
    
   // block_bullet_handle();                                 //卡弹处理 blocked bullet handle
    
    /* 闭环计算拨弹电机电流 Close loop calculation drum motor current*/
    trigger_moto_current = pid_calc(&pid_trigger_speed, moto_trigger.speed_rpm, trigger_moto_speed_ref);
  }
  else
  {
    trigger_moto_current = 0;
  }
  /* 发送电流值到拨弹电机电调 Send current value to drum motor*/
  //在云台控制中，拨弹电机和云台电机的电流数据同时被发送 In gimbal control, drum motor and gimbal motor current data are being sent at the same time

}

/* 开关摩擦轮处理 Turn on and off friction wheel*/
void turn_on_off_friction_wheel(void)
{
  if (fric_wheel_run)
  {
    //打开摩擦轮 turn on friction wheel
    set_pwm_param(PWM_IO1, fric_wheel_speed);
    set_pwm_param(PWM_IO2, fric_wheel_speed);
    //打开激光 turn on laser
    write_led_io(LASER_IO, LED_ON);
  }
  else
  {
    //关闭摩擦轮 turn off friction wheel
    set_pwm_param(PWM_IO1, 1000);
    set_pwm_param(PWM_IO2, 1000);
    //关闭激光 turn off laser
    write_led_io(LASER_IO, LED_OFF);
  }
}
