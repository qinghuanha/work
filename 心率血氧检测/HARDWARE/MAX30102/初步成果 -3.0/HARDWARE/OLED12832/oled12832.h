#ifndef _OLED12832_H
#define _OLED12832_H
#include "i2c.h"
#define OLED 0x78
#define CommondMask 0x00
#define DataMask 0x40


void oled_Init(void);//初始化
void oled_WriteCmd(unsigned char CMD);//写命令
void oled_WriteData(unsigned char data);//写数据
void oled_Clear(void);//清屏
void oled_Write_On(void);//开显示
void oled_Write_Off(void);//关显示
void oled_Light(unsigned char x);//亮度调节
void oled_Display8x16(unsigned char x,unsigned char y,unsigned char w);//在第x行第y列显示8*16字符
void oled_Display_8x16_Buffer(unsigned char row, unsigned char *str);//显示字符串 不超过64
void oled_Display_Number(unsigned char );
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_SetPos(unsigned char x, unsigned char y);//设置起始位置
void OLED_DrawPoint(u8 x,u8 y,u8 t);//设置一个点
void OLED_DrawCircle(u8 x,u8 y,u8 r);//画圆
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);//划线
void Boot_Animation(void);//开机动画

#endif 
