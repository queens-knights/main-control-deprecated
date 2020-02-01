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
 


  
#ifndef __CHASSIS_TASK_H__
#define __CHASSIS_TASK_H__

#include "stm32f4xx_hal.h"

/* 底盘控制周期 (ms) */
/* chassis control period in ms*/
#define CHASSIS_PERIOD 10
/* 底盘扭腰角度 (degree)*/
/* chassis twist angel in degree*/
#define TWIST_ANGLE    50
/* 底盘扭腰周期 (ms) */
/* chassis twist period in ms*/
#define TWIST_PERIOD   1500

/**
  * @brief     底盘控制模式枚举 chassis task mode type define
  */
typedef enum
{
  CHASSIS_STOP,          //底盘停止chassis stopped
  CHASSIS_RELAX,         //底盘失能chassis deenergized 
  CHASSIS_OPEN_LOOP,     //底盘开环chassis open loop
  CHASSIS_FOLLOW_GIMBAL, //底盘跟随云台chassis follow gimbal
  CHASSIS_FIXED_ROUTE,   //底盘固定路线chassis in fixed route
  CHASSIS_TWIST,         //底盘扭腰模式chassis twisting
} chassis_mode_e;

/**
  * @brief     底盘控制数据结构体 chassis control struct
  */
typedef struct
{
  /* 底盘控制模式相关 */
  chassis_mode_e  mode;       //当前底盘控制模式current chassis mode
  chassis_mode_e  last_mode;  //上次底盘控制模式previous chassis mode
  
  /* 底盘移动速度相关数据 */
  float           vx;         //底盘前后速度chassis speed forward backword
  float           vy;         //底盘左右速度chassis speed left right
  float           vw;         //底盘旋转速度chassis speed twisting

  
  uint8_t         last_sw2;
} chassis_t;


/**
  * @brief     底盘控制任务函数chassis control function
  */
void chassis_task(const void* argu);
/**
  * @brief     底盘速度分解，计算底盘每个轮子速度calculate speed of each motor from vx vy vw
  * @param     vx: 底盘前后速度forward backword 
  * @param     vy: 底盘左右速度left right
  * @param     vw: 底盘旋转速度twisting
  * @param     speed[]: 4 个轮子速度数组struct for speed on 4 wheels
  */
void chassis_moto_speed_calc(float vx, float vy, float vw, int16_t speed[]);
/**
  * @brief     获取底盘控制模式get chassis control mode
  */
void get_chassis_mode(void);
/**
  * @brief     底盘控制参数初始化chassis parameter init
  */
void chassis_pid_param_init(void);
/**
  * @brief     底盘自定义控制代码接口chassis custom control 
  */
void chassis_custom_control(void);
/**
  * @brief     底盘控制信息获取chassis get information
  */
void chassis_control_information_get(void);
/**
  * @brief     底盘速度闭环处理计算函数calculte close loop speed
  */
void chassis_close_loop_calculate(void);
/**
  * @brief     底盘速度开环处理计算函数calculate open loop speed
  */
void chassis_open_loop_calculate(void);
/**
  * @brief     底盘扭腰处理函数twisting speed calculate
  */
void chassis_twist_handle(void);

extern chassis_t chassis;
extern int16_t   chassis_moto_current[];

#endif
