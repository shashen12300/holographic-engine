#ifndef __LCD_H
#define __LCD_H	
#include "sys.h"	 
#include "stdlib.h"

#define uchar      unsigned char
#define uint       unsigned int

//#define A0_0  GPIOC->BRR = GPIO_Pin_8
//#define A0_1  GPIOC->BSRR = GPIO_Pin_8

//#define WR_0  GPIOC->BRR = GPIO_Pin_7
//#define WR_1  GPIOC->BSRR = GPIO_Pin_7

//#define RD_0  GPIOC->BRR = GPIO_Pin_6
//#define RD_1  GPIOC->BSRR = GPIO_Pin_6

//#define CS_0  GPIOC->BRR = GPIO_Pin_9
//#define CS_1  GPIOC->BSRR = GPIO_Pin_9

#define LCD_RST_0  GPIOC->BRR = GPIO_Pin_10
#define LCD_RST_1  GPIOC->BSRR = GPIO_Pin_10

#define lcm_wr   	PCout(7)
#define lcm_rd  	PCout(6)
#define lcm_cs   	PCout(9)
#define lcm_a0   	PCout(8)
#define lcm_rst  	PCout(10)
#define lcm_busy  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)

//#define BUSY  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)

//#define DataOUT GPIOD->ODR

//#define DataIN  GPIOD->IDR

#define lcm_WriteByte GPIOD->ODR
/*--------------------------------------------------------------*/
//???????????

#define		SystemSet	0x40
#define		SleepIn		0x53
#define		DispOn		0x59
#define		DispOff		0x58
#define		Scroll		0x44
#define		Csrform		0x5d
#define		CgramAdr	0x50
#define		CsrDirR		0x4c
#define		CsrDirL		0x4d
#define		CsrDirU		0x4e
#define		CsrDirD		0x4f	
#define		HdotSet		0x5a
#define		Ovlay		0x5b
#define		CsrW		0x46
#define		CsrR		0x47
#define		mWrite		0x42	
#define		mRead		0x43

void LCD_PinInit(void);
void chk_busy(void);
void send_cmd(uchar cmd);
void send_dat(uchar dat);

void Delay_Nms(uint n);
void Delay_Nus(uint n);
#define LCD_SCROLL		0x44

void LcdClear(void);
//------------flag  0??  1??-----------------------------------------------
void LcdHZ(unsigned char x, unsigned int y,unsigned char *pdata,unsigned char flag); 
void LcdChar(unsigned char x, unsigned char y, unsigned char *pdata, unsigned char flag);
//-----------flag = 0 ??(?), bf=1 ??(?), bf=2 ????(??)-----------
void LcdPoint( unsigned int x, unsigned int y, unsigned char flag); 
//-----------flag = 0 ??(?), bf=1 ??(?), bf=2 ????(??)-----------
void LcdLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned char flag);
void lcm_init(void);
void LcdCsrW ( unsigned char x, unsigned char y);
void Delay_ns(); 

#endif

