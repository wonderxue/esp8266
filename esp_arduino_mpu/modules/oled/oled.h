#ifndef __OLED_H__
#define __OLED_H__

#include "i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

//Device Information
#define _oled_Adress 0x3c

struct oled_DisMode
{
    unsigned char horiz;
    unsigned char verti;
    unsigned char page;
};

struct oled_Frame
{
    unsigned char frame5;
    unsigned char frame64;
    unsigned char frame128;
    unsigned char frame256;
    unsigned char frame3;
    unsigned char frame4;
    unsigned char frame25;
    unsigned char frame2;
};

struct oled_Dir
{
    unsigned char right;
    unsigned char left;
    unsigned char up_right;
    unsigned char uo_left;
};
extern struct oled_DisMode oled_DisMode;
extern struct oled_Frame oled_Frame;
extern struct oled_Dir oled_Dir;

void oledInit(void);
void oledCls(void);
void oledFill(void);
void oledOff(void);
void oledOn(void);
void oledStartPage(unsigned char pag, unsigned int seg);
void oledAreaHoriz(unsigned int colu1, unsigned int colu2);
void oledAreaVerti(unsigned int page1, unsigned int page2);
void oledStartLine(unsigned char line);
void oledSetPos(unsigned char x, unsigned char y);
void oledDisplayMode(unsigned char oled_DisMode);
void oledShowChar(unsigned char x, unsigned char y, unsigned char chr, unsigned char Char_Size);
void oledShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char size2);
void oledShowString(unsigned char x, unsigned char y, unsigned char *chr, unsigned char Char_Size);
void oledScroll(unsigned char oled_Dir, unsigned char oled_Frame, unsigned char vs_page, unsigned char vd_page, unsigned char row);

#ifdef __cplusplus
}
#endif

#endif //__OLED_H__