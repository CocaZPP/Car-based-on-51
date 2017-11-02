#ifndef __L298N_H_
#define __L298N_H_

//---����ͷ�ļ�---//
#include<reg51.h>
#include<intrins.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//---����L298Nʹ�õ�IO��---//
sbit ENA=P0^0;
sbit A1=P2^0; 
sbit A2=P2^1;

sbit ENB=P1^0;
sbit B1=P2^2;
sbit B2=P2^3;

//---����ȫ�ֺ���---//
void forward();		//��ת
void later();		//��ת
//void stop();		//ֹͣ
void braking();		//����ֹͣ
void left_run();	//��ת
void right_run();	 //��ת
void delay(uint y);
//---����ȫ�ֱ���--//
extern uchar low;
extern uchar high;	//����ȫ�ֱ���
#endif