#ifndef __TFT_H__
#define __TFT_H__

#include "esp_common.h"

// #define TFT_SCL         12
// #define TFT_SDA         13
// #define TFT_RST         4
// #define TFT_RS          5
// #define TFT_CS          2
// #define TFT_LED         15
#define TFT_SCL         FUNC_GPIO12
#define TFT_SDA         FUNC_GPIO13
#define TFT_RST         FUNC_GPIO4
#define TFT_RS          FUNC_GPIO5
#define TFT_CS          FUNC_GPIO2
#define TFT_LED         FUNC_GPIO15

#define TFT_SCL_SET   gpio_output_set(0, BIT12, BIT12, 0)//digitalWrite(TFT_SCL, HIGH) 
#define TFT_SDA_SET   gpio_output_set(0, BIT13, BIT13, 0)//digitalWrite(TFT_SDA, HIGH)   
#define TFT_CS_SET    gpio_output_set(0, BIT2, BIT2, 0)//digitalWrite(TFT_CS, HIGH)  

    
#define TFT_LED_SET   gpio_output_set(0, BIT15, BIT15, 0)//digitalWrite(TFT_LED, HIGH)   
#define TFT_RS_SET    gpio_output_set(0, BIT5, BIT5, 0)//digitalWrite(TFT_RS, HIGH)
#define TFT_RST_SET   gpio_output_set(0, BIT4, BIT4, 0)//digitalWrite(TFT_RST, HIGH)

#define TFT_SCL_CLR   gpio_output_set(BIT12, 0, BIT12, 0)//digitalWrite(TFT_SCL, LOW)
#define TFT_SDA_CLR   gpio_output_set(BIT13, 0, BIT13, 0)//digitalWrite(TFT_SDA, LOW)
#define TFT_CS_CLR    gpio_output_set(BIT2, 0, BIT2, 0)//digitalWrite(TFT_CS, LOW)
    
#define TFT_LED_CLR   gpio_output_set(BIT15, 0, BIT15, 0)//digitalWrite(TFT_LED, LOW)
#define TFT_RST_CLR   gpio_output_set(BIT5, 0, BIT5, 0)//digitalWrite(TFT_RST, LOW)
#define TFT_RS_CLR    gpio_output_set(BIT4, 0, BIT4, 0)//digitalWrite(TFT_RS, LOW)

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


#endif  //__TFT_H__
