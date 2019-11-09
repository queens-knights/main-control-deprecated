#include "remote_task.h"

RC_Ctl_t RC_CtrlData;   //remote control data
ChassisSpeed_Ref_t ChassisSpeedRef;
Gimbal_Ref_t GimbalRef;

FrictionWheelState_e friction_wheel_state = FRICTION_WHEEL_OFF;
static RemoteSwitch_t switch1;   //遥控器左侧拨杆
static volatile Shoot_State_e shootState = NOSHOOTING;
static InputMode_e inputmode = REMOTE_INPUT;   //输入模式设定



//输入模式设置 
void SetInputMode(Remote *rc)
{
	if(rc->s2 == 1)
	{
		inputmode = REMOTE_INPUT;
	}
	else if(rc->s2 == 3)
	{
		inputmode = KEY_MOUSE_INPUT;
	}
	else if(rc->s2 == 2)
	{
		inputmode = STOP;
	}	
}

InputMode_e GetInputMode()
{
	return inputmode;
}
 

void RemoteDataPrcess(uint8_t *pData)
{
	if(pData == NULL)
	{
			return;
	}
	
	RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
	RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
	RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |	((int16_t)pData[4] << 10)) & 0x07FF;
	RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
	
	RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);

	RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
	RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
	RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);    

	RC_CtrlData.mouse.press_l = pData[12];
	RC_CtrlData.mouse.press_r = pData[13];

	RC_CtrlData.key.v = ((int16_t)pData[14]) | ((int16_t)pData[15] << 8);

	SetInputMode(&RC_CtrlData.rc);
	Remote_Mode = GetInputMode();
	
	switch(GetInputMode())
	{
		case REMOTE_INPUT:
		{
			//遥控器控制模式
			RemoteControlProcess(&(RC_CtrlData.rc));
		}break;
		case KEY_MOUSE_INPUT:
		{
			//键盘控制模式
			MouseKeyControlProcess(&RC_CtrlData.mouse,&RC_CtrlData.key);
		}break;
		case STOP:
		{
			//紧急停车
			Stop_immediate();
 
		}break;
	}

////	
//	//数据帧出错，强制复位：
//	if(RC_CtrlData.rc.s1 != 1 && RC_CtrlData.rc.s1 != 2 && RC_CtrlData.rc.s1 != 3)
//	{
//		__set_FAULTMASK(1);
//		NVIC_SystemReset();
//	}
}


//遥控器控制模式处理
void RemoteControlProcess(Remote *rc)
{
	ChassisSpeedRef.forward_back_ref = (RC_CtrlData.rc.ch1 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET) * STICK_TO_CHASSIS_SPEED_REF_FACT;
	if(ChassisSpeedRef.forward_back_ref >= 200)
	{
		box_motor_locationset = box_motor_locationmax;
	}
	else if(ChassisSpeedRef.forward_back_ref <= -200)
	{
		box_motor_locationset = 0;
	}
		
	GimbalRef.pitch_speed_ref = rc->ch3 - (int16_t)REMOTE_CONTROLLER_STICK_OFFSET;    //speed_ref仅做输入量判断用
	if(GimbalRef.pitch_speed_ref >= 200)
	{
		open_or_close_motorlocationset = open_or_close_motorlocationmax;
	}
	else if(GimbalRef.pitch_speed_ref <= -200)
	{
		open_or_close_motorlocationset = 0;
	}
	
}

//键盘鼠标控制模式处理
u8 front_leg_moveflag = 1 , behind_leg_moveflag = 1 , pick_moveflag = 1 , push_and_openframe_flag = 1 , pick_function_flag = 1;
int mouse_press_lcnt = 1 , mouse_press_rcnt = 1 , pick_cnt = 1 , push_and_openframe_cnt = 1 , pick_function_cnt = 1;

void MouseKeyControlProcess(Mouse *mouse, Key *key)
{
//(key->v & 0x01
		
 
}


void Stop_immediate()
{
	ChassisSpeedRef.forward_back_out = 0;
	ChassisSpeedRef.left_right_out   = 0;
	GimbalRef.yaw_speed_out          = 0;
}







 