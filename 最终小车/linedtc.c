#include<reg51.h>
#include"config.h"
#include"TimeDLY.h"
#include"IOCfg.c"
#include"StepMot.h"
#include"linedtc.h"

//���߼�⺯����linedtc()
bit  linedtc()
{
	bit x;
	if(Follow_L  == 0) //��⵽����
	{
		Guide = 1;  //���ⱨ��
		x = 1;	   	
	}
	else
	{
		Guide = 0;
		x = 0;
	}
	return x;
}