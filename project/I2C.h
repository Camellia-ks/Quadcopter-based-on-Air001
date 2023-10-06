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
#define READ_SDA        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)  //����SDA


void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);               //����IIC��ʼ�ź�
void IIC_Stop(void);                //����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);         //IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void IIC_Ack(void);                 //IIC����ACK�ź�
void IIC_NAck(void);                //IIC������ACK�ź�



#endif









