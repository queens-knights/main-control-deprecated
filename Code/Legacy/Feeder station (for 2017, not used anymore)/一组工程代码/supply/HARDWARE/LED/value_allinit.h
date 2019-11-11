#include "stm32f4xx.h"

#define remote_mode 1
#define auto_mode   0
#define uping_locationreset  0 
#define uping_locationmax  250000
#define extern_locationreset 0
#define extern_locationmax 250000
#define rotate_locationreset 0
#define rotate_locationmax 100000

#define remote_up   1
#define remote_mid  3
#define remote_down 2

extern int Tim_circle_flag_1ms  ;
extern int Tim_circle_flag_2ms  ;
extern int Tim_circle_flag_3ms ;

//电机各变量：
extern s16 rm2006_1[4] , rm2006_1_offset , rm2006_1_cnt , rm2006_1_last;
extern s16 rm2006_2[4] , rm2006_2_offset , rm2006_2_cnt , rm2006_2_last;
extern s16 rm2006_3[4] , rm2006_3_offset , rm2006_3_cnt , rm2006_3_last;
extern s16 rm3508[4]   , rm3508_offset , rm3508_cnt , rm3508_last;


extern s16 gimbal_yaw_Motor[4] ;
extern s16 gimbal_pitch_Motor[4]  ;

extern s16 trigger_Motor[4] ;
//拨弹电机期望转速:
extern int trigger_motor_speedtar;

extern s16 chassis_Motor0x201_tar , chassis_Motor0x202_tar , chassis_Motor0x203_tar , chassis_Motor0x204_tar;
extern s16 externd_Motor0x201_tar , externd_Motor0x202_tar , externd_Motor0x203_tar , externd_Motor0x204_tar;
extern float chassismoto_location_0x201 , chassismoto_location_0x202 , chassismoto_location_0x203 , chassismoto_location_0x204;

//3508电机转动位置：
extern float box_motor_location;
extern float box_motor_locationset;
extern float box_motor_locationmax ;//最大行程

//箱子开合2006电机
extern float open_or_close_motorlocation;
extern float open_or_close_motorlocationset;
extern float open_or_close_motorlocationmax;


//拨弹电机预期转速：
extern int rm2006_1_tar  , rm2006_3_tar  ;

//漏弹器1 五十颗上限标志
extern int bullet_outer1_limit50_flag ;
//漏弹器2 五十颗上限标志
extern int bullet_outer2_limit50_flag;
//步兵在漏弹器1补完弹标志：
extern int infantry_supply1_confirmflag ;
//步兵在漏弹器1补完弹标志：
extern int infantry_supply2_confirmflag ;





























extern float chassismoto_location[4];
extern float chassimotor_locationset[4];
extern s16 chassis_Motor_tar[4];
extern s16 externmoto_tar[4];
extern float externmoto_location[4];
extern float externmotor_locationset[4];

extern s16 externmoto_0x201_tar , externmoto_0x202_tar , externmoto_0x203_tar , externmoto_0x204_tar;
extern float externmoto_location_0x201 , externmoto_location_0x202 , externmoto_location_0x203 , externmoto_location_0x204;
extern float externmotor_locationset_0x201 , externmotor_locationset_0x202 , externmotor_locationset_0x203 , externmotor_locationset_0x204;
extern float pickmotor_location_extern , pickmotor1_location_rotate , pickmotor2_location_rotate;
extern float pickmotor_locationset_extern , pickmotor1_locationset_rotate , pickmotor2_locationset_rotate;

extern s16 location_calc_flag ;
extern s16 speed_calc_flag    ;
extern s16 pidcalc_startflag_can1  , pidcalc_startflag_can2  ;
extern s16 pickmotor_extern_tar , pickmotor1_rotate_tar , pickmotor2_rotate_tar;

extern int Tim_circle_flag  ;
extern u8 remote_movepara_diretion ;
extern u8 remote_or_autoflag   ;
extern int movement_cnt , move_flag1 , move_flag2 , move_flag3 , move_flag4 , move_flag5 , move_flag6 , move_flag7 , move_flag8 , move_flag9 , move_flag10 , move_flag11 , move_flag12;                                     

extern u8 key[6];
extern u8 light[4] ;

extern int speed_set_1 , speed_set_2 , speed_set_3 , speed_set_4;
extern float set_1  , set_2  ,set_3 ;

//云台电机期望位置：
extern int gimbal_yawmotor_locationset , gimbal_pitchmotor_locationset;
extern int gimbal_yawmotor_locationinit , gimbal_pitchmotor_locationinit  ;


extern u8 chassis_reset_flag ;
extern u8 Remote_Mode ;

extern int usart_cnt ;
extern int last_usart_cnt ;
extern int remote_detect_flag  ;
extern int cnt_bais  ;
extern int danger_cnt ;

extern float extern_longth  ; //0是初始位置，负为底盘下降，正为底盘上升   520000
extern float pick_position ;

extern u8 high_low_speedswitch;
extern int speedswitch_cnt ;
extern int high_speed_value  ;
extern int low_speed_value  ;

extern float pick_longth;
extern float pick_rotate_distance;

//云台转动角速度：
extern float gimbal_speed_yaw ,gimbal_speed_pitch;

//射击状态：
extern int shoot_status;

//云台运动参数;
extern float gimbal_movepara ;

extern int trigger_motor_speedinit  ;



