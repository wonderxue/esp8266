#include "spi.h"
extern void ErrorReport(char * source,char * code);
struct spiMode spiMode = {0, 1, 2, 3};
enum _spi_CS_Status
{
    _spi_UnSelect = 0,
    _spi_Select
};
void _spi_Error(char *code)
{
    ErrorReport("--SPI--",code);
}
void _spiSelectPin(unsigned char spiSelectPin, enum _spi_CS_Status spi_CS_Status)
{
    _spi_PinMode(spiSelectPin,_spi_OUTPUT);
    if(spi_CS_Status)
    _spi_PinWrite(spiSelectPin,_spi_LOW);
    else
    _spi_PinWrite(spiSelectPin,_spi_HIGH);
}

unsigned char spiRegist(unsigned char spiSelectPin)
{
    _spi_SDI_In;
    _spi_SDO_Out;
    _spi_SCLK_Out;
    return spiSelectPin;
}
unsigned short _spi_TransferModeByte0(unsigned char fd, unsigned short dataIn, unsigned char dataLength)
{
    unsigned short dataOut=0;
    unsigned char i;
    _spi_SCLK_L;
    _spiSelectPin(fd, _spi_Select);
    for (i = 0; i < dataLength; i++)
    {
        if (dataIn & 0x8000)
            _spi_SDO_H;
        else
            _spi_SDO_L;
        dataIn <<= 1;
        _spi_DelayUs(1);
        _spi_SCLK_H;
        dataOut <<= 1;
        if (_spi_SDI_Read)
            dataOut++;
        _spi_DelayUs(1);
        _spi_SCLK_L;
    }
    _spiSelectPin(fd, _spi_UnSelect);
    return dataOut;
}

unsigned char _spi_TransferModeByte1(unsigned char fd, unsigned short dataIn, unsigned char dataLength)
{
    unsigned char dataOut = 0;
    unsigned char i;
    _spi_SCLK_L;
    _spiSelectPin(fd, _spi_Select);
    for (i = 0; i < dataLength; i++)
    {
        _spi_SCLK_H;
        if (dataIn & 0x8000)
            _spi_SDO_H;
        else
            _spi_SDO_L;
        dataIn <<= 1;
        _spi_DelayUs(1);
        _spi_SCLK_L;
        dataOut <<= 1;
        if (_spi_SDI_Read)
            dataOut++;
        _spi_DelayUs(1);
    }
    _spiSelectPin(fd, _spi_UnSelect);
    return dataOut;
}

unsigned short _spi_TransferModeByte2(unsigned char fd, unsigned short dataIn, unsigned char dataLength)
{
    unsigned short dataOut=0;
    unsigned char i;
    _spi_SCLK_H;
    _spiSelectPin(fd, _spi_Select);
    for (i = 0; i < dataLength; i++)
    {
        if (dataIn & 0x8000)
            _spi_SDO_H;
        else
            _spi_SDO_L;
        dataIn <<= 1;
        _spi_DelayUs(1);
        _spi_SCLK_L;
        dataOut <<= 1;
        if (_spi_SDI_Read)
            dataOut++;
        _spi_DelayUs(1);
        _spi_SCLK_H;
    }
    _spiSelectPin(fd, _spi_UnSelect);
    return dataOut;
}
unsigned short _spi_TransferModeByte3(unsigned char fd, unsigned short dataIn, unsigned char dataLength)
{
    unsigned short dataOut = 0;
    unsigned char i;
    _spi_SCLK_H;
    _spiSelectPin(fd, _spi_Select);
    for (i = 0; i < dataLength; i++)
    {
        _spi_SCLK_L;
        if (dataIn & 0x8000)
            _spi_SDO_H;
        else
            _spi_SDO_L;
        dataIn <<= 1;
        _spi_DelayUs(1);
        _spi_SCLK_H;
        dataOut <<= 1;
        if (_spi_SDI_Read)
            dataOut++;
        _spi_DelayUs(1);
    }
    _spiSelectPin(fd, _spi_UnSelect);
    return dataOut;
}
unsigned char spiByteTransfer(unsigned char fd, unsigned char data, unsigned char spiMode)
{
    unsigned short dataIn=data<<8;
    unsigned char dataOut;
    switch (spiMode)
    {
    case 0:
        dataOut= _spi_TransferModeByte0(fd, dataIn, 8);
        break;
    case 1:
        dataOut= _spi_TransferModeByte1(fd, dataIn, 8);
        break;
    case 2:
        dataOut= _spi_TransferModeByte2(fd, dataIn, 8);
        break;
    case 3:
        dataOut= _spi_TransferModeByte3(fd, dataIn, 8);
        break;
    default:
        _spi_Error("spiMode Error");
        return 1;
        break;
    }
    return dataOut;
}
unsigned short spiWordTransfer(unsigned char fd, unsigned short data, unsigned char spiMode)
{
    unsigned short dataOut;
    switch (spiMode)
    {
    case 0:
        dataOut= _spi_TransferModeByte0(fd, data, 16);
        break;
    case 1:
        dataOut=  _spi_TransferModeByte1(fd, data, 16);
        break;
    case 2:
        dataOut=  _spi_TransferModeByte2(fd, data, 16);
        break;
    case 3:
        dataOut=  _spi_TransferModeByte3(fd, data, 16);
        break;
    default:
        _spi_Error("spiMode Error");
        return 1;
        break;
    }
    return dataOut;
}
