#include <stc89.h>
#include "basic.h"
void delay(unsigned int n);
void int_uart(void);
Byte rec_Data=0;
void main()
{
 int_uart();
 while(1)
 {
  P0=rec_Data;
  P1=rec_Data;
 }

}

void int_uart(void) 
{ 
 SCON = 0x50 ; 
 TMOD = 0x20 ; 
 TH1 = 0xfd ; 
 TL1 = 0xfd ;
 IE  = 0x90 ; 
 EA=1;
 TR1 = 1 ; 
}
void uart_receive(void) interrupt 4
{
 RI=0;
 rec_Data=SBUF;
 RI=0;
}

