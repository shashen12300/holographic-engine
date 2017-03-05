#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f10x.h"

#define SPI_FLASH_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOB
#define SPI_FLASH_SPI_SCK_PIN                   GPIO_Pin_13                  
#define SPI_FLASH_SPI_SCK_GPIO_PORT             GPIOB   

#define SPI_FLASH_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOB
#define SPI_FLASH_SPI_MISO_PIN                  GPIO_Pin_14                  
#define SPI_FLASH_SPI_MISO_GPIO_PORT            GPIOB         

#define SPI_FLASH_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOB
#define SPI_FLASH_SPI_MOSI_PIN                  GPIO_Pin_15    
#define SPI_FLASH_SPI_MOSI_GPIO_PORT            GPIOB             

#define SPI_FLASH_CS_GPIO_CLK                   RCC_APB2Periph_GPIOB
#define SPI_FLASH_CS_PIN                        GPIO_Pin_12                  
#define SPI_FLASH_CS_GPIO_PORT                  GPIOB                       

#define  sFLASH_ID              0xEF4000
	
//#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(SPI_FLASH_CS_GPIO_PORT, SPI_FLASH_CS_PIN)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(SPI_FLASH_CS_GPIO_PORT, SPI_FLASH_CS_PIN)

#define SPI_FLASH_SPI_SCK_0()		GPIO_ResetBits(SPI_FLASH_SPI_SCK_GPIO_PORT, GPIO_Pin_13)
#define SPI_FLASH_SPI_SCK_1()		GPIO_SetBits(SPI_FLASH_SPI_SCK_GPIO_PORT, GPIO_Pin_13)

#define SPI_FLASH_SPI_MOSI_0()		GPIO_ResetBits(SPI_FLASH_SPI_MOSI_GPIO_PORT, SPI_FLASH_SPI_MOSI_PIN)
#define SPI_FLASH_SPI_MOSI_1()		GPIO_SetBits(SPI_FLASH_SPI_MOSI_GPIO_PORT, SPI_FLASH_SPI_MOSI_PIN)

#define SPI_FLASH_SPI_MISO_HIGH()	(GPIO_ReadInputDataBit(SPI_FLASH_SPI_MISO_GPIO_PORT, SPI_FLASH_SPI_MISO_PIN) == Bit_SET)

void SPI_FLASH_Init(void);
void SPI_FLASH_SectorErase(u32 SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
u32 SPI_FLASH_ReadID(void);
u32 SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);


u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);
void SPI_Flash_Delay(void);
void SPI_FLASH_CS_LOW(void);
#endif /* __SPI_FLASH_H */

