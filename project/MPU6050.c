#include "MPU6050.h"
#include <stdlib.h>
#include <math.h>

float gyroCoef,accCoef;
uint32_t preInterval;
float interval;
u8 MPU_Init(void)
{
    accCoef = 0.02;
    gyroCoef = 0.98;

    IIC_Init();
    MPU_Write_Byte(MPU6050_SMPLRT_DIV, 0x00);
    MPU_Write_Byte(MPU6050_CONFIG, 0x00);
    MPU_Write_Byte(MPU6050_GYRO_CONFIG, 0x08);
    MPU_Write_Byte(MPU6050_ACCEL_CONFIG, 0x00);
    MPU_Write_Byte(MPU6050_PWR_MGMT_1,0X01);
    mpu_update();
    angleGyroX = 0;
    angleGyroY = 0;
    preInterval = timer;
    return 0;
}

void calcGyroOffsets(void){
    float x = 0, y = 0, z = 0;
    int16_t rx, ry, rz;
    int i;
    for(i =0; i < 1000; i++){
    MPU_Get_Gyroscope(&rx,&ry,&rz);
    x += ((double)rx) / 65.5;
    y += ((double)ry) / 65.5;
    z += ((double)rz) / 65.5;
    }
    gyroXoffset = x / 1000;
    gyroYoffset = y / 1000;
    gyroZoffset = z / 1000;
}
void mpu_update(void){
    MPU_Get_Accelerometer(&rawAccX, &rawAccY, &rawAccZ);
    temp = MPU_Get_Temperature();
    MPU_Get_Gyroscope(&rawGyroX,&rawGyroY,&rawGyroZ);

    accX = ((double)rawAccX) / 16384.0;
    accY = ((double)rawAccY) / 16384.0;
    accZ = ((double)rawAccZ) / 16384.0;

    angleAccX = atan2(accY, accZ + abs(accX)) * 360 / 2.0 / PI;
    angleAccY = atan2(accX, accZ + abs(accY)) * 360 / -2.0 / PI;

    gyroX = ((double)rawGyroX) / 65.5;
    gyroY = ((double)rawGyroY) / 65.5;
    gyroZ = ((double)rawGyroZ) / 65.5;

    gyroX -= gyroXoffset;
    gyroY -= gyroYoffset;
    gyroZ -= gyroZoffset;

    angleGyroX += gyroX * interval;
    angleGyroY += gyroY * interval;
    angleGyroZ += gyroZ * interval;

    interval = (timer - preInterval) * 0.001;

    angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
    angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
    angleZ = angleGyroZ;
    preInterval = timer ;

}
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ��
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
    return MPU_Write_Byte(MPU6050_GYRO_CONFIG,fsr<<3);//���������������̷�Χ
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ��
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
    return MPU_Write_Byte(MPU6050_ACCEL_CONFIG,fsr<<3);//���ü��ٶȴ����������̷�Χ
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ��
u8 MPU_Set_LPF(u16 lpf)
{
    u8 data=0;
    if(lpf>=188)data=1;
    else if(lpf>=98)data=2;
    else if(lpf>=42)data=3;
    else if(lpf>=20)data=4;
    else if(lpf>=10)data=5;
    else data=6;
    return MPU_Write_Byte(MPU6050_CONFIG,data);//�������ֵ�ͨ�˲���
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ��
u8 MPU_Set_Rate(u16 rate)
{
    u8 data;
    if(rate>1000)rate=1000;
    if(rate<4)rate=4;
    data=1000/rate-1;
    data=MPU_Write_Byte(MPU6050_SMPLRT_DIV,data);  //�������ֵ�ͨ�˲���
    return MPU_Set_LPF(rate/2); //�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2];
    short raw;
    float temp;
    MPU_Read_Len(MPU6050_ADDR,MPU6050_TEMP_H,2,buf);
    raw=((u16)buf[0]<<8)|buf[1];
    temp=36.53+((double)raw)/340;
    return temp*100;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(int16_t *gx,int16_t *gy,int16_t *gz)
{
    u8 buf[6],res;
    res=MPU_Read_Len(MPU6050_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
    if(res==0)
    {
        *gx=((u16)buf[0]<<8)|buf[1];
        *gy=((u16)buf[2]<<8)|buf[3];
        *gz=((u16)buf[4]<<8)|buf[5];
    }
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(int16_t *ax,int16_t *ay,int16_t *az)
{
    u8 buf[6],res;
    res=MPU_Read_Len(MPU6050_ADDR ,MPU_ACCEL_XOUTH_REG,6,buf);
    if(res==0)
    {
        *ax=((u16)buf[0]<<8)|buf[1];
        *ay=((u16)buf[2]<<8)|buf[3];
        *az=((u16)buf[4]<<8)|buf[5];
    }
    return res;;
}
//IIC����д
//addr:������ַ
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    u8 i;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0);//����������ַ+д����
    if(IIC_Wait_Ack())  //�ȴ�Ӧ��
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg); //д�Ĵ�����ַ
    IIC_Wait_Ack();     //�ȴ�Ӧ��
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte(buf[i]);  //��������
        if(IIC_Wait_Ack())      //�ȴ�ACK
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
}
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0 );//����������ַ+д����
    if(IIC_Wait_Ack())  //�ȴ�Ӧ��
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg); //д�Ĵ�����ַ
    IIC_Wait_Ack();     //�ȴ�Ӧ��
    IIC_Start();
    IIC_Send_Byte((addr<<1)|1 );//����������ַ+������
    IIC_Wait_Ack();     //�ȴ�Ӧ��
    while(len)
    {
        if(len==1)*buf=IIC_Read_Byte(0);//������,����nACK
        else *buf=IIC_Read_Byte(1);     //������,����ACK
        len--;
        buf++;
    }
    IIC_Stop(); //����һ��ֹͣ����
    return 0;
}
//IICдһ���ֽ�
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data)
{
    IIC_Start();
    IIC_Send_Byte((MPU6050_ADDR << 1) | 0);//����������ַ+д����
    if(IIC_Wait_Ack())  //�ȴ�Ӧ��
    {
        IIC_Stop();
        //printf("%s\r\n","error");
        Delay_ms(100);
        return 1;
    }
    IIC_Send_Byte(reg); //д�Ĵ�����ַ
    IIC_Wait_Ack();     //�ȴ�Ӧ��
    IIC_Send_Byte(data);//��������
    if(IIC_Wait_Ack())  //�ȴ�ACK
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}
//IIC��һ���ֽ�
//reg:�Ĵ�����ַ
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
    u8 res;
    IIC_Start();
    IIC_Send_Byte((MPU6050_ADDR << 1) | 0 );//����������ַ+д����
    IIC_Wait_Ack();
    IIC_Send_Byte(reg); //д�Ĵ�����ַ
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte((MPU6050_ADDR << 1) | 1 );//����������ַ+������
    IIC_Wait_Ack();
    res=IIC_Read_Byte(0);//��ȡ����,����nACK
    IIC_Stop();         //����һ��ֹͣ����
    return res;
}


