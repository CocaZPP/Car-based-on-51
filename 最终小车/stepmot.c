#include<reg51.h>
#include"stepmot.h"
#include"config.h"
#include"TimeDLY.h"
#include"IOCfg.c"
INT8U ADD;

/**��ߵ��**/
//��ָ���ٶ����к�����MotRun()
void MotRun(INT16U speed)
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
void MotStop(void)
{	 

      LAN=0;
	  LAP=0;
	  RBN=0;
	  RBP=0;

}
///**��ߵ��**/
////��ָ���ٶ����к�����MotRun()
void LMotRun(INT16U speed)
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
////ֹͣ���������MotStop()
//void RMotStop(void)
//{	 
//
//      RBN=0;
//	  RBP=0;
//
//}
                     