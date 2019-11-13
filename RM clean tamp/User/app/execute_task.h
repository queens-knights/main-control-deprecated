#ifndef __EXECUTE_TASK_H__
#define __EXECUTE_TASK_H__

#include "stm32f4xx_hal.h"

void execute_task(const void* argu);

static void jump(int i);
static void delay(int i);
static void jump_back();
static void jump_next();


#endif

