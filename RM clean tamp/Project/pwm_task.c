#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "pwm_task.h"

void pwm_task(const void* argu){
	start_pwm_output(PWM_GROUP1);
	set_pwm_group_param(PWM_GROUP1,100);
	while(1){
	set_pwm_param(PWM_IO1,100);
	
	}

}

