#include <reg52.h>
#include<intrins.h>	
#define uint unsigned int
#define uchar unsigned char
//uchar num=0,high=1,low=3;
sbit ENA=P2^0;
sbit A1=P2^1; sbit A2=P2^2;	 
sbit A3=P2^3;	 
//////////
//sbit ENB=P1^0;sbit B1=P2^6;
//sbit B2=P2^5;
//sbit jia_key=P3^1 ;sbit jian_key=P3^2;
//void delay (uint xms)
//
//{	   uint i,j;				------
//for(i=xms;i>0;i--)
//	    for(j=110;j>0;j--);
//}
////正转
//void forward()
//{
//	     ENA=1;
//	     A1=1;
//		 A2=0;
//
//		 ENB=1;
//	     B1=1;
//		 B2=0;
//}
//////反转
//void later()
//{	    ENA=1;
//	     A1=0;
//		 A2=1;
//
//		 ENB=1;
//	     B1=0;
//		 B2=1;
//}
////停止
//void stop()
//{
//    ENA=0; ENB=0;
//}
////快速停止
//void braking()
//{	    ENA=1;
//	     A1=0;
//		 A2=0;
//
//		 ENA=1;
//	     A1=0;
//		 A2=0;
//
//}
	//按键控制
//void key()	//按键扫描子程序
//{   if(jia_key!=1)
//	{
//	   delay(20);
//	   if(jia_key!=1)
//	   {
//	    num++;
//		if(num==4)
//		num=3;
//		while(jia_key!=1);
//	   }
//	}
//	if(jian_key!=1)
//	{
//		delay(20);
//		if(jian_key!=1)
//		{
//		  if(num!=0)
//		  num--;
//		  else 
//		    num=0;
//		  while(jian_key!=1);
//		
//			
//		}
//	}	 
//
//}
////速度处理
//void dispose()
//{
//  switch(num)
//  {
//  	case 0: high=1;
//	       low=3; 
//		   break;
//    case 1:  high=2;
//	       low=2; 
//		   break;
//
//    case 2:  high=3;
//	       low=1; 
//		   break;
//    case 3:  high=4;
//	       low=0; 
//		   break;
//  
//  
//  }
//}
////电机驱动
//void pwm()
//{
//  uchar i;
//  if(low!=0)
//  {
//  	  for(i=0;i<low;i++)
//	  {
//	  	 A2=0;B2=0;
//	  }
//  }
//  for(i=0;i<high;i++)
//  {
//  	 A1=1;B1=1;
//  }


			     
void main()
{
	 while(1)
	 {	 ENA=0;
	 	 A1=1;
		 A2=0;
		 A3=1;

//		 ENB=1;
//	     B1=1;
//		 B2=0;
	 
	 }
//	{ ENA=1;ENB=1;
//		key();
//		dispose();
//		pwm();  
      
	  

	
}



 




