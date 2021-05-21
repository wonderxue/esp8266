#ifndef __MPU_H__
#define __MPU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"
#define GY_Adress 0x68

struct GY_Config
{
    unsigned char Sample_Rate;
    unsigned char Low_Filter_Freq;
    unsigned char GY_Self_Check;
    unsigned char AC_Self_Check;
    unsigned char Pow_Manage;
};

struct Data_Read
{
    unsigned char ACCEL_XOUT_H;
    unsigned char ACCEL_XOUT_L;
    unsigned char ACCEL_YOUT_H;
    unsigned char ACCEL_YOUT_L;
    unsigned char ACCEL_ZOUT_H;
    unsigned char ACCEL_ZOUT_L;

    unsigned char TEMP_OUT_H;
    unsigned char TEMP_OUT_L;

    unsigned char GYRO_XOUT_H;
    unsigned char GYRO_XOUT_L;
    unsigned char GYRO_YOUT_H;
    unsigned char GYRO_YOUT_L;
    unsigned char GYRO_ZOUT_H;
    unsigned char GYRO_ZOUT_L;
};

extern struct GY_Config GY_Config;
extern struct Data_Read Data_Read;

void GY_Write_Cmd(unsigned char reg_address, unsigned char cmd);
unsigned char GY_Read_Byte(unsigned char reg_address);
void GY_Init(void);
short GY_Read_Data(unsigned char reg_address);

#ifdef __cplusplus
}
#endif
#endif //__MPU_H__