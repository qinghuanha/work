#include "oled12832.h"
#include "ASCII_8x16.h"
u8 OLED_GRAM[128][4];//�����Դ�
/*
�������ƣ� oled_WriteCmd
������unsigned char CMD
�������ã���oled��д��CMDָ��
��������ֵ����
*/
void oled_WriteCmd(unsigned char CMD){
  I2C_Start();
	I2C_Send_Byte(OLED);
	I2C_Writr_Ack();
	I2C_Send_Byte(CommondMask);
	I2C_Writr_Ack();
  I2C_Send_Byte(CMD);
	I2C_Writr_Ack();
  I2C_Stop();	
}

/*
�������ƣ� oled_WriteData
������unsigned char data
�������ã���oled��д��data����
��������ֵ����
*/
void oled_WriteData(unsigned char data){
	 I2C_Start();
	I2C_Send_Byte(OLED);
	I2C_Writr_Ack();
	I2C_Send_Byte(DataMask);
	I2C_Writr_Ack();
  I2C_Send_Byte(data);
	I2C_Writr_Ack();
  I2C_Stop();
}

/*
�������ƣ� oled_Clear
��������
�������ã�����
��������ֵ����
*/
void oled_Clear(void){
  for(unsigned char i=0 ;i<4;i++){
		oled_WriteCmd(0XB0|i);
		oled_WriteCmd(0X00);
		oled_WriteCmd(0X10);
		for(unsigned char j=0;j<128;j++){
			oled_WriteData(0x00);
		}
	}	
}

/*
�������ƣ� oled_Init
��������
�������ã�oled��ʼ��
��������ֵ����
*/
void oled_Init(void){
	delay_ms(200);
  oled_WriteCmd(0XA8);//���÷ֱ���
	oled_WriteCmd(0X1F);//128*64��0x3f 128*32 : 0x1f
	
	oled_WriteCmd(0XDA);//����COMӲ���������ã���Ӧ�ֱ���
	oled_WriteCmd(0X02);// 0x12:0.96-128*64 0x02:0.91-128*32
	

	oled_WriteCmd(0XD3);//������ʾƫ��
	oled_WriteCmd(0X00);//Ĭ������00û��ƫ��
	oled_WriteCmd(0X40);//������ʾ��ʼ 0-63
	oled_WriteCmd(0XA1);//��SEGMENT��ӳ�����IICͨѶ������0LEDҪ����0XA1
	oled_WriteCmd(0X81);//�Աȶ�����ָ��
	oled_WriteCmd(0XFF);//���ȵ���0X00-0XFF��ֵԽ������Խ������෴
	oled_WriteCmd(0XA4);//�����ѭRAM���� 0X05�������RAM����
	oled_WriteCmd(0XA6);//������ʾ��ʽ������ʾ��0XA6��������ʾ����0XA7��������ʾ
	oled_WriteCmd(0XD5);//������ʾʱ�ӷ�Ƶ/����Ƶ��
	oled_WriteCmd(0XF0);//���÷ֱ���ֵ
	oled_WriteCmd(0X8D);//��������
	oled_WriteCmd(0X14);//0x14:��������ʾ������ʱ��ʹ��,0x10:�������ڿ���ǰʹ��
	oled_WriteCmd(0XAE);//��ʾ�ر� 0XAF:��ʾ���� 0XAE:��ʾ�ر�
	oled_WriteCmd(0X20);//�����ڴ��ַģʽ������ģʽˮƽ/��ֱ/ҳѰַ(Ĭ��)
	oled_WriteCmd(0X02);//ˮƽ0x00/��ֱ0x01/ҳѰַ0x02(Ĭ��)
	oled_WriteCmd(0XB0);//ΪҳѰַģʽ����ҳ�濪����ַ0-7
	oled_WriteCmd(0XC8);//����COMɨ�跽ʽ0XC0���·�������/0XC8�����ҵ���
	oled_WriteCmd(0X00);//���õ��е�ַ
	oled_WriteCmd(0X10);//���ø��е�ַ
	oled_WriteCmd(0X40);//������ʾ��ʼ�� 0-63
	oled_WriteCmd(0XD9);//����Ԥ���ʱ��
	oled_WriteCmd(0X22);//���ʱ��
	oled_WriteCmd(0XDB);//����ȡ��ѡ�񼶱�
	oled_WriteCmd(0X20);//Ĭ��0x20 0.77xvcc
	oled_WriteCmd(0XAF);//��ʾ����	
}

