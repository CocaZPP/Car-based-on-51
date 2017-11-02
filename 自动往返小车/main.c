#include "LCD1602.h"
#include "reg51.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "math.h"

uint line,ring;
uchar fen,miao,a,t,count; 
#define girth 0.204
sbit xian1=P1^1;
sbit xian2=P1^2;

sbit ENA=P0^0;
sbit A1=P2^0; sbit A2=P2^1;
//////////
sbit ENB=P1^0;sbit B1=P2^2;
sbit B2=P2^3;

//void delay (uint xms)
//
//{	   uint i,j;
//for(i=xms;i>0;i--)
//	    for(j=110;j>0;j--);
//}
////��ת
void forward1()
{	 	uchar i;
ENA=1;ENB=1;

  
  
  	  for(i=0;i<500;i++)
	  {
	  	 A2=0;B2=0;
	  }
  
      for(i=0;i<100;i++)
      {
  	    A1=1;B1=1;
      }
}

void forward2()
{	 uchar i;
 ENA=1;ENB=1;
	
  
  
  	  for(i=0;i<500;i++)
	  {
	  	 A2=0;B2=0;
	  }
  
      for(i=0;i<100;i++)
      {
  	    A1=1;B1=1;
      }
}
////��ת
void later1()
{	   	uchar i;
  		ENA=1;ENB=1;
  
  	  for(i=0;i<500;i++)
	  {
	  	 A2=0;B2=0;
	  }
  
      for(i=0;i<100;i++)
      {
  	    A1=1;B1=1;
      }
}
void later2()
{	   	uchar i;
  		ENA=1;ENB=1;
  
  	  for(i=0;i<500;i++)
	  {
	  	 A2=0;B2=0;
	  }
  
      for(i=0;i<100;i++)
      {
  	    A1=1;B1=1;
      }
} 
////����ֹͣ
void braking()
{	    ENA=1;
	     A1=0;
		 A2=0;

		 ENA=1;
	     A1=0;
		 A2=0;
}

//������
void ce_heixian()
{
   if(xian1==0x00||xian2==0x00)
   line++;
}
//ʱ��
void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������

	TH0=0Xc78;	//����ʱ������ֵ����ʱ5ms
	TL0=0Xc78;	

	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
}
void Timer0() interrupt 1
{

	TH0=0Xc78;	//����ʱ������ֵ����ʱ5ms
	TL0=0Xc78;
	t++;
	
	
}
void init()
{		TMOD|=0X10;//ѡ��Ϊ��ʱ��1ģʽ��������ʽ1������TR1��������

	TH1=0X3cb0;	//����ʱ������ֵ����ʱ50ms
	TL1=0X3cb0;	

	EA=1;//�����ж�
	TR1=1;//�򿪶�ʱ��
	ET1=1;//�򿪶�ʱ��1�ж�����	

}
void Timer1() interrupt 3
{		TH1=0X3cb0;	//����ʱ������ֵ����ʱ50ms
	    TL1=0X3cb0;
		count++;
		 if(count==20)	//1S
		 { count=0;
		   miao++;
		   if(miao==60)
		    { miao=0;
			  fen++;
			   if(fen==60)
			    { fen=0;
				}
				 
			}
		
         }
		 
}
void write_sf(uchar add,uchar date)
{
  uchar shi,ge;
  shi=date/10;
  ge=date%10;
   LcdWriteCom(0x80+add);
   LcdWriteData(0x30+shi);
   LcdWriteData(0x30+ge);
}
//����
void Int0Init()
{
	//����INT0
	IT0=1;//�����س�����ʽ���½��أ�
	EX0=1;//��INT0���ж�����	
	EA=1;//�����ж�	
}
void Int0()	interrupt 0		//�ⲿ�ж�0���жϺ���
{	ET1=1;//�򿪶�ʱ��1�ж�����
    ring++;
}
void write_jl(uchar add,uchar date)
{   uchar shi,ge;
   shi=date/10;
   ge=date%10;
   LcdWriteCom(0x80+add);
   LcdWriteData(0x30+shi);
   LcdWriteData(0x30+ge);
}
void chuli()
{  
  a=ring*girth;
   

}
//���ߴ���
void dispose()
{	   if(line<=2)
        {forward1();}
	   else 
	     if(line==3)
	       {forward2();}
		   else 
		      if(line>3&&line<6)
			  { forward1(); }
			  else 
			    if(line==6)
				{ braking();
				  ET0=1;//�򿪶�ʱ��0�ж�����
				  if(t==2000)
				  {later1();}
				}
				else 
				   if(line==9)
				   {later2();}
				   else 
				     if(line>9&&line<12)
					 {later1();}
					 else 
					    {
						 braking();
						 write_sf(1,fen);
						 write_sf(3,miao);
						  chuli();
						 write_jl(5,a);
						}
}
void main()
{	Timer0Init();
	init();
	Int0Init();
	LcdInit();
	while(1)
	{	ce_heixian();
	   dispose();
	
	}

}




