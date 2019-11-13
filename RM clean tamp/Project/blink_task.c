#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "blink_task.h"

void blink_task(const void* argu)
{
	while(1)
	{
		write_led_io(LED_IO1,LED_ON);
		osDelay(200);
		write_led_io(LED_IO2,LED_ON);
		osDelay(200);
		write_led_io(LED_IO3,LED_ON);
		osDelay(200);
		write_led_io(LED_IO4,LED_ON);
		osDelay(200);
		write_led_io(LED_IO5,LED_ON);
		osDelay(200);
		write_led_io(LED_IO6,LED_ON);
		osDelay(200);
		write_led_io(LED_IO7,LED_ON);
		osDelay(200);
		write_led_io(LED_IO8,LED_ON);
		osDelay(200);		
		write_led_io(LED_IO8,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO7,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO6,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO5,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO4,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO3,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO2,LED_OFF);
		osDelay(200);
		write_led_io(LED_IO1,LED_OFF);
		osDelay(200);
	}
		
	
}