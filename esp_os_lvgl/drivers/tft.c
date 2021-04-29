#include "tft.h"
void TFT_SPI_Init(void)
{
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, TFT_SCL);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, TFT_SDA);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, TFT_RST);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, TFT_RS);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, TFT_CS);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, TFT_LED);
}

void SPI_WriteData(unsigned char Data)
{
  unsigned char i=0;
  for(i=8;i>0;i--)
  {
    if(Data&0x80) 
      TFT_SDA_SET;
    else 
      TFT_SDA_CLR;
    TFT_SCL_CLR;       
    TFT_SCL_SET;
    Data<<=1; 
  }
}

void TFT_WriteCmd(unsigned char Cmd)
{
   TFT_CS_CLR;
   TFT_RS_CLR;
   SPI_WriteData(Cmd);
   TFT_CS_SET;
}

void TFT_WriteData_U8(unsigned char Data)
{
   TFT_CS_CLR;
   TFT_RS_SET;
   SPI_WriteData(Data);
   TFT_CS_SET; 
}

void TFT_WriteData_U16(unsigned short Data)
{
   TFT_CS_CLR;
   TFT_RS_SET;
   SPI_WriteData(Data>>8);
   SPI_WriteData(Data);
   TFT_CS_SET; 
}

void TFT_WriteReg(unsigned char Index,unsigned char Data)
{
  TFT_WriteCmd(Index);
  TFT_WriteData_U8(Data);
}

void TFT_Reset(void)
{
  TFT_RST_CLR;
  delay(100);
  TFT_RST_SET;
  delay(50);
}

void TFT_Init(void)
{ 
  TFT_SPI_Init();
  TFT_Reset();
  TFT_LED_SET;
  //0x10sleepin  0x11sleepout 
  TFT_WriteCmd(0x11);
  delay(120);
  
  //Frame Rate Control (In normal mode/ Full colors)
  TFT_WriteCmd(0xB1);
  TFT_WriteData_U8(0x01); 
  TFT_WriteData_U8(0x2C); 
  TFT_WriteData_U8(0x2D); 

  //Frame Rate Control (In Idle mode/ 8-colors)
  TFT_WriteCmd(0xB2); 
  TFT_WriteData_U8(0x01); 
  TFT_WriteData_U8(0x2C); 
  TFT_WriteData_U8(0x2D); 
  
  //Frame Rate Control (In Partial mode/ full colors)
  TFT_WriteCmd(0xB3); 
  TFT_WriteData_U8(0x01); 
  TFT_WriteData_U8(0x2C); 
  TFT_WriteData_U8(0x2D); 
  TFT_WriteData_U8(0x01); 
  TFT_WriteData_U8(0x2C); 
  TFT_WriteData_U8(0x2D); 
  
  //Display Inversion Control
  TFT_WriteCmd(0xB4); 
  TFT_WriteData_U8(0x07); 
  
  //Power Control 1
  TFT_WriteCmd(0xC0); 
  TFT_WriteData_U8(0xA2); 
  TFT_WriteData_U8(0x02); 
  TFT_WriteData_U8(0x84); 
  
  //Power Control 2
  TFT_WriteCmd(0xC1); 
  TFT_WriteData_U8(0xC5); 

  //Power Control 3 (in Normal mode/ Full colors)
  TFT_WriteCmd(0xC2); 
  TFT_WriteData_U8(0x0A); 
  TFT_WriteData_U8(0x00); 

  //Power Control 4 (in Idle mode/ 8-colors)
  TFT_WriteCmd(0xC3); 
  TFT_WriteData_U8(0x8A); 
  TFT_WriteData_U8(0x2A); 
  
  //Power Control 5 (in Partial mode/ full-colors)
  TFT_WriteCmd(0xC4); 
  TFT_WriteData_U8(0x8A); 
  TFT_WriteData_U8(0xEE); 
  
  //VCOM Control 1
  TFT_WriteCmd(0xC5); 
  TFT_WriteData_U8(0x0E); 
  
  //Memory Data Access Control
  TFT_WriteCmd(0x36);
  TFT_WriteData_U8(0xC0); 
  
  //Gamma (‘+’polarity) Correction Characteristics Setting
  TFT_WriteCmd(0xe0); 
  TFT_WriteData_U8(0x0f); 
  TFT_WriteData_U8(0x1a); 
  TFT_WriteData_U8(0x0f); 
  TFT_WriteData_U8(0x18); 
  TFT_WriteData_U8(0x2f); 
  TFT_WriteData_U8(0x28); 
  TFT_WriteData_U8(0x20); 
  TFT_WriteData_U8(0x22); 
  TFT_WriteData_U8(0x1f); 
  TFT_WriteData_U8(0x1b); 
  TFT_WriteData_U8(0x23); 
  TFT_WriteData_U8(0x37); 
  TFT_WriteData_U8(0x00);   
  TFT_WriteData_U8(0x07); 
  TFT_WriteData_U8(0x02); 
  TFT_WriteData_U8(0x10); 
  
  //Gamma ‘-’polarity Correction Characteristics Setting
  TFT_WriteCmd(0xe1); 
  TFT_WriteData_U8(0x0f); 
  TFT_WriteData_U8(0x1b); 
  TFT_WriteData_U8(0x0f); 
  TFT_WriteData_U8(0x17); 
  TFT_WriteData_U8(0x33); 
  TFT_WriteData_U8(0x2c); 
  TFT_WriteData_U8(0x29); 
  TFT_WriteData_U8(0x2e); 
  TFT_WriteData_U8(0x30); 
  TFT_WriteData_U8(0x30); 
  TFT_WriteData_U8(0x39); 
  TFT_WriteData_U8(0x3f); 
  TFT_WriteData_U8(0x00); 
  TFT_WriteData_U8(0x07); 
  TFT_WriteData_U8(0x03); 
  TFT_WriteData_U8(0x10);  
  
  //Column Address Set
  TFT_WriteCmd(0x2a);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(0x7f);

  //Row Address Set
  TFT_WriteCmd(0x2b);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(0x9f);
  
  //
  TFT_WriteCmd(0xF0);
  TFT_WriteData_U8(0x01); 
  
  TFT_WriteCmd(0xF6);
  TFT_WriteData_U8(0x00); 
  
  //Interface Pixel Format
  TFT_WriteCmd(0x3A);
  TFT_WriteData_U8(0x05); 
  
  //Display On
  TFT_WriteCmd(0x29);
}

void TFT_SetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end)
{   
  TFT_WriteCmd(0x2a);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(x_start);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(x_end);

  TFT_WriteCmd(0x2b);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(y_start);
  TFT_WriteData_U8(0x00);
  TFT_WriteData_U8(y_end);
  
  TFT_WriteCmd(0x2c);
}

void TFT_SetXY(unsigned short x,unsigned short y)
{
    TFT_SetRegion(x,y,x,y);
}

void Gui_DrawPoint(unsigned short x,unsigned short y,unsigned short Data)
{
  TFT_SetRegion(x,y,x+1,y+1);
  TFT_WriteData_U16(Data);
}

void TFT_Clear(unsigned short Color)               
{ 
   unsigned int i,m;
   TFT_SetRegion(0,0,127,179);
   TFT_WriteCmd(0x2C);
   for(i=0;i<128;i++)
    for(m=0;m<180;m++)
    { 
      TFT_WriteData_U16(Color);
    }   
}
