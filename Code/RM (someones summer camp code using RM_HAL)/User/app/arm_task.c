#include "can_device.h"
#include "uart_device.h"
#include "keyboard.h"
#include "pid.h"
#include "sys.h"

#include "stdlib.h"
#include "can.h"
#include "cmsis_os.h"
#include "string.h"
#include "arm_task.h"
#include "arm.h"


extern int target_arm;
extern int trans_bias;
extern int arm_bias;
extern uint8_t test_servo;


int16_t all_current[4]={0,0,0,0};
int arm_power;
int claw_power;
int trans_power;

void claw_param_init(void);
void trans_param_init(void);
void arm_param_init(void);

void arm_task(const void* argu){
	pc_kb_hook();
	//initialize all motor&device
	arm_bias=moto_arm.total_angle;
	trans_bias=moto_trans.total_angle;
	arm_param_init();
	claw_param_init();
	trans_param_init();
	camera_servo_init();
	set_pwm_param(PWM_IO1,2500);
	
   //¿ªÆô¿ØÖÆ¶Ë¿Ú
   uint32_t arm_wake_time = osKernelSysTick();
	
  while(1){
		arm_power=arm_power_calculate();
		claw_power=claw_power_calculate();
		trans_power=trans_power_calculate();
		all_current[0]=arm_power;
    all_current[1]=-arm_power; 
    all_current[2]=claw_power;
		all_current[3]=trans_power;
    send_other_moto_current(all_current);
		//camera_servo_ctrl(); 
		
		osDelayUntil(&arm_wake_time, 5);//Thread delay 5ms every loop
  }  

}




