#include "tft.h"
unsigned char _tft_Fd;

void _tft_WriteCmd(unsigned char Cmd)
{
   _tft_RS_L;
   spiByteTransfer(_tft_Fd,Cmd,spiMode.spi_Mode_2);
}

void _tft_WriteByteData(unsigned char Data)
{
   _tft_RS_H;
   spiByteTransfer(_tft_Fd,Data,spiMode.spi_Mode_2);
}

void _tft_WriteWordData(unsigned short Data)
{
   _tft_RS_H;
   spiWordTransfer(_tft_Fd,Data,spiMode.spi_Mode_2);
}

void tftWriteReg(unsigned char Index,unsigned char Data)
{
  _tft_WriteCmd(Index);
  _tft_WriteByteData(Data);
}

void tftReset(void)
{
  _tft_RST_L;
  _tft_DelayMs(100);
  _tft_RST_H;
  _tft_DelayMs(50);
}

void tftInit(void)
{ 
  _tft_LED_Out;
  _tft_RS_Out;
  _tft_RST_Out;
  _tft_Fd=spiRegist(_tft_CS);
  tftReset();
  _tft_LED_H;
  //0x10sleepin  0x11sleepout 
  _tft_WriteCmd(0x11);
  _tft_DelayMs(120);
  
  //Frame Rate Control (In normal mode/ Full colors)
  _tft_WriteCmd(0xB1);
  _tft_WriteByteData(0x01); 
  _tft_WriteByteData(0x2C); 
  _tft_WriteByteData(0x2D); 

  //Frame Rate Control (In Idle mode/ 8-colors)
  _tft_WriteCmd(0xB2); 
  _tft_WriteByteData(0x01); 
  _tft_WriteByteData(0x2C); 
  _tft_WriteByteData(0x2D); 
  
  //Frame Rate Control (In Partial mode/ full colors)
  _tft_WriteCmd(0xB3); 
  _tft_WriteByteData(0x01); 
  _tft_WriteByteData(0x2C); 
  _tft_WriteByteData(0x2D); 
  _tft_WriteByteData(0x01); 
  _tft_WriteByteData(0x2C); 
  _tft_WriteByteData(0x2D); 
  
  //Display Inversion Control
  _tft_WriteCmd(0xB4); 
  _tft_WriteByteData(0x07); 
  
  //Power Control 1
  _tft_WriteCmd(0xC0); 
  _tft_WriteByteData(0xA2); 
  _tft_WriteByteData(0x02); 
  _tft_WriteByteData(0x84); 
  
  //Power Control 2
  _tft_WriteCmd(0xC1); 
  _tft_WriteByteData(0xC5); 

  //Power Control 3 (in Normal mode/ Full colors)
  _tft_WriteCmd(0xC2); 
  _tft_WriteByteData(0x0A); 
  _tft_WriteByteData(0x00); 

  //Power Control 4 (in Idle mode/ 8-colors)
  _tft_WriteCmd(0xC3); 
  _tft_WriteByteData(0x8A); 
  _tft_WriteByteData(0x2A); 
  
  //Power Control 5 (in Partial mode/ full-colors)
  _tft_WriteCmd(0xC4); 
  _tft_WriteByteData(0x8A); 
  _tft_WriteByteData(0xEE); 
  
  //VCOM Control 1
  _tft_WriteCmd(0xC5); 
  _tft_WriteByteData(0x0E); 
  
  //Memory Data Access Control
  _tft_WriteCmd(0x36);
  _tft_WriteByteData(0xC0); 
  
  //Gamma (‘+’polarity) Correction Characteristics Setting
  _tft_WriteCmd(0xe0); 
  _tft_WriteByteData(0x0f); 
  _tft_WriteByteData(0x1a); 
  _tft_WriteByteData(0x0f); 
  _tft_WriteByteData(0x18); 
  _tft_WriteByteData(0x2f); 
  _tft_WriteByteData(0x28); 
  _tft_WriteByteData(0x20); 
  _tft_WriteByteData(0x22); 
  _tft_WriteByteData(0x1f); 
  _tft_WriteByteData(0x1b); 
  _tft_WriteByteData(0x23); 
  _tft_WriteByteData(0x37); 
  _tft_WriteByteData(0x00);   
  _tft_WriteByteData(0x07); 
  _tft_WriteByteData(0x02); 
  _tft_WriteByteData(0x10); 
  
  //Gamma ‘-’polarity Correction Characteristics Setting
  _tft_WriteCmd(0xe1); 
  _tft_WriteByteData(0x0f); 
  _tft_WriteByteData(0x1b); 
  _tft_WriteByteData(0x0f); 
  _tft_WriteByteData(0x17); 
  _tft_WriteByteData(0x33); 
  _tft_WriteByteData(0x2c); 
  _tft_WriteByteData(0x29); 
  _tft_WriteByteData(0x2e); 
  _tft_WriteByteData(0x30); 
  _tft_WriteByteData(0x30); 
  _tft_WriteByteData(0x39); 
  _tft_WriteByteData(0x3f); 
  _tft_WriteByteData(0x00); 
  _tft_WriteByteData(0x07); 
  _tft_WriteByteData(0x03); 
  _tft_WriteByteData(0x10);  
  
  //Column Address Set
  _tft_WriteCmd(0x2a);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(0x7f);

  //Row Address Set
  _tft_WriteCmd(0x2b);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(0x9f);
  
  //
  _tft_WriteCmd(0xF0);
  _tft_WriteByteData(0x01); 
  
  _tft_WriteCmd(0xF6);
  _tft_WriteByteData(0x00); 
  
  //Interface Pixel Format
  _tft_WriteCmd(0x3A);
  _tft_WriteByteData(0x05); 
  
  //Display On
  _tft_WriteCmd(0x29);
}

void tftSetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end)
{   
  _tft_WriteCmd(0x2a);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(x_start);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(x_end);

  _tft_WriteCmd(0x2b);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(y_start);
  _tft_WriteByteData(0x00);
  _tft_WriteByteData(y_end);
  
  _tft_WriteCmd(0x2c);
}

void tftSetXY(unsigned short x,unsigned short y)
{
    tftSetRegion(x,y,x,y);
}

void tftDrawArea(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short *Data)
{
  unsigned char i,j;
  tftSetRegion(x1,y1,x2,y2);
  for(i=y1;i<=y2;i++)
  for(j=x1;j<=x2;j++)
  {
    _tft_WriteWordData(*Data);
    Data++;
  }
}
void tftClear(unsigned short Color)
{ 
   unsigned int i,m;
   tftSetRegion(0,0,127,179);
   _tft_WriteCmd(0x2C);
   for(i=0;i<128;i++)
    for(m=0;m<180;m++)
    { 
      _tft_WriteWordData(Color);
    }   
}
