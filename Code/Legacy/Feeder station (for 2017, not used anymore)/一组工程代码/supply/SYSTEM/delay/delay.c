#include "delay.h"
#include "sys.h"
 
 
void delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=20;
		while(a--);
	}
}

void delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=40;
		while(a--);
	}
}



