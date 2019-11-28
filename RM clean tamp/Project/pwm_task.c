#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "pwm_task.h"
int ki = 0;


void pwm_task(const void* argu){
	
	set_pwm_group_param(PWM_GROUP1,20000);
	start_pwm_output(PWM_IO1);
	while(1){
			for(ki=500;ki<2500;ki+=30){
				set_pwm_param(PWM_IO1,ki);
				osDelay(50);
			}
			for(ki=2500;ki>500;ki-=30){
				set_pwm_param(PWM_IO1,ki);
				osDelay(50);
			}
	}

}

