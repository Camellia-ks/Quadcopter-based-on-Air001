#include "BMP280_I2C.h"

void BMP280_GPIO_Config_OUT(void)
{
	GPIO_InitTypeDef GPIO_BMP280 = {
		.Pin = GPIO_PIN_0,
		.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOF_CLK_ENABLE();
	HAL_GPIO_Init(GPIOF, &GPIO_BMP280);
}

void BMP280_GPIO_Config_IN(void)
{
	GPIO_InitTypeDef GPIO_BMP280 = {
		.Pin = GPIO_PIN_0,
		.Mode = GPIO_MODE_INPUT,
	};
	__HAL_RCC_GPIOF_CLK_ENABLE();
	HAL_GPIO_Init(GPIOF, &GPIO_BMP280);
}

void B_IIC_Init(void)
{
	
	GPIO_InitTypeDef GPIO_BMP280 = {
		.Pin = GPIO_PIN_1 + GPIO_PIN_0,
		.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOF_CLK_ENABLE();
	HAL_GPIO_Init(GPIOF, &GPIO_BMP280);

  B_IIC_SCL_High();
  B_IIC_SDA_High();

}

void B_IIC_Start(void)//SDA 10 SCL 010
{
    B_SDA_OUT();     //sda线输出
    B_IIC_SCL_High();
    B_IIC_SDA_High();
    Delay_us(4);
    B_IIC_SDA_Low();//START:when CLK is high,DATA change form high to low
    Delay_us(4);
    B_IIC_SCL_Low();//钳住I2C总线，准备发送或接收数据
}

void B_IIC_Stop(void)//SDA 01 SCL 01
{
    B_SDA_OUT();//sda线输出
    B_IIC_SCL_Low();//STOP:when CLK is high DATA change form low to high
    B_IIC_SDA_Low();
    Delay_us(4);
    B_IIC_SCL_High();
    B_IIC_SDA_High();//发送I2C总线结束信号
    Delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t B_IIC_Wait_Ack(void)//
{
    uint8_t cy;
    B_SDA_IN();      //SDA设置为输入
    B_IIC_SCL_High();Delay_us(10);
    B_IIC_SDA_High();Delay_us(10);
    if(B_READ_SDA)
    {
        cy=1;
        B_IIC_SCL_Low();
        return cy;
    }
    else
    {
        cy=0;
    }
    B_IIC_SCL_Low();//时钟输出0
    return cy;
}
//产生ACK应答
void B_IIC_Ack(void)
{
    B_IIC_SCL_Low();
    B_SDA_OUT();
    B_IIC_SDA_Low();
    Delay_us(2);
    B_IIC_SCL_High();
    Delay_us(2);
    B_IIC_SCL_Low();
}
//不产生ACK应答
void B_IIC_NAck(void)
{
    B_IIC_SCL_Low();
    B_SDA_OUT();
    B_IIC_SDA_High();
    Delay_us(2);
    B_IIC_SCL_High();
    Delay_us(2);
    B_IIC_SCL_Low();
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void B_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    B_SDA_OUT();
    B_IIC_SCL_Low();//拉低时钟开始数据传输
    Delay_us(2);
    for(t=0;t<8;t++)
    {
        if(txd&0x80)
        {
            B_IIC_SDA_High();Delay_us(2);
        }
        else
        {
            B_IIC_SDA_Low();Delay_us(2);
        }
        txd<<=1;
        B_IIC_SCL_High();
        Delay_us(4);
        B_IIC_SCL_Low();
        Delay_us(2);
    }
        Delay_us(2);

}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t B_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    B_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        B_IIC_SCL_Low();
        Delay_us(2);
        B_IIC_SCL_High();
        receive<<=1;
        if(B_READ_SDA)
            receive++;
        Delay_us(2);
    }
    if (!ack)
        B_IIC_NAck();//发送nACK
    else
        B_IIC_Ack(); //发送ACK
    return receive;


}



