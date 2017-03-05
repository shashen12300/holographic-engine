#ifndef __DS18B20_H
#define	__DS18B20_H

#include "stm32f10x.h"
//#include "bsp_SysTick.h"

#define HIGH  1
#define LOW   0

#define DS18B20_CLK     RCC_APB2Periph_GPIOD
#define DS18B20_PIN     GPIO_Pin_2                  
#define DS18B20_PORT		GPIOD

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DS18B20_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(DS18B20_PORT,DS18B20_PIN);\
					else		\
					GPIO_ResetBits(DS18B20_PORT,DS18B20_PIN)
 //读取引脚的电平
#define  DS18B20_DATA_IN()	   GPIO_ReadInputDataBit(DS18B20_PORT,DS18B20_PIN)

typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DS18B20_Data_TypeDef;

uint8_t DS18B20_Init(void);
float DS18B20_Get_Temp(void);
void DS18B20_Delay_us(u32 nus);
#endif /* __DS18B20_H */







