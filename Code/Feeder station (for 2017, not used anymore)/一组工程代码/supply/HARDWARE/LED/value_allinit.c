#include "value_allinit.h"


//定时周期标志：
int Tim_circle_flag_1ms = 1;
int Tim_circle_flag_2ms = 1;
int Tim_circle_flag_3ms = 1;

//电机各变量：
s16 rm2006_1[4] , rm2006_1_offset , rm2006_1_cnt , rm2006_1_last;
s16 rm2006_2[4] , rm2006_2_offset , rm2006_2_cnt , rm2006_2_last;
s16 rm2006_3[4] , rm2006_3_offset , rm2006_3_cnt , rm2006_3_last;
s16 rm3508[4]   , rm3508_offset , rm3508_cnt , rm3508_last;

//拨弹电机预期转速：
int rm2006_1_tar = 6000 , rm2006_3_tar = 6000;//6000合适

//3508电机转动位置：
float box_motor_location;
float box_motor_locationset;
float box_motor_locationmax = 1110000;//最大行程

//箱子开合2006电机
float open_or_close_motorlocation;
float open_or_close_motorlocationset;
float open_or_close_motorlocationmax = 1000000;

//漏弹器1 五十颗上限标志
int bullet_outer1_limit50_flag = 0;
//漏弹器2 五十颗上限标志
int bullet_outer2_limit50_flag = 0;

//步兵在漏弹器1补完弹标志：
int infantry_supply1_confirmflag = 0;
//步兵在漏弹器2补完弹标志：
int infantry_supply2_confirmflag = 0;


//位置pid计算标志：
s16 location_calc_flag = 0;

//速度pid计算标志：
s16 speed_calc_flag = 1;

//pid计算标志：
s16 pidcalc_startflag_can1 = 0 , pidcalc_startflag_can2 = 0;
 
//限位开关标志：
u8 key[6];

//光电开关标志：
u8 light[4] ;

//串级PID中间传递参数
int speed_set_1 = 0 , speed_set_2 = 0 , speed_set_3 = 0 , speed_set_4 = 0;
float set_1 = 0 , set_2 = 0 ,set_3 = 0;

//底盘复位标志：
u8 chassis_reset_flag = 1;

//控制模式：
u8 Remote_Mode = 0;

//防止遥控器失灵:
int usart_cnt = 1;
int last_usart_cnt = 1;
int remote_detect_flag = 1;
int cnt_bais = 0;
int danger_cnt = 0;

   






