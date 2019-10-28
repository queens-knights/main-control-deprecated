#include "delay.h"

void xdelay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=12000;
		while(a--);
	}
}

void xdelay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=12;
		while(a--);
	}
}



