#include "can2.h"

/*----CAN2_TX-----PB13----*/
/*----CAN2_RX-----PB12----*/



void CAN2_Configuration(void)
{
    CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_AF;
	  gpio.GPIO_OType = GPIO_OType_PP;//????     
	  gpio.GPIO_Speed = GPIO_Speed_100MHz;//100MHz     
	  gpio.GPIO_PuPd = GPIO_PuPd_UP;//??     
	  GPIO_Init(GPIOB, &gpio);//???PA11,PA12
 
    GPIO_PinAFConfig(GPIOB , GPIO_PinSource12, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB , GPIO_PinSource13, GPIO_AF_CAN2);

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
    CAN_Init(CAN2, &can);

		can_filter.CAN_FilterNumber=14;
		can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
		can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
		can_filter.CAN_FilterIdHigh=0x0000;
		can_filter.CAN_FilterIdLow=0x0000;
		can_filter.CAN_FilterMaskIdHigh=0x0000;                  //可以通过0X210,0X211,0X212,0X213数据来自陀螺仪
		can_filter.CAN_FilterMaskIdLow=0x0000;	
		can_filter.CAN_FilterFIFOAssignment=0;			
		can_filter.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&can_filter);
		
    nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE); 
}


void Send_motorvalue_CAN2(s16 data1 , s16 data2 , s16 data3 , s16 data4)
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
    
    CAN_Transmit(CAN2,&tx_message);
}


void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if (CAN_GetITStatus(CAN2 , CAN_IT_FMP0)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN2, CAN_IT_FF0);
		CAN_ClearFlag(CAN2, CAN_FLAG_FF0); 
		CAN_Receive(CAN2, CAN_FIFO0, &rx_message);		
		 //电机编码器数据处理
    	
		//上电前1000个中断里不进行位置环计算
		if(pidcalc_startflag_can2 < 1000)
		{
		  pidcalc_startflag_can2++;
		}
		else  if(pidcalc_startflag_can2 >= 1000)
		{
			pidcalc_startflag_can2 = 1000;
		}
		
		//解码电机信息：
		switch(rx_message.StdId)
		{
		  case 0x201:
				if(pidcalc_startflag_can2 < 1000)
				{
					DecodeS16Data(&chassis_Motor0x201[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x201[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x201[2] , &rx_message.Data[4]); 
					chassis_Motor0x201[3] = rx_message.Data[6];
					chassismoto_offset_201 = chassis_Motor0x201[0];
				}
				else
        {
					chassislast_Motor_0x201 = chassis_Motor0x201[0];
					DecodeS16Data(&chassis_Motor0x201[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x201[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x201[2] , &rx_message.Data[4]); 
					chassis_Motor0x201[3] = rx_message.Data[6];
					
					if (chassis_Motor0x201[0] - chassislast_Motor_0x201 > 6000)
					{
            chassisMotor_0x201_cnt--;
					}
					else if (chassis_Motor0x201[0] - chassislast_Motor_0x201 < -6000)
					{
						chassisMotor_0x201_cnt++;
					}
					chassismoto_location[0] = chassisMotor_0x201_cnt * 8192 + chassis_Motor0x201[0] - chassismoto_offset_201;
				}
			break;
			
			case 0x202:
				if(pidcalc_startflag_can2 < 1000)
				{
					DecodeS16Data(&chassis_Motor0x202[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x202[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x202[2] , &rx_message.Data[4]); 
					chassis_Motor0x202[3] = rx_message.Data[6];
					chassismoto_offset_202 = chassis_Motor0x202[0];
				}
				else
        {
					chassislast_Motor_0x202 = chassis_Motor0x202[0];
					DecodeS16Data(&chassis_Motor0x202[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x202[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x202[2] , &rx_message.Data[4]); 
					chassis_Motor0x202[3] = rx_message.Data[6];
					
					if (chassis_Motor0x202[0] - chassislast_Motor_0x202 > 6000)
					{
            chassisMotor_0x202_cnt--;
					}
					else if (chassis_Motor0x202[0] - chassislast_Motor_0x202 < -6000)
					{
						chassisMotor_0x202_cnt++;
					}
					chassismoto_location[1] = chassisMotor_0x202_cnt * 8192 + chassis_Motor0x202[0] - chassismoto_offset_202;
				}
			break;
			
			case 0x203:
				if(pidcalc_startflag_can2 < 1000)
				{
					DecodeS16Data(&chassis_Motor0x203[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x203[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x203[2] , &rx_message.Data[4]); 
					chassis_Motor0x203[3] = rx_message.Data[6];
					chassismoto_offset_203 = chassis_Motor0x203[0];
				}
				else
        {
					chassislast_Motor_0x203 = chassis_Motor0x203[0];
					DecodeS16Data(&chassis_Motor0x203[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x203[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x203[2] , &rx_message.Data[4]); 
					chassis_Motor0x203[3] = rx_message.Data[6];
					
					if (chassis_Motor0x203[0] - chassislast_Motor_0x203 > 6000)
					{
            chassisMotor_0x203_cnt--;
					}
					else if (chassis_Motor0x203[0] - chassislast_Motor_0x203 < -6000)
					{
						chassisMotor_0x203_cnt++;
					}
					chassismoto_location[2] = chassisMotor_0x203_cnt * 8192 + chassis_Motor0x203[0] - chassismoto_offset_203;
				}
			break;
						
			case 0x204:
				if(pidcalc_startflag_can2 < 1000)
				{
					DecodeS16Data(&chassis_Motor0x204[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x204[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x204[2] , &rx_message.Data[4]); 
					chassis_Motor0x204[3] = rx_message.Data[6];
					chassismoto_offset_204 = chassis_Motor0x204[0];
				}
				else
        {
					chassislast_Motor_0x204 = chassis_Motor0x204[0];
					DecodeS16Data(&chassis_Motor0x204[0] , &rx_message.Data[0]);
					DecodeS16Data(&chassis_Motor0x204[1] , &rx_message.Data[2]);     
					DecodeS16Data(&chassis_Motor0x204[2] , &rx_message.Data[4]); 
					chassis_Motor0x204[3] = rx_message.Data[6];
					
					if (chassis_Motor0x204[0] - chassislast_Motor_0x204 > 6000)
					{
            chassisMotor_0x204_cnt--;
					}
					else if (chassis_Motor0x204[0] - chassislast_Motor_0x204 < -6000)
					{
						chassisMotor_0x204_cnt++;
					}
					chassismoto_location[3] = chassisMotor_0x204_cnt * 8192 + chassis_Motor0x204[0] - chassismoto_offset_204;
				}
			break;
		}
	}
}












