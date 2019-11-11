#include "pon_limit.h"

//限位开关：
void pon_limit_Init()     
{
	GPIO_InitTypeDef GPIO_Struct;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOI , ENABLE);//GPIOE??
	 
	GPIO_Struct.GPIO_Pin = GPIO_Pin_2; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOI, &GPIO_Struct);//???GPIOE2,3,4
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_7; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOI, &GPIO_Struct);//???GPIOE2,3,4
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_6; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOI, &GPIO_Struct);//???GPIOE2,3,4
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_5; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOI, &GPIO_Struct);//???GPIOE2,3,4
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_10; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOA, &GPIO_Struct);//???GPIOE2,3,4
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_2; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOA, &GPIO_Struct);//???GPIOE2,3,4


}

void guangdian_sensor()     
{
	GPIO_InitTypeDef GPIO_Struct;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOI , ENABLE);//GPIOE??
	 
	GPIO_Struct.GPIO_Pin = GPIO_Pin_12; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOD, &GPIO_Struct);//???GPIOE2,3,4
	
	GPIO_Struct.GPIO_Pin = GPIO_Pin_13; 
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;//??????
  GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOD, &GPIO_Struct);//???GPIOE2,3,4
}



