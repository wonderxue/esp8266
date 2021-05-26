#include "func.h"

void floatToString(float num,char*buff,unsigned char size)  //浮点型数，存储的字符数组，字符数组的长度
{
    int temp,i,j;
    if(num>=0)//判断是否大于0
        buff[0] = ' ';
    else
    {
        buff[0] = '-';
        num = -num;
    }
    temp = (int)num;//取整数部分
    for(i=0;temp!=0;i++)//计算整数部分的位数
        temp /=10;
    temp =(int)num;
    for(j=i;j>0;j--)//将整数部分转换成字符串型
    {
        buff[j] = temp%10+'0';
        temp /=10;
    }
    if(i==0)
    {
        buff[++i] = '0';
    }
    buff[i+1] = '.';
    num -=(int)num;
    for(i=i+2;i<size-1;i++)//将小数部分转换成字符串型
    {
        if(num==0)
        {
            buff[i] ='\0';
            return ;
        }
        num*=10;
        buff[i]=(int)num+'0';
        num-=(int)num;
    }
    buff[size-1] ='\0';
}
