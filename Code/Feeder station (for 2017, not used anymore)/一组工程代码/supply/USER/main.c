#include "stm32f4xx.h" 
#include "duty.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart1.h"
#include "can1.h"
#include "TIM2.h"
#include "TIM3.h"
#include "pid.h"
#include "value_allinit.h"
#include "chassistask.h"
#include "remote_task.h"
#include "spi.h"
#include "imu_task.h"
#include "bsp_imu.h"
#include "TIM12.h"
#include "usart6.h"
#include "pon_limit.h"
#include "digital_display.h"


int main(void)
{ 
	SystemInit();
	CAN1_Configuration();
	Tim2_Configuration();
	Tim3_Configuration();
	Tim4_Configuration();
	USART1_Configuration(100000);
	PID_InitALL();
	Usart6_Init(115200);
  pon_limit_Init();
	Display_IO_init();
	guangdian_sensor();
	
	while(1)
	{
    Loop();
	}
}






 