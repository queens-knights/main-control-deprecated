#include "detect_task.h"


//限位开关检测：
void pon_detect_circle()
{
	key[0]  = GPIO_ReadInputDataBit(GPIOI , GPIO_Pin_2);//漏弹器1   1是没有  0是被触碰
  key[1]  = GPIO_ReadInputDataBit(GPIOI , GPIO_Pin_7);//漏弹器2
	key[2]  = GPIO_ReadInputDataBit(GPIOI , GPIO_Pin_6);//KEY_STATE;
  key[3]  = GPIO_ReadInputDataBit(GPIOI , GPIO_Pin_5);//KEY_STATE;
	key[4]  = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_3);//KEY_STATE;
  key[5]  = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_2);//KEY_STATE;
}
void guangdian_detect_circle()
{
   light[0] = GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_12);
	 light[1] = GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_13);
}


extern int rm2006_fanzhuan_flag1;
int last_key0_status = 0;
int bullet_cnt_1 = 0;
void bullet_outer_1()
{
	if(bullet_outer1_limit50_flag == 0)
	{
		if(rm2006_fanzhuan_flag1 == 0)
		{
			speed_set_1 += 7 ;
		}
		if(speed_set_1 >= rm2006_1_tar)
		{
			speed_set_1 = rm2006_1_tar;
		}
	}
	
	if(key[0] == 0 && last_key0_status == 1)
	{
		bullet_cnt_1++;
	}
	//上限50颗子弹
	if(bullet_cnt_1 >= 100)
	{
		bullet_outer1_limit50_flag = 1;
		speed_set_1 = 0; //计满50颗拨弹器停转
	}
	
	last_key0_status = key[0];
}


extern int rm2006_fanzhuan_flag2;
int last_key1_status = 0;
int bullet_cnt_2 = 0;
void bullet_outer_2()
{
	if(bullet_outer2_limit50_flag == 0)
	{
		if(rm2006_fanzhuan_flag2 == 0)
		{
			speed_set_3 += 7 ;
		}
		if(speed_set_3 >= rm2006_3_tar)
		{
			speed_set_3 = rm2006_3_tar;
		}
	}
	
	if(key[1] == 0 && last_key1_status == 1)
	{
		bullet_cnt_2++;
	}
	//上限100颗子弹
	if(bullet_cnt_2 >= 100)
	{
		bullet_outer2_limit50_flag = 1;
		speed_set_3 = 0; //计满50颗拨弹器停转
	}
	
	last_key1_status = key[1];
}




