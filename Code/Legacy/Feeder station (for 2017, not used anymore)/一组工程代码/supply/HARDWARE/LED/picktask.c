#include "picktask.h"

int pick_flag = 0 , receive_flag = 0 , push_confirm_flag = 0;
 

//void picktask()
//{
//	//此标志用于切换遥控或自动，上岛前为遥控模式
//	if(remote_or_autoflag == remote_mode)
//	{
//		chassisMove();//底盘控制
//	}
//	
//	if(pick_flag)  //取弹标志
//	{
//		if(move_flag1 == 0)
//		{
//			//伸出取弹机构：
//			pickmotor_locationset_extern  = extern_locationmax;
//			
//			//底盘抬升：
//			externmotor_locationset[0] = uping_locationmax;                                                      
//			externmotor_locationset[1] = uping_locationmax;
//			externmotor_locationset[2] = uping_locationmax;
//			externmotor_locationset[3] = uping_locationmax;
//			move_flag1 = 1;
//			movement_cnt++;
//		}
//		
//		//此时在手动对位
//		if(move_flag2 == 0 && movement_cnt == 2)
//		{
//			if(push_confirm_flag) //按下开始抓取
//			{
//				//底盘下降:
//				externmotor_locationset[0] = uping_locationreset;                                                      
//				externmotor_locationset[1] = uping_locationreset;
//				externmotor_locationset[2] = uping_locationreset;
//				externmotor_locationset[3] = uping_locationreset;
//				
//				//底盘下降到最低
//				if((externmoto_location[0] <= uping_locationreset + 2000) && (externmoto_location[1] <= uping_locationreset + 2000) && (externmoto_location[2] <= uping_locationreset + 2000) && (externmoto_location[3] <= uping_locationreset + 2000))
//				{
//					//底盘一旦停止，立即夹取弹药箱并上升
//					//触发电磁阀，启动夹取
//					
//					//这期间需要延时不到1s，夹取需要时间
//					
//					//然后上升，即拔出弹药箱
//					externmotor_locationset[0] = uping_locationmax;                                                      
//					externmotor_locationset[1] = uping_locationmax;
//					externmotor_locationset[2] = uping_locationmax;
//					externmotor_locationset[3] = uping_locationmax;
//					move_flag2 = 1;
//					movement_cnt++;//movement_cnt == 3;
//				}		
//			}
//		}
//		
//		//底盘升到最高
//		if((externmoto_location[0] >= uping_locationmax - 2000) && (externmoto_location[1] >= uping_locationmax - 2000) && (externmoto_location[2] >= uping_locationmax - 2000) && (externmoto_location[3] >= uping_locationmax - 2000))
//		{
//			move_flag3 = 1;
//		}
//		
//		//收回弹药箱并倒子弹
//		if(move_flag3 == 1 && movement_cnt == 3)
//		{
//			pickmotor_locationset_extern = extern_locationreset;
//			
//			//触发限位开关
//			
//			if(1)//内框架旋转，即倒子弹
//			{
//				pickmotor_locationset_rotate = rotate_locationmax;
//				
//				move_flag1 = 0;
//				move_flag2 = 0;
//				move_flag3 = 0;
//				pick_flag  = 0;
//				movement_cnt = 1;
//			}
//		}
//		
//	}
//	
//	
//	
//}





