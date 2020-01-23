#ifndef __PNEU_TASK_H__
#define __PNEU_TASK_H__


#include "stm32f4xx_hal.h"                           

void pneu_task(const void* argu);
void RC_handler(const void* argu);
void USART4_pneu_callback(void);
#endif
