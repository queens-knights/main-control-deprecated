/********************************************************************************************************
*                                DJI System Global Macros Definations
*
*                                   (c) Copyright 2017; Dji, Inc.
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
********************************************************************************************************/
/**
  ********************************(C) COPYRIGHT 2017 DJI************************
  * @file       imu_task.h
	* @brief      basic attitude calculation
	* @update	        
	*	@history
	* Version     Date          Author           Modification
  * V1.0.0      Aug-30-2017   Richard.luo      basic attitude calculation
  *
  * @verbatim
	* yaw axis  : angle feedback is single axis gyro, palstance feedback is mpu6500 gyro
	* pitch axis: angle feedback is encoder, palstance feedback is mpu6500 gyro
	********************************(C) COPYRIGHT 2017 DJI************************
	*/
	
#ifndef __IMU_TASK_H__
#define __IMU_TASK_H__

#include "value_allinit.h"

void imu_task(void);
void init_quaternion(void);

#endif
