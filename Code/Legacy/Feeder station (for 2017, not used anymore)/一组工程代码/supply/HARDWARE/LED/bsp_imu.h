/**
  ********************************(C) COPYRIGHT 2017 DJI************************
  * @file       mpu.h
	* @brief      mpu6050/mpu6500/mpu9250 module driver.
  *             Configuration MPU6500 or MPU 9250 and Read the Accelerator
	*             and Gyrometer data using SPI interface
	* @update	  
	*	@history
	* Version     Date          Author           Modification
  * V1.0.0      Nov-19-2015   langgo.chen      
  * @verbatim
	*   
	********************************(C) COPYRIGHT 2017 DJI************************
	*/


#ifndef __MPU_H__
#define __MPU_H__

#include "stm32f4xx.h" 
#include "delay.h"
#include "value_allinit.h"

typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t mx;
    int16_t my;
    int16_t mz;

    int16_t temp;

    int16_t gx;
    int16_t gy;
    int16_t gz;
		
		int16_t ax_offset;
		int16_t ay_offset;
		int16_t az_offset;
	
		int16_t gx_offset;
		int16_t gy_offset;
		int16_t gz_offset;
		
} mpu_data_t;

typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t mx;
    int16_t my;
    int16_t mz;

    float temp;
    float temp_ref;
	
    float wx; //omiga, +- 2000dps => +-32768  so gx/16.384/57.3 =	rad/s
    float wy;
    float wz;

		float vx;
		float vy;
		float vz;
	
    float rol;
    float pit;
    float yaw;
} imu_data_t;

uint8_t mpu_device_init(void);
void    mpu_get_data(void);
void 		mpu_offset_cal(void);

extern mpu_data_t mpu_data;
extern imu_data_t imu;

#endif
