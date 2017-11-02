#include  <REG52.H>	
#include  <basic.h>
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
sbit	  SCL=P1^0;      //IIC时钟引脚定义
sbit 	  SDA=P1^1;      //IIC数据引脚定义
#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地
#define JudgeP_M  0x8000   //正负数判断
#define Left_cmp  0x006e   //方向数据比较值，数值越小，越灵敏
#define Right_cmp 0x006e
#define Go_cmp    0x006e
#define Back_cmp  0x006e
#define Go    0xaa		   //小车实际动作控制字符，以实物为准
#define Back  0x55
#define Left  0xa0
#define Right 0x0a
#define Stop  0x00		   //停止控制字符
Byte BUF[8];                         //接收数据缓存区 
Byte Sbuf[8]; 
Word Wbuf[2];    	
int  dis_data;                       //变量
void delay(unsigned int k);
void Init_ADXL345(void);             //初始化ADXL345
void WriteDataLCM(Byte dataW);
void WriteCommandLCM(Byte CMD,Byte Attribc);
void DisplayOneChar(Byte X,Byte Y,Byte DData);
void conversion(Word temp_data);
void  Single_Write_ADXL345(Byte REG_Address,Byte REG_data);   //单个写入数据
Byte Single_Read_ADXL345(Byte REG_Address);                   //单个读取内部寄存器数据
void  Multiple_Read_ADXL345();                                  //连续的读取内部寄存器数据
//------------------------------------
void Delay5us();
void Delay5ms();
void Delay20ms();
void ADXL345_Start();
void ADXL345_Stop();
void ADXL345_SendACK(bit ack);
bit  ADXL345_RecvACK();
void ADXL345_SendByte(Byte dat);
Byte ADXL345_RecvByte();
void ADXL345_ReadPage();
void ADXL345_WritePage();
void send();
void uart();
void Data_Convert();
void Data_Process();
void direction_judge();


//******主程序********
void main()
{ 
	void Delay20ms();	                   	//上电延时		                   
	uart();	
	Init_ADXL345();                 	//初始化ADXL345
	while(1)                         	//循环
	{ 
		Multiple_Read_ADXL345();       	//连续读出数据，存储在BUF中
		Data_Convert();
        Data_Process();
		direction_judge();
		Delay20ms();                   	//延时      
	}
}

/*******************************/
void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
										
/*******************************/					
/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
    Word n = 560;

    while (n--);
}
/**************************************
起始信号
**************************************/
void ADXL345_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}
/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}
/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}
/**************************************
接收应答信号
**************************************/
bit ADXL345_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}
/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(Byte dat)
{
    Byte i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    ADXL345_RecvACK();
}
//从IIC总线接收一个字节数据
Byte ADXL345_RecvByte()
{
    Byte i;
    Byte dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}
//******单字节写入*******************************************
void Single_Write_ADXL345(Byte REG_Address,Byte REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}
//********单字节读取*****************************************
Byte Single_Read_ADXL345(Byte REG_Address)
{  Byte REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);            //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
void Multiple_read_ADXL345(void)
{   Byte i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    Delay5ms();
}
//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
   Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
void uart()
{
 SCON=0x50;
 TMOD=0x20;
 PCON=0x00;
 TH1=0xfd;
 TL1=0xfd;
 IE=0x90;
 TR1=1;
}

void send(unsigned char ch) 
{
 ES=0; 
 SBUF=ch; 
 while (TI==0); 
 TI=0 ;
 ES=1; 
}
void Data_Convert()						//将两个八位数据合成为一个16位数据
{
  Wbuf[0]=BUF[1]<<8|BUF[0];
  Wbuf[1]=BUF[3]<<8|BUF[2];
  Wbuf[2]=BUF[5]<<8|BUF[4];
} 
void Data_Process()
{
   Word i=0;
    i=Wbuf[0]&JudgeP_M;	   //X轴数据处理
  if(i==0x8000)	           //当结果为负数时
  {
   Wbuf[0]=~Wbuf[0]+1;
   Wbuf[0]=Wbuf[0]&0x7fff;
   if(Wbuf[0]>Left_cmp)
   {
   Sbuf[0]=Left;
   }
   else
   {
   Sbuf[0]=Stop;
   }
  }
  else					   //当结果为正数时
  {
   if(Wbuf[0]>Right_cmp)
   {
      Sbuf[0]=Right;
   }
   else
   {
	   Sbuf[0]=Stop;
   }
  }
  i=Wbuf[1]&JudgeP_M;		   //Y轴数据处理
  if(i==0x8000)	           //当结果为负数时
  {
   Wbuf[1]=~Wbuf[1]+1;
   Wbuf[1]=Wbuf[1]&0x7fff;
   if(Wbuf[1]>Back_cmp)
   {
   Sbuf[1]=Back;
   }
   else
   {
   Sbuf[1]=Stop;
   }
  }
  else					   //当结果为正数时
  {
   if(Wbuf[1]>Go_cmp)
   {
     Sbuf[1]=Go;
   }
   else
   {
	 Sbuf[1]=Stop;
   }
  }
}

void direction_judge()
{

  if(Sbuf[0]==Left|Sbuf[0]==Right)
  {
   send(Sbuf[0]);
  }
  else
  {
   send(Sbuf[1]);
  }
}
 