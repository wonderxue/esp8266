#include "mpu.h"

struct GY_Config GY_Config = {0x19, 0x1a, 0x1b, 0x1c, 0x6b};
struct Data_Read Data_Read = {0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48};
unsigned char _mpu_fd;

void _GY_Write_Cmd(unsigned char reg_address, unsigned char cmd)
{
    spiWriteRegByte(_mpu_fd, reg_address, cmd);
}

unsigned char _GY_Read_Byte(unsigned char reg_address)
{
    unsigned char data;
    data = spiReadRegByte(_mpu_fd, reg_address);
    return data;
}

void GY_Init()
{
    _mpu_fd = spiBegin(GY_Adress);
    _GY_Write_Cmd(GY_Config.Pow_Manage, 0x80);
    delay(100);
    _GY_Write_Cmd(GY_Config.Pow_Manage, 0x00);
    _GY_Write_Cmd(GY_Config.Sample_Rate, 0x07);
    _GY_Write_Cmd(GY_Config.AC_Self_Check, 0x00); //+/-2g
    _GY_Write_Cmd(GY_Config.GY_Self_Check, 0x18); //+/-2000/s
    _GY_Write_Cmd(GY_Config.Low_Filter_Freq, 0x06);
}

short GY_Read_Data(unsigned char reg_address)
{
    unsigned char H, L;
    short temp;
    H = _GY_Read_Byte(reg_address);
    L = _GY_Read_Byte(reg_address + 1);
    temp = (H << 8) + L;
    return temp;
}