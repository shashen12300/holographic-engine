#ifndef __RA8835_H
#define __RA8835_H	
#include "stm32f10x.h"
/************************************************************************************/
//LCD��������
/************************************************************************************/
//8080������������
#define RD_PORT  GPIOC
#define RD_PIN   GPIO_Pin_6
#define WR_PORT  GPIOC
#define WR_PIN   GPIO_Pin_7
#define CS_PORT  GPIOC
#define CS_PIN   GPIO_Pin_9
#define A0_PORT  GPIOC
#define A0_PIN   GPIO_Pin_8
#define RST_PORT GPIOC
#define RST_PIN  GPIO_Pin_10
//8080������������
#define BUSY_PIN  GPIO_Pin_6
#define DATA_PORT GPIOD
#define DATA_PORT_IN   (DATA_PORT->CRL=0x88888888) 
#define DATA_PORT_OUT  (DATA_PORT->CRL=0x33333333)
#define lcm_WriteByte  (DATA_PORT->ODR)
//ע�⣺������ƽŸ����˿ڣ�����LCD_GPIO_Init�����д򿪶�Ӧ�˿ڵ�ʱ��
//8080���ݶ˿�D0~D7��̶���STM32 GPIOX 0~7�������������LCD_GPIO_Init�и��ĳ�ʼ��
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
#define READ_BUSY GPIO_ReadInputDataBit(DATA_PORT,BUSY_PIN) //��D6�жϿ������Ƿ�æ
/************************************************************************************/
//LCD��ʾ�������
/************************************************************************************/
//��ʾ�������ѡ��һ
#define DIR_Horizontal  //��ʾ����ˮƽ����(������ʾ)
//#define DIR_Vertical    //��ʾ����ֱ����(��ֱ��ʾ)


void lcm_init(void); 
void clr_ram(void);
void delay_n_ms(unsigned int ms);


void setPoint(unsigned int x,unsigned int y,unsigned short int pixel);
unsigned short int getPoint(unsigned int x,unsigned int y);
void DrawHLine(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int color);
void DrawVLine(unsigned short int x0,unsigned short int y0,unsigned short int y1,unsigned short int color);
void FillRect(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int y1,unsigned short int color);
void DrawBitmap(unsigned short int x0,unsigned short int y0,
							  unsigned short int xsize,unsigned short int ysize,
								const	unsigned char * pData);
#endif

