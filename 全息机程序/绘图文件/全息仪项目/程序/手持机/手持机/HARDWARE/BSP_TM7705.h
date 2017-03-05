#ifndef __AD7705_H
#define __AD7705_H
#include "sys.h"

//#define AD7705_CS_OUT 									PCout(2)
//#define	AD7705_CS_GPIO_CLK							RCC_APB2Periph_GPIOC 
//#define	AD7705_CS_GPIO_PIN							GPIO_Pin_2
//#define	AD7705_CS_GPIO_PORT							GPIOC



	
void TM7705_MCLK_1Mhz_Init(void);

void TM7705_Delay_ms(u32 us);
void TM7705_Delay_us(u32 us);

void TM7705_Init(void);
void TM7705_CalibSelf(uint8_t _ch);
void TM7705_SytemCalibZero(uint8_t _ch);
void TM7705_SytemCalibFull(uint8_t _ch);
uint16_t TM7705_ReadAdc(uint8_t _ch);

void TM7705_WriteReg(uint8_t _RegID, uint32_t _RegValue);
uint32_t TM7705_ReadReg(uint8_t _RegID);

extern uint8_t g_TM7705_OK;		/* 全局标志，表示TM7705芯片是否连接正常  */
#endif

//endfile
