#include "motor_pid_task.h"

int fabs_1(int a)
{
	if(a >= 0)
	{
		a = a;
	}
	else 
	{
		a = -a;
	}
}
void motor_pid_task()
{
	speed_set_2 =          PID_Calc(&PidDataLocation_rm2006_2 , open_or_close_motorlocation , open_or_close_motorlocationset);
	speed_set_4 =          PID_Calc(&PidDataLocation_rm3508   , box_motor_location , box_motor_locationset);

	Send_motorvalue_CAN1_4(PID_Calc(&PidDataSpeed_rm2006_1 , rm2006_1[1] , -speed_set_1) ,
												 PID_Calc(&PidDataSpeed_rm2006_2 , rm2006_2[1] , speed_set_2),
												 PID_Calc(&PidDataSpeed_rm2006_3 , rm2006_3[1] , -speed_set_3) ,
												 PID_Calc(&PidDataSpeed_rm3508   , rm3508[1]   , -speed_set_4));

	kasi_defending();//防止卡弹
}

int rm2006_1rpm_err, rm2006_fanzhuan_flag1 = 0;
int rm2006_3rpm_err, rm2006_fanzhuan_flag2 = 0;

void kasi_defending()
{
	rm2006_1rpm_err = fabs_1(speed_set_1) - fabs_1(rm2006_1[1]);
	if(rm2006_1rpm_err >= rm2006_1_tar - 2000 && rm2006_fanzhuan_flag1 == 0)
	{
		rm2006_fanzhuan_flag1 = 1;
	}
	if(rm2006_fanzhuan_flag1 == 1)//反转
	{
		speed_set_1 = -rm2006_1_tar;
	}
	///////////////////////
	rm2006_3rpm_err = fabs_1(speed_set_3) - fabs_1(rm2006_3[1]);
	if(rm2006_3rpm_err >= rm2006_3_tar - 2000 && rm2006_fanzhuan_flag2 == 0)
	{
		rm2006_fanzhuan_flag2 = 1;
	}
	if(rm2006_fanzhuan_flag2 == 1)//反转
	{
		speed_set_3 = -rm2006_3_tar;
	}
}




