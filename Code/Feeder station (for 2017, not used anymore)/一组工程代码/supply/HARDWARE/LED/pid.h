#ifndef _PID_H_
#define _PID_H_

#include "stm32f4xx.h"
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

//typedef struct
//{
//	//PID 三个参数 
//	double Kp;
//	double Ki;
//	double Kd;
//	//积分分离
//	int beta;//0就是不带积分分离， 如果不为零那么就是积分范围 
//	int outbeta;//0就是不带输出限幅，如果不为零那么就是限幅范围
//	//微分先行
//	int dif_prior;//0是不带微分先行 
//	//变速积分 
//	//PID输出值
//	double last_U; //上一次的输出值 
//	double delta_U;//增量式PID
//	double U;//位置式PID
//	//设定值
//	double s[3]; 
//	//误差
//	double e[3];//每次的误差2是最新的1是上一次的0是大上次
//	//实际值
//	double r[3];
//	//前馈参数
//	double Kvff; 
//	double Kaff;
//	int full_beta;
//	 
//}PidTypeDef;

typedef struct
{
	//PID 三个参数 
	float Kp;
	float Ki;
	float Kd;
	float out_kp;
	float out_ki;
	float out_kd;
	float err;
	float last_err;
	float U;

	//
	float   limit_Ki;
	float   limit_U;
	 
}PidTypeDef;


extern PidTypeDef PidDataLocation_rm2006_1;
extern PidTypeDef PidDataLocation_rm2006_2;
extern PidTypeDef PidDataLocation_rm2006_3;
extern PidTypeDef PidDataLocation_rm3508; 
extern PidTypeDef PidDataSpeed_rm2006_1;
extern PidTypeDef PidDataSpeed_rm2006_2;
extern PidTypeDef PidDataSpeed_rm2006_3;
extern PidTypeDef PidDataSpeed_rm3508; 




void PID_InitALL(void);
void PID_Init(PidTypeDef * pid);

void PID_SetParam(PidTypeDef * pid,float p, float i, float d, float limit_Ki , float limit_U)	;
void datalimit(double data , double limit);
float PID_Calc(PidTypeDef * pid, double rel_val, double set_val);


#endif
