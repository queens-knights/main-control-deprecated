#include "can_device.h"
#include "uart_device.h"
#include "keyboard.h"
#include "pid.h"
#include "sys.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "arm.h"

short block_num;
int target_claw;
int target_arm;
int target_trans;
short block_bool;
short arm_position_bool;
short sensor_bool;
uint8_t sensor_status;
int i;
int arm_bias;
int trans_bias;
float amp=-6;

int arm_power_calculate(void){
  //Q->Arm up 
  //E->Arm down
  int16_t arm_power;
  /*if(rc.kb.bit.Q){
    arm_power=500; 
    target_arm=moto_arm.total_angle;
}
  else{if(rc.kb.bit.E){
    arm_power=rc.ch1; 
    target_arm=moto_arm.total_angle;}*/
	if(rc.ch2>0){
		
		if(rc.ch2>200)arm_power=-2000; //TODO:???
		else{arm_power=rc.ch2*amp;}
	}   
	
	if(rc.ch2<0){
	
		if(rc.ch2<-200) arm_power=2000;
		else{arm_power=rc.ch2*amp;}
	}
	
	
  return arm_power;
}


int arm_close_loop(void){
	int16_t arm_power;
	if(rc.ch2>0) {arm_power=rc.ch2*2; target_arm=moto_arm.total_angle;}
	else{
		if(rc.ch2<0) {arm_power=rc.ch2*2; target_arm=moto_arm.total_angle;}
		else{
			pid_calc(&pid_arm_moto,moto_arm.total_angle,target_arm);
		}
	}
	return arm_power;

}

int claw_power_calculate(void){
  //right click->close
  //left click->open
  int16_t claw_power;
  if(rc.mouse.l){ //read mouse left 'n' right click button.
    claw_power=2000; 
}
  else{if(rc.mouse.r){ //
    claw_power=-2000; }}
    
  if(rc.sw1==1){
		claw_power=3000;
		i=1;
	}
	else{
		if(rc.sw1==2){
			claw_power=-3000;
			i=0;
		}
		else{
			if(rc.sw1==3) {
				if(i==0) claw_power=-3000; 
				if(i==1) claw_power=0;
			}
		}
	}
		
	
  return claw_power;
}



void camera_servo_ctrl(){
	int degree=rc.mouse.y;//read mouse up 'n' down.
	if(abs(degree)<100) degree=0;
	degree+=1500;
	set_pwm_param(PWM_IO1,degree);
}


void camera_servo_init(void){
	set_pwm_group_param(PWM_GROUP1,20000);
  start_pwm_output(PWM_IO1);
}


void trans_param_init(void)
{
	pid_init(&pid_trans_moto, 6500 , 23333, 4.0f, 0.002f, 50.0f);
}

void arm_param_init(void)
{
  pid_init(&pid_arm_moto, 2000, 500, 0.85f, 0.0003f, 20.0f);
}


void claw_param_init(void)
{
  pid_init(&pid_arm_moto, 2000, 500, 0.85f, 0.0003f, 20.0f);
}

int trans_power_calculate(void){
	int trans_power;
	switch(rc.sw2){
		case 2: target_trans=trans_bias+0; break;
		
		case 3: target_trans=trans_bias+0; break;
		
		case 1: target_trans=trans_bias+0; break;
		
		default: break;
	}
	trans_power=pid_calc(&pid_trans_moto,moto_trans.total_angle,target_trans);
	return trans_power;
 }

 
 
 
 
short arm_position_test(void){//0->down_up_down 1->else
	short result=0;
	return result;
}



void sensor_init(void){
	set_digital_io_dir(DIGI_IO2,IO_INPUT);
}

short sensor_test(void){//0->falseTOtrue 1->TrueToFalse
	short result;
	read_digital_io(LED_IO2,&sensor_status);
	return result;
}



