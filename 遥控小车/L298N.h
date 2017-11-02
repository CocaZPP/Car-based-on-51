#ifndef __L298N_H_
#define __L298N_H_

//---包含头文件---//
#include<reg51.h>
#include<intrins.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//---定义L298N使用的IO口---//
sbit ENA=P0^0;
sbit A1=P2^0; 
sbit A2=P2^1;

sbit ENB=P1^0;
sbit B1=P2^2;
sbit B2=P2^3;

//---定义全局函数---//
void forward();		//正转
void later();		//反转
//void stop();		//停止
void braking();		//快速停止
void left_run();	//左转
void right_run();	 //右转
void delay(uint y);
//---加入全局变量--//
extern uchar low;
extern uchar high;	//加入全局变量
#endif