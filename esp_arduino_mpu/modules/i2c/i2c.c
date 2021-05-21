#include "i2c.h"
unsigned char _spi_timeOut = 200;
__attribute__((weak)) void _spi_I2cError(char *code)
{
    //#warning redefine function i2cError may better
    //HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
    //while (1)
    //    ;
}
void _spi_Start()
{
    _spi_SDA_Out;
    _spi_SDA_H;
    _spi_SCL_H;
    _spi_i2cDelay(5);
    _spi_SDA_L;
    _spi_i2cDelay(6);
    _spi_SCL_L;
}
void _spi_Stop()
{
    _spi_SDA_Out;
    _spi_SCL_L;
    _spi_SDA_L;
    _spi_SCL_H;
    _spi_i2cDelay(6);
    _spi_SDA_H;
    _spi_i2cDelay(6);
}
void _spi_SendAck(_Bool ack) //低 应答
{
    _spi_SCL_L;
    _spi_SDA_Out;
    if (ack)
        _spi_SDA_H;
    else
        _spi_SDA_L;
    _spi_i2cDelay(2);
    _spi_SCL_H;
    _spi_i2cDelay(5);
    _spi_SCL_L;
}
_Bool _spi_WaitAck()
{
    unsigned char tempTime = 0;
    _spi_SDA_In; //配置为上拉输入。
    _spi_SDA_H;  //主机释放数据总线，等待从机产生应答信号
    _spi_i2cDelay(1);
    _spi_SCL_H;
    _spi_i2cDelay(1);
    //等待从机对数据总线的操作。低电平代表应答
    while (_spi_SDA_Read)
    {
        tempTime++;
        //这个属于软件延时，不一定准确。
        if (tempTime > _spi_timeOut) //如果时间超时，没有应答就停止。
        {
            _spi_Stop();
            return 1; //没有响应的话返回1.
        }
    }
    _spi_SCL_L;
    return 0; //如果有响应的话就返回0.
}
_Bool _spi_Write(unsigned char data)
{
    _spi_SDA_Out;
    _spi_SCL_L;
    _spi_i2cDelay(2);
    for (int i = 0; i < 8; i++) //从高位开始一位一位地传送
    {
        //发数据放到数据线上
        if ((data & 0x80) > 0) //当前的最高位为1
            _spi_SDA_H;             //拉高数据线
        else
            _spi_SDA_L;
        data = data << 1; //数据左移一位
        //开始发送数据
        _spi_SCL_H;
        _spi_i2cDelay(2);
        //上一个数据发送完毕，为下一个数据发送准备
        _spi_SCL_L;
        _spi_i2cDelay(2);
    }
    return _spi_WaitAck();
}
unsigned char _spi_Read(_Bool ack)
{
    unsigned char data = 0; //接收到的数据
    _spi_SDA_In;
    for (int i = 0; i < 8; i++)
    {
        //数据准备
        _spi_SCL_L;
        _spi_i2cDelay(2);
        _spi_SCL_H;        //主机开始读数据，从机不能再改变数据了，即改变SDA的电平
        if (_spi_SDA_Read) //接收到的是1
            data++;
        data = data << 1;
        _spi_i2cDelay(1);
    }
    _spi_SendAck(ack);
    return data;
}
unsigned char spiBegin(unsigned short dev_addr)
{
    _spi_SCL_Out;
    _spi_SDA_Out;
    return dev_addr;
}
void spiSetTimeOut(int count)
{
    _spi_timeOut=count;
}
_Bool spiWriteByte(unsigned char fid, unsigned char data)
{
    _Bool status;
    unsigned char dev_addr = fid << 1;
    _spi_Start();
    status = _spi_Write(dev_addr);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("write dev_addr error");
        return status;
    }
    status = _spi_Write(data);
    if (status)
        _spi_I2cError("write data error");
    _spi_Stop();
    return status;
}
_Bool spiWriteRegByte(unsigned char fid, unsigned char reg_addr, unsigned char data)
{
    _Bool status;
    unsigned char dev_addr = fid << 1;
    _spi_Start();
    status = _spi_Write(dev_addr);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("write dev_addr error");
        return status;
    }
    status = _spi_Write(reg_addr);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("write reg_addr error");
        return status;
    }
    status = _spi_Write(data);
    if (status)
        _spi_I2cError("write data error");
    _spi_Stop();
    return status;
}
unsigned char spiReadbyte(unsigned char fid)
{
    _Bool status;
    unsigned char data;
    unsigned char dev_addr = fid << 1 + 1;
    _spi_Start();
    status = _spi_Write(dev_addr);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("read dev_addr error");
        return status;
    }
    data = _spi_Read(1);
    _spi_Stop();
    return data;
}
unsigned char spiReadRegByte(unsigned char fid, unsigned char reg_addr)
{
    _Bool status;
    unsigned char data;
    unsigned char dev_addr = fid << 1;
    _spi_Start();
    status = _spi_Write(dev_addr);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("read dev_addr1 error");
        return status;
    }
    status = _spi_Write(reg_addr);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("read reg_addr error");
        return status;
    }
    _spi_Start();
    status = _spi_Write(dev_addr + 1);
    if (status)
    {
        _spi_Stop();
        _spi_I2cError("read dev_addr2 error");
        return status;
    }
    data = _spi_Read(1);
    _spi_Stop();
    return data;
}
