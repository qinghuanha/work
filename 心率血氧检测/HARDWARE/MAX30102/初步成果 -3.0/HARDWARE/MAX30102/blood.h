#ifndef _BLOOD_H
#define _BLOOD_H
#include "sys.h"                  // Device header
#include "max30102.h"
#include "algorithm.h"
#include "math.h"
extern unsigned char Display_Init_flag;
extern unsigned int Last_time;
typedef enum
{
	BLD_NORMAL,		//����
	BLD_ERROR,		//������
	
}BloodState;//ѪҺ״̬

typedef struct
{
	int 		heart;		//��������
	float 			SpO2;			//Ѫ������
}BloodData;


void blood_data_translate(void);
void blood_data_update(void);
u8 blood_Loop(void);

#endif


