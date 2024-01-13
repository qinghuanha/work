#include "bsp_buzzer.h"
#include "tim.h"

extern TIM_HandleTypeDef htim4;

/**
* NAME: void promising_young(void)
* FUNCTION : promising_young
*/
void promising_young(void)
{
    int promising_young[]=
    {
        H1,50

    };

    int length = sizeof(promising_young)/sizeof(promising_young[0]);//�������鳤��
    for(int i=0; i<(length/2); i++)//ȡ��������
    {
        buzzer_on(promising_young[2*i], 200);
        HAL_Delay(10*promising_young[2*i+1]);//������ʱ�䶼����5��һ��Ϊ500΢�룬��ֵ"5"�ɵ�����ֻ�ǲ��ŵ������������ѣ��е���������Ƶ����ͺ���
		
    }
	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
}

/**
* NAME: void Solitary_brave(void)
* FUNCTION : Solitary_brave
*/
void Solitary_brave(void)
{
	int16_t solitary_brave[]=
	{
		H1,50
		
	};
	int length = sizeof(solitary_brave)/sizeof(solitary_brave[0]);
	for(uint8_t i=0;i<(length/2);i++)
	{
		buzzer_on(solitary_brave[i*2],500);
		HAL_Delay(5*solitary_brave[i*2+1]);
	}
	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
}

/**
* NAME: void Wind_Rises(void)
* FUNCTION : Wind_Rises
*/
void Wind_Rises(void)
{
	int wind_rise[]=
	{	
		H1,50		
	};
	int length = sizeof(wind_rise)/sizeof(wind_rise[0]);
	
	for(int i=0;i<(length/2);i++)
	{
		buzzer_on(wind_rise[i*2],260);
		HAL_Delay(wind_rise[i*2+1]*5);
	}
	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
}

void Wind_Rises1(void)
{
	int wind_rise1[]=
	{	
		H1,50		
	};
	int length = sizeof(wind_rise1)/sizeof(wind_rise1[0]);
	
	for(int i=0;i<(length/2);i++)
	{
		buzzer_on(wind_rise1[i*2],260);
		HAL_Delay(wind_rise1[i*2+1]*5);
	}
	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
}

void Wind_Rises2(void)
{
	int wind_rise2[]=
	{	
		H1,50		
	};
	int length = sizeof(wind_rise2)/sizeof(wind_rise2[0]);
	
	for(int i=0;i<(length/2);i++)
	{
		buzzer_on(wind_rise2[i*2],260);
		HAL_Delay(wind_rise2[i*2+1]*5);
	}
	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
}

void Wind_Rises3(void)
{
	int wind_rise3[]=
	{	
		H7,50		
	};
	int length = sizeof(wind_rise3)/sizeof(wind_rise3[0]);
	
	for(int i=0;i<(length/2);i++)
	{
		buzzer_on(wind_rise3[i*2],260);
		HAL_Delay(wind_rise3[i*2+1]*5);
	}
	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
}

void buzzer_on(uint16_t psc, uint16_t pwm)
{
    __HAL_TIM_PRESCALER(&htim4, psc);
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);

}
void buzzer_off(void)
{
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 0);
}
