#include "i2c.h"
extern void ErrorReport(char * source,char * code);
unsigned char _i2c_TimeOut = 200;
void _i2c_Error(char *code)
{
    ErrorReport("--I2C--",code);
}

void _i2c_Start()
{
    _i2c_SDA_Out;
    _i2c_SDA_H;
    _i2c_SCL_H;
    _i2c_DelayUs(5);
    _i2c_SDA_L;
    _i2c_DelayUs(6);
    _i2c_SCL_L;
}
void _i2c_Stop()
{
    _i2c_SDA_Out;
    _i2c_SCL_L;
    _i2c_SDA_L;
    _i2c_SCL_H;
    _i2c_DelayUs(6);
    _i2c_SDA_H;
    _i2c_DelayUs(6);
}
void _i2c_SendAck(_Bool ack) //低 应答
{
    _i2c_SCL_L;
    _i2c_SDA_Out;
    if (ack)
        _i2c_SDA_H;
    else
        _i2c_SDA_L;
    _i2c_DelayUs(2);
    _i2c_SCL_H;
    _i2c_DelayUs(5);
    _i2c_SCL_L;
}
_Bool _i2c_WaitAck()
{
    unsigned char tempTime = 0;
    _i2c_SDA_In; //配置为上拉输入。
    _i2c_SDA_H;  //主机释放数据总线，等待从机产生应答信号
    _i2c_DelayUs(1);
    _i2c_SCL_H;
    _i2c_DelayUs(1);
    //等待从机对数据总线的操作。低电平代表应答
    while (_i2c_SDA_Read)
    {
        tempTime++;
        //这个属于软件延时，不一定准确。
        if (tempTime > _i2c_TimeOut) //如果时间超时，没有应答就停止。
        {
            _i2c_Stop();
            return 1; //没有响应的话返回1.
        }
    }
    _i2c_SCL_L;
    return 0; //如果有响应的话就返回0.
}
_Bool _i2c_Write(unsigned char data)
{
    _i2c_SDA_Out;
    _i2c_SCL_L;
    _i2c_DelayUs(2);
    for (int i = 0; i < 8; i++) //从高位开始一位一位地传送
    {
        //发数据放到数据线上
        if ((data & 0x80) > 0) //当前的最高位为1
            _i2c_SDA_H;        //拉高数据线
        else
            _i2c_SDA_L;
        data = data << 1; //数据左移一位
        //开始发送数据
        _i2c_SCL_H;
        _i2c_DelayUs(2);
        //上一个数据发送完毕，为下一个数据发送准备
        _i2c_SCL_L;
        _i2c_DelayUs(2);
    }
    return _i2c_WaitAck();
}
unsigned char _i2c_Read(_Bool ack)
{
    unsigned char data = 0; //接收到的数据
    _i2c_SDA_In;
    for (int i = 0; i < 8; i++)
    {
        //数据准备
        data = data << 1;
        _i2c_SCL_L;
        _i2c_DelayUs(2);
        _i2c_SCL_H;        //主机开始读数据，从机不能再改变数据了，即改变SDA的电平
        if (_i2c_SDA_Read) //接收到的是1
            data++;
        _i2c_DelayUs(1);
    }
    _i2c_SendAck(ack);
    return data;
}
unsigned char i2cBegin(unsigned short dev_addr)
{
    _i2c_SCL_Out;
    _i2c_SDA_Out;
    return dev_addr;
}
void i2cSetTimeOut(int count)
{
    _i2c_TimeOut = count;
}
_Bool i2cWriteByte(unsigned char fid, unsigned char data)
{
    _Bool status;
    unsigned char dev_addr = fid << 1;
    _i2c_Start();
    status = _i2c_Write(dev_addr);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("write dev_addr error");
        return status;
    }
    status = _i2c_Write(data);
    if (status)
        _i2c_Error("write data error");
    _i2c_Stop();
    return status;
}
_Bool i2cWriteRegByte(unsigned char fid, unsigned char reg_addr, unsigned char data)
{
    _Bool status;
    unsigned char dev_addr = fid << 1;
    _i2c_Start();
    status = _i2c_Write(dev_addr);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("write dev_addr error");
        return status;
    }
    status = _i2c_Write(reg_addr);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("write reg_addr error");
        return status;
    }
    status = _i2c_Write(data);
    if (status)
        _i2c_Error("write data error");
    _i2c_Stop();
    return status;
}
unsigned char i2cReadbyte(unsigned char fid)
{
    _Bool status;
    unsigned char data;
    unsigned char dev_addr = (fid << 1) + 1;
    _i2c_Start();
    status = _i2c_Write(dev_addr);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("read dev_addr error");
        return status;
    }
    data = _i2c_Read(1);
    _i2c_Stop();
    return data;
}
unsigned char i2cReadRegByte(unsigned char fid, unsigned char reg_addr)
{
    _Bool status;
    unsigned char data;
    unsigned char dev_addr = fid << 1;
    _i2c_Start();
    status = _i2c_Write(dev_addr);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("read dev_addr1 error");
        return status;
    }
    status = _i2c_Write(reg_addr);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("read reg_addr error");
        return status;
    }
    _i2c_Start();
    status = _i2c_Write(dev_addr + 1);
    if (status)
    {
        _i2c_Stop();
        _i2c_Error("read dev_addr2 error");
        return status;
    }
    data = _i2c_Read(1);
    _i2c_Stop();
    return data;
}
