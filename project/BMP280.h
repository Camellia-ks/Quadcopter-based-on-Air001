#ifndef __BMP280_H
#define __BMP280_H

#include "air001xx_hal.h"
#include "Delay.h"
#include "BMP280_I2C.h"





#include "stdbool.h"
#include <math.h>
#include "delay.h"
#include "usart.h"

#define BMP280_ADDRESS						0x76		//���豸��ַ
#define BMP280_RESET_VALUE					0xB6		//��λ�Ĵ���д��ֵ

#define BMP280_CHIPID_REG                    0xD0  /*Chip ID Register */
#define BMP280_RESET_REG                     0xE0  /*Softreset Register */
#define BMP280_STATUS_REG                    0xF3  /*Status Register */
#define BMP280_CTRLMEAS_REG                  0xF4  /*Ctrl Measure Register */
#define BMP280_CONFIG_REG                    0xF5  /*Configuration Register */
#define BMP280_PRESSURE_MSB_REG              0xF7  /*Pressure MSB Register */
#define BMP280_PRESSURE_LSB_REG              0xF8  /*Pressure LSB Register */
#define BMP280_PRESSURE_XLSB_REG             0xF9  /*Pressure XLSB Register */
#define BMP280_TEMPERATURE_MSB_REG           0xFA  /*Temperature MSB Reg */
#define BMP280_TEMPERATURE_LSB_REG           0xFB  /*Temperature LSB Reg */
#define BMP280_TEMPERATURE_XLSB_REG          0xFC  /*Temperature XLSB Reg */
//״̬�Ĵ���ת����־
#define	BMP280_MEASURING					0x01
#define	BMP280_IM_UPDATE					0x08


/*calibration parameters */
#define BMP280_DIG_T1_LSB_REG                0x88
#define BMP280_DIG_T1_MSB_REG                0x89
#define BMP280_DIG_T2_LSB_REG                0x8A
#define BMP280_DIG_T2_MSB_REG                0x8B
#define BMP280_DIG_T3_LSB_REG                0x8C
#define BMP280_DIG_T3_MSB_REG                0x8D
#define BMP280_DIG_P1_LSB_REG                0x8E
#define BMP280_DIG_P1_MSB_REG                0x8F
#define BMP280_DIG_P2_LSB_REG                0x90
#define BMP280_DIG_P2_MSB_REG                0x91
#define BMP280_DIG_P3_LSB_REG                0x92
#define BMP280_DIG_P3_MSB_REG                0x93
#define BMP280_DIG_P4_LSB_REG                0x94
#define BMP280_DIG_P4_MSB_REG                0x95
#define BMP280_DIG_P5_LSB_REG                0x96
#define BMP280_DIG_P5_MSB_REG                0x97
#define BMP280_DIG_P6_LSB_REG                0x98
#define BMP280_DIG_P6_MSB_REG                0x99
#define BMP280_DIG_P7_LSB_REG                0x9A
#define BMP280_DIG_P7_MSB_REG                0x9B
#define BMP280_DIG_P8_LSB_REG                0x9C
#define BMP280_DIG_P8_MSB_REG                0x9D
#define BMP280_DIG_P9_LSB_REG                0x9E
#define BMP280_DIG_P9_MSB_REG                0x9F


//BMP����ģʽ
typedef enum {
	BMP280_SLEEP_MODE = 0x0,
	BMP280_FORCED_MODE = 0x1,	//����˵0x2
	BMP280_NORMAL_MODE = 0x3
} BMP280_WORK_MODE;

//BMPѹ������������
typedef enum 
{
	BMP280_P_MODE_SKIP = 0x0,	/*skipped*/
	BMP280_P_MODE_1,			/*x1*/
	BMP280_P_MODE_2,			/*x2*/
	BMP280_P_MODE_3,			/*x4*/
	BMP280_P_MODE_4,			/*x8*/
	BMP280_P_MODE_5			    /*x16*/
} BMP280_P_OVERSAMPLING;	

//BMP�¶ȹ���������
typedef enum {
	BMP280_T_MODE_SKIP = 0x0,	/*skipped*/
	BMP280_T_MODE_1,			/*x1*/
	BMP280_T_MODE_2,			/*x2*/
	BMP280_T_MODE_3,			/*x4*/
	BMP280_T_MODE_4,			/*x8*/
	BMP280_T_MODE_5			    /*x16*/
} BMP280_T_OVERSAMPLING;
									
//IIR�˲���ʱ�䳣��
typedef enum {
	BMP280_FILTER_OFF = 0x0,	/*filter off*/
	BMP280_FILTER_MODE_1,		/*0.223*ODR*/	/*x2*/
	BMP280_FILTER_MODE_2,		/*0.092*ODR*/	/*x4*/
	BMP280_FILTER_MODE_3,		/*0.042*ODR*/	/*x8*/
	BMP280_FILTER_MODE_4		/*0.021*ODR*/	/*x16*/
} BMP280_FILTER_COEFFICIENT;

//����ʱ��
typedef enum {
	BMP280_T_SB1 = 0x0,	    /*0.5ms*/
	BMP280_T_SB2,			/*62.5ms*/
	BMP280_T_SB3,			/*125ms*/
	BMP280_T_SB4,			/*250ms*/
	BMP280_T_SB5,			/*500ms*/
	BMP280_T_SB6,			/*1000ms*/
	BMP280_T_SB7,			/*2000ms*/
	BMP280_T_SB8,			/*4000ms*/
} BMP280_T_SB;


typedef struct  
{
	/* T1~P9 Ϊ����ϵ�� */
	uint16_t T1;
	int16_t	T2;
	int16_t	T3;
	uint16_t P1;
	int16_t	P2;
	int16_t	P3;
	int16_t	P4;
	int16_t	P5;
	int16_t	P6;
	int16_t	P7;
	int16_t	P8;
	int16_t	P9;
} BMP280;


typedef struct
{
	BMP280_P_OVERSAMPLING P_Osample;
	BMP280_T_OVERSAMPLING T_Osample;
	BMP280_WORK_MODE		WORKMODE;
} BMP_OVERSAMPLE_MODE;
	
typedef struct
{
	BMP280_T_SB 				T_SB;
	BMP280_FILTER_COEFFICIENT 	FILTER_COEFFICIENT;
	FunctionalState				SPI_EN;
} BMP_CONFIG;

extern BMP280* bmp280;


uint8_t BMP280_ReadID(void);
void Bmp_Init(void);
void BMP280_Set_TemOversamp(BMP_OVERSAMPLE_MODE * Oversample_Mode);
void BMP280_Set_Standby_FILTER(BMP_CONFIG * BMP_Config);
uint8_t  BMP280_GetStatus(uint8_t status_flag);
long BMP280_Get_Pressure(void);
#endif




