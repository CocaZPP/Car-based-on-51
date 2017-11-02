#include  <REG52.H>	
#include  <basic.h>
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
sbit	  SCL=P1^0;      //IICʱ�����Ŷ���
sbit 	  SDA=P1^1;      //IIC�������Ŷ���
#define	SlaveAddress   0xA6	  //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0xA6���ӵ�Դʱ��
#define JudgeP_M  0x8000   //�������ж�
#define Left_cmp  0x006e   //�������ݱȽ�ֵ����ֵԽС��Խ����
#define Right_cmp 0x006e
#define Go_cmp    0x006e
#define Back_cmp  0x006e
#define Go    0xaa		   //С��ʵ�ʶ��������ַ�����ʵ��Ϊ׼
#define Back  0x55
#define Left  0xa0
#define Right 0x0a
#define Stop  0x00		   //ֹͣ�����ַ�
Byte BUF[8];                         //�������ݻ����� 
Byte Sbuf[8]; 
Word Wbuf[2];    	
int  dis_data;                       //����
void delay(unsigned int k);
void Init_ADXL345(void);             //��ʼ��ADXL345
void WriteDataLCM(Byte dataW);
void WriteCommandLCM(Byte CMD,Byte Attribc);
void DisplayOneChar(Byte X,Byte Y,Byte DData);
void conversion(Word temp_data);
void  Single_Write_ADXL345(Byte REG_Address,Byte REG_data);   //����д������
Byte Single_Read_ADXL345(Byte REG_Address);                   //������ȡ�ڲ��Ĵ�������
void  Multiple_Read_ADXL345();                                  //�����Ķ�ȡ�ڲ��Ĵ�������
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


//******������********
void main()
{ 
	void Delay20ms();	                   	//�ϵ���ʱ		                   
	uart();	
	Init_ADXL345();                 	//��ʼ��ADXL345
	while(1)                         	//ѭ��
	{ 
		Multiple_Read_ADXL345();       	//�����������ݣ��洢��BUF��
		Data_Convert();
        Data_Process();
		direction_judge();
		Delay20ms();                   	//��ʱ      
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
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms()
{
    Word n = 560;

    while (n--);
}
/**************************************
��ʼ�ź�
**************************************/
void ADXL345_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}
/**************************************
ֹͣ�ź�
**************************************/
void ADXL345_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}
/**************************************
����Ӧ���ź�
**************************************/
bit ADXL345_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}
/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void ADXL345_SendByte(Byte dat)
{
    Byte i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    ADXL345_RecvACK();
}
//��IIC���߽���һ���ֽ�����
Byte ADXL345_RecvByte()
{
    Byte i;
    Byte dat = 0;
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}
//******���ֽ�д��*******************************************
void Single_Write_ADXL345(Byte REG_Address,Byte REG_data)
{
    ADXL345_Start();                  //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    ADXL345_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
    ADXL345_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
    ADXL345_Stop();                   //����ֹͣ�ź�
}
//********���ֽڶ�ȡ*****************************************
Byte Single_Read_ADXL345(Byte REG_Address)
{  Byte REG_data;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ	
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=ADXL345_RecvByte();              //�����Ĵ�������
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
//��������ADXL345�ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
void Multiple_read_ADXL345(void)
{   Byte i;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_SendByte(0x32);                   //���ʹ洢��Ԫ��ַ����0x32��ʼ	
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           ADXL345_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //��ӦACK
       }
   }
    ADXL345_Stop();                          //ֹͣ�ź�
    Delay5ms();
}
//��ʼ��ADXL345��������Ҫ��ο�pdf�����޸�************************
void Init_ADXL345()
{
   Single_Write_ADXL345(0x31,0x0B);   //������Χ,����16g��13λģʽ
   Single_Write_ADXL345(0x2C,0x08);   //�����趨Ϊ12.5 �ο�pdf13ҳ
   Single_Write_ADXL345(0x2D,0x08);   //ѡ���Դģʽ   �ο�pdf24ҳ
   Single_Write_ADXL345(0x2E,0x80);   //ʹ�� DATA_READY �ж�
   Single_Write_ADXL345(0x1E,0x00);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
   Single_Write_ADXL345(0x1F,0x00);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
   Single_Write_ADXL345(0x20,0x05);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
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
void Data_Convert()						//��������λ���ݺϳ�Ϊһ��16λ����
{
  Wbuf[0]=BUF[1]<<8|BUF[0];
  Wbuf[1]=BUF[3]<<8|BUF[2];
  Wbuf[2]=BUF[5]<<8|BUF[4];
} 
void Data_Process()
{
   Word i=0;
    i=Wbuf[0]&JudgeP_M;	   //X�����ݴ���
  if(i==0x8000)	           //�����Ϊ����ʱ
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
  else					   //�����Ϊ����ʱ
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
  i=Wbuf[1]&JudgeP_M;		   //Y�����ݴ���
  if(i==0x8000)	           //�����Ϊ����ʱ
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
  else					   //�����Ϊ����ʱ
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
 