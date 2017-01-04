#ifndef __RTC_H
#define __RTC_H

#include "stm32f10x.h"

#define RTC_SDA(x)		GPIOB->ODR=(GPIOB->ODR&~(1<<9))|(x ? (1<<9):0)	//PB9	
#define RTC_SCL(x)		GPIOB->ODR=(GPIOB->ODR&~(1<<8))|(x ? (1<<8):0)	//PB8	
#define IS_SDA				(GPIOB->IDR&(1<<9))?1:0		


//¶ÁÈ¡HT1381 IOÏß		
#define	RTC_SDA_RCC								RCC_APB2Periph_GPIOB 
#define	RTC_SDA_PIN								GPIO_Pin_9
#define	RTC_SDA_GPIOX							GPIOB

#define	RTC_SCL_RCC								RCC_APB2Periph_GPIOB 
#define	RTC_SCL_PIN								GPIO_Pin_8
#define	RTC_SCL_GPIOX							GPIOB

#define RTC_ADDR     				0xa2

#define	ADD_SECOND					0x02
#define	ADD_MINUTES					0x03
#define	ADD_HOUR						0x04
#define	ADD_DAY							0x05
#define	ADD_WEEK						0x06
#define	ADD_MONTH						0x07
#define	ADD_YEAR						0x08

typedef struct 
{
	u8	Second;
	u8	Minutes;
	u8	Hour;
	u8	Day;
	u8	Week;
	u8	Month;
	u16	Year;
}Stru_Time;

void fnRTC_Init(void);
void fnRTC_GetTime(Stru_Time* Time);
void fnRTC_SetTime(Stru_Time su_Time);


void RTC_Delay(u32 us);
void RTC_IIC_SDA_Mode_IN_IPU(void);
void RTC_IIC_SDA_Mode_Out_OD(void);
u8 RTC_IIC_Wait_Ack(void);
u8 RTC_IIC_ReadByte(u8 dev, u8 reg, u8 *data);
u8 RTC_IIC_ReadBytes(u8 dev, u8 reg, u8 length, u8 *data);
unsigned char RTC_IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char RTC_IIC_WriteByte(unsigned char dev, unsigned char reg, unsigned char data);

#endif
