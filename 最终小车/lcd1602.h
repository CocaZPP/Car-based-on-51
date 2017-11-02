#ifndef __LCD1602_H_
#define __LCD1602_H_

/*LCD1602写入8位命令子函数*/
void LcdWriteCom(INT8U com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(INT8U dat)	;
/*LCD1602初始化子程序*/		
void LcdInit();						  

#endif	 //__LCD_H_