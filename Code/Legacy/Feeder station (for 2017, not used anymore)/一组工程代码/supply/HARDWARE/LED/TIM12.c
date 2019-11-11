#include "TIM12.h"

void TIM12_PWM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9; //GPIO_Pin_0 | GPIO_Pin_1 | 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOH, &GPIO_InitStructure); 

  GPIO_PinAFConfig(GPIOH, GPIO_PinSource6, GPIO_AF_TIM12);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource9, GPIO_AF_TIM12);
								
  TIM_TimeBaseStructure.TIM_Prescaler = 89;	
  TIM_TimeBaseStructure.TIM_Period = 2499;		
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
	
  TIM_OC1Init(TIM12, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM12 , TIM_OCPreload_Enable);
	
  TIM_OC2Init(TIM12, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM12 , TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM12, ENABLE);
  TIM_ARRPreloadConfig(TIM12, ENABLE);
  TIM_Cmd(TIM12, ENABLE);	
	
	TIM12->CCR1 = 500;
  TIM12->CCR2 = 500;
}






 
