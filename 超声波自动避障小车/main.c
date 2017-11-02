#include<reg51.h>
#include<intrins.h>	
sbit Trig = P1^0;
sbit Echo = P1^1;

sbit  LAN    = P2^0;
sbit  LAP    = P2^1;

sbit  RBN    = P2^2;
sbit  RBP    = P2^3;

   unsigned int  time=0;
   unsigned long s=0;
   unsigned long m=0;
   unsigned long t=0;
 unsigned char ADD;

//void delay21us(void)   //误差 0us
//{
//    unsigned char a;
//    for(a=9;a>0;a--);
//}
//void delay500us(void)   //误差 0us
//{
//    unsigned char a,b;
//    for(b=99;b>0;b--)
//        for(a=1;a>0;a--)
//		  {ADD++;}
//}
//
//void delay6ms553us(void)   //误差 0us
//{
//    unsigned char a,b,c;
//    for(c=4;c>0;c--)
//        for(b=86;b>0;b--)
//            for(a=8;a>0;a--)
//			 {
//			 m++;t=m;
//			  }
//}

void Conut(void)
{
	 time=TH1*256+TL1;

	 s=time*0.172;     //算出来是CM
}


void  StartModule() 		         //启动模块
{
	  Trig=1;			                     //启动一次模块
	 delay21us();
	  Trig=0;
 }

void delayms(unsigned int ms)
{
	unsigned char i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}

/**左边电机**/
//以指定速度运行函数：MotRun()
void MotRun(unsigned char speed)
{	
     
     if(ADD>100)  //PWM周期为100*0.5ms
        {
            ADD=0;      
        }
        if(ADD < speed)  
        {
            LAN=0;
            LAP=1;
            RBN=0;
            RBP=1;

        }
        else
        {	 
		     LAN=0;
             LAP=0;
		     RBN=0;
             RBP=0;
        }
}
//停止电机函数：MotStop()
//void MotStop(void)
//{	 
//
//      LAN=0;
//	  LAP=0;
//	  RBN=0;
//	  RBP=0;
//
//}
///**左边电机**/
////以指定速度运行函数：MotRun()
void LMotRun( unsigned char speed)
{
  	 
  if(ADD>100)  //PWM周期为100*0.5ms
        {
            ADD=0;     
        }
        if(ADD < speed)  
        {
           LAN=0;
           LAP=1;
        }
        else
        {	 
		   LAN=0;
	      LAP=0;
           
        }
}

void  UTC()
{
	     StartModule();
	     while(!Echo);		//当RX为零时等待
	     TR1=1;			    //开启计数
	     while(Echo);			//当RX为1计数并等待
	     TR1=0;				//关闭计数
         Conut();			//计算
		 delayms(80);
		 if(s<20)
		 {	  
		    TR1=1;	
		   LMotRun(30);
		 }
		 else 
		  {
		   TR1=1;	
		   MotRun(30);
		  }
	


}


void main(void)
{							   
	 
	TMOD = TMOD | 0x10 ;        //T1 工作在方式1（8位计数器,自动重载）
	TH1 = 0x0FE;  //重新赋初值 定时500微秒
    TL1 = 0x0C;
	EA  = 1;
	ET1 = 1;
//	TR1 = 1;

//	 TH0=0;
//	 TL0=0;          
//	 ET0=1;             //允许T0中断

	while(1)
	{
		UTC();
	}
			
}

//void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
// {
//
// }

 void Time1_IT(void) interrupt 3 		 //T1
{  	
		TH1 = 0x0FE;  //重新赋初值
        TL1 = 0x0C;	
 	    ADD++;

}

