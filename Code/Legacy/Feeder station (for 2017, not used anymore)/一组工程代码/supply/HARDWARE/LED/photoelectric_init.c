#include "photoelectric_init.h"

//光电开关：
void photoelectric_init()   
{
	GPIO_InitTypeDef GPIO_Struct;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF , ENABLE);//GPIOE??
	 
	GPIO_Struct.GPIO_Pin = GPIO_Pin_4; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOA, &GPIO_Struct);//???GPIOE2,3,4

	GPIO_Struct.GPIO_Pin = GPIO_Pin_5; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOA, &GPIO_Struct);//???GPIOE2,3,4

	GPIO_Struct.GPIO_Pin = GPIO_Pin_9; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOI, &GPIO_Struct);//???GPIOE2,3,4

	GPIO_Struct.GPIO_Pin = GPIO_Pin_10; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOF, &GPIO_Struct);//???GPIOE2,3,4

}





