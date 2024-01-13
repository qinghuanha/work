#ifndef _OLED12832_H
#define _OLED12832_H
#include "i2c.h"
#define OLED 0x78
#define CommondMask 0x00
#define DataMask 0x40


void oled_Init(void);//��ʼ��
void oled_WriteCmd(unsigned char CMD);//д����
void oled_WriteData(unsigned char data);//д����
void oled_Clear(void);//����
void oled_Write_On(void);//����ʾ
void oled_Write_Off(void);//����ʾ
void oled_Light(unsigned char x);//���ȵ���
void oled_Display8x16(unsigned char x,unsigned char y,unsigned char w);//�ڵ�x�е�y����ʾ8*16�ַ�
void oled_Display_8x16_Buffer(unsigned char row, unsigned char *str);//��ʾ�ַ��� ������64
void oled_Display_Number(unsigned char );
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_SetPos(unsigned char x, unsigned char y);//������ʼλ��
void OLED_DrawPoint(u8 x,u8 y,u8 t);//����һ����
void OLED_DrawCircle(u8 x,u8 y,u8 r);//��Բ
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);//����
void Boot_Animation(void);//��������

#endif 
