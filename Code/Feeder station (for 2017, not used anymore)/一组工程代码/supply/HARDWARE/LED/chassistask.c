//#include "chassistask.h"



//int16_t Fabs(int16_t a)//取绝对值
//{
//	if(a >= 0)
//	{
//		a = a;
//	}
//	else
//  {
//		a = -a;
//	}
//	return a;
//}

//float rotate_kp = 3.3;
//void chassisMove(void) //底盘电机转速解算
//{
//	ChassisSpeedRef.rotate_out = rotate_kp * (gimbal_yaw_Motor[0] - gimbal_yawmotor_locationinit);

//	chassis_Motor_tar[0] = -ChassisSpeedRef.forward_back_out +  ChassisSpeedRef.left_right_out + ChassisSpeedRef.rotate_out;
//	chassis_Motor_tar[1] =  ChassisSpeedRef.forward_back_out +  ChassisSpeedRef.left_right_out + ChassisSpeedRef.rotate_out;
//	chassis_Motor_tar[2] =  ChassisSpeedRef.forward_back_out + -ChassisSpeedRef.left_right_out + ChassisSpeedRef.rotate_out;
//	chassis_Motor_tar[3] = -ChassisSpeedRef.forward_back_out + -ChassisSpeedRef.left_right_out + ChassisSpeedRef.rotate_out;  
//	
//		//底盘电机速度环：
//	Send_motorvalue_CAN1_4(PID_Calc(&PidDataSpeed_chassis_1 , chassis_Motor0x201[1] , chassis_Motor_tar[0]) ,
//												 PID_Calc(&PidDataSpeed_chassis_2 , chassis_Motor0x202[1] , chassis_Motor_tar[1]),
//												 PID_Calc(&PidDataSpeed_chassis_3 , chassis_Motor0x203[1] , chassis_Motor_tar[2]) ,
//												 PID_Calc(&PidDataSpeed_chassis_4 , chassis_Motor0x204[1] , chassis_Motor_tar[3]));
//}


















