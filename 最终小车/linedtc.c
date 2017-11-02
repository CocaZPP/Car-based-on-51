#include<reg51.h>
#include"config.h"
#include"TimeDLY.h"
#include"IOCfg.c"
#include"StepMot.h"
#include"linedtc.h"

//黑线检测函数：linedtc()
bit  linedtc()
{
	bit x;
	if(Follow_L  == 0) //检测到黑线
	{
		Guide = 1;  //声光报警
		x = 1;	   	
	}
	else
	{
		Guide = 0;
		x = 0;
	}
	return x;
}