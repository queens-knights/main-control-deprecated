#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "stm32f4xx_hal.h"
#include "can.h"
#include "cmsis_os.h"

/** 
  * @brief  CAN发送或是接收的ID
  */
typedef enum
{
	ZERO,
	MOTOR_A,
	MOTOR_B,
	MOTOR_C,
	MOTOR_D,
	MOTOR_CATCH=0x08,
	
	MOTOR_1_BACK=0x205,
	MOTOR_2_BACK=0x206,
	MOTOR_3_BACK=0x207,
	MOTOR_4_BACK=0x208,
	
	MOTOR_A_BACK=0x201,
	MOTOR_B_BACK=0x202,
	MOTOR_C_BACK=0x203,
	MOTOR_D_BACK=0x204,
	MOTOR_5_BACK=0x207,
	MOTOR_6_BACK=0x208,
	 
	CAN_MAIN_CONTROL_RECEIVE_ID   = 0x110,  //主控板接收ID
	CAN_EXTEND_RECEIVE_ID         = 0x101,  //Mos1板板接收ID
	CAN_EXTEND_SENT_ID            = 0x111,  //Mos1板板发送ID
	
	CAN_EXTEND2_RECEIVE_ID        = 0x102,  //Mos2板板接收ID
	CAN_EXTEND2_SENT_ID           = 0x112,  //Mos2板板发送ID
	
	CAN_DisMesure_RECEIVE_ID      = 0x150,  //测距板接收ID
	CAN_DisMesure_SENT_ID         = 0x160,  //测距板发送ID
	
	CAN_YunTai_RECEIVE_ID         = 0x120,  //云台板接收ID	主控->云台
	CAN_YunTai_SENT_ID            = 0x125,  //云台板发送ID  云台->主控
	
	CAN_YunTaiUart_RECEIVE_ID     = 0x121,  //云台板串口转发接收ID	主控->云台
	CAN_YunTaiUart_SENT_ID        = 0x126,  //云台板串口转发发送ID  云台->主控

}CAN_Message_ID;

void My_CAN1_FilterConfig(CAN_HandleTypeDef* _hcan);
void My_CAN2_FilterConfig(CAN_HandleTypeDef* _hcan);
HAL_StatusTypeDef CAN_Send_Message(CAN_HandleTypeDef* _hcan, CAN_Message_ID, uint8_t* _message);
BaseType_t Can_Sent_msgToQue(short can_num,short ID, unsigned char* date);//发送数据到Can发送队列

int Can_Inite(void);//Can初始化 成功返回1 失败返回0

extern xQueueHandle Can_TXData_QueHandle;//Can发送数据队列
extern int g_CanSent_n;//CAN消息发送个数
#endif
