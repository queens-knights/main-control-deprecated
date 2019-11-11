#ifndef _REOMTE_TASK_H_
#define _REOMTE_TASK_H_
#include "stm32f4xx.h"
#include "stdio.h"
#include "value_allinit.h"
/*
****************************************************************************
*
*																	MARCO
****************************************************************************
*/
//remote control parameters
#define REMOTE_CONTROLLER_STICK_OFFSET      1024u   

#define STICK_TO_CHASSIS_SPEED_REF_FACT     0.45f
#define STICK_TO_PITCH_ANGLE_INC_FACT       0.004f
#define STICK_TO_YAW_ANGLE_INC_FACT         0.004f
#define FRICTION_WHEEL_MAX_DUTY             1600

//mouse control parameters
#define MOUSE_TO_PITCH_ANGLE_INC_FACT 		0.025f
#define MOUSE_TO_YAW_ANGLE_INC_FACT 		0.025f

#define NORMAL_FORWARD_BACK_SPEED 			500
#define NORMAL_LEFT_RIGHT_SPEED   			700
#define HIGH_FORWARD_BACK_SPEED 			660
#define HIGH_LEFT_RIGHT_SPEED   			800

#define FRICTION_RAMP_TICK_COUNT			100
#define MOUSE_LR_RAMP_TICK_COUNT			50
#define MOUSR_FB_RAMP_TICK_COUNT			60

#define REMOTE_SWITCH_VALUE_UP         		0x01u  
#define REMOTE_SWITCH_VALUE_DOWN			0x02u
#define REMOTE_SWITCH_VALUE_CENTRAL			0x03u

#define REMOTE_SWITCH_CHANGE_1TO3      (uint8_t)((REMOTE_SWITCH_VALUE_UP << 2) | REMOTE_SWITCH_VALUE_CENTRAL)   
#define REMOTE_SWITCH_CHANGE_2TO3      (uint8_t)((REMOTE_SWITCH_VALUE_DOWN << 2) | REMOTE_SWITCH_VALUE_CENTRAL)  
#define REMOTE_SWITCH_CHANGE_3TO1      (uint8_t)((REMOTE_SWITCH_VALUE_CENTRAL << 2) | REMOTE_SWITCH_VALUE_UP)
#define REMOTE_SWITCH_CHANGE_3TO2      (uint8_t)((REMOTE_SWITCH_VALUE_CENTRAL << 2) | REMOTE_SWITCH_VALUE_DOWN)

#define REMOTE_SWITCH_CHANGE_1TO3TO2   (uint8_t)((REMOTE_SWITCH_VALUE_UP << 4) |\
                                                 (REMOTE_SWITCH_VALUE_CENTRAL << 2) |\
                                                 (REMOTE_SWITCH_VALUE_DOWN))   

#define REMOTE_SWITCH_CHANGE_2TO3TO1   (uint8_t)((REMOTE_SWITCH_VALUE_DOWN << 4) |\
                                                 (REMOTE_SWITCH_VALUE_CENTRAL << 2) |\
                                                 (REMOTE_SWITCH_VALUE_UP)) 

#define REMOTE_SWITCH_VALUE_BUF_DEEP   16u

////RC_CtrlData
//typedef struct{
//	uint8_t rc_bytes[RC_FRAME_LENGTH];
//}RC_Raw_t;

typedef __packed struct
{
	int16_t ch0;
	int16_t ch1;
	int16_t ch2;
	int16_t ch3;
	int8_t s1;
	int8_t s2;
}Remote;
typedef __packed struct
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t last_press_l;
	uint8_t last_press_r;
	uint8_t press_l;
	uint8_t press_r;
}Mouse;	
typedef	__packed struct
{
	uint16_t v;
}Key;

typedef __packed struct
{
	Remote rc;
	Mouse mouse;
	Key key;
}RC_Ctl_t;

typedef enum
{
	NOSHOOTING = 0,
	SHOOTING = 1,
}Shoot_State_e;



//ÊäÈëÄ£Ê½:Ò£¿ØÆ÷/¼üÅÌÊó±ê/Í£Ö¹ÔËÐÐ
typedef enum
{
	REMOTE_INPUT = 1,
	KEY_MOUSE_INPUT = 3,
	STOP = 2,
}InputMode_e;

//Ä¦²ÁÂÖ×´Ì¬Ã¶¾Ù
typedef enum
{
	FRICTION_WHEEL_OFF = 0,
	FRICTION_WHEEL_START_TURNNING = 1,
	FRICTION_WHEEL_ON = 2,
}FrictionWheelState_e;

//²¦¸Ë¶¯×÷Ã¶¾Ù
typedef enum
{
	FROM1TO2,
	FROM1TO3,
	FROM2TO1, 
	FROM3TO1,
	FROM3TO2,
}RC_SWITCH_ACTION_e;

//remote data process
typedef __packed struct
{
    int16_t forward_back_ref;
    int16_t left_right_ref;
	  int16_t forward_back_out;
    int16_t left_right_out;
    int16_t rotate_out;
 
}ChassisSpeed_Ref_t;

//remote data process
typedef struct
{
    int16_t pitch_speed_ref;
    int16_t yaw_speed_ref;
	  int16_t pitch_speed_out;
    int16_t yaw_speed_out;
}Gimbal_Ref_t;

//to detect the action of the switch
typedef struct RemoteSwitch_t
{
	 uint8_t switch_value_raw;            // the current switch value
	 uint8_t switch_value1;				  //  last value << 2 | value
	 uint8_t switch_value2;				  //
	 uint8_t switch_long_value; 		  //keep still if no switching
	 uint8_t switch_value_buf[REMOTE_SWITCH_VALUE_BUF_DEEP]; 
	 uint8_t buf_index;
	 uint8_t buf_last_index;
	 uint8_t buf_end_index;
}RemoteSwitch_t;

extern RC_Ctl_t RC_CtrlData;   //remote control data
extern ChassisSpeed_Ref_t ChassisSpeedRef;
extern Gimbal_Ref_t GimbalRef;


void RemoteDataPorcess(uint8_t *pData);
void RemoteControlProcess(Remote *rc);
void MouseKeyControlProcess(Mouse *mouse, Key *key);
void Stop_immediate();
void upstair_test();
#endif



