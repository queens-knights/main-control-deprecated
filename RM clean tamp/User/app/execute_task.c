#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "cmsis_os.h"
#include "calibrate.h"
#include "pid.h"
#include "sys.h"



//uint8_t test_key_value;
extern uint8_t test_servo;

//uint16_t servo_angle = 1000;

int current=0;
int last=0;

int _delay=0;


#include "can_device.h"

int16_t mCurrent[1];

void execute_task(const void* argu)
{
   while(1){
		switch(current){
		case 0:
			mCurrent[0]=2333;
			break;
		case 1:
			delay(1000);
			break;
		case 2:
			mCurrent[0]=0;
			break;
		case 99999:
			if(_delay--!=-1)
			 osDelay(1);
			else current=last;
			break;
		}
		if(current<99997)
			jump_next();
		
		set_test_motor_current(mCurrent);
		osDelay(5);
  }
}

static void jump(int i){
	last=current;
	current=i;
}

static void delay(int i){
	_delay=i/6.4;
	jump(99999);
}

static void jump_back(){
	current=last;
	last=current;
}

static void jump_next(){
	jump(current+1);
}