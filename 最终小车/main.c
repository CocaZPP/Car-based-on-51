#include<reg51.h>
#include"stepmot.h"
#include"config.h"
#include"TimeDLY.h"
#include"IOCfg.c"
#include"ultradtc.h"
#include"LCD1602.h"
#include"linedtc.h"

 #include"ds1302.h"


INT8U   linenum=0; //直道的黑线数目
INT8U code table[]="linenum:";
INT8U code table1[]="Runnum:";

 void write_a()
{	   Ds1302ReadTime();
	LcdWriteCom(0x80+0X40+10);					
   LcdWriteData('0'+TIME[1]/16);				//分
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);				//秒
	LcdWriteData('0'+(TIME[0]&0x0f));
     

}
 void write_b(INT8U date)
{

      LcdWriteCom(0x80+12);
	  LcdWriteData(0x30+date);
}

void InitIO()
{  	  INT8U y;
LAN=0;LAP=0;RBN=0;RBP=0;
   Follow_L=1;Follow_R=1;
   UltraDTC_TR=0;UltraDTC_RE=1;
   Guide=0;
   LcdInit();	    //初始化LCD1602
    Ds1302Init();		  //初始化DS1302 
//	VEE=1;
          LcdWriteCom(0x80); 
   for(y=0;y<8;y++)
         {
         LcdWriteData(table[y]);
         }
		  LcdWriteCom(0x80+0x40);
		  for(y=0;y<7;y++)
         {
         LcdWriteData(table1[y]);
         }	 	 
}
void  beep()
{
   Guide=~ Guide;
		Delay1ms(1);

}
void main()
{
     INT8U i,j;
	 InitIO();
	 MotRun(MSPEED);
//	 RMotRun(MSPEED);
   	 TMOD = TMOD | 0x10 ;        //T1 工作在方式1（8位计数器,自动重载）
	TH1 = 0x0FE;  //重新赋初值 定时500微秒
    TL1 = 0x0C;
	EA  = 1;
	ET1 = 1;
	TR1 = 1;


	while(1)
	 {
	 	do	//均速运行区
		 {	 
		   if(linedtc()) linenum++;
		 }
		while(linenum<1);
	   //第一次停车
		MotStop();
//		RMotStop();
			write_a();
		write_b(linenum);

	  for (j=0;j<5;j++)
  {	 for(i=0;i<100;i++)
	   { beep();
	     
		}
		   Delay1ms(1000);  
  }					 // 延时5S
			

			do	//快速运行区
		 {	MotRun(HSPEED);
//	    	RMotRun(HSPEED);
		   if(linedtc()) linenum++;
		 }
		  while(linenum<2);
	   //第二次停车
		MotStop();
//		RMotStop();
			write_a();
		write_b(linenum);

		  for (j=0;j<5;j++)
  {	 for(i=0;i<100;i++)
	   { beep();
	     
		}
		   Delay1ms(1000);  
  }					 // 延时5S

		  	do	//慢速运行区
		 {	MotRun(LSPEED);
//	    	RMotRun(LSPEED);
		   if(linedtc()) linenum++;
		 }
		  while(linenum<3);
	   //第三次停车
		MotStop();
//		RMotStop();
			write_a();
		write_b(linenum);

		  for (j=0;j<5;j++)
  {	 for(i=0;i<100;i++)
	   { beep();
	     
		}
		   Delay1ms(1000);  
  }					 // 延时5S

		   do //进入障碍区
		{
	         Ultra_DTC();
			if(linedtc()) linenum++;
		}						   
		while(linenum<4);
		
		MotStop();
//		RMotStop();
		write_a();
		write_b(linenum);

		  for (j=0;j<5;j++)
      {	 for(i=0;i<100;i++)
	      { beep();
	     
		  }
     		   Delay1ms(1000);  
       }	
	 }
}


void Time1_IT(void) interrupt 3 
{  	
		TH1 = 0x0FE;  //重新赋初值
        TL1 = 0x0C;	
 	ADD++;

}


