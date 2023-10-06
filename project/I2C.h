#ifndef __I2C_H
#define __I2C_H

#include "air001xx_hal.h"
#include "Delay.h"

void MPU6050_GPIO_Config_OUT(void);
void MPU6050_GPIO_Config_IN(void);

#define SDA_IN()  MPU6050_GPIO_Config_IN();
#define SDA_OUT() MPU6050_GPIO_Config_OUT();
// SDA = B0

#define IIC_SCL_High()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET) //SCL_High
#define IIC_SCL_Low()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET) //SCL_Low
#define IIC_SDA_High()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET) //SDA_High
#define IIC_SDA_Low()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET) //SDA_Low
#define READ_SDA        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)  //输入SDA


void IIC_Init(void);                //初始化IIC的IO口
void IIC_Start(void);               //发送IIC开始信号
void IIC_Stop(void);                //发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);         //IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void);              //IIC等待ACK信号
void IIC_Ack(void);                 //IIC发送ACK信号
void IIC_NAck(void);                //IIC不发送ACK信号



#endif









