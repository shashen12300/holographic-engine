/*
*********************************************************************************************************
*	                                  
*	模块名称 : nRF24L01驱动模块
*	文件名称 : bsp_nrf24l01.c
*	版    本 : V1.0
*	说    明 : nRF24L01驱动
*	修改记录 :
*		版本号    日期          作者          说明
*		v1.0    2015-02-12     Eric2013	      首版
*
*	Copyright (C), 2015-2016, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "BSP_nrf24l01.h"
#include "includes.h"
#include "KD_CH4.h"

/* 定义GPIO端口 */

#define RCC_SCK 	RCC_APB2Periph_GPIOB
#define PIN_SCK		GPIO_Pin_13
#define PORT_SCK	GPIOB

#define RCC_DIN 	RCC_APB2Periph_GPIOB
#define PIN_DIN		GPIO_Pin_15
#define PORT_DIN	GPIOB

#define RCC_DOUT 	RCC_APB2Periph_GPIOB
#define PIN_DOUT	GPIO_Pin_14
#define PORT_DOUT	GPIOB

#define RCC_CS 		RCC_APB2Periph_GPIOA
#define PIN_CS		GPIO_Pin_6
#define PORT_CS		GPIOA

#define RCC_CE 		RCC_APB2Periph_GPIOA
#define PIN_CE		GPIO_Pin_7
#define PORT_CE		GPIOA

#define RCC_IRQ 	RCC_APB2Periph_GPIOC
#define PIN_IRQ		GPIO_Pin_7
#define PORT_IRQ	GPIOC
	

/* 引脚操作，采用寄存器的形式，加快操作速度 */
#define nRF24L01_CSN_1()    GPIO_SetBits(PORT_CS, PIN_CS)
//#define nRF24L01_CSN_0()    GPIO_ResetBits(PORT_CS, PIN_CS)


#define nRF24L01_CE_1()    	GPIO_SetBits(PORT_CE, PIN_CE)
#define nRF24L01_CE_0()     GPIO_ResetBits(PORT_CE, PIN_CE)

#define nRF24L01_IRQ_Read()	  (GPIO_ReadInputDataBit(PORT_IRQ, PIN_IRQ))

#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(PORT_CS, PIN_CS)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(PORT_CS, PIN_CS)

#define SPI_FLASH_SPI_SCK_0()		GPIO_ResetBits(PORT_SCK, PIN_SCK)
#define SPI_FLASH_SPI_SCK_1()		GPIO_SetBits(PORT_SCK, PIN_SCK)

#define SPI_FLASH_SPI_MOSI_0()		GPIO_ResetBits(PORT_DIN, PIN_DIN)
#define SPI_FLASH_SPI_MOSI_1()		GPIO_SetBits(PORT_DIN, PIN_DIN)

#define SPI_FLASH_SPI_MISO_HIGH()	(GPIO_ReadInputDataBit(PORT_DOUT, PIN_DOUT) == Bit_SET)

/* 发射端和接收端地址 */
uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x55,0x55,0x55,0x55,0x55};
uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};   //目标地址


