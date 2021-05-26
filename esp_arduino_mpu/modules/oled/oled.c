#include "oled.h"
#include "oledfont.h"
struct oled_DisMode oled_DisMode = {0, 1, 2};
struct oled_Frame oled_Frame = {0, 1, 2, 3, 4, 5, 6, 7};
struct oled_Dir oled_Dir = {0, 1, 2, 3};
int _oled_fd;

void _oled_WriteCmd(unsigned char cmd)
{
    i2cWriteRegByte(_oled_fd, 0x00, cmd);
}

void _oled_WriteData(unsigned char data)
{
    i2cWriteRegByte(_oled_fd, 0x40, data);
}
unsigned int _oled_Pow(unsigned char m, unsigned char n)
{
    unsigned int result = 1;
    while (n--)
        result *= m;
    return result;
}
void oledCls()
{
    unsigned char i, j;
    for (i = 0; i < 8; i++)
    {
        _oled_WriteCmd(0xb0 + i);
        for (j = 0; j < 128; j++)
            _oled_WriteData(0x00);
    }
}
void oledFill()
{
    unsigned char i, j;
    for (i = 0; i < 8; i++)
    {
        _oled_WriteCmd(0xb0 + i);
        for (j = 0; j < 128; j++)
            _oled_WriteData(0xff);
    }
}
void oledOn()
{
    _oled_WriteCmd(0x8D);
    _oled_WriteCmd(0x14);
    _oled_WriteCmd(0xAF);
}

void oledOff()
{
    _oled_WriteCmd(0x8D);
    _oled_WriteCmd(0x10);
    _oled_WriteCmd(0xAE);
}

void oledInit()
{
    _oled_fd = i2cBegin(_oled_Adress);

    _oled_WriteCmd(0xAE); //off-AE on-AF

    _oled_WriteCmd(0x20); //mode
    _oled_WriteCmd(0x02); //page

    _oled_WriteCmd(0x00); //low column
    _oled_WriteCmd(0x10); //high column
    _oled_WriteCmd(0x40); //line
    _oled_WriteCmd(0xb0); //page

    _oled_WriteCmd(0x81); //contrast control
    _oled_WriteCmd(0xFE);

    _oled_WriteCmd(0xA1); //set segment remap
    _oled_WriteCmd(0xA4); //with ram-A4  without ram-A5
    _oled_WriteCmd(0xA6); //normal-A6 reverse-A7
    _oled_WriteCmd(0xA8); //ratio 1-64
    _oled_WriteCmd(0x3F);
    _oled_WriteCmd(0xC8); //COM Scan Direction-C0 or C8

    _oled_WriteCmd(0xD3); //display offset
    _oled_WriteCmd(0x00);

    _oled_WriteCmd(0xD5); //Set Display Clock Divide Ration/Oscillator Frequency
    _oled_WriteCmd(0x80); //0-3 for Clock Divide Ration 4-7 for Oscillator Frequency

    _oled_WriteCmd(0xD8); //area color mode
    _oled_WriteCmd(0x05);

    _oled_WriteCmd(0xD9); //pre charge
    _oled_WriteCmd(0xF1);

    _oled_WriteCmd(0xDA); //pin configuartion
    _oled_WriteCmd(0x12);

    _oled_WriteCmd(0xDB); //VCOMH
    _oled_WriteCmd(0x30);
}

void oledStartPage(unsigned char pag, unsigned int seg)
{
    _oled_WriteCmd(0xb0 + pag);
    _oled_WriteCmd(0x00 + seg % 16);
    _oled_WriteCmd(0x10 + seg / 16);
}

void oledStartLine(unsigned char line)
{
    _oled_WriteCmd(0x40 + line);
}

void oledSetPos(unsigned char x, unsigned char y)
{
    _oled_WriteCmd(0xb0 + y);
    _oled_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    _oled_WriteCmd(x & 0x0f);
}

void oledAreaHoriz(unsigned int colu1, unsigned int colu2)
{
    _oled_WriteCmd(0x21);
    _oled_WriteCmd(colu1);
    _oled_WriteCmd(colu2);
}

void oledAreaVerti(unsigned int page1, unsigned int page2)
{
    _oled_WriteCmd(0x22);
    _oled_WriteCmd(page1);
    _oled_WriteCmd(page2);
}

void oledDisplayMode(unsigned char mode)
{
    _oled_WriteCmd(0x20);
    _oled_WriteCmd(mode);
}

void oledShowChar(unsigned char x, unsigned char y, unsigned char chr, unsigned char Char_Size)
{
    unsigned char c = 0, i = 0;
    c = chr - ' ';
    if (x > 127)
    {
        x = 0;
        y = y + 2;
    }
    if (Char_Size == 16)
    {
        oledSetPos(x, y);
        for (i = 0; i < 8; i++)
            _oled_WriteData(F8X16[c * 16 + i]);
        oledSetPos(x, y + 1);
        for (i = 0; i < 8; i++)
            _oled_WriteData(F8X16[c * 16 + i + 8]);
    }
    else
    {
        oledSetPos(x, y);
        for (i = 0; i < 6; i++)
            _oled_WriteData(F6x8[c][i]);
    }
}


void oledShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char size2)
{
    unsigned char t, temp;
    unsigned char enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / _oled_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                oledShowChar(x + (size2 / 2) * t, y, ' ', size2);
                continue;
            }
            else
                enshow = 1;
        }
        oledShowChar(x + (size2 / 2) * t, y, temp + '0', size2);
    }
}

void oledShowString(unsigned char x, unsigned char y, unsigned char *chr, unsigned char Char_Size)
{
    unsigned char j = 0;
    while (chr[j] != '\0')
    {
        oledShowChar(x, y, chr[j], Char_Size);
        x += 8;
        if (x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}

void oledScroll(unsigned char dir, unsigned char frame, unsigned char vs_page, unsigned char vd_page, unsigned char row)
{
    _oled_WriteCmd(0x2E);
    //hor
    if (dir < 2)
    {
        _oled_WriteCmd(0x26 + dir);
        _oled_WriteCmd(0);
        _oled_WriteCmd(vs_page);
        _oled_WriteCmd(frame);
        _oled_WriteCmd(vd_page);
    }
    else
    {
        _oled_WriteCmd(0x29 + dir - 2);
        _oled_WriteCmd(0);
        _oled_WriteCmd(vs_page);
        _oled_WriteCmd(frame);
        _oled_WriteCmd(vd_page);
        _oled_WriteCmd(row);
    }
    _oled_WriteCmd(0x2F);
}