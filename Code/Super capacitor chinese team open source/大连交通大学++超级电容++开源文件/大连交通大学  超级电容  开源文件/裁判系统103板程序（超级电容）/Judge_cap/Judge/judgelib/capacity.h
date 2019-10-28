#ifndef _CAPACITY_H_
#define _CAPACITY_H_

#include "stm32f1xx_hal.h"
#include "gpio.h"

#define CAPACITY_INPUT_START  HAL_GPIO_WritePin(Charge_GPIO_Port, Charge_Pin, GPIO_PIN_SET);
#define CAPACITY_INPUT_STOP   HAL_GPIO_WritePin(Charge_GPIO_Port, Charge_Pin, GPIO_PIN_RESET);
#define CAPACITY_OUTPUT_START HAL_GPIO_WritePin(CurOut_GPIO_Port, CurOut_Pin, GPIO_PIN_SET);
#define CAPACITY_OUTPUT_STOP  HAL_GPIO_WritePin(CurOut_GPIO_Port, CurOut_Pin, GPIO_PIN_RESET);

void Capacity_Ctrl(void);

extern uint8_t usecap;
extern int16_t chassis_speed[4];
extern float imu_gx,imu_gy,imu_gz;
extern int16_t imu_gy_trans,imu_gz_trans;
extern float angletrans;

#endif
