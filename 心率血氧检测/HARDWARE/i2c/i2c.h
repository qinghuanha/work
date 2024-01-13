#ifndef _I2C_H_
#define _I2C_H_

#include "sys.h"
#include "delay.h"
#define SDA GPIO_Pin_7
#define SCL GPIO_Pin_6
#define I2C_Prot GPIOB

#define SDA_High GPIO_SetBits(I2C_Prot,SDA)
#define SDA_Low GPIO_ResetBits(I2C_Prot,SDA)

#define SCL_High GPIO_SetBits(I2C_Prot,SCL)
#define SCL_Low GPIO_ResetBits(I2C_Prot,SCL)

#define OUT 1
#define INPUT 0

void I2C_UserConfig(void);
void I2C_Start(void);
void I2C_Stop(void);
u8 I2C_Writr_Ack(void);
void I2C_Send_Byte(u8 Data);
u8 I2C_Read_Data(void);
void I2C_Sende_Ack(u8 ack);

uint8_t I2C_Read_Byte(uint8_t device_addr,uint8_t register_addr);
uint8_t I2C_Write_Byte(uint8_t device_addr,uint8_t register_addr,uint8_t data);

uint8_t I2C_Read_Array(uint8_t device_addr,u16 register_addr,uint8_t *Data,u16 Num);
uint8_t I2C_Write_Array(uint8_t device_addr,u16 register_addr,u8 *Data,u16 Num);
static void i2c_Delay(void);
#endif
