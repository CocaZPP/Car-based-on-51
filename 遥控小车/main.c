#include"L298N.h"
#include "reg51.h"
sbit IRIN=P3^2;	  
uchar IrValue[6];

uchar Time,num;
/*******************************************************************************
* 函 数 名         : Delay1ms
* 函数功能		   : 延时函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

/*******************************************************************************
* 函数名         : IrInit()
* 函数功能		   : 初始化红外线接收
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

//
//void IrInit()
//{
//	IT0=1;//下降沿触发
//	EX0=1;//打开中断0允许
//	EA=1;	//打开总中断
//
//	IRIN=1;//初始化端口
//}
//
//void interrupt0()interrupt 0
//{
//	uchar i=0,j=0,k=0,us=0;
//	uchar addr[4]={0};
//
//	EX0=0;
//
//	for(i=0;i<255;i++)  //9ms内有高电平认为是干扰
//	{
//		if(P3&0x04)	    //255的值实际时间为800us
//		{
//			EX0=1;
//			return;
//		}
//	}
//	while(!(P3&0x04));	//等待9ms低电平过去
//   	for(i=0;i<4;i++)
//	{
//		for(j=0;j<8;j++)
//		{
//			while(P3&0x04);	//等待4.5ms高电平过去	
//			while(!(P3&0x04));	//等待0.56ms低电平后面的高电平
//			while(P3&0x04)		//计算这个高电平的时间
//			{
//				for(us=0;us<=32;us++);	//100us的延时语句
//				if((k++)>=30)		//高电平时间过长退出程序
//				{
//					EX0=1;
//					return;
//				}
//			}
//			addr[i]=addr[i]>>1;	//接收一位数据
//			if(k>=8)
//				IrValue[i]=IrValue[i]|0x80;	//高电平大于0.56ms，则为1
//			k=0;
//		}
//	}	
//
//	P1=~(IrValue[2]);	 //P2的LED显示二进制键值
//	EX0=1;	  
//}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
    TMOD=0x01;
   TH0=(65535-45872)/256;
   TL0=(65535-45872)%256;
   EA=1;
   ET0=1;
   TR0=1; 
//	IrInit();
	while(1)
	{ 
//	  	if(IrValue[2]==0x15)
//	   {
//	       low++;
//	    	if(low==4)
//		    {low=3;}
//		 
//		     high--;
//		     if(high==0)
//		     {high=1;}
//          break;
//	   }
//	  else 
//	    if(IrValue[2]==0x09)
//	     {
//	          low--;
//	    	if(low==0)
//		     {low=1;}
//		 
//		      high++;
//		     if(high==4)
//		     {high=3;}
//          break;
//	      }
//
//	   switch ( IrValue[2])
//	    { case 0x45: forward();break;
//		  case 0x18: forward();break;
//		  case 0x52: later();break;
//		  case 0x08: left_run();break;
//		  case 0x5a: right_run();break;
//		  case 0x1c: braking();break;
//		}
    if(num<1)
	{ 	A1=1;A2=0;B1=1;
	
	} else
	 {	 A1=0; A2=0;B2=0;
	  
	 }
	
	}
    
	
		
}									   
void T0_time()interrupt 1
 { 		  TH0=(65535-45872)/256;
       TL0=(65535-45872)%256;
		  num++;
		  if(num==5)
		   {
		   	num=0;
		   }
    
 }