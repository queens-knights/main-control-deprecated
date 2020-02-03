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
 



#ifndef __SYS_H__
#define __SYS_H__

#include "rm_hal_lib.h"

/*************************课程模块设置 Course module setup*******************************/
///* 可用的课程模块选项有 Course module that can be used*/
//enum
//{
//  ALONE_MOTO_TEST,    //单独电机测试 Single motor testing
//  ALONE_CHASSIS,      //单独底盘机构 Single chassis mechanism
//  ALONE_GIMBAL,       //单独云台机构 Single gimbal mechanism
//  ALONE_SHOOT,        //单独发射机构 Single shooting mechanism
//  COMPLETE_STRUCTURE, //整车结构模式 Entire robot structure mode
//};
///* 将上面课程模块使用如下的宏定义使能 Enable the above course module using the following macro definition*/
//#define INFANTRY_STRUCT COMPLETE_STRUCTURE
/* 4轮车，如果使用3轮车注释掉此宏定义 Four wheels, if using three wheel then comment out this macro definition*/
#define FOUR_WHEEL

/*************************底盘速度设置 Chassis speed setup*******************************/

/* 遥控器模式下的底盘最大速度限制 Chassis max speed limit under remote control mode*/
/* 底盘平移速度 Chassis side way moving speed*/
#define CHASSIS_RC_MOVE_RATIO_X 1.0f
/* 底盘前进速度 Chassis forward moving speed*/
#define CHASSIS_RC_MOVE_RATIO_Y 1.0f
/* 底盘旋转速度，只在底盘开环模式下使用 Chassis spinning speed, only use under chassis open loop mode*/
#define CHASSIS_RC_MOVE_RATIO_R 1.0f

/* 鼠标键盘模式下的底盘最大速度限制 Chassis max speed limite under keyboard and mouse mode*/
/* 底盘平移速度 Chassis side way moving speed*/
#define CHASSIS_PC_MOVE_RATIO_X 1.0f
/* 底盘前进速度 Chassis forward moving speed*/
#define CHASSIS_PC_MOVE_RATIO_Y 1.0f
/* 底盘旋转速度，只在底盘开环模式下使用 Chassis spinning speed, only use under chassis open loop mode*/
#define CHASSIS_PC_MOVE_RATIO_R 5.0f

/*************************云台速度设置 Gimbal speed setup*******************************/

/* 遥控器模式下的云台速度限制 Gimbal speed limit under remote control mode*/
/* 云台pitch轴速度 Gimbal pitch axis speed*/
#define GIMBAL_RC_MOVE_RATIO_PIT 1.0f
/* 云台yaw轴速度 Gimbal yaw axis speed*/
#define GIMBAL_RC_MOVE_RATIO_YAW 1.0f
/* 鼠标键盘模式下的云台速度限制 Gimbal speed limit under keyboard and mouse mode*/
/* 云台pitch轴速度 Gimbal pitch axis speed*/
#define GIMBAL_PC_MOVE_RATIO_PIT 1.2f
/* 云台yaw轴速度 Gimbal yaw axis speed*/
#define GIMBAL_PC_MOVE_RATIO_YAW 1.0f


/*************************发射速度设置 Shooting speed setup*******************************/
#define SHOT_FRIC_WHEEL_SPEED    1300 //最大为2500 max
 

/*************************发射频率设置 Shooting frequency setup*******************************/
#define TRIGGER_MOTOR_SPEED      -5000 //






/*************************下面是系统接口设置，请勿改动 Below is system port setup, DO NOT MODIFY**************************/


/* 遥控器的最大行程 Max stroke of remote control*/
#define RC_MAX_VALUE      660.0f

#define RC_RATIO          0.002f
#define KB_RATIO          0.02f

/* 单发拨弹的编码器行程 Single-stroke encoder stroke*/
#define DEGREE_60_TO_ENCODER  -49146


/********** 4轮底盘信息 Four wheel chassis information**********/
/* 底盘轮距(mm) Chassis wheel distance*/
#define WHEELTRACK     353
/* 底盘轴距(mm) Chassis axis distance*/
#define WHEELBASE      370
/* 云台偏移(mm) Gimbal offset distance*/
#define GIMBAL_OFFSET  0


/* 底盘轮子周长(mm) Chassis wheel circumference*/
#define PERIMETER      478

/******** 底盘电机使用3508 Chassis motor use 3508*******/
/* 3508底盘电机减速比 3508 Chassis motor speed reduction ratio*/
#define CHASSIS_DECELE_RATIO (1.0f/19.0f)
/* 单个电机速度极限，单位是分钟每转 SIngle motor speed limit, unit is rpm*/
#define MAX_WHEEL_RPM        8500   //8347rpm = 3500mm/s


/******** 底盘最大速度设置 Chassis speed limit setup*******/
/* 底盘移动最大速度，单位是毫米每秒 CHassis movement speed limit, unit is mm/sec*/
#define MAX_CHASSIS_VX_SPEED 3300
#define MAX_CHASSIS_VY_SPEED 3300
/* 底盘旋转最大速度，单位是度每秒 Chassis rotation speed limit, unit is degree/sec*/
#define MAX_CHASSIS_VR_SPEED 300

/* yaw轴最大转角 yaw axis max turning angle*/
#define YAW_ANGLE_MAX        80
/* yaw轴最小转角 yaw axis min turning angle*/
#define YAW_ANGLE_MIN        -80
/* pitch轴最大仰角 pitch axis max elevation angle*/
#define PIT_ANGLE_MAX        20
/* pitch轴最大俯角 pitch axis max depression angle*/
#define PIT_ANGLE_MIN        -20



/* 串口数据相关 Serial data related*/
#define MAX_DMA_COUNT        200
#define DBUS_FRAME_SIZE      18

/* 常用的一些物理系数 Some physical parameter that used often*/
/* 角度转弧度系数 Angle to radian coefficient*/
#define RADIAN_COEF          57.3f

/* 极值限制函数宏定义 Extreme value limit function macro definition */
#define VAL_LIMIT(val, min, max)\
if((val) <= (min))\
{\
  (val) = (min);\
}\
else if((val) >= (max))\
{\
  (val) = (max);\
}\

#endif
