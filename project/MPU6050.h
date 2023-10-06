#ifndef __MPU6050_H
#define __MPU6050_H

#include "air001xx_hal.h"
#include "Delay.h"




#include <stdint.h>
#include <stdbool.h>
//#include "usart.h"
#include "I2C.h"
#include <delay.h>
#include <math.h>

#define MPU6050_ADDR         0x68
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6b
#define MPU6050_PWR_MGMT_2   0x6c
#define MPU_ACCEL_XOUTH_REG  0x3b
#define MPU_GYRO_XOUTH_REG   0x43
#define MPU6050_TEMP_H       0x41
#define MPU6050_TEMP_L       0x42
#define MPU_DEVICE_ID_REG    0x75
typedef uint8_t u8;
typedef uint16_t u16;

#define PI 3.1415926535897932384626433832795

extern int16_t rawAccX, rawAccY, rawAccZ,rawGyroX, rawGyroY, rawGyroZ;
extern float gyroXoffset, gyroYoffset, gyroZoffset;
extern float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
extern float angleGyroX, angleGyroY, angleGyroZ,angleAccX, angleAccY, angleAccZ;
extern float angleX, angleY, angleZ;
extern uint32_t timer;
extern float accCoef;
extern float gyroCoef;

u8 MPU_Init(void);
void calcGyroOffsets(void);
void mpu_update(void);
u8 MPU_Set_Gyro_Fsr(u8 fsr);
u8 MPU_Set_Accel_Fsr(u8 fsr);
u8 MPU_Set_LPF(u16 lpf);
u8 MPU_Set_Rate(u16 rate);
short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(int16_t *gx,int16_t *gy,int16_t *gz);
u8 MPU_Get_Accelerometer(int16_t *ax,int16_t *ay,int16_t *az);
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf);
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf);
u8 MPU_Write_Byte(u8 reg,u8 data);
u8 MPU_Read_Byte(u8 reg);

#endif /* MPU6050_H_ */






