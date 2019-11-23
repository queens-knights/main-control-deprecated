#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "RGB_task.h"


void RGB11_task(const void* argu)
{
	
	while(1)
	{

			write_led_io(LED_G,LED_ON);
			osDelay(200);
			write_led_io(LED_R,LED_ON);
			osDelay(200);
			write_led_io(LED_G,LED_OFF);
			osDelay(200);
			write_led_io(LED_R,LED_OFF);
			osDelay(200);
			write_led_io(LASER_IO,LED_ON);
			osDelay(200);
			write_led_io(LASER_IO,LED_OFF);
	}

}
