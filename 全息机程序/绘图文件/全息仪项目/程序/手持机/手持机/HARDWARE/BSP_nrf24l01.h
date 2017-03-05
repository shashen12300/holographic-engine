/*
*********************************************************************************************************
*	                                  
*	模块名称 : nRF24L01驱动模块
*	文件名称 : bsp_nrf24l01.h
*	版    本 : V1.0
*	说    明 : nRF24L01驱动头文件
*	修改记录 :
*		版本号    日期          作者          说明
*		v1.0    2015-02-12     Eric2013	      首版
*
*	Copyright (C), 2015-2016, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#ifndef __BSP_NRF24L01_H
#define __BSP_NRF24L01_H

#include "stm32f10x.h"


#define TX_ADR_WIDTH 	5  	 /* 发射地址宽度 */
#define TX_PLOAD_WIDTH  32   /* 发射数据通道有效数据宽度0~32Byte */

#define RX_ADR_WIDTH    5    /* 接收地址宽度 */
#define RX_PLOAD_WIDTH  32   /* 接收数据通道有效数据宽度0~32Byte */

#define CHANAL 40	/* 频道选择 */ 

/* nRF24L01的命令宏定义，详见nRF24L01功能使用文档 */
#define NRF_READ_REG    0x00  // Define read command to register
#define NRF_WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD 	0xA0  // Define TX payload register address
#define FLUSH_TX    	0xE1  // Define flush TX register command
#define FLUSH_RX    	0xE2  // Define flush RX register command
#define REUSE_TX_PL 	0xE3  // Define reuse TX payload register command
#define NOP         	0xFF  // Define No Operation, might be used to read status register

/* NRF24L01 相关寄存器地址的宏定义 */
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address

#define MAX_RT      0x10 //达到最大重发次数中断标志位
#define TX_DS		0x20 //发送完成中断标志位	 
#define RX_DR		0x40 //接收到数据中断标志位

/* 供外部文件调用的函数 */
void nRF24L01_Init(void);
void nRF24L01_RxMode(void);
void nRF24L01_TxMode(void);
uint8_t nRF24L01_TxData(uint8_t *_pTxBuf);
uint8_t nRF24L01_RxData(uint8_t *_pRxBuf);
uint8_t nRF24L01_ConnectCheck(void); 
void nRF24L01_Delay_us(u32 us);
uint8_t nRF24L01_ReadReg(uint8_t _ucRegAddr);
void nRF24L01_CSN_0(void);
#endif 

#define RCC_CE 		RCC_APB2Periph_GPIOA
#define PIN_CE		GPIO_Pin_7
#define PORT_CE		GPIOA

#define RCC_IRQ 	RCC_APB2Periph_GPIOC
#define PIN_IRQ		GPIO_Pin_7
#define PORT_IRQ	GPIOC

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
