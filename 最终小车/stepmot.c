#include<reg51.h>
#include"stepmot.h"
#include"config.h"
#include"TimeDLY.h"
#include"IOCfg.c"
INT8U ADD;

/**左边电机**/
//以指定速度运行函数：MotRun()
void MotRun(INT16U speed)
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
void MotStop(void)
{	 

      LAN=0;
	  LAP=0;
	  RBN=0;
	  RBP=0;

}
///**左边电机**/
////以指定速度运行函数：MotRun()
void LMotRun(INT16U speed)
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
////停止电机函数：MotStop()
//void RMotStop(void)
//{	 
//
//      RBN=0;
//	  RBP=0;
//
//}
                     