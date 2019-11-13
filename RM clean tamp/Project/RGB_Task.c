#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "RGB_task.h"
uint8_t addw=0;
uint8_t key1,key2,key3,key4;

void RGB11_task(const void* argu)
{
	
	while(1)
	{
		read_key_io(KEY_IO1,&key1);
		read_key_io(KEY_IO2,&key2);
		read_key_io(KEY_IO3,&key3);
		read_key_io(KEY_IO4,&key4);
		if(key1==1 && key2==1 && key3==1 && key4==1)
			{
			write_led_io(LED_G,LED_ON);
			osDelay(200);
			write_led_io(LED_R,LED_ON);
			osDelay(200);
			write_led_io(LED_G,LED_OFF);
			osDelay(200);
			write_led_io(LED_R,LED_OFF);
			osDelay(200);
			}
		else
		{
			write_led_io(LED_G,LED_OFF);
			write_led_io(LED_R,LED_OFF);
			}
	}
}
