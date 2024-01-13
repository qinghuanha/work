#include "oled12832.h"
#include "ASCII_8x16.h"
u8 OLED_GRAM[128][4];//虚拟显存
/*
函数名称： oled_WriteCmd
参数：unsigned char CMD
函数作用：向oled中写入CMD指令
函数返回值：无
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
函数名称： oled_WriteData
参数：unsigned char data
函数作用：向oled中写入data数据
函数返回值：无
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
函数名称： oled_Clear
参数：无
函数作用：清屏
函数返回值：无
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
函数名称： oled_Init
参数：无
函数作用：oled初始化
函数返回值：无
*/
void oled_Init(void){
	delay_ms(200);
  oled_WriteCmd(0XA8);//设置分辨率
	oled_WriteCmd(0X1F);//128*64：0x3f 128*32 : 0x1f
	
	oled_WriteCmd(0XDA);//设置COM硬件引脚配置，适应分辨率
	oled_WriteCmd(0X02);// 0x12:0.96-128*64 0x02:0.91-128*32
	

	oled_WriteCmd(0XD3);//设置显示偏移
	oled_WriteCmd(0X00);//默认设置00没有偏移
	oled_WriteCmd(0X40);//设置显示开始 0-63
	oled_WriteCmd(0XA1);//段SEGMENT重映射对于IIC通讯四引脚0LED要设置0XA1
	oled_WriteCmd(0X81);//对比度设置指令
	oled_WriteCmd(0XFF);//亮度调节0X00-0XFF数值越大亮度越大否则相反
	oled_WriteCmd(0XA4);//输出遵循RAM内容 0X05输出忽略RAM内容
	oled_WriteCmd(0XA6);//设置显示方式正常显示（0XA6）正常显示：（0XA7）反向显示
	oled_WriteCmd(0XD5);//设置显示时钟分频/振荡器频率
	oled_WriteCmd(0XF0);//设置分辨率值
	oled_WriteCmd(0X8D);//充电泵设置
	oled_WriteCmd(0X14);//0x14:允许在显示开启的时候使用,0x10:不允许在开启前使用
	oled_WriteCmd(0XAE);//显示关闭 0XAF:显示开启 0XAE:显示关闭
	oled_WriteCmd(0X20);//设置内存地址模式有三种模式水平/垂直/页寻址(默认)
	oled_WriteCmd(0X02);//水平0x00/垂直0x01/页寻址0x02(默认)
	oled_WriteCmd(0XB0);//为页寻址模式设置页面开启地址0-7
	oled_WriteCmd(0XC8);//设置COM扫描方式0XC0上下反置左到右/0XC8正常右到左
	oled_WriteCmd(0X00);//设置低列地址
	oled_WriteCmd(0X10);//设置高列地址
	oled_WriteCmd(0X40);//设置显示开始行 0-63
	oled_WriteCmd(0XD9);//设置预充电时期
	oled_WriteCmd(0X22);//充电时间
	oled_WriteCmd(0XDB);//设置取消选择级别
	oled_WriteCmd(0X20);//默认0x20 0.77xvcc
	oled_WriteCmd(0XAF);//显示开启	
}

/*
函数名称： oled_Write_On
参数：无
函数作用：oled开显示
函数返回值：无
*/
void oled_Write_On(void){
	oled_WriteCmd(0X8D);//显示开启
	oled_WriteCmd(0X24);//开启电荷泵
	oled_WriteCmd(0XAF);//显示开启
}

/*
函数名称： oled_Write_Off
参数：无
函数作用：oled开显示
函数返回值：无
*/
void oled_Write_Off(void){
	oled_WriteCmd(0X8D);//显示开启
	oled_WriteCmd(0X24);//开启电荷泵
	oled_WriteCmd(0XAE);//显示开启	
}

/*
函数名称： oled_Light
参数：亮度 x(0-255)
函数作用：oled亮度调节二
函数返回值：无
*/
void oled_Light(unsigned char x){
	oled_WriteCmd(0x81);
  oled_WriteCmd(x);
}

/*
函数名称： oled_Display8x16
参数：行 x(0-3) 列 y(0-7) 显示字符 w
函数作用：oled显示字符
函数返回值：无
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
函数名称： oled_Display_8x16_Buffer
参数：行 row(0-3) 列 y(0-7) 显示字符串 *str
函数作用：oled显示字符串
函数返回值：无
*/
void oled_Display_8x16_Buffer(unsigned char row, unsigned char *str){
		u8 r=0;
	while(*str != '\0'){
		oled_Display8x16(row,r*8,*str++);
		r++;
    }	
}


/*
更新显存
*/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<4;i++)  
	{  
		oled_WriteCmd(0xb0+i);  //设置页地址（0~7）
		oled_WriteCmd(0x00);   // 设置显示位置—列低地址
		oled_WriteCmd(0x10);    //设置显示位置—列高地址	
		for(n=0;n<128;n++)
			oled_WriteData(OLED_GRAM[n][i]); 
	}   
}


/*
清屏函数--显存版本
*/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<4;i++)
		for(n=0;n<128;n++)
			OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显示
}

/*
设置起始位置
*/
void OLED_SetPos(unsigned char x, unsigned char y) 
{ 
    oled_WriteCmd(0xB0 + y);
    oled_WriteCmd(((x & 0xF0) >> 4) | 0x10);
    oled_WriteCmd((x & 0x0F) | 0x01);
}

/*
设置一个点
*/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>31)
		return;//超出范围了.
	pos = 7-y/8;            //第几页  其实是反过来，然后       然后会翻转
	bx = y%8;
	temp = 1<<(7-bx);       //这里使这个 1 与具体的y相匹配
	if(t)
		OLED_GRAM[x][pos] |= temp;
	else 
		OLED_GRAM[x][pos] &= ~temp;	
}
/*
开机动画
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
