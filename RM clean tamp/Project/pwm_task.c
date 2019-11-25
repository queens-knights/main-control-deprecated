#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "pwm_task.h"

void pwm_task(const void* argu){
	
	set_pwm_group_param(PWM_GROUP2,500);
	start_pwm_output(PWM_IO5);
	while(1){
	set_pwm_param(PWM_IO5,300);
	
	}

}

