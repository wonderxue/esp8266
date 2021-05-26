#ifndef __SPI_H__
#define __SPI_H__

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

//硬件配置
#define _spi_SDI    0
#define _spi_SDO    13
#define _spi_SCLK   12

#define _spi_PinMode(x,y)  pinMode(x, y)
#define _spi_PinWrite(x,y) digitalWrite(x, y)
#define _spi_PinRead(x)    digitalRead(x)

#define _spi_INPUT INPUT
#define _spi_OUTPUT OUTPUT
#define _spi_HIGH HIGH
#define _spi_LOW LOW

#define _spi_SDI_In     ;//_spi_PinMode(_spi_SDI,_spi_INPUT)
#define _spi_SDO_Out    _spi_PinMode(_spi_SDO,_spi_OUTPUT)
#define _spi_SCLK_Out   _spi_PinMode(_spi_SCLK,_spi_OUTPUT)

#define _spi_SDI_Read   0//_spi_PinRead(_spi_SDI)
#define _spi_SDO_H      _spi_PinWrite(_spi_SDO,_spi_HIGH)
#define _spi_SDO_L      _spi_PinWrite(_spi_SDO,_spi_LOW)
#define _spi_SCLK_H     _spi_PinWrite(_spi_SCLK,_spi_HIGH)
#define _spi_SCLK_L     _spi_PinWrite(_spi_SCLK,_spi_LOW)

#define _spi_DelayUs(x)   delayUs(x)

struct spiMode
{
    /*  
    Mode0:CPOL=0,CPHA=0
    Mode1:CPOL=0,CPHA=1
    Mode2:CPOL=1,CPHA=0
    Mode3:CPOL=1,CPHA=1
    CPOL:spi时钟信号电平（1:空闲时高电平; 0:空闲时低电平）
    CPHA:spi时钟信号采样（0:第一个边沿开始; 1:第二个边沿开始）
    */
    unsigned char spi_Mode_0;
    unsigned char spi_Mode_1;
    unsigned char spi_Mode_2;
    unsigned char spi_Mode_3;
};
extern struct spiMode spiMode;
//功能定义
unsigned char spiRegist(unsigned char spiSelectPin);
unsigned char spiByteTransfer(unsigned char fd, unsigned char data, unsigned char spiMode);
unsigned short spiWordTransfer(unsigned char fd, unsigned short data, unsigned char spiMode);

#ifdef __cplusplus
}
#endif

#endif //__SPI_H__