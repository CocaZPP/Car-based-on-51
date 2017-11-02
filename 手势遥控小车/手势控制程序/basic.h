#ifndef __basic_H__
#define __basic_H__


typedef unsigned char Byte;
typedef unsigned int  Word;
typedef signed int    sWord;
#define exchange(m,n) m=m+n;n=m-n;m=m-n; //变量交换

#define EA_on   EA=1    //总中断    
#define EA_off  EA=0

#define ET2_on  ET2=1   //定时器2
#define ET2_off ET2=0

#define ES_on   ES=1    //串口中断
#define ES_off  ES=0

#define ET1_on  ET1=1   //定时器1
#define ET1_off ET1=0

#define EX1_on  EX1=1  //外部中断1
#define EX1_off EX1=0

#define ET0_on  ET0=1   //定时器0
#define ET0_off ET0=0

#define EX0_on  EX0=1   //外部中断1
#define EX0_off EX0=0


#define EX0_int0   EA=1;IT0=0;EX0=1;  //外部中断0低电平触发设置
#define EX0_int1   EA=1;IT0=1;EX0=1;  //外部中断0下降沿触发设置

#define EX1_int0   EA=1;IT1=0;EX1=1;  //外部中断1低电平触发设置
#define EX1_int1   EA=1;IT1=1;EX1=1;  //外部中断1下降沿触发设置


#endif