/*
*********************************************************************************************************
*	函 数 名: nRF24L01_InitHard
*	功能说明: SPI配置
*	形    参：无
*	返 回 值: 无		                   			  
*********************************************************************************************************
*/
void nRF24L01_Init(void)
{
	uint8_t CPUID[12],i;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*使能GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_SCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_SCK;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(PORT_SCK, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(RCC_DIN, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_DIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(PORT_DIN, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_DOUT, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_DOUT;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(PORT_DOUT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_CS, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_CS;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(PORT_CS, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_CE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_CE;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(PORT_CE, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_IRQ, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_IRQ;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(PORT_IRQ, &GPIO_InitStructure);	
	/* 用于拉高csn引脚，NRF进入空闲状态 */
	nRF24L01_CSN_1();  
	

} 
void nRF24L01_CSN_0(void)
{
	SPI_FLASH_SPI_SCK_0();
	nRF24L01_Delay_us(1);
	GPIO_ResetBits(PORT_CS, PIN_CS);
	nRF24L01_Delay_us(1);
}
/*
*********************************************************************************************************
*	函 数 名: nRF24L01_WriteReadByte
*	功能说明: 用于向NRF读/写一字节数据
*	形    参: 写入的数据
*	返 回 值: 读取得的数据		        
*********************************************************************************************************
*/
static uint8_t nRF24L01_WriteReadByte(uint8_t byte)
{  	
	uint8_t i;
	uint8_t read = 0;
	
	for(i = 0; i < 8; i++)
	{
		if (byte & 0x80)
		{
			SPI_FLASH_SPI_MOSI_1();
		}
		else
		{
			SPI_FLASH_SPI_MOSI_0();
		}
		
		
		byte <<= 1;
		nRF24L01_Delay_us(1);
		SPI_FLASH_SPI_SCK_1();
		
		read = read<<1;
		
		if (SPI_FLASH_SPI_MISO_HIGH())
		{
			read++;
		}
		
		
		nRF24L01_Delay_us(1);
		SPI_FLASH_SPI_SCK_0();
	}
	return read;
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_WriteReg
*	功能说明: 用于向nRF24L01特定的寄存器写入数据
*	形    参: _ucRegAddr: nRF24L01的命令+寄存器地址。
 		      _usValue:   将要向寄存器写入的数据
*	返 回 值: nRF24L01的status寄存器的状态		        
*********************************************************************************************************
*/
static uint8_t nRF24L01_WriteReg(uint8_t _ucRegAddr, uint8_t _usValue)
{
	uint8_t ucStatus;
	
	nRF24L01_CE_0();
	
	/* 置低CSN，使能SPI传输 */
	nRF24L01_CSN_0();
				
	/* 发送命令及寄存器号 */
	ucStatus = nRF24L01_WriteReadByte(_ucRegAddr);
		 
	 /* 向寄存器写入数据 */
	nRF24L01_WriteReadByte(_usValue); 
	          
	/* CSN拉高，完成 */	   
	nRF24L01_CSN_1();	
		
	/* 返回状态寄存器的值 */
	return(ucStatus);
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_ReadReg
*	功能说明: 用于从nRF24L01特定的寄存器读出数据
*	形    参: reg: nRF24L01的命令+寄存器地址
*	返 回 值: 寄存器中的数据		        
*********************************************************************************************************
*/
uint8_t nRF24L01_ReadReg(uint8_t _ucRegAddr)
{
 	uint8_t usValue;

	nRF24L01_CE_0();
	
	/* 置低CSN，使能SPI传输 */
 	nRF24L01_CSN_0();
				
  	 /* 发送寄存器号 */
	nRF24L01_WriteReadByte(_ucRegAddr); 

	 /* 读取寄存器的值 */
	usValue = nRF24L01_WriteReadByte(NOP);
	            
   	/*CSN拉高，完成*/
	nRF24L01_CSN_1();		
   	
	return usValue;
}	

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_ReadBuf
*	功能说明: 用于从nRF24L01的寄存器中读出一串数据
*	形    参: _ucRegAddr: nRF24L01的命令+寄存器地址。
 		      _pBuf：     数据缓冲地址。
		      _ucLen:     _pBuf据长度
*	返 回 值: nRF24L01的status寄存器的状态		        
*********************************************************************************************************
*/
static uint8_t nRF24L01_ReadBuf(uint8_t _ucRegAddr, uint8_t *_pBuf, uint8_t _ucLen)
{
 	uint8_t ucStatus, i;

	nRF24L01_CE_0();
	
	/* 置低CSN，使能SPI传输 */
	nRF24L01_CSN_0();
		
	/*发送寄存器号*/		
	ucStatus = nRF24L01_WriteReadByte(_ucRegAddr); 

 	/*读取缓冲区数据*/
	for(i = 0; i < _ucLen; i++)
	{
		_pBuf[i] = nRF24L01_WriteReadByte(NOP);
	}
	    
	/* CSN拉高，完成 */
	nRF24L01_CSN_1();	
		
 	return ucStatus;	
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_WriteBuf
*	功能说明: 用于向nRF24L01的寄存器中写入一串数据
*	形    参：_ucRegAddr: nRF24L01的命令+寄存器地址。
 		      _pBuf：     数据缓冲地址。
		      _ucLen:     _pBuf的数据长度。
*	返 回 值: NRF的status寄存器的状态。	        
*********************************************************************************************************
*/
static uint8_t nRF24L01_WriteBuf(uint8_t _ucRegAddr, uint8_t *_pBuf, uint8_t _ucLen)
{
	 uint8_t ucStatus,i;
	
	 nRF24L01_CE_0();
	
   	 /*置低CSN，使能SPI传输*/
	 nRF24L01_CSN_0();			

	 /*发送寄存器号*/	
  	 ucStatus = nRF24L01_WriteReadByte(_ucRegAddr); 
 	
  	  /*向缓冲区写入数据*/
	 for(i = 0; i < _ucLen; i++)
	{
		nRF24L01_WriteReadByte(*_pBuf++);
	}
	  	   
	/*CSN拉高，完成*/
	nRF24L01_CSN_1();			
  
  	return (ucStatus);	
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_RxMode
*	功能说明: 设置nRF24L01工作在接收模式
*	形    参: 无
*	返 回 值: 无		        
*********************************************************************************************************
*/
void nRF24L01_RxMode(void)
{
	nRF24L01_CE_0();
	nRF24L01_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);  /* 写RX节点地址 */
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_AA, 0x01);               			/* 使能通道0的自动应答 */    
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_RXADDR, 0x01);           			/* 使能通道0的接收地址 */    
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_CH, CHANAL);             			/* 设置RF通信频率 */    
	nRF24L01_WriteReg(NRF_WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);  			/* 选择通道0的有效数据宽度 */      
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_SETUP, 0x0f); /* 设置TX发射参数,0db增益,2Mbps,低噪声增益开启 */   
	nRF24L01_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);   /* 配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 */ 
	
	/*CE拉高，进入接收模式*/	
	nRF24L01_CE_1(); 
}    

void nRF24L01_Delay_us(u32 us)
{
	us=us*50;
	while(--us);
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_TxMode
*	功能说明: 设置nRF24L01工作在发送模式
*	形    参: 无
*	返 回 值: 无		        
*********************************************************************************************************
*/
void nRF24L01_TxMode(void)
{  
	nRF24L01_CE_0();
	nRF24L01_WriteBuf(NRF_WRITE_REG+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    /* 写TX节点地址 */ 
	nRF24L01_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); /* 设置TX节点地址,主要为了使能ACK */   
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_AA, 0x01);     /* 使能通道0的自动应答 */    	
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_RXADDR, 0x01); /* 使能通道0的接收地址 */  	
	nRF24L01_WriteReg(NRF_WRITE_REG+SETUP_RETR, 0x0f);/* 设置自动重发间隔时间:250us + 86us;最大自动重发次数:10次 */	
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_CH, CHANAL);   /* 设置RF通道为CHANAL */	
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_SETUP, 0x0f);  /* 设置TX发射参数,0db增益,2Mbps,低噪声增益开启 */   	
	nRF24L01_WriteReg(NRF_WRITE_REG+CONFIG, 0x0e);    /* 配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,发射模式,开启所有中断 */	
	
	/*CE拉高，进入发送模式*/	
	nRF24L01_CE_1();
	nRF24L01_Delay_us(100);  /* CE要拉高一段时间才进入发送模式，时间大于10us */
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_ConnectCheck
*	功能说明: 主要用于nRF24L01_与MCU是否正常连接
*	形    参: 无
*	返 回 值: 1 表示连接正常，0 表示连接不正常	        
*********************************************************************************************************
*/
uint8_t nRF24L01_ConnectCheck(void)
{
	uint8_t ucBuf[TX_ADR_WIDTH];

	/*写入TX_ADR_WIDTH个字节的地址.  */  
	nRF24L01_WriteBuf(NRF_WRITE_REG+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);

	/*读出写入的地址 */
	nRF24L01_ReadBuf(TX_ADDR, ucBuf, TX_ADR_WIDTH); 
	 
	/* 用于调试目的 */
//	printf("ucBuf[0] = %d, TX_ADDRESS[0] = %d\r\n", ucBuf[0], TX_ADDRESS[0]);
//	printf("ucBuf[1] = %d, TX_ADDRESS[1] = %d\r\n", ucBuf[1], TX_ADDRESS[1]);
//	printf("ucBuf[2] = %d, TX_ADDRESS[2] = %d\r\n", ucBuf[2], TX_ADDRESS[2]);
//	printf("ucBuf[3] = %d, TX_ADDRESS[3] = %d\r\n", ucBuf[3], TX_ADDRESS[3]);
//	printf("ucBuf[4] = %d, TX_ADDRESS[4] = %d\r\n", ucBuf[4], TX_ADDRESS[4]);
	
	/* 比较写入的数据和读出的是否相同 */
	if(strncmp((char *)TX_ADDRESS, (char *)ucBuf, TX_ADR_WIDTH) == 0)
	{
		return 1;  /* 相同 */
	}
	else
	{
		return 0;  /* 不相同 */
	}
}

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_TxData
*	功能说明: 用于向nRF24L01的发送缓冲区中写入数据
*	形    参: _pTxBuf 数据缓冲地址
*	返 回 值: 发送结果，成功返回TX_DS, 失败返回MAX_RT或0		        
*********************************************************************************************************
*/
uint8_t nRF24L01_TxData(uint8_t *_pTxBuf)
{
	uint8_t ucState;
	uint32_t ulCount = 0;   

	/*CE为低，进入待机模式1*/
	nRF24L01_CE_0();

	/*写数据到_pTxBuf最大32个字节*/						
	nRF24L01_WriteBuf(WR_TX_PLOAD, _pTxBuf, TX_PLOAD_WIDTH);

	/*CE为高，_pTxBuf非空，发送数据包 */   
	nRF24L01_CE_1();
	  	
	/*
	  等待发送完成中断                            
   	  while(nRF24L01_IRQ_Read()!=0); 
      选择下面这种方式可以有效防止发送数据阻塞时，死在这个状态 
	*/
	while((nRF24L01_IRQ_Read() != 0) && (ulCount < 65535))
	{
		ulCount++;
	}
	
	if(ulCount >= 65535) 
	{
		return 0;		
	}
	
	/* 读取状态寄存器的值 */                              
	ucState = nRF24L01_ReadReg(STATUS);

	/*清除TX_DS或MAX_RT中断标志*/                  
	nRF24L01_WriteReg(NRF_WRITE_REG+STATUS, ucState); 	

	nRF24L01_WriteReg(FLUSH_TX,NOP);      /* 清除TX FIFO寄存器 */ 

	 /*判断中断类型*/ 
	/* 达到最大重发次数 */
	if(ucState & MAX_RT)                     
	{
		return MAX_RT;
	}
	/* 发送完成 */
	else if(ucState & TX_DS)
	{
		return TX_DS;
	} 
	/* 其他原因发送失败 */	
	else
	{
		return 0;               
	}
} 

/*
*********************************************************************************************************
*	函 数 名: nRF24L01_RxData
*	功能说明: 用于从nRF24L01的接收缓冲区中读出数据
*	形    参: _pRxBuf 数据缓冲地址
*	返 回 值: 接收结果，成功返回RX_DS, 失败返回0		        
*********************************************************************************************************
*/
uint8_t nRF24L01_RxData(uint8_t *_pRxBuf)
{
	uint8_t ucState;
	uint32_t ulCount = 0;  

	nRF24L01_CE_1();	  /* 进入接收状态 */
	
	/*
	  等待接收中断
	  while(nRF24L01_IRQ_Read()!=0);
	  选择下面这种方式可以有效防止发送数据阻塞时，死在这个状态 
	*/
	while((nRF24L01_IRQ_Read() != 0) && (ulCount < 65535))
	{
		ulCount++;
	}
	
	if(ulCount >= 65535) 
	{
		return 0;		
	}
	
	nRF24L01_CE_0();  	 /* 进入待机状态 */

	/*读取status寄存器的值  */               
	ucState=nRF24L01_ReadReg(STATUS);
	 
	/* 清除中断标志*/      
	nRF24L01_WriteReg(NRF_WRITE_REG+STATUS, ucState);

	/*判断是否接收到数据*/
	if(ucState & RX_DR)    /* 接收到数据 */
	{
		nRF24L01_ReadBuf(RD_RX_PLOAD, _pRxBuf, RX_PLOAD_WIDTH); /* 读取数据 */
		nRF24L01_WriteReg(FLUSH_RX, NOP);                       /* 清除RX FIFO寄存器 */
		return RX_DR; 
	}
	else 
    {
		return 0;   /* 没收到任何数据 */
	}			
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
