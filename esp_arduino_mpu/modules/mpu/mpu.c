#include "mpu.h"

struct _mpu_Config
{
    unsigned char Sample_Rate;
    unsigned char Low_Filter_Freq;
    unsigned char GY_Self_Check;
    unsigned char AC_Self_Check;
    unsigned char Pow_Manage;
};
struct _mpu_Config _mpu_Config = {0x19, 0x1a, 0x1b, 0x1c, 0x6b};
struct mpu_Read mpu_Read = {0x3b, 0x3d, 0x3f, 0x41, 0x43, 0x45, 0x47};
unsigned char _mpu_Fd;

void _mpu_WriteCmd(unsigned char reg_Address, unsigned char cmd)
{
    i2cWriteRegByte(_mpu_Fd, reg_Address, cmd);
}

unsigned char _mpu_ReadByte(unsigned char reg_Address)
{
    unsigned char data;
    data = i2cReadRegByte(_mpu_Fd, reg_Address);
    return data;
}

void mpuInit()
{
    _mpu_Fd = i2cBegin(_mpu_Adress);
    _mpu_WriteCmd(_mpu_Config.Pow_Manage, 0x80);
    _mpu_DelayMs(100);
    _mpu_WriteCmd(_mpu_Config.Pow_Manage, 0x00);
    _mpu_WriteCmd(_mpu_Config.Sample_Rate, 0x07);
    _mpu_WriteCmd(_mpu_Config.AC_Self_Check, 0x00); //+/-2g
    _mpu_WriteCmd(_mpu_Config.GY_Self_Check, 0x18); //+/-2000/s
    _mpu_WriteCmd(_mpu_Config.Low_Filter_Freq, 0x06);
}

short mpuReadData(unsigned char reg_Address)
{
    unsigned char H, L;
    short temp;
    H = _mpu_ReadByte(reg_Address);
    L = _mpu_ReadByte(reg_Address + 1);
    temp = (H << 8) + L;
    return temp;
}