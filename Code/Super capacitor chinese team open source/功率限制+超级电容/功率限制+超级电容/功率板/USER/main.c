#include "adc.h"
#include "dma.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "can.h"
#include "timer.h"  
s16 temp1;
 int main(void)
 {		
	 		int i = 0;
	int j = 0;
		delay_init();	    	 //延时函数初始化	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//		uart_init(256000);	 //串口初始化为115200
		Adc_Int(); 
		MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)&value,M*N);//初始化DMA 
	 	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_2tq,CAN_BS1_9tq,3,CAN_Mode_LoopBack);	
//	 CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_5tq,4,CAN_Mode_LoopBack);
//	 TIM2_Int_Init(72-1,20-1);
//	 utilFilterInit(adc_f, 0.001f, 0.020f, 0.0f);
//	  TIM4_Int_Init(72-1, 200-1);
	 delay_ms(1000);
	 filter_correct();
	 
   	while(1)
	{
		filter();
		for(j = 0;j < 4;j++)
		{
			canSendBuff[2 * j + 1] = (u8)((int16_t)aftervalue[j] >> 8);
			canSendBuff[2 * j] = (u8)((int16_t)aftervalue[j] & 0x00ff);
		}
		temp1=Can_Send_Msg(canSendBuff,8);
		delay_ms(2);
    }
}
 
