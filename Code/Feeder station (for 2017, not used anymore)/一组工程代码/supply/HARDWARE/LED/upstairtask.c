#include "upstairtask.h"

int up_flag = 0 , down_flag = 0;
int Photoelectric_detect1 , Photoelectric_detect2 , Photoelectric_detect3 , Photoelectric_detect4 , Photoelectric_detect5 , Photoelectric_detect6;



void upstair_task()
{
	//此标志用于切换遥控或自动，上岛前为遥控模式
	if(remote_or_autoflag == remote_mode)
	{
		chassisMove();//底盘控制
	}
	
	//上岛:
	if(up_flag)
	{
		//第一个动作：四腿抬升，导轮打开：
		if(move_flag1 == 0)
		{
			externmotor_locationset[0] = uping_locationmax;                                                      
			externmotor_locationset[1] = uping_locationmax;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			//触发电磁阀，打开气缸
			move_flag1 = 1;
			movement_cnt++;  // movement_cnt == 2;
		}
		
		//前导轮已上台阶，检测到台面
		if(Photoelectric_detect1 == 1 && Photoelectric_detect2 == 1 && movement_cnt == 2)
		{
			move_flag2 = 1;                                              
		}
		
		//前导轮上第一级台阶后执行运动：底盘前轮抬升
		if(move_flag2)
		{
			//前轮升到底盘,后轮不动
			externmotor_locationset[0] = uping_locationreset;
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//此时底盘刹住
			remote_or_autoflag = auto_mode;  //此时切换到自动模式 
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag2 = 0;
			movement_cnt++;  // movement_cnt == 3;
		}
					
		//当电机升到底盘固定时，前轮已超过台阶
		if((externmoto_location[0] <= uping_locationreset + 2000) && (externmoto_location[1] <= uping_locationreset + 2000) && movement_cnt == 3)
		{
      move_flag3 = 1;
		}
		
		//车缓慢启动
		if(move_flag3)
		{
			//1000转的速度是估计值，转速较小
			chassis_Motor_tar[0] = -1000;
			chassis_Motor_tar[1] =  1000; 
			chassis_Motor_tar[2] =  1000;
			chassis_Motor_tar[3] = -1000;
			move_flag3 = 0;
			movement_cnt++;  // movement_cnt == 4;
		}
		
		//当后导轮靠上台阶时，后两个检测器检测到台阶
		if(Photoelectric_detect3 == 1 && Photoelectric_detect4 == 1 && movement_cnt == 4)
		{  
      move_flag4 = 1;			
		}
		
		//底盘刹住，后轮抬升
		if(move_flag4)
		{
			//前轮不动，后腿抬升
			externmotor_locationset[0] = uping_locationreset;
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationreset;
			externmotor_locationset[3] = uping_locationreset;
			
			//此时底盘刹住
			remote_or_autoflag = auto_mode;  //此时切换到自动模式 
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag4 = 0;
			movement_cnt++; // movement_cnt == 5;
		}
		
		//当后轮抬升到底盘，后轮已超过台阶，车往前开
		if((externmotor_locationset[2] <= uping_locationreset + 2000) && (externmotor_locationset[3] <= uping_locationreset + 2000) && movement_cnt == 5)
		{
      move_flag5 = 1;
		}
		
		//车往前开
		if(move_flag5)
		{
			chassis_Motor_tar[0] = -1000;
			chassis_Motor_tar[1] =  1000; 
			chassis_Motor_tar[2] =  1000;
			chassis_Motor_tar[3] = -1000;
			move_flag5 = 0;
			movement_cnt++; // movement_cnt == 6;
		}
		
		//车最后两个光电检测触发，车已完全上第一级台阶
		if(Photoelectric_detect5 == 1 && Photoelectric_detect6 == 1 && movement_cnt == 6)
		{
			move_flag6 = 1;
		}
		
		//车的底盘重新抬升，准备上第二级台阶
		if(move_flag6)
		{
			//底盘抬升
			externmotor_locationset[0] = uping_locationmax;                                                      
			externmotor_locationset[1] = uping_locationmax;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//车刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag6 = 0;
			movement_cnt++; //movement_cnt == 7
		}
		
		//底盘抬升到最高
		if(externmotor_locationset[0] >= uping_locationmax - 2000 && externmotor_locationset[1] >= uping_locationmax - 2000 && externmotor_locationset[2] >= uping_locationmax - 2000 && externmotor_locationset[3] >= uping_locationmax - 2000 && movement_cnt == 7)           
		{
			move_flag7 = 1;
		}
		
		//底盘抬升到最高，底盘电机驱动，车往前开
		if(move_flag7)
		{
			chassis_Motor_tar[0] = -1000;
			chassis_Motor_tar[1] =  1000; 
			chassis_Motor_tar[2] =  1000;
			chassis_Motor_tar[3] = -1000;
			move_flag7 = 0;
			movement_cnt++; // movement_cnt == 8;
		}
		
		//前导轮已上台阶，检测到台面
		if(Photoelectric_detect1 == 1 && Photoelectric_detect2 == 1 && movement_cnt == 8)
		{
			move_flag8 = 1;                                              
		}
		
		//前轮抬升
		if(move_flag8)
		{
			//前轮升到底盘，后轮不动
			externmotor_locationset[0] = uping_locationreset;
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//车刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag8 = 0;
			movement_cnt++; // movement_cnt == 9;
		}
		
		//当电机升到底盘固定时，前轮已超过台阶
		if((externmoto_location[0] <= uping_locationreset + 2000) && (externmoto_location[1] <= uping_locationreset + 2000) && movement_cnt == 9)
		{
      move_flag9 = 1;
		}
		
		//启动车
		if(move_flag9)
		{
			chassis_Motor_tar[0] = -1000;
			chassis_Motor_tar[1] =  1000; 
			chassis_Motor_tar[2] =  1000;
			chassis_Motor_tar[3] = -1000;
			move_flag9 = 0;
			movement_cnt++; // movement_cnt == 10;
		}
			
		//当后导轮靠上台阶时，后两个检测器检测到台阶
		if(Photoelectric_detect3 == 1 && Photoelectric_detect4 == 1 && movement_cnt == 10)
		{  
      move_flag10 = 1;			
		}
		
		//底盘刹住，后轮抬升
		if(move_flag10)
		{
			//前轮不动，后腿抬升
			externmotor_locationset[0] = uping_locationreset;
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationreset;
			externmotor_locationset[3] = uping_locationreset;
			
			//此时底盘刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag10 = 0;
			movement_cnt++; // movement_cnt == 11;
		}
 
		//当后轮抬升到底盘，后轮已超过台阶，车往前开
		if((externmotor_locationset[2] <= uping_locationreset + 2000) && (externmotor_locationset[3] <= uping_locationreset + 2000) && movement_cnt == 11)
		{
      move_flag11 = 1;
		}
		
		//车往前开
		if(move_flag11)
		{
			chassis_Motor_tar[0] = -1000;
			chassis_Motor_tar[1] =  1000; 
			chassis_Motor_tar[2] =  1000;
			chassis_Motor_tar[3] = -1000;
			move_flag11 = 0;
			movement_cnt++; // movement_cnt == 12;
		}
		
		//车最后两个光电检测触发，车已完全上第二级台阶
		if(Photoelectric_detect5 == 1 && Photoelectric_detect6 == 1 && movement_cnt == 12)
		{
			move_flag12 = 1;
		}
		
		//上岛之后，车刹住
		if(move_flag12)
		{
			//此时底盘刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag12 = 0;
			movement_cnt++; // movement_cnt == 13;
		}
		
		//上岛结束，切换到遥控模式
		if(movement_cnt == 13)
		{
			up_flag = 0;
			move_flag1 = 0;
			movement_cnt = 1;
			remote_or_autoflag = remote_mode;
		}
	}
	
	//下岛：
	if(down_flag)
	{
		
		//第一个动作：底盘下降到最低，准备下岛
		if(move_flag1 == 0)
		{
			externmotor_locationset[0] = uping_locationreset;                                                      
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationreset;
			externmotor_locationset[3] = uping_locationreset;
			//触发电磁阀，打开气缸
			move_flag1 = 1;
			movement_cnt++;  // movement_cnt == 2;
		}
		
		//后导轮检测到第一级台阶，开始伸腿
		if(Photoelectric_detect3 == 1 && Photoelectric_detect4 == 1 && movement_cnt == 2)
		{
			move_flag2 = 1;                                              
		}
		
		//后轮伸腿
		if(move_flag2)
		{
			//前轮升到底盘,后轮不动
			externmotor_locationset[0] = uping_locationreset;
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//此时底盘刹住
			remote_or_autoflag = auto_mode;  //此时切换到自动模式 
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag2 = 0;
			movement_cnt++;  // movement_cnt == 3;
		}
					
		//当后轮下降到第一级台阶
		if((externmoto_location[2] >= uping_locationmax - 2000) && (externmoto_location[3] >= uping_locationmax - 2000) && movement_cnt == 3)
		{
      move_flag3 = 1;
		}
		
		//车缓慢启动
		if(move_flag3)
		{
			//1000转的速度是估计值，转速较小
			chassis_Motor_tar[0] =  1000;
			chassis_Motor_tar[1] = -1000; 
			chassis_Motor_tar[2] = -1000;
			chassis_Motor_tar[3] =  1000;
			move_flag3 = 0;
			movement_cnt++;  // movement_cnt == 4;
		}
		
		//当后导轮靠上台阶时，后两个检测器检测到台阶
		if(Photoelectric_detect1 == 1 && Photoelectric_detect2 == 1 && movement_cnt == 4)
		{  
      move_flag4 = 1;			
		}
		
		//底盘刹住，前轮伸腿
		if(move_flag4)
		{
			//后轮不动，前轮伸腿
			externmotor_locationset[0] = uping_locationmax;
			externmotor_locationset[1] = uping_locationmax;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//此时底盘刹住
			remote_or_autoflag = auto_mode;  //此时切换到自动模式 
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag4 = 0;
			movement_cnt++; // movement_cnt == 5;
		}
		
		//当下降到第一级台阶时
		if((externmotor_locationset[0] >= uping_locationmax - 2000) && (externmotor_locationset[1] >= uping_locationmax - 2000) && movement_cnt == 5)
		{
      move_flag5 = 1;
		}
		
		//车往后开
		if(move_flag5)
		{
			chassis_Motor_tar[0] =  1000;
			chassis_Motor_tar[1] = -1000; 
			chassis_Motor_tar[2] = -1000;
			chassis_Motor_tar[3] =  1000;
			move_flag5 = 0;
			movement_cnt++; // movement_cnt == 6;
		}
		
		//车最后两个光电检测触发，车已运动到第一级台阶边缘
		if(Photoelectric_detect5 == 1 && Photoelectric_detect6 == 1 && movement_cnt == 6)
		{
			move_flag6 = 1;
		}
		
		//车的底盘重新下降，准备下岛
		if(move_flag6)
		{
			//底盘抬升
			externmotor_locationset[0] = uping_locationreset;                                                      
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationreset;
			externmotor_locationset[3] = uping_locationreset;
			
			//车刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag6 = 0;
			movement_cnt++; //movement_cnt == 7
		}
		
		//底盘抬升到最高
		if(externmotor_locationset[0] <= uping_locationreset + 2000 && externmotor_locationset[1] <= uping_locationreset + 2000 && externmotor_locationset[2] <= uping_locationreset + 2000 && externmotor_locationset[3] <= uping_locationreset + 2000 && movement_cnt == 7)           
		{
			move_flag7 = 1;
		}
		
		//底盘降到最低，车往后倒
		if(move_flag7)
		{
			chassis_Motor_tar[0] =  1000;
			chassis_Motor_tar[1] = -1000; 
			chassis_Motor_tar[2] = -1000;
			chassis_Motor_tar[3] =  1000;
			move_flag7 = 0;
			movement_cnt++; // movement_cnt == 8;
		}
		
		//前导轮已上台阶，检测到台面
		if(Photoelectric_detect3 == 1 && Photoelectric_detect4 == 1 && movement_cnt == 8)
		{
			move_flag8 = 1;                                              
		}
		
		//后轮下降
		if(move_flag8)
		{
			//前轮升到底盘，后轮不动
			externmotor_locationset[0] = uping_locationreset;
			externmotor_locationset[1] = uping_locationreset;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//车刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag8 = 0;
			movement_cnt++; // movement_cnt == 9;
		}
		
		//当后轮下到地面时
		if((externmoto_location[2] >= uping_locationmax + 2000) && (externmoto_location[3] >= uping_locationmax + 2000) && movement_cnt == 9)
		{
      move_flag9 = 1;
		}
		
		//启动车
		if(move_flag9)
		{
			chassis_Motor_tar[0] =  1000;
			chassis_Motor_tar[1] = -1000; 
			chassis_Motor_tar[2] = -1000;
			chassis_Motor_tar[3] =  1000;
			move_flag9 = 0;
			movement_cnt++; // movement_cnt == 10;
		}
			
		//当前导轮检测到地面时
		if(Photoelectric_detect1 == 1 && Photoelectric_detect2 == 1 && movement_cnt == 10)
		{  
      move_flag10 = 1;			
		}
		
		//底盘刹住，前轮下降
		if(move_flag10)
		{
			//前轮不动，后腿抬升
			externmotor_locationset[0] = uping_locationmax;
			externmotor_locationset[1] = uping_locationmax;
			externmotor_locationset[2] = uping_locationmax;
			externmotor_locationset[3] = uping_locationmax;
			
			//此时底盘刹住
			chassis_Motor_tar[0] = 0;
			chassis_Motor_tar[1] = 0; 
			chassis_Motor_tar[2] = 0;
			chassis_Motor_tar[3] = 0;
			move_flag10 = 0;
			movement_cnt++; // movement_cnt == 11;
		}
 
		//当前轮下到地面时，车已经完全下岛
		if((externmotor_locationset[0] >= uping_locationmax - 2000) && (externmotor_locationset[2] >= uping_locationmax - 2000) && movement_cnt == 11)
		{
      move_flag11 = 1;
		}
		
		//下岛之后切换为遥控模式
		if(move_flag11)
		{
			down_flag = 0;
			move_flag11 = 0;
			movement_cnt = 1;
			remote_or_autoflag = remote_mode;
		}

	}
	
}


































