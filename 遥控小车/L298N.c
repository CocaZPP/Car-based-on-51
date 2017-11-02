#include"L298N.h"
uchar high=1;
uchar low=10;



void delay(uint y)
{
	uint x;
	for( ; y>0; y--)
	{
		for(x=110; x>0; x--);
	}
}

void forward()
{	   uchar i;  
        ENA=1;
        ENB=1;
  
  if(low!=0)
  {
  	  for(i=0;i<low;i++)
	  {
	  	 A2=0;B2=0;
		 delay(1000);
	  }
  }
  for(i=0;i<high;i++)
  {
  	 A1=1;B1=1;
	  delay(1000);
  }
  
}
void later()
{	    uchar i;    
        ENA=1;
        ENB=1;
  
  	  

  if(low!=0)
  {
  	  for(i=0;i<low;i++)
	  {
	  	 A2=1;B2=1;
	  }
  }
  for(i=0;i<high;i++)
  {
  	 A1=0;B1=0;
  }
  
}
//void stop()
//{  ENA=0;
//   ENB=0;
//}
void braking()
{        ENA=1;
	     A1=0;
		 A2=0;

		 ENB=1;
	     A1=0;
		 A2=0;
}
void left_run()
{        ENA=1;
	     A1=1;
		 A2=0;

         ENB=1;
	     B1=0;
		 B2=0;
}
void right_run()
{	     ENA=1;
	     A1=0;
		 A2=0;

		 ENB=1;
	     B1=1;
		 B2=0;

}