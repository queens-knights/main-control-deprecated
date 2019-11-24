#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "ai_task.h"
uint8_t usart3_recv[4];
uint8_t aa=0,bb=0,cc=0,dd=0;
void USART3_callback(void){
		aa = usart3_recv[0];
		bb = usart3_recv[1];
		cc = usart3_recv[2];
		dd = usart3_recv[3];
}


void ai_task(const void* argu){
	uart_init(USER_UART3,9600,WORD_LEN_8B,STOP_BITS_1,PARITY_NONE);
	uart_recv_callback_register(USER_UART3,USART3_callback);
	uart_receive_start(USER_UART3,usart3_recv,4);

	while(1){
		USART3_callback();
		if(aa=='1')
		{
			write_led_io(LED_IO1,LED_ON);} 
		else
		{
			write_led_io(LED_IO1,LED_OFF);
		}
		if(bb=='1')
		{
			write_led_io(LED_IO2,LED_ON);
		} 
		else
		{
			write_led_io(LED_IO2,LED_OFF);}
		if(cc=='1')
		{
			write_led_io(LED_IO3,LED_ON);
		} 
		else
		{
			write_led_io(LED_IO3,LED_OFF);
		}
		if(dd=='1')
		{
			write_led_io(LED_IO4,LED_ON);
		} 
		else
		{
			write_led_io(LED_IO4,LED_OFF);
		}		
		//write_uart(USER_UART3,"hi",13);
		//write_uart(USER_UART3,usart3_recv,13);
	}
}
