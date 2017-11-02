#ifndef __LCD1602_H_
#define __LCD1602_H_


/**********************************
����ͷ�ļ�
**********************************/
#include<reg51.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0		//���������
sbit LCD1602_E=P3^4; //1602ʹ���ź�
//sbit LCD1602_RW=P2^0;//1602��дѡ���
sbit LCD1602_RS=P3^5;//1602���� ����ѡ���

/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  

#endif
