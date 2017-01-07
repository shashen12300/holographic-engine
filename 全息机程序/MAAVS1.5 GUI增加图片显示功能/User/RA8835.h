#ifndef __RA8835_H
#define __RA8835_H	
#include "stm32f10x.h"
/************************************************************************************/
//LCD引脚配置
/************************************************************************************/
//8080控制引脚配置
#define RD_PORT  GPIOB
#define RD_PIN   GPIO_Pin_14
#define WR_PORT  GPIOB
#define WR_PIN   GPIO_Pin_13
#define CS_PORT  GPIOB
#define CS_PIN   GPIO_Pin_15
#define A0_PORT  GPIOB
#define A0_PIN   GPIO_Pin_12
#define RST_PORT GPIOC
#define RST_PIN  GPIO_Pin_8
//8080数据引脚配置
#define BUSY_PIN  GPIO_Pin_6
#define DATA_PORT GPIOC
#define DATA_PORT_IN   (DATA_PORT->CRL=0x88888888) 
#define DATA_PORT_OUT  (DATA_PORT->CRL=0x33333333)
//#define lcm_WriteByte  (DATA_PORT->ODR)
#define lcm_WriteByte(data)  DATA_PORT->ODR&=0xff00,DATA_PORT->ODR|=data&0x00ff
//注意：如果控制脚更换端口，需在LCD_GPIO_Init函数中打开对应端口的时钟
//8080数据端口D0~D7需固定用STM32 GPIOX 0~7，如需更换需在LCD_GPIO_Init中更改初始化
#define RD_1      {GPIO_SetBits(RD_PORT, RD_PIN);}      //RD=1
#define RD_0      {GPIO_ResetBits(RD_PORT, RD_PIN);}    //RD=0
#define WR_1      {GPIO_SetBits(WR_PORT, WR_PIN);}      //WR=1
#define WR_0      {GPIO_ResetBits(WR_PORT, WR_PIN);}    //WR=0
#define CS_1      {GPIO_SetBits(CS_PORT, CS_PIN);}      //CS=1
#define CS_0      {GPIO_ResetBits(CS_PORT, CS_PIN);}    //CS=0
#define A0_1      {GPIO_SetBits(A0_PORT, A0_PIN);}      //A0=1
#define A0_0      {GPIO_ResetBits(A0_PORT, A0_PIN);}    //A0=0
#define RST_1     {GPIO_SetBits(RST_PORT, RST_PIN);}      //RST=1
#define RST_0     {GPIO_ResetBits(RST_PORT, RST_PIN);}    //RST=0
#define READ_BUSY GPIO_ReadInputDataBit(DATA_PORT,BUSY_PIN) //读D6判断控制器是否繁忙
/************************************************************************************/
//LCD显示相关配置
/************************************************************************************/
//显示方向二者选其一
#define DIR_Horizontal  //显示方向水平方向(横向显示)
//#define DIR_Vertical    //显示方向垂直方向(竖直显示)


void lcm_init(void); 
void clr_ram(void);
void delay_n_ms(unsigned int ms);

void changeDir(unsigned char dir);
void readDataByAddress(unsigned short int address,unsigned short int length,unsigned char * data);
void setPoint(unsigned int x,unsigned int y,unsigned short int pixel);
unsigned short int getPoint(unsigned int x,unsigned int y);
void DrawHLine(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int color);
void DrawVLine(unsigned short int x0,unsigned short int y0,unsigned short int y1,unsigned short int color);
void FillRect(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int y1,unsigned short int color);
void DrawBitmap(unsigned short int x0,unsigned short int y0,
							  unsigned short int xsize,unsigned short int ysize,
								const	unsigned char * pData);
void DrawAreaBitmap(unsigned short int x0,unsigned short int y0,
							  unsigned short int xsize,unsigned short int ysize,
								const	unsigned char *pData,unsigned short int area);
#endif

