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
	BLD_NORMAL,		//正常
	BLD_ERROR,		//侦测错误
	
}BloodState;//血液状态

typedef struct
{
	int 		heart;		//心率数据
	float 			SpO2;			//血氧数据
}BloodData;


void blood_data_translate(void);
void blood_data_update(void);
u8 blood_Loop(void);

#endif


