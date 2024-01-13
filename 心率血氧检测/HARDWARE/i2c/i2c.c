#include "i2c.h"

static void i2c_Delay(void)
{
	uint8_t i=6;
	while(i--);
}


void I2C_UserConfig(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = SDA|SCL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(I2C_Prot,&GPIO_InitStructure);
}
void I2C_SDA_Mode(u8 addr){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(addr){ //1 OUT
			
		GPIO_InitStructure.GPIO_Pin   = SDA;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(I2C_Prot,&GPIO_InitStructure);	
	}
	else{     //0 INPUT
		
		GPIO_InitStructure.GPIO_Pin   = SDA;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
		GPIO_Init(I2C_Prot,&GPIO_InitStructure);
	}
}
void I2C_Start(void){
	
	I2C_SDA_Mode(OUT);
	
	SCL_High;
	SDA_High;
	i2c_Delay();
	
	SDA_Low;
	i2c_Delay();
	SCL_Low;
}
void I2C_Stop(void){
	
	I2C_SDA_Mode(OUT);
	
	SDA_Low;
	i2c_Delay();
	
	SCL_High;
	i2c_Delay();
	SDA_High;
}
u8 I2C_Writr_Ack(void){
	
	u8 TimeAck;
	
	I2C_SDA_Mode(INPUT);
	
	SCL_High;
	i2c_Delay();
	
	while(GPIO_ReadInputDataBit(I2C_Prot,SDA)){
		
		if(++TimeAck > 250){
			
			I2C_Stop();return 1;
		}
	}
	SCL_Low;
	i2c_Delay();
	
	return 0;
}
void I2C_Send_Byte(u8 Data){
	
	SCL_Low;
	i2c_Delay();
	
	for(u8 i=0;i<8;i++){
		
		I2C_SDA_Mode(OUT); // *
		
		if((Data<<i) & 0x80) SDA_High; //H / L  1000 0000 
		else SDA_Low;
		
		SCL_High;
	  i2c_Delay();
		SCL_Low;
	  i2c_Delay();
	}
}
u8 I2C_Read_Data(void){
	
	u8 Data;
	
	for(u8 i=0;i<8;i++){
		
		I2C_SDA_Mode(INPUT); // *
		
		SCL_High;
	  i2c_Delay();
		
		Data <<= 1; // 0000 0001 1000 0000 << 1
		
		if(GPIO_ReadInputDataBit(I2C_Prot,SDA) == 1){
			
			Data |= 0x01;
		}
		
		SCL_Low;
		i2c_Delay();
	}
	
	return Data;
}

void I2C_Sende_Ack(u8 ack){
	
	I2C_SDA_Mode(OUT);
	
	if(ack)
		SDA_High;
	else
		SDA_Low;
	
	SCL_High;
	i2c_Delay();
	SCL_Low;
	i2c_Delay();
}


uint8_t I2C_Write_Byte(uint8_t device_addr,uint8_t register_addr,uint8_t data)
{
	I2C_Start();
	I2C_Send_Byte(device_addr+0);
	I2C_Writr_Ack();
	I2C_Send_Byte(register_addr);   
	I2C_Writr_Ack();
	I2C_Send_Byte(data);
	I2C_Writr_Ack(); 
	I2C_Stop();
	return 1;
}

uint8_t I2C_Read_Byte(uint8_t device_addr,uint8_t register_addr)
{
	uint8_t read_data;
	I2C_Start();
	I2C_Send_Byte(device_addr+0);
	I2C_Writr_Ack(); 
	I2C_Send_Byte(register_addr);
	I2C_Writr_Ack();
	I2C_Start();
	I2C_Send_Byte(device_addr+1);
  I2C_Writr_Ack();
	read_data = I2C_Read_Data();
	I2C_Sende_Ack(1);
	I2C_Stop();
	return read_data;
}

uint8_t I2C_Write_Array(uint8_t device_addr,uint16_t register_addr,u8 *Data,uint16_t Num)
{
	uint16_t i;
	I2C_Start();
	I2C_Send_Byte(device_addr+0);
  I2C_Writr_Ack();
	I2C_Send_Byte(register_addr);
  I2C_Writr_Ack();
	I2C_Start();
	I2C_Send_Byte(device_addr+1);
  I2C_Writr_Ack();
	for(i=0;i<Num;i++)
	{
		I2C_Send_Byte(*Data++);
    I2C_Writr_Ack();
	}
	I2C_Stop();
	return 1;
}

uint8_t I2C_Read_Array(uint8_t device_addr,uint16_t register_addr,uint8_t *Data,uint16_t Num)
{
	uint16_t i;
	I2C_Start();
	I2C_Send_Byte(device_addr+0);
  I2C_Writr_Ack();
	I2C_Send_Byte(register_addr);
  I2C_Writr_Ack();
	I2C_Start();
	I2C_Send_Byte(device_addr+1);
  I2C_Writr_Ack();
	for(i=0;i<Num;i++)
	{
		*Data++ = I2C_Read_Data();
		if(i==Num-1)
	    I2C_Sende_Ack(1);
		else
		  I2C_Sende_Ack(0);
	}
	I2C_Stop();
	return 1;
}
