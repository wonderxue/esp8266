#ifndef __TFT_H__
#define __TFT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>
#include "lvgl.h"

#define TFT_SCL         12
#define TFT_SDA         13
#define TFT_RST         4
#define TFT_RS          5
#define TFT_CS          2
#define TFT_LED         15


#define TFT_SCL_SET   digitalWrite(TFT_SCL, HIGH) 
#define TFT_SDA_SET   digitalWrite(TFT_SDA, HIGH)   
#define TFT_CS_SET    digitalWrite(TFT_CS, HIGH)  

    
#define TFT_LED_SET   digitalWrite(TFT_LED, HIGH)   
#define TFT_RS_SET    digitalWrite(TFT_RS, HIGH)
#define TFT_RST_SET   digitalWrite(TFT_RST, HIGH)

#define TFT_SCL_CLR   digitalWrite(TFT_SCL, LOW)
#define TFT_SDA_CLR   digitalWrite(TFT_SDA, LOW)
#define TFT_CS_CLR    digitalWrite(TFT_CS, LOW)
    
#define TFT_LED_CLR   digitalWrite(TFT_LED, LOW)
#define TFT_RST_CLR   digitalWrite(TFT_RST, LOW)
#define TFT_RS_CLR    digitalWrite(TFT_RS, LOW)

void TFT_SPI_Init(void);
void TFT_WriteCmd(unsigned char Cmd);
void TFT_WriteData_U8(unsigned char Data);
void TFT_WriteData_U16(unsigned short Data);
void TFT_WriteReg(unsigned char Index,unsigned char Data);
void TFT_Reset(void);
void TFT_Init(void);

void TFT_SetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end);
void TFT_SetXY(unsigned short x,unsigned short y);
void Gui_DrawPoint(unsigned short x,unsigned short y,unsigned short Data);
void TFT_Clear(unsigned short Color);
void Gui_DrawArea(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,lv_color_t *color);

#ifdef __cplusplus
}
#endif
#endif  //__TFT_H__
