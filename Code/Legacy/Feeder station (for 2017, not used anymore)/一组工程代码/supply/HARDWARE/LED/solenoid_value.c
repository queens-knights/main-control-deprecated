#include "solenoid_value.h"


//电磁阀IO口:
void power_gpio_Configuration(void)
{
  GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOH,&gpio);
 
	GPIO_ResetBits(GPIOH, GPIO_Pin_2); //夹取
	GPIO_ResetBits(GPIOH, GPIO_Pin_3); //弹仓
	GPIO_ResetBits(GPIOH, GPIO_Pin_4); //前爪子
	GPIO_ResetBits(GPIOH, GPIO_Pin_5); //前推出架
}


