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

//void delay21us(void)   //��� 0us
//{
//    unsigned char a;
//    for(a=9;a>0;a--);
//}
//void delay500us(void)   //��� 0us
//{
//    unsigned char a,b;
//    for(b=99;b>0;b--)
//        for(a=1;a>0;a--)
//		  {ADD++;}
//}
//
//void delay6ms553us(void)   //��� 0us
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

	 s=time*0.172;     //�������CM
}


void  StartModule() 		         //����ģ��
{
	  Trig=1;			                     //����һ��ģ��
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

/**��ߵ��**/
//��ָ���ٶ����к�����MotRun()
void MotRun(unsigned char speed)
{	
     
     if(ADD>100)  //PWM����Ϊ100*0.5ms
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
//ֹͣ���������MotStop()
//void MotStop(void)
//{	 
//
//      LAN=0;
//	  LAP=0;
//	  RBN=0;
//	  RBP=0;
//
//}
///**��ߵ��**/
////��ָ���ٶ����к�����MotRun()
void LMotRun( unsigned char speed)
{
  	 
  if(ADD>100)  //PWM����Ϊ100*0.5ms
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
	     while(!Echo);		//��RXΪ��ʱ�ȴ�
	     TR1=1;			    //��������
	     while(Echo);			//��RXΪ1�������ȴ�
	     TR1=0;				//�رռ���
         Conut();			//����
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
	 
	TMOD = TMOD | 0x10 ;        //T1 �����ڷ�ʽ1��8λ������,�Զ����أ�
	TH1 = 0x0FE;  //���¸���ֵ ��ʱ500΢��
    TL1 = 0x0C;
	EA  = 1;
	ET1 = 1;
//	TR1 = 1;

//	 TH0=0;
//	 TL0=0;          
//	 ET0=1;             //����T0�ж�

	while(1)
	{
		UTC();
	}
			
}

//void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
// {
//
// }

 void Time1_IT(void) interrupt 3 		 //T1
{  	
		TH1 = 0x0FE;  //���¸���ֵ
        TL1 = 0x0C;	
 	    ADD++;

}

