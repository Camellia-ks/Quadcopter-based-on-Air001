#include "air001xx_hal.h"
#include "NRF24L01.h"
#include "Delay.h"
#include "I2C.h"
#include "MPU6050.h"
#include "usart.h"
#include "air001_Core_Board.h"
#include "MPU6050_TIMER.h"
#include "PWM.h"
#include "BMP280.h"
#include "BMP280_I2C.h"


void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)
{
  TIMx->CCR1 = Compare1;
}
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2)
{
  TIMx->CCR2 = Compare2;
}
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3)
{
  TIMx->CCR3 = Compare3;
}
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4)
{
  TIMx->CCR4 = Compare4;
}

int16_t rawAccX, rawAccY, rawAccZ,rawGyroX, rawGyroY, rawGyroZ;
float gyroXoffset, gyroYoffset, gyroZoffset;
float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
float angleGyroX, angleGyroY, angleGyroZ,angleAccX, angleAccY, angleAccZ;
float angleX, angleY, angleZ;

uint32_t timer;

double P[2][2] = {{ 1, 0 },{ 0, 1 }};
double Pdot[4] ={ 0,0,0,0};
//static const double Q_angle=0.001, Q_gyro=0.003, R_angle=0.5,dtt=0.005,C_0 = 1;
//double q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
uint32_t counterValue;
//int BMP_Temperature;
int main(void)
{
	HAL_Init();
	PWM_Init();
	BSP_USART_Config();
	
	IIC_Init();
	MPU_Init();
	Timer_init();
  calcGyroOffsets();
	
	Bmp_Init();
	B_IIC_Init();
	printf("\r\nBMP280 ID:0x%02x",BMP280_ReadID());

	
	//TIM_SetCompare1(TIM3,10);
	while (1)
	{
		//mpu_update();
		
		//while(BMP280_GetStatus(BMP280_MEASURING) != RESET);
		//while(BMP280_GetStatus(BMP280_IM_UPDATE) != RESET);
		//BMP_Temperature = BMP280_Get_Temperature();
		printf("\r\nPressure %ld", BMP280_Get_Pressure());
		//Delay_ms(200);
		
		
	}
}


//int main()
//{
//	/*Parameter Configuration*/
//	long BMP_Pressure;
//	/*Init*/
//	delay_init(168);
//	USART_Config();
//	MY_I2C_GPIO_Config();
//	Bmp_Init();
//	printf("\r\nBMP280大气压传感器实验");
//	delay_ms(50);
//	/*Configuration Operation*/
//	printf("\r\nBMP280 ID:0x%02x",BMP280_ReadID());	
//	delay_ms(2000);	//给你看一下ID
//	/*LOOP*/
//	while(1)
//	{
//		while(BMP280_GetStatus(BMP280_MEASURING) != RESET);
//		while(BMP280_GetStatus(BMP280_IM_UPDATE) != RESET);
//		BMP_Temperature = BMP280_Get_Temperature();
//		printf("\r\nPressure %ld",BMP_Pressure);
//		delay_ms(200);
//	}
//}


