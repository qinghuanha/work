#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h" 
#include "algorithm.h"
#include "blood.h"
#include "max30102.h"
#include "oled12832.h"
#include "store.h"
#include "event_groups.h"
/*
�궨��
*/ 
#define OLED_Wait_Max30102_EventBit (1<<2)
#define Max30102_EventBit  (1<<5)


/*
ȫ�ֱ�������
*/
extern BloodData g_blooddata; //Ѫ��������
float pitch,roll,yaw; 		//ŷ����
float Temp;   //�¶�
unsigned long Step;  //����
short gx=0,gy=0,gz=0;//������x,y,z���ԭʼ����(������)
short ax=0,ay=0,az=0;//������x,y,z���ԭʼ����(������)
unsigned char Data[16]="               ";//OLED����
u8 Max30102_Flag = 0;  //�Ƿ�����ָ����
/*
��������
*/
void 	prvSetupHardware(void);//Ӳ����ʼ��

/*
������
*/
void  startTask(void *param);//��ʼ�������ڴ�����������

void  MAX30102Task(void *param);//MAX30102����
void  OLEDTask(void *param);//OLED


/*
������
*/

TaskHandle_t  MAX30102TaskHandle;//MAX30102������
TaskHandle_t  OLEDTaskHandle;//OLED������


/*
�ź������¼���
*/
EventGroupHandle_t EventGroupHandler;	//�¼���־����


/*
������
*/
int main(void)
{
	prvSetupHardware();
	printf("This is HomeWork\r\n");
	xTaskCreate(startTask,"startTask",64,NULL,1,NULL);	
	vTaskStartScheduler();
	return 0;
}

/*
��������
*/
void 	prvSetupHardware(void){
	u8 res=0;
	EventGroupHandler=xEventGroupCreate();	 //�����¼���־��
  xEventGroupSetBits(EventGroupHandler,Max30102_EventBit); 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 
	delay_init();	    				//��ʱ������ʼ��	  
	uart_init(115200);					//��ʼ������
	I2C_UserConfig();           //I2C���߳�ʼ��
  Store_Init();
	oled_Write_Off();          //OLED��ʼ��           
	oled_Init();
	oled_Clear();
	oled_Write_On();

	Boot_Animation();          //��������
	
	
	MAX30102_GPIO();           // MAX30102��ʼ��       
	Max30102_reset();
	MAX30102_Config();

}

/*
startTask����������
*/
void  startTask(void *param)//��ʼ�������ڴ�����������
{
	  taskENTER_CRITICAL();
	
		xTaskCreate(MAX30102Task,"MAX30102Task",256,NULL,1,&MAX30102TaskHandle);//��������
    xTaskCreate(OLEDTask,"OLEDTask",256,NULL,1,&OLEDTaskHandle);
	  vTaskDelete(NULL);//ɾ���Լ�
	  taskEXIT_CRITICAL();   	
}



/*
MAX30102Task����������
*/
void  MAX30102Task(void *param)
{
	  while(1)
		{
			xEventGroupWaitBits(EventGroupHandler,Max30102_EventBit,pdTRUE,pdTRUE,portMAX_DELAY);			
			taskENTER_CRITICAL();		
      Max30102_Flag =  blood_Loop();
			printf("%d\r\n",Max30102_Flag);
			printf("HR:%d SPO2:%.1f\r\n",g_blooddata.heart,g_blooddata.SpO2);	
			xEventGroupSetBits(EventGroupHandler,OLED_Wait_Max30102_EventBit);	
			taskEXIT_CRITICAL(); 			
			vTaskDelay(10);
		}
		
}

/*
OLEDTask����������
*/
void  OLEDTask(void *param)
{
	int c=1;
	  while(1)
		{
		
			xEventGroupWaitBits(EventGroupHandler,OLED_Wait_Max30102_EventBit,pdTRUE,pdTRUE,portMAX_DELAY);			
			taskENTER_CRITICAL();	
			printf("OLED\r\n");
			oled_Clear();
     // sprintf(Data,"TEMP:%.2f",Temp);
 
     // oled_Display_8x16_Buffer(2,Data);
      if(Max30102_Flag!=0){
				delay_xms(500);
			  oled_Clear();
        sprintf(Data,"Heart Rate:%d",g_blooddata.heart);
        oled_Display_8x16_Buffer(0,Data);
        sprintf(Data,"SPO2:%.2f",g_blooddata.SpO2);
        oled_Display_8x16_Buffer(2,Data);
				Store_Data[c] = g_blooddata.heart;
				Store_Data[c+1] = g_blooddata.SpO2 ;
				c+=2;
        Store_Save();
				Max30102_Flag = 0;
			}
      else{
				delay_xms(500);
			  oled_Clear();
        sprintf(Data,"Heart Rate:--");
        oled_Display_8x16_Buffer(0,Data);
        sprintf(Data,"SPO2:--.--");
        oled_Display_8x16_Buffer(2,Data);
				Max30102_Flag = 0;				
			}			
			xEventGroupSetBits(EventGroupHandler,Max30102_EventBit);        			
			taskEXIT_CRITICAL(); 
			vTaskDelay(10);				
	
		}
		
}


