#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "blink_task.h"
int usart3_recv[4];
int a=0,b=0,c=0,d=0;
/*

	void UART3_callback(void){
		a = usart3_recv[0];
		b = usart3_recv[1];
		c = usart3_recv[2];
		d = usart3_recv[3];
	}
*/
void blink_task(const void* argu)
{/*
	uint8_t usart3_recv[12];
	uint8_t a=0,b=0,c=0,d=0;
	uart_init(USER_UART3,9600,WORD_LEN_8B,STOP_BITS_1,PARITY_NONE);
	uart_recv_callback_register(USER_UART3,UART3_callback);
	uart_receive_start(USER_UART3,usart3_recv,4);

	*/
	
	while(1)
	{
		/*
		if(a=='1'){write_led_io(LED_IO1,LED_ON);} else{write_led_io(LED_IO1,LED_OFF);}
		if(b=='1'){write_led_io(LED_IO2,LED_ON);} else{write_led_io(LED_IO2,LED_OFF);}
		if(c=='1'){write_led_io(LED_IO3,LED_ON);} else{write_led_io(LED_IO3,LED_OFF);}
		if(d=='1'){write_led_io(LED_IO4,LED_ON);} else{write_led_io(LED_IO4,LED_OFF);}		
		write_uart(USER_UART3," result\n",13);
		write_uart(USER_UART3,usart3_recv,13);
		osDelay(500);*/
		/*
		write_uart(USER_UART3,"wtf\n",13);
		osDelay(500);
		*/
		
		
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