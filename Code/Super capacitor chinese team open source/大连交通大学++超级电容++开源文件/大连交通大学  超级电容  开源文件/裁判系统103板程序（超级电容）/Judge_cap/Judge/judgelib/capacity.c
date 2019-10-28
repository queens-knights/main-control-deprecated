#include "capacity.h"
#include "Judge.h"
#include <math.h>
static int starttic;
uint8_t usecap = 0;
float imu_gx,imu_gy,imu_gz;
int16_t imu_gy_trans,imu_gz_trans;
float angletrans;
int16_t chassis_speed[4] = {0};

float Vx=0.0,Vy=0.0,VOmega=0.0;

void InvMecanumCal(float *vx,float *vz,float *omega,const int16_t *speed){ // mm/s deg/s
#define ScaleConst 0.42025691199337f // 152.5*pi/60/19
	*omega = imu_gz;
    *vz = 0.25*(speed[0]-speed[1]+speed[2]-speed[3])*ScaleConst;
    *vx = 0.25*(speed[0]-speed[3]+speed[1]-speed[2])*ScaleConst;
}

void Capacity_Ctrl(void){
	InvMecanumCal(&Vx,&Vy,&VOmega,chassis_speed);
	if(usecap){
		CAPACITY_OUTPUT_START;
		CAPACITY_INPUT_STOP;		
	}else{
		if(Judge_extPowerHeatData.chassisPowerBuffer > 45){
			if(fabs(Vx) < 30.0 && fabs(Vy)< 30.0 && fabs(VOmega) < 5.0){
				CAPACITY_INPUT_START;
				CAPACITY_OUTPUT_STOP;					
			}else{
				CAPACITY_INPUT_STOP;
				CAPACITY_OUTPUT_STOP;
			}
		}else{
			CAPACITY_INPUT_STOP;
			CAPACITY_OUTPUT_STOP;
		}
	}
}


