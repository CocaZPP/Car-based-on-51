#include<reg51.h>

/*���Ŷ���*/

//�����������
//��ߵ��
//sbit  ENA   = P1^0;
sbit  LAN    = P2^0;
sbit  LAP    = P2^1;

//�ұߵ��
//sbit  ENB   = P1^3;
sbit  RBN    = P2^2;
sbit  RBP    = P2^3;


//Ѱ�ߵ�·����
sbit  Follow_L 		= P2^4;
sbit  Follow_R  	= P2^7;

//�������ϰ���������
sbit  UltraDTC_TR   = P3^6;
sbit  UltraDTC_RE   = P3^7;


//����ָʾ����
sbit  Guide   = P3^5;
//1602��ʾ����
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P1^0; //1602ʹ���ź�
sbit LCD1602_RS=P1^1;//1602���� ����ѡ���



//---����ds1302ʹ�õ�IO��---//
//sbit  VEE=P1^4;
//sbit DSIO=P1^5;
//sbit RST=P1^6;
//sbit SCLK=P1^7;