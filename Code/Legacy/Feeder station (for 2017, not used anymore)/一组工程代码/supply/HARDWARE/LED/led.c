#include "led.h"

void Laser_Config(void)
{
 
	GPIO_InitTypeDef GPIO_Struct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOG,&GPIO_Struct);
	 
//	GPIO_SetBits(GPIOG , GPIO_Pin_13);//开激光
	GPIO_ResetBits(GPIOG , GPIO_Pin_13);//关激光
}

