#include "TIM2.h"


void Tim2_Configuration(void)
{
		TIM_TimeBaseInitTypeDef  tim;
	  NVIC_InitTypeDef         nvic;
		
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    nvic.NVIC_IRQChannel = TIM2_IRQn;
	  nvic.NVIC_IRQChannelPreemptionPriority = 2;
   	nvic.NVIC_IRQChannelSubPriority = 2;
  	nvic.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&nvic);	
	
		tim.TIM_Prescaler = 168 - 1;                             
	  tim.TIM_Period = 1000;	 				
	  tim.TIM_ClockDivision = 0;
	  tim.TIM_CounterMode = TIM_CounterMode_Up;
	  TIM_TimeBaseInit(TIM2 , &tim);
	
	  TIM_ARRPreloadConfig(TIM2, ENABLE);
  	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	  TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	
		
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //GPIO_Pin_0 | GPIO_Pin_1 | 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
								
  TIM_TimeBaseStructure.TIM_Prescaler = 84;	
  TIM_TimeBaseStructure.TIM_Period = 20000;		
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2 , TIM_OCPreload_Enable);
	
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2 , TIM_OCPreload_Enable);
	
//  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
//  TIM_OC3PreloadConfig(TIM2 , TIM_OCPreload_Enable);
//	
//  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
//  TIM_OC4PreloadConfig(TIM2 , TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);	
	
	TIM2->CCR1 = 2150; // 2150是关，2500是开
  TIM2->CCR2 = 2000; // 2000是关，2400是开
 
}

//TIM2作功能定时：
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
	{
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		
//		//检测遥控器通信:如果收不到信号，立即复位
//		remote_detect_flag++;
//		if(remote_detect_flag >= 10)
//		{
//			remote_detect_flag = 1;
//		  last_usart_cnt = usart_cnt ;
//		}
//		cnt_bais = usart_cnt - last_usart_cnt;
//		if(cnt_bais == 0)
//		{
//			danger_cnt++;
//			if(danger_cnt >= 20)
//			{
//				//????,????
//			  __set_FAULTMASK(1);
//				NVIC_SystemReset();
//			}
//		}
//		else
//		{
//			danger_cnt = 0;
//		}
	}
	
	//
}

void Tim4_Configuration(void)
{
		
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //GPIO_Pin_0 | GPIO_Pin_1 | 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);

  TIM_TimeBaseStructure.TIM_Prescaler = 84;	
  TIM_TimeBaseStructure.TIM_Period = 20000;		
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
	
//	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
//  TIM_OC1PreloadConfig(TIM2 , TIM_OCPreload_Enable);
//	
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4 , TIM_OCPreload_Enable);
	
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4 , TIM_OCPreload_Enable);
	
//  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
//  TIM_OC4PreloadConfig(TIM2 , TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);	
	
//	TIM2->CCR1 = 2150; // 2150是关，2500是开
  TIM4->CCR3 = 1000; // 2200取到子弹   1000 没取到
  
}



