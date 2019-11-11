#ifndef __CAN1_H__
#define __CAN1_H__
#include "stm32f4xx.h"
#include "value_allinit.h"
#include "MyDataProcess.h"


#define	RM2006_1        0x201 
#define	RM2006_2        0x202
#define	RM2006_3        0x203
#define	RM3508          0x204
 
	
	
	
void power_gpio_Configuration(void);
void CAN1_Configuration(void);
void Send_motorvalue_CAN1_4(s16 data1 , s16 data2 , s16 data3 , s16 data4);
void Send_motorvalue_CAN1_2(s16 data1 , s16 data2 , s16 data3 , s16 data4);


extern s16 Motor_0x201[4];
extern s16 Motor_0x202[4];
extern s16 Motor_0x203[4];
extern s16 Motor_0x204[4];

#endif 


