#include "pid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PidTypeDef PidDataLocation_rm2006_1;
PidTypeDef PidDataLocation_rm2006_2;
PidTypeDef PidDataLocation_rm2006_3;
PidTypeDef PidDataLocation_rm3508; 
PidTypeDef PidDataSpeed_rm2006_1;
PidTypeDef PidDataSpeed_rm2006_2;
PidTypeDef PidDataSpeed_rm2006_3;
PidTypeDef PidDataSpeed_rm3508; 
 

//初始化PID 
void PID_Init(PidTypeDef * pid)
{
	memset(pid, 0, sizeof(PidTypeDef));
}

 

//设置参数 
void PID_SetParam(PidTypeDef * pid,float p, float i, float d, float limit_Ki , float limit_U)	
{
	pid->Kp = p;
	pid->Ki = i;
	pid->Kd = d;  
	pid->limit_Ki = limit_Ki;
	pid->limit_U = limit_U;
}


void PID_InitALL(void)
{
	//取弹电机参数：	
	//位置：
	PID_Init(&PidDataLocation_rm2006_2);
	PID_SetParam(&PidDataLocation_rm2006_2 , 0.5 , 0.001 , 0 , 100 , 20000);
	PID_Init(&PidDataLocation_rm3508);
	PID_SetParam(&PidDataLocation_rm3508 , 0.5 , 0.001 , 0 , 100 , 3000);
	
	//速度：    
	PID_Init(&PidDataSpeed_rm2006_1);
	PID_SetParam(&PidDataSpeed_rm2006_1 , 3 , 0.01 , 1 , 2000 , 20000);		   
	PID_Init(&PidDataSpeed_rm2006_2);
	PID_SetParam(&PidDataSpeed_rm2006_2 , 3 , 0.01 , 1 , 200 , 20000);		 
	PID_Init(&PidDataSpeed_rm2006_3);
	PID_SetParam(&PidDataSpeed_rm2006_3 , 3 , 0.01 , 1 , 2000 , 20000);		   
	PID_Init(&PidDataSpeed_rm3508);
	PID_SetParam(&PidDataSpeed_rm3508   , 3 , 0.01 , 1 , 15000 , 20000);		 
}



//PID计算 
float PID_Calc(PidTypeDef * pid, double rel_val, double set_val)
{
	double p = 0,
         i = 0,
         d = 0;
 
	//误差:
	pid->err = set_val - rel_val;
	
	//p输出：
	pid->out_kp  = pid->err * pid->Kp;
	
	//i输出：
	pid->out_ki += pid->err * pid->Ki;
	if(pid->out_ki > pid->limit_Ki)
	{
		pid->out_ki = pid->limit_Ki;
	}
	else if(pid->out_ki < -pid->limit_Ki)
	{
		pid->out_ki = -pid->limit_Ki;
	}

	//d输出：
	pid->out_kd  = -( pid->last_err - pid->err ) * pid->Kd;
	pid->last_err = pid->err;
	
	//总输出：
	pid->U = pid->out_kp + pid->out_ki + pid->out_kd ;
	if(pid->U > pid->limit_U)
	{
		pid->U = pid->limit_U;
	}
	else if(pid->U < -pid->limit_U)
	{
		pid->U = -pid->limit_U;
	}

	
	return pid->U;
}



 