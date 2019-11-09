#ifndef __ARM_H__
#define __ARM_H__

#include "stm32f4xx_hal.h"

short arm_position_test(void);

short sensor_test(void);

int trans_power_calculate(void);

void trans_param_init(void);
	
void claw_param_init(void);
	
void arm_param_init(void);

void camera_servo_init(void);

void camera_servo_ctrl(void);
	
int claw_power_calculate(void);
	
int arm_power_calculate(void);

void sensor_init(void);

int arm_close_loop(void);
#endif
