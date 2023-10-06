#ifndef __BMP280_I2C_H
#define __BMP280_I2C_H

#include "air001xx_hal.h"
#include "Delay.h"

void BMP280_GPIO_Config_OUT(void);
void BMP280_GPIO_Config_IN(void);

#define B_SDA_IN()  BMP280_GPIO_Config_IN();
#define B_SDA_OUT() BMP280_GPIO_Config_OUT();
// SDA = F0

#define B_IIC_SCL_High()  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET) //SCL_High
#define B_IIC_SCL_Low()   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET) //SCL_Low
#define B_IIC_SDA_High()  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET) //SDA_High
#define B_IIC_SDA_Low()   HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET) //SDA_Low
#define B_READ_SDA        HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_0)  //����SDA


void B_IIC_Init(void);                //��ʼ��IIC��IO��
void B_IIC_Start(void);               //����IIC��ʼ�ź�
void B_IIC_Stop(void);                //����IICֹͣ�ź�
void B_IIC_Send_Byte(uint8_t txd);         //IIC����һ���ֽ�
uint8_t B_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t B_IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void B_IIC_Ack(void);                 //IIC����ACK�ź�
void B_IIC_NAck(void);                //IIC������ACK�ź�



#endif









