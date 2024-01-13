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
宏定义
*/ 
#define OLED_Wait_Max30102_EventBit (1<<2)
#define Max30102_EventBit  (1<<5)


/*
全局变量定义
*/
extern BloodData g_blooddata; //血氧和心率
float pitch,roll,yaw; 		//欧拉角
float Temp;   //温度
unsigned long Step;  //步数
short gx=0,gy=0,gz=0;//陀螺仪x,y,z轴的原始读数(带符号)
short ax=0,ay=0,az=0;//陀螺仪x,y,z轴的原始读数(带符号)
unsigned char Data[16]="               ";//OLED数据
u8 Max30102_Flag = 0;  //是否有手指靠近
/*
函数声明
*/
void 	prvSetupHardware(void);//硬件初始化

/*
任务函数
*/
void  startTask(void *param);//开始任务，用于创建其他任务

void  MAX30102Task(void *param);//MAX30102任务
void  OLEDTask(void *param);//OLED


/*
任务句柄
*/

TaskHandle_t  MAX30102TaskHandle;//MAX30102任务句柄
TaskHandle_t  OLEDTaskHandle;//OLED任务句柄


/*
信号量、事件组
*/
EventGroupHandle_t EventGroupHandler;	//事件标志组句柄


/*
主函数
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
函数定义
*/
void 	prvSetupHardware(void){
	u8 res=0;
	EventGroupHandler=xEventGroupCreate();	 //创建事件标志组
  xEventGroupSetBits(EventGroupHandler,Max30102_EventBit); 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);					//初始化串口
	I2C_UserConfig();           //I2C总线初始化
  Store_Init();
	oled_Write_Off();          //OLED初始化           
	oled_Init();
	oled_Clear();
	oled_Write_On();

	Boot_Animation();          //开机动画
	
	
	MAX30102_GPIO();           // MAX30102初始化       
	Max30102_reset();
	MAX30102_Config();

}

/*
startTask任务任务函数
*/
void  startTask(void *param)//开始任务，用于创建其他任务
{
	  taskENTER_CRITICAL();
	
		xTaskCreate(MAX30102Task,"MAX30102Task",256,NULL,1,&MAX30102TaskHandle);//创建任务
    xTaskCreate(OLEDTask,"OLEDTask",256,NULL,1,&OLEDTaskHandle);
	  vTaskDelete(NULL);//删除自己
	  taskEXIT_CRITICAL();   	
}



/*
MAX30102Task任务任务函数
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
OLEDTask任务任务函数
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


