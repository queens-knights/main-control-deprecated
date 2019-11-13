#ifndef __ARM_TASK_H__
#define __ARM_TASK_H__

#include "stm32f4xx_hal.h"

void arm_param_init(void);


void claw_param_init(void);


void trans_param_init(void);


int arm_power_calculate(void);


int claw_power_calculate(void);


int trans_power_calculate(void);


short arm_postition_test(void);


void claw_param_init(void);


void arm_task(const void* argu);


void camera_servo_init(void);


void camera_servo_ctrl(void);


#endif
