#include "digital_display.h"

//sck pd12   A5
//si pd13    C5
//rck  pd14  F10

  
//  0    1    2    3     4    5   6    7    8    9 
u8 ma[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};//?????

void Display_IO_init()
{
	GPIO_InitTypeDef GPIO_Struct;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF , ENABLE);//GPIOE??
	 
	//sck
  GPIO_Struct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	//si
  GPIO_Struct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_Struct);
	
	//rck
  GPIO_Struct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOF,&GPIO_Struct);
	
	////////////////////////
	//sck
  GPIO_Struct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_Struct);
	
	//si
  GPIO_Struct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_Struct);
	
	//rck
  GPIO_Struct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_Struct);
 
}
	
void Tan_left(u8 dat)//??????
{
	u8 i;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);     //SCK
		if(dat&0x80) 
			GPIO_SetBits(GPIOC,GPIO_Pin_5);     //SI
		else 
			GPIO_ResetBits(GPIOC,GPIO_Pin_5);
			dat<<=1;
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}	

}

void display_left(u8 a,u8 b,u8 c)//
{
	Tan_left(ma[a]);
	Tan_left(ma[b]);
	Tan_left(ma[c]);
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_10);       //RCK
 
	GPIO_SetBits(GPIOF,GPIO_Pin_10);
}


////////////////////////////
void Tan_right(u8 dat)//??????
{
	u8 i;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);     //SCK
		if(dat&0x80) 
			GPIO_SetBits(GPIOC,GPIO_Pin_4);     //SI
		else 
			GPIO_ResetBits(GPIOC,GPIO_Pin_4);
			dat<<=1;
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			GPIO_SetBits(GPIOC,GPIO_Pin_3);
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	}	

}

void display_right(u8 a,u8 b,u8 c)//
{
	Tan_right(ma[a]);
	Tan_right(ma[b]);
	Tan_right(ma[c]);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);       //RCK
 
	GPIO_SetBits(GPIOC,GPIO_Pin_2);
}

