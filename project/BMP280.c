#include "BMP280.h"



static uint8_t BMP280_Read_Byte(uint8_t reg)
{
	uint8_t rec_data;
	B_IIC_Start();
	B_IIC_Send_Byte(BMP280_ADDRESS<<1|0);
	B_IIC_Wait_Ack();
	B_IIC_Send_Byte(reg);
	B_IIC_Wait_Ack();
	
	B_IIC_Start();
	B_IIC_Send_Byte(BMP280_ADDRESS<<1|1);
	B_IIC_Wait_Ack();
	rec_data = B_IIC_Read_Byte(0);	//��Ӧ��
	B_IIC_Stop();
	return rec_data;
}

static void BMP280_Write_Byte(uint8_t reg,uint8_t data)
{
	B_IIC_Start();
	B_IIC_Send_Byte(BMP280_ADDRESS<<1);
	B_IIC_Wait_Ack();
	B_IIC_Send_Byte(reg);
	B_IIC_Wait_Ack();
	
	B_IIC_Send_Byte(data);
	B_IIC_Wait_Ack();
	B_IIC_Stop();
}


uint8_t BMP280_ReadID(void)
{
	return BMP280_Read_Byte(BMP280_CHIPID_REG);
}

BMP280 bmp280_inst;
BMP280* bmp280 = &bmp280_inst;		//���ȫ�ֽṹ����������������оƬ��ROM��������
void Bmp_Init(void)
{
	uint8_t Lsb,Msb;
	
	/********************������������������*********************/
	//�¶ȴ������Ľ���ֵ
	Lsb = BMP280_Read_Byte(BMP280_DIG_T1_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_T1_MSB_REG);
	bmp280->T1 = (((uint16_t)Msb)<<8) + Lsb;			//��λ�ӵ�λ
	Lsb = BMP280_Read_Byte(BMP280_DIG_T2_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_T2_MSB_REG);
	bmp280->T2 = (((uint16_t)Msb)<<8) + Lsb;		
	Lsb = BMP280_Read_Byte(BMP280_DIG_T3_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_T3_MSB_REG);
	bmp280->T3 = (((uint16_t)Msb)<<8) + Lsb;		
	
	//����ѹ�������Ľ���ֵ
	Lsb = BMP280_Read_Byte(BMP280_DIG_P1_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P1_MSB_REG);
	bmp280->P1 = (((uint16_t)Msb)<<8) + Lsb;		
	Lsb = BMP280_Read_Byte(BMP280_DIG_P2_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P2_MSB_REG);
	bmp280->P2 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P3_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P3_MSB_REG);
	bmp280->P3 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P4_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P4_MSB_REG);
	bmp280->P4 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P5_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P5_MSB_REG);
	bmp280->P5 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P6_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P6_MSB_REG);
	bmp280->P6 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P7_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P7_MSB_REG);
	bmp280->P7 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P8_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P8_MSB_REG);
	bmp280->P8 = (((uint16_t)Msb)<<8) + Lsb;	
	Lsb = BMP280_Read_Byte(BMP280_DIG_P9_LSB_REG);
	Msb = BMP280_Read_Byte(BMP280_DIG_P9_MSB_REG);
	bmp280->P9 = (((uint16_t)Msb)<<8) + Lsb;	
	/******************************************************/
	BMP280_Write_Byte(BMP280_RESET_REG,BMP280_RESET_VALUE);	//����λ�Ĵ���д�����ֵ
	
	BMP_OVERSAMPLE_MODE			BMP_OVERSAMPLE_MODEStructure;
	BMP_OVERSAMPLE_MODEStructure.P_Osample = BMP280_P_MODE_3;
	BMP_OVERSAMPLE_MODEStructure.T_Osample = BMP280_T_MODE_1;
	BMP_OVERSAMPLE_MODEStructure.WORKMODE  = BMP280_NORMAL_MODE;
	BMP280_Set_TemOversamp(&BMP_OVERSAMPLE_MODEStructure);
	
	BMP_CONFIG					BMP_CONFIGStructure;
	BMP_CONFIGStructure.T_SB = BMP280_T_SB1;
	BMP_CONFIGStructure.FILTER_COEFFICIENT = BMP280_FILTER_MODE_4;
	BMP_CONFIGStructure.SPI_EN = DISABLE;
	
	BMP280_Set_Standby_FILTER(&BMP_CONFIGStructure);
}

//����BMP���������� MODE 
//BMP280_SLEEP_MODE||BMP280_FORCED_MODE||BMP280_NORMAL_MODE
void BMP280_Set_TemOversamp(BMP_OVERSAMPLE_MODE * Oversample_Mode)
{
	uint8_t Regtmp;
	Regtmp = ((Oversample_Mode->T_Osample)<<5)|
			 ((Oversample_Mode->P_Osample)<<2)|
			 ((Oversample_Mode)->WORKMODE);
	
	BMP280_Write_Byte(BMP280_CTRLMEAS_REG,Regtmp);
}


//���ñ���ʱ����˲�����Ƶ����
void BMP280_Set_Standby_FILTER(BMP_CONFIG * BMP_Config)
{
	uint8_t Regtmp;
	Regtmp = ((BMP_Config->T_SB)<<5)|
			 ((BMP_Config->FILTER_COEFFICIENT)<<2)|
			 ((BMP_Config->SPI_EN));
	
	BMP280_Write_Byte(BMP280_CONFIG_REG,Regtmp);
}

//��ȡBMP��ǰ״̬
//status_flag = BMP280_MEASURING ||
//			 	BMP280_IM_UPDATE
uint8_t  BMP280_GetStatus(uint8_t status_flag)
{
	uint8_t flag;
	flag = BMP280_Read_Byte(BMP280_STATUS_REG);
	if(flag&status_flag)	return SET;
	else return RESET;
}
//����ѹֵ-Pa
long BMP280_Get_Pressure(void)
{
	uint8_t XLsb,Lsb, Msb;
	long signed Bit32;
	//double pressure;
	XLsb = BMP280_Read_Byte(BMP280_PRESSURE_XLSB_REG);
	Lsb	 = BMP280_Read_Byte(BMP280_PRESSURE_LSB_REG);
	Msb	 = BMP280_Read_Byte(BMP280_PRESSURE_MSB_REG);
	Bit32 = ((long)(Msb << 12))|((long)(Lsb << 4))|(XLsb>>4);	//�Ĵ�����ֵ�������
	return Bit32 ;
}


