#ifndef __TCP_H
#define __TCP_H 			   
#include "stm32f10x.h"


/*
*���²�����Ҫ�û������޸Ĳ��ܲ����ù�
*/

#define User_ESP8266_SSID     "iPhone"          //wifi��
#define User_ESP8266_PWD      "12345678"      //wifi����

#define User_ESP8266_TCPServer_IP     "172.20.10.3"     //������IP
#define User_ESP8266_TCPServer_PORT   "8000"      //�������˿ں�


extern volatile uint8_t TcpClosedFlag;  //����״̬��־

void ESP8266_STA_TCPClient_Test(void);

#endif
