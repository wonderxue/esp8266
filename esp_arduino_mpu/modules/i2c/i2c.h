#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>

//硬件配置
#define _spi_SDA     14
#define _spi_SCL     16
#define _spi_SCL_L   digitalWrite(_spi_SCL,LOW)
#define _spi_SCL_H   digitalWrite(_spi_SCL,HIGH)
#define _spi_SDA_L   digitalWrite(_spi_SDA,LOW)
#define _spi_SDA_H   digitalWrite(_spi_SDA,HIGH)
#define _spi_SDA_In  pinMode(_spi_SDA,INPUT)
#define _spi_SDA_Out pinMode(_spi_SDA,OUTPUT)
#define _spi_SCL_Out pinMode(_spi_SCL,OUTPUT)
#define _spi_SDA_Read digitalRead(_spi_SDA)
#define _spi_i2cDelay(x) delay_us(x)
extern void delay_us(int us);
//功能定义
unsigned char spiBegin(unsigned short dev_addr);
void spiSetTimeOut(int count);
_Bool spiWriteByte(unsigned char fid,unsigned char data);
_Bool spiWriteRegByte(unsigned char fid,unsigned char reg_addr,unsigned char data);
unsigned char spiReadbyte(unsigned char fid);
unsigned char spiReadRegByte(unsigned char fid,unsigned char reg_addr);

#ifdef __cplusplus
}
#endif
#endif //__I2C_H__