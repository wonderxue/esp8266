#ifndef __TFT_H__
#define __TFT_H__

#include <Arduino.h>
#include "spi/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define _tft_RST         4
#define _tft_RS          5
#define _tft_LED         15
#define _tft_CS          2

#define _tft_PinMode(x,y)  pinMode(x, y)
#define _tft_PinWrite(x,y) digitalWrite(x, y)
#define _tft_DelayMs(x)    delay(x)

#define _tft_INPUT INPUT
#define _tft_OUTPUT OUTPUT
#define _tft_HIGH HIGH
#define _tft_LOW LOW

#define _tft_LED_Out   _tft_PinMode(_tft_LED, _tft_OUTPUT)   
#define _tft_RS_Out    _tft_PinMode(_tft_RS, _tft_OUTPUT)
#define _tft_RST_Out   _tft_PinMode(_tft_RST, _tft_OUTPUT)
    
#define _tft_LED_H   _tft_PinWrite(_tft_LED, _tft_HIGH)   
#define _tft_RS_H    _tft_PinWrite(_tft_RS, _tft_HIGH)
#define _tft_RST_H   _tft_PinWrite(_tft_RST, _tft_HIGH)
    
#define _tft_LED_L   _tft_PinWrite(_tft_LED, _tft_LOW)
#define _tft_RST_L   _tft_PinWrite(_tft_RST, _tft_LOW)
#define _tft_RS_L   _tft_PinWrite(_tft_RS, _tft_LOW)

void tftInit(void);
void tftSetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end);
void tftSetXY(unsigned short x,unsigned short y);
void tftDrawArea(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short *Data);
void tftClear(unsigned short Color);

#ifdef __cplusplus
}
#endif

#endif  //__TFT_H__
