#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

void lcd_wr_point(unsigned int Xpos,unsigned int Ypos,unsigned int Color);
unsigned int lcd_get_point(unsigned int Xpos,unsigned int Ypos);
/****************************************************************
*中层功能函数，将一块区域用某种颜色覆盖
*****************************************************************/
void Lcd_ColorBox(unsigned short xStart,unsigned short yStart,unsigned short xLong,unsigned short yLong,unsigned short Color) ;
void Dis_image(unsigned short xStart,unsigned short yStart,unsigned short xLong,unsigned short yLong, const unsigned char *image);
void LCD_Setup(void);

#endif
