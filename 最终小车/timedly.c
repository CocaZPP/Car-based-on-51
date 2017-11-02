#include<reg51.h>
#include"Config.h"
#include"TimeDLY.h"

void Delay1ms(INT16U c)   //Îó²î 0us
{
    INT8U a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

