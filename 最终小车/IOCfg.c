#include<reg51.h>

/*引脚定义*/

//步进电机引脚
//左边电机
//sbit  ENA   = P1^0;
sbit  LAN    = P2^0;
sbit  LAP    = P2^1;

//右边电机
//sbit  ENB   = P1^3;
sbit  RBN    = P2^2;
sbit  RBP    = P2^3;


//寻线电路引脚
sbit  Follow_L 		= P2^4;
sbit  Follow_R  	= P2^7;

//超声波障碍物检测引脚
sbit  UltraDTC_TR   = P3^6;
sbit  UltraDTC_RE   = P3^7;


//声光指示引脚
sbit  Guide   = P3^5;
//1602显示引脚
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P1^0; //1602使能信号
sbit LCD1602_RS=P1^1;//1602数据 命令选择端



//---定义ds1302使用的IO口---//
//sbit  VEE=P1^4;
//sbit DSIO=P1^5;
//sbit RST=P1^6;
//sbit SCLK=P1^7;