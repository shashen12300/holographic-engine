#ifndef __LCD_DXDCG8448_H
#define __LCD_DXDCG8448_H

#include "sys.h"


#define LCD_MX 1

 //sfr   P1=0x90;
// sbit  RS=   0x92;      //6
// sbit  REST= 0x90;    //5
// sbit  CLK = 0x94;
// sbit  DI  = 0x93;
// sbit  CS_S =0x91;   //4

//RS=A0
#define LCD_RS_OUT 									PCout(6)
#define	LCD_RS_GPIO_CLK							RCC_APB2Periph_GPIOC 
#define	LCD_RS_GPIO_PIN							GPIO_Pin_6
#define	LCD_RS_GPIO_PORT						GPIOC

//REST
#define LCD_REST_OUT 									PCout(4)
#define	LCD_REST_GPIO_CLK							RCC_APB2Periph_GPIOC 
#define	LCD_REST_GPIO_PIN							GPIO_Pin_4
#define	LCD_REST_GPIO_PORT						GPIOC

//CLK
#define LCD_CLK_OUT 									PBout(3)
#define	LCD_CLK_GPIO_CLK							RCC_APB2Periph_GPIOB 
#define	LCD_CLK_GPIO_PIN							GPIO_Pin_3
#define	LCD_CLK_GPIO_PORT							GPIOB

//DI
#define LCD_DI_OUT  									PBout(5)
#define	LCD_DI_GPIO_CLK								RCC_APB2Periph_GPIOB 
#define	LCD_DI_GPIO_PIN								GPIO_Pin_5
#define	LCD_DI_GPIO_PORT							GPIOB

//CS
#define LCD_CS_OUT 										PBout(4)
#define	LCD_CS_GPIO_CLK								RCC_APB2Periph_GPIOB 
#define	LCD_CS_GPIO_PIN								GPIO_Pin_4
#define	LCD_CS_GPIO_PORT							GPIOB

//BL
#define LCD_BL_OUT 									TIM3->CCR3
#define	LCD_BL_GPIO_CLK							RCC_APB2Periph_GPIOB
#define	LCD_BL_GPIO_PIN							GPIO_Pin_0
#define	LCD_BL_GPIO_PORT						GPIOB

#define READ_LCD_BL_OUT 						GPIO_ReadOutputDataBit(LCD_BL_GPIO_PORT,LCD_BL_GPIO_PIN)

/*LCD»º³å*/
#define LCD_BUFF_LEN (102*10)

extern char LCD_buff[LCD_BUFF_LEN];

void LCD_Init(void);
void LCD_BL_Init(int BLLum);
u8 SPIx_ReadWriteByte(u8 TxData);
void LCD_Delay_us(u32 us);
void LCD_Delay_ns(u16 ns);
void LCD_Delay_ms(u16 us);
void LCD_WriteCommand(unsigned char dat);
void LCD_WriteData(unsigned char dat);
void LCD_write_dot(unsigned char x,unsigned char y,char data);
void LCD_Set_disp_Addr(unsigned char x,unsigned char y);
void LCD_Set_ram_addr(unsigned char x,unsigned char y,unsigned char tmp);
void LCD_clear(void);
void LCD_clear_range(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl);
void LCD_PutAscii_5x8(unsigned char x, unsigned char y, char ch);
void LCD_Printf(unsigned char x, unsigned char y,char* ch);
void LCD_Printf_invert(unsigned char x, unsigned char y,char* ch,char p);
void LCD_PutImage(unsigned char x, unsigned char y,unsigned char xl, unsigned char yl,char* tmp);
void LCD_PutGB2312_12x12(unsigned char x, unsigned char y,char* ch);
void LCD_Printf_GB2312_12x12(unsigned char x, unsigned char y,char* ch);
void LCD_PutNUMBER_16x24(unsigned char x, unsigned char y,char ch);
void LCD_Printf_NUMBER_16x24(unsigned char x, unsigned char y,char* ch);
void LCD_PutNUMBER_10x15(unsigned char x, unsigned char y,char ch);
void LCD_Printf_NUMBER_10x15(unsigned char x, unsigned char y,char* ch);
void LCD_PutAscii_5x8_invert(unsigned char x, unsigned char y, char ch);
void LCD_PutASCII_6x12(unsigned char x, unsigned char y,char ch);
void LCD_Printf_12x12(unsigned char x, unsigned char y,char* ch);
void LCD_PutASCII_7x11(unsigned char x, unsigned char y,char ch);
void LCD_PutGB2312_10x10(unsigned char x, unsigned char y,char* ch);
void LCD_Printf_10x10(unsigned char x, unsigned char y,char* ch);
#endif
