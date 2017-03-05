#ifndef __PCF8563_H
#define __PCF8563_H
#include "sys.h"

#define RTC_IIC_SDA_OUT 									PBout(9)
#define	RTC_IIC_SDA_GPIO_CLK							RCC_APB2Periph_GPIOB 
#define	RTC_IIC_SDA_GPIO_PIN							GPIO_Pin_9
#define	RTC_IIC_SDA_GPIO_PORT							GPIOB

#define RTC_IIC_SCL_OUT 									PBout(8)
#define	RTC_IIC_SCL_GPIO_CLK							RCC_APB2Periph_GPIOB 
#define	RTC_IIC_SCL_GPIO_PIN							GPIO_Pin_8
#define	RTC_IIC_SCL_GPIO_PORT							GPIOB

#define RTC_IIC_SDA_IN()	   GPIO_ReadInputDataBit(RTC_IIC_SDA_GPIO_PORT,RTC_IIC_SDA_GPIO_PIN)

#define PCF8563_Addr     		0xa2

#define	Control_status_1		0x00
#define	Control_status_2		0x01
#define	VL_seconds					0x02
#define	Minutes							0x03
#define	Hours								0x04
#define	Days								0x05
#define	Weekdays						0x06
#define	Century_months			0x07
#define	Years								0x08
#define	Minute_alarm				0x09
#define	Hour_alarm					0x0A
#define	Day_alarm						0x0B
#define	Weekday_alarm				0x0C
#define	CLKOUT_control			0x0D
#define	Timer_control				0x0E
#define	Timer								0x0F

typedef struct 
{
	u8 Second;
	u8 Minute;
	u8 Hour;
	u8 Day;
	u8 Month;
	u8 Week;
	u8 Year;
}	RTC_TimeTypeDef;

RTC_TimeTypeDef PCF8563_Get_Time(void);
void PCF8563_Set_Time(RTC_TimeTypeDef su_Time);
void PCF8563_Init(void);

void RTC_Init(void);
void RTC_Delay(u32 us);
void RTC_IIC_SDA_Mode_IN_IPU(void);
void RTC_IIC_SDA_Mode_Out_OD(void);
u8 RTC_IIC_Wait_Ack(void);
u8 RTC_IIC_ReadByte(u8 dev, u8 reg, u8 *data);
u8 RTC_IIC_ReadBytes(u8 dev, u8 reg, u8 length, u8 *data);
unsigned char RTC_IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char RTC_IIC_WriteByte(unsigned char dev, unsigned char reg, unsigned char data);

#endif
