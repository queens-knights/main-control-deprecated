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
 



#ifndef __GIMBAL_TASK_H__
#define __GIMBAL_TASK_H__

#include "stm32f4xx_hal.h"
#include "rm_hal_lib.h"

/* 云台控制周期 (ms) */
// gimbal control period in ms
#define GIMBAL_PERIOD 5
/* 云台回中初始化时间 (ms) */
//gimbal center return initilize time in ms
#define BACK_CENTER_TIME 10000

/**
  * @brief     云台控制任务函数gimbal control premeter
  */
void gimbal_task(const void* argu);

/**
  * @brief     云台控制模式枚举gimbal control struct
  */
typedef enum
{
  GIMBAL_INIT = 0,         //云台初始化gimbal initilize
  GIMBAL_RELAX,            //云台断电gimbal deenergized
  GIMBAL_CLOSE_LOOP_ZGYRO, //云台跟随单轴角度gimbal follow z axis angle
  GIMBAL_NO_ACTION,        //无手动信号输入状态gimbval no input data
} gimbal_mode_e;

/**
  * @brief     云台控制信号输入状态枚举gimbal input status struct
  */
typedef enum
{
  NO_ACTION = 0,           //无控制信号输入no control input
  IS_ACTION,               //有控制信号输入have control input
} action_mode_e;

/**
  * @brief     云台回中状态枚举gimbal back to center struct
  */
typedef enum
{
  BACK_PIT_STEP,           //云台 pitch 轴回中gimbal pitch center
  YAW_BACK_STEP,           //云台 yaw 轴回中gimbal yaw center
  BACK_IS_OK,              //云台回中完毕centered
} gimbal_back_e;

/**
  * @brief     云台控制数据结构体gimbal control data struct
  */
typedef struct
{
  gimbal_mode_e ctrl_mode; //云台当前控制模式current gimbal mode
  gimbal_mode_e last_mode; //云台上次控制模式previous gimbal mode

  action_mode_e ac_mode;   //云台控制信号输入模式gimbal have control input
  
  uint8_t  no_action_flag; //无控制信号标志no control input flag
  uint32_t no_action_time; //无控制信号时间no control input time

  float ecd_offset_angle;  //云台初始编码器值gimbal initial encoder value
  float yaw_offset_angle;  //云台初始 yaw 轴角度pitch angle
} gimbal_yaw_t;

extern gimbal_yaw_t gim;
extern imu_t        imu;

/* 云台 PID 控制相关数据 */
//gimbal pid related
extern float yaw_angle_ref;
extern float pit_angle_ref; 
extern float yaw_angle_fdb;
extern float pit_angle_fdb;
extern float yaw_speed_ref;
extern float pit_speed_ref;
/* 云台相对角度 */
//gimbal relative angel 
extern float yaw_relative_angle;
extern float pit_relative_angle;


/* 发射机构控制相关数据 */
//shooting related
extern int16_t  trigger_moto_speed_ref;    //拨弹电机速度目标值target dialwhgeel speed
extern uint8_t  fric_wheel_run;            //摩擦轮开关friction wheel on off
extern uint16_t fric_wheel_speed;          //摩擦轮速度friction wheel speed
extern int32_t  trigger_moto_position_ref; //拨弹电机位置目标值target potisioon of dialwheel 
extern uint8_t  shoot_cmd;                 //单发发射命令single shoot input
extern uint8_t  continuous_shoot_cmd;      //连发发射命令continue shoot input

/**
  * @brief     读取云台中点的编码器偏移数据read gimbal center encoder offset
  * @param     pit_offset: pitch 轴编码器数据指针pitch pointer
  * @param     yaw_offset: yaw 轴编码器数据指针yaw pointer
  */
static void read_gimbal_offset(int32_t *pit_offset, int32_t *yaw_offset);
/**
  * @brief     获取云台传感器信息get gimbal sensor data
  */
static void get_gimbal_information(void);
/**
  * @brief     获取云台控制模式get gimbal mode
  */
static void get_gimbal_mode(void);
/**
  * @brief     云台控制参数初始化initalize gimbal control parameter
  */
static void gimbal_init_param(void);
/**
  * @brief     云台回中初始化模式处理函数gimbal center init function
  */
static void gimbal_init_handle(void);
/**
  * @brief     云台无控制信号输入模式处理函数gimbal no input premeter
  */
static void gimbal_noaction_handle(void);
/**
  * @brief     云台跟随编码器闭环控制处理函数gimbal encoder close loop handling
  */
static void gimbal_loop_handle(void);
/**
  * @brief     发射机构控制任务函数shooting control
  */
void shoot_task(void);
/**
  * @brief     云台自定义控制代码接口gimbal custom parameter
  */
void gimbal_custom_control(void);
/**
  * @brief     云台 yaw 轴位置闭环控制yaw close loop control
  */
void gimbal_yaw_control(void);
/**
  * @brief     云台 pitch 轴位置闭环控制pitch close loop control
  */
void gimbal_pitch_control(void);
/**
  * @brief     发射机构自定义控制代码接口custom shoot custom control 
  */
void shoot_custom_control(void);
/**
  * @brief     开关摩擦轮控制函数friction wheel control
  */
void turn_on_off_friction_wheel(void);

#endif

