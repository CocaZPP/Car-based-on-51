#ifndef  _CONFIG_H_
#define  _CONFIG_H_

typedef unsigned char  INT8U;        //无符号8位整型变量
typedef signed   char  INT8;         //有符号8位整型变量
typedef unsigned short INT16U;       //无符号16位整型变量
typedef signed   short INT16;        //有符号16位整型变量
typedef unsigned long  INT32U;       //无符号32位整型变量 
typedef signed   long  INT32;        //有符号32位整型变量 
typedef float          FP32;         //单精度浮点数（32位长度）
typedef double         FP64;         //双精度浮点数（64位长度）

//电机速度
#define HSPEED  60
#define MSPEED	45
#define LSPEED  30




extern INT8U ADD;
//extern INT8U TIME[12];	//加入全局变量
#endif  //_CONFIG_H_