/*
�������ƣ� oled_Write_On
��������
�������ã�oled����ʾ
��������ֵ����
*/
void oled_Write_On(void){
	oled_WriteCmd(0X8D);//��ʾ����
	oled_WriteCmd(0X24);//������ɱ�
	oled_WriteCmd(0XAF);//��ʾ����
}

/*
�������ƣ� oled_Write_Off
��������
�������ã�oled����ʾ
��������ֵ����
*/
void oled_Write_Off(void){
	oled_WriteCmd(0X8D);//��ʾ����
	oled_WriteCmd(0X24);//������ɱ�
	oled_WriteCmd(0XAE);//��ʾ����	
}

/*
�������ƣ� oled_Light
���������� x(0-255)
�������ã�oled���ȵ��ڶ�
��������ֵ����
*/
void oled_Light(unsigned char x){
	oled_WriteCmd(0x81);
  oled_WriteCmd(x);
}

/*
�������ƣ� oled_Display8x16
�������� x(0-3) �� y(0-7) ��ʾ�ַ� w
�������ã�oled��ʾ�ַ�
��������ֵ����
*/
void oled_Display8x16(unsigned char x,unsigned char y,unsigned char w){
  	unsigned char j,t,c=0;
	y=y+2;
	for(t=0;t<2;t++){
		oled_WriteCmd(0XB0|x);
		oled_WriteCmd(((y&0xf0)>>4)|0x10);
		oled_WriteCmd(y&0x0f);
		for(j=0;j<8;j++){
			oled_WriteData(ASCII_8x16[(w*16)-512+c]);
			c++;
		}x++;
	}
}

/*
�������ƣ� oled_Display_8x16_Buffer
�������� row(0-3) �� y(0-7) ��ʾ�ַ��� *str
�������ã�oled��ʾ�ַ���
��������ֵ����
*/
void oled_Display_8x16_Buffer(unsigned char row, unsigned char *str){
		u8 r=0;
	while(*str != '\0'){
		oled_Display8x16(row,r*8,*str++);
		r++;
    }	
}


/*
�����Դ�
*/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<4;i++)  
	{  
		oled_WriteCmd(0xb0+i);  //����ҳ��ַ��0~7��
		oled_WriteCmd(0x00);   // ������ʾλ�á��е͵�ַ
		oled_WriteCmd(0x10);    //������ʾλ�á��иߵ�ַ	
		for(n=0;n<128;n++)
			oled_WriteData(OLED_GRAM[n][i]); 
	}   
}


/*
��������--�Դ�汾
*/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<4;i++)
		for(n=0;n<128;n++)
			OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//������ʾ
}

/*
������ʼλ��
*/
void OLED_SetPos(unsigned char x, unsigned char y) 
{ 
    oled_WriteCmd(0xB0 + y);
    oled_WriteCmd(((x & 0xF0) >> 4) | 0x10);
    oled_WriteCmd((x & 0x0F) | 0x01);
}

/*
����һ����
*/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>31)
		return;//������Χ��.
	pos = 7-y/8;            //�ڼ�ҳ  ��ʵ�Ƿ�������Ȼ��       Ȼ��ᷭת
	bx = y%8;
	temp = 1<<(7-bx);       //����ʹ��� 1 ������y��ƥ��
	if(t)
		OLED_GRAM[x][pos] |= temp;
	else 
		OLED_GRAM[x][pos] &= ~temp;	
}
/*
��������
*/
void Boot_Animation(void)
{

	oled_Display8x16(1,8,'g');
	oled_Display8x16(1,16,'r');
	oled_Display8x16(1,24,'o');
	oled_Display8x16(1,32,'u');
	oled_Display8x16(1,40,'p');
	oled_Display8x16(1,70,'I');
	oled_Display8x16(1,78,'I');
	oled_Display8x16(1,86,'I');
	delay_ms(1000);
}
