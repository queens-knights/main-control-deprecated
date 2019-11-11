#include "can1.h"

/*----CAN1_TX-----PA12----*/
/*----CAN1_RX-----PA11----*/

void CAN1_Configuration(void)
{
    CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    gpio.GPIO_Mode = GPIO_Mode_AF;
	  gpio.GPIO_OType = GPIO_OType_PP;//????     
	  gpio.GPIO_Speed = GPIO_Speed_100MHz;//100MHz     
	  gpio.GPIO_PuPd = GPIO_PuPd_UP;//??     
	  GPIO_Init(GPIOD, &gpio);//???PA11,PA12
 
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;
    can.CAN_AWUM = DISABLE;
    can.CAN_NART = ENABLE;
    can.CAN_RFLM = DISABLE;
    can.CAN_TXFP = ENABLE;
    can.CAN_Mode = CAN_Mode_Normal;
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_4tq;
    can.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN1, &can);

		can_filter.CAN_FilterNumber=0;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=0x0000;
		can_filter.CAN_FilterIdLow=0x0000;
		can_filter.CAN_FilterMaskIdHigh=0x0000;                  //可以通过0X210,0X211,0X212,0X213数据来自陀螺仪
		can_filter.CAN_FilterMaskIdLow=0x0000;	
		can_filter.CAN_FilterFIFOAssignment=0;			
		can_filter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&can_filter);
		
    nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
}



void Send_motorvalue_CAN1_4(s16 data1 , s16 data2 , s16 data3 , s16 data4)
{
    CanTxMsg tx_message;
    
    tx_message.StdId = 0x200;//send to gyro controll board
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = data1 >> 8;
    tx_message.Data[1] = data1;
    tx_message.Data[2] = data2 >> 8;
    tx_message.Data[3] = data2;
    tx_message.Data[4] = data3 >> 8;
    tx_message.Data[5] = data3;
    tx_message.Data[6] = data4 >> 8;
    tx_message.Data[7] = data4;
    
    CAN_Transmit(CAN1,&tx_message);
}


void Send_motorvalue_CAN1_2(s16 data1 , s16 data2 , s16 data3 , s16 data4)
{
    CanTxMsg tx_message;
    
    tx_message.StdId = 0x1ff;//send to gyro controll board
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = data1 >> 8;
    tx_message.Data[1] = data1;
    tx_message.Data[2] = data2 >> 8;
    tx_message.Data[3] = data2;
    tx_message.Data[4] = data3 >> 8;
    tx_message.Data[5] = data3;
    tx_message.Data[6] = data4 >> 8;
    tx_message.Data[7] = data4;
    
    CAN_Transmit(CAN1,&tx_message);
}

/*************************************************************************
                          CAN1_RX0_IRQHandler
描述：CAN1的接收中断函数
*************************************************************************/
 
 

void CAN1_RX0_IRQHandler(void)
{   
	CanRxMsg rx_message;	
  if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		
		//上电前1000个中断里不进行位置环计算
		if(pidcalc_startflag_can1 < 1000)
		{
		  pidcalc_startflag_can1++;
		}
		else if(pidcalc_startflag_can1 >= 1000)
		{
			pidcalc_startflag_can1 = 1000;
		}
		
		//解码电机信息：
		switch(rx_message.StdId)
		{
			case RM2006_1:
				if(pidcalc_startflag_can1 < 1000)
				{
				}
				else
        {
					DecodeS16Data(&rm2006_1[0] , &rx_message.Data[0]);
					DecodeS16Data(&rm2006_1[1] , &rx_message.Data[2]);     
					DecodeS16Data(&rm2006_1[2] , &rx_message.Data[4]); 
					rm2006_1[3] = rx_message.Data[6];
				} 
			break;
				
			case RM2006_2:
				if(pidcalc_startflag_can1 < 1000)
				{
					DecodeS16Data(&rm2006_2[0] , &rx_message.Data[0]);
					DecodeS16Data(&rm2006_2[1] , &rx_message.Data[2]);     
					DecodeS16Data(&rm2006_2[2] , &rx_message.Data[4]); 
					rm2006_2[3] = rx_message.Data[6];
					rm2006_2_offset = rm2006_2[0];
				}
				else
        {
					rm2006_2_last = rm2006_2[0];
					DecodeS16Data(&rm2006_2[0] , &rx_message.Data[0]);
					DecodeS16Data(&rm2006_2[1] , &rx_message.Data[2]);     
					DecodeS16Data(&rm2006_2[2] , &rx_message.Data[4]); 
					rm2006_2[3] = rx_message.Data[6];
					
					if (rm2006_2[0] - rm2006_2_last > 6000)
					{
            rm2006_2_cnt--;
					}
					else if (rm2006_2[0] - rm2006_2_last < -6000)
					{
						rm2006_2_cnt++;
					}
				  open_or_close_motorlocation = rm2006_2_cnt * 8192 + rm2006_2[0] - rm2006_2_offset;
				}
			break;
				
			case RM2006_3:
				if(pidcalc_startflag_can1 < 1000)
				{

				}
				else
        {
					DecodeS16Data(&rm2006_3[0] , &rx_message.Data[0]);
					DecodeS16Data(&rm2006_3[1] , &rx_message.Data[2]);     
					DecodeS16Data(&rm2006_3[2] , &rx_message.Data[4]); 
					rm2006_3[3] = rx_message.Data[6];
				}
			break;
				
			case RM3508:  //往上为负
				//底盘复位前只使用速度环
				if(pidcalc_startflag_can1 < 1000)
				{
					DecodeS16Data(&rm3508[0] , &rx_message.Data[0]);
					DecodeS16Data(&rm3508[1] , &rx_message.Data[2]);     
					DecodeS16Data(&rm3508[2] , &rx_message.Data[4]); 
					rm3508[3] = rx_message.Data[6];
					rm3508_offset = rm3508[0];
				}
				else//复位时立即开启位置环
        {
					rm3508_last = rm3508[0];
					DecodeS16Data(&rm3508[0] , &rx_message.Data[0]);
					DecodeS16Data(&rm3508[1] , &rx_message.Data[2]);     
					DecodeS16Data(&rm3508[2] , &rx_message.Data[4]); 
					rm3508[3] = rx_message.Data[6];
					
					if (rm3508[0] - rm3508_last > 6000)
					{
            rm3508_cnt--;
					}
					else if (rm3508[0] - rm3508_last < -6000)
					{
						rm3508_cnt++;
					}
					 box_motor_location = -(rm3508_cnt * 8192 + rm3508[0] - rm3508_offset);
				}
			break;

		}
  }
}



