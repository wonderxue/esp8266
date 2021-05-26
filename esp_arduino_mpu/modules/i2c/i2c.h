#ifndef __I2C_H__
#define __I2C_H__

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

//硬件配置
#define _i2c_SDA     13
#define _i2c_SCL     12

#define _i2c_PinMode(x,y)  pinMode(x, y)
#define _i2c_PinWrite(x,y) digitalWrite(x, y)
#define _i2c_PinRead(x)    digitalRead(x)

#define _i2c_INPUT INPUT
#define _i2c_OUTPUT OUTPUT
#define _i2c_HIGH HIGH
#define _i2c_LOW LOW

#define _i2c_SCL_L   _i2c_PinWrite(_i2c_SCL,_i2c_LOW)
#define _i2c_SCL_H   _i2c_PinWrite(_i2c_SCL,_i2c_HIGH)
#define _i2c_SDA_L   _i2c_PinWrite(_i2c_SDA,_i2c_LOW)
#define _i2c_SDA_H   _i2c_PinWrite(_i2c_SDA,_i2c_HIGH)
#define _i2c_SDA_In  _i2c_PinMode(_i2c_SDA,_i2c_INPUT)
#define _i2c_SDA_Out _i2c_PinMode(_i2c_SDA,_i2c_OUTPUT)
#define _i2c_SCL_Out _i2c_PinMode(_i2c_SCL,_i2c_OUTPUT)
#define _i2c_SDA_Read _i2c_PinRead(_i2c_SDA)
#define _i2c_DelayUs(x) delayUs(x)

//功能定义
unsigned char i2cBegin(unsigned short dev_addr);
void i2cSetTimeOut(int count);
_Bool i2cWriteByte(unsigned char fid,unsigned char data);
_Bool i2cWriteRegByte(unsigned char fid,unsigned char reg_addr,unsigned char data);
unsigned char i2cReadbyte(unsigned char fid);
unsigned char i2cReadRegByte(unsigned char fid,unsigned char reg_addr);

#ifdef __cplusplus
}
#endif

#endif //__I2C_H__