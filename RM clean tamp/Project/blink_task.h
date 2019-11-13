#ifndef __BLINK_TASK_H__
#define __BLINK_TASK_H__


#include "stm32f4xx_hal.h"                           

void blink_task(const void* argu);
void UART3_callback(void);
#endif