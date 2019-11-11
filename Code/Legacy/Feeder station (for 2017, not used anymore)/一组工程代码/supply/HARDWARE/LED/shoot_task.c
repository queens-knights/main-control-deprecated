#include "shoot_task.h"
 
int last_rc_s1;

void shoot_task(void)
{
	if(RC_CtrlData.rc.s2 != remote_down) //非停止模式
	{
		//关闭摩擦轮：
		if(RC_CtrlData.rc.s1 == remote_up && last_rc_s1 == remote_mid && shoot_status == drive_fric_motor)
		{
			shoot_status = stop_fric_motor;
			TIM12->CCR1 = 500;
      TIM12->CCR2 = 500;
		}
		
		//开启摩擦轮：
		else if(RC_CtrlData.rc.s1 == remote_up && last_rc_s1 == remote_mid && shoot_status == stop_fric_motor)
		{
			shoot_status = drive_fric_motor;
			TIM12->CCR1 = 1200;
      TIM12->CCR2 = 1200;
		}
			
		//开始射击，连续启动拨弹轮:
		else if(RC_CtrlData.rc.s1 == remote_down && last_rc_s1 == remote_mid && shoot_status == drive_fric_motor)
		{
			trigger_motor_speedtar = -trigger_motor_speedinit;
		}
		
		//关闭拨弹轮：
		else if(RC_CtrlData.rc.s1 == remote_mid && last_rc_s1 == remote_down && shoot_status == drive_fric_motor)
		{
			trigger_motor_speedtar = 0;
		}
		
		last_rc_s1 = RC_CtrlData.rc.s1 ;
	}
}





