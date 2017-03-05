/*
*********************************************************************************************************
*	                                  
*	ģ������ : nRF24L01����ģ��
*	�ļ����� : bsp_nrf24l01.c
*	��    �� : V1.0
*	˵    �� : nRF24L01����
*	�޸ļ�¼ :
*		�汾��    ����          ����          ˵��
*		v1.0    2015-02-12     Eric2013	      �װ�
*
*	Copyright (C), 2015-2016, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "BSP_nrf24l01.h"
#include "includes.h"
#include "KD_CH4.h"

/* ����GPIO�˿� */

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
	

/* ���Ų��������üĴ�������ʽ���ӿ�����ٶ� */
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

/* ����˺ͽ��ն˵�ַ */
uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x55,0x55,0x55,0x55,0x55};
uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};   //Ŀ���ַ


/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_InitHard
*	����˵��: SPI����
*	��    �Σ���
*	�� �� ֵ: ��		                   			  
*********************************************************************************************************
*/
void nRF24L01_Init(void)
{
	uint8_t CPUID[12],i;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*ʹ��GPIOʱ�� */
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
	/* ��������csn���ţ�NRF�������״̬ */
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
*	�� �� ��: nRF24L01_WriteReadByte
*	����˵��: ������NRF��/дһ�ֽ�����
*	��    ��: д�������
*	�� �� ֵ: ��ȡ�õ�����		        
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
*	�� �� ��: nRF24L01_WriteReg
*	����˵��: ������nRF24L01�ض��ļĴ���д������
*	��    ��: _ucRegAddr: nRF24L01������+�Ĵ�����ַ��
 		      _usValue:   ��Ҫ��Ĵ���д�������
*	�� �� ֵ: nRF24L01��status�Ĵ�����״̬		        
*********************************************************************************************************
*/
static uint8_t nRF24L01_WriteReg(uint8_t _ucRegAddr, uint8_t _usValue)
{
	uint8_t ucStatus;
	
	nRF24L01_CE_0();
	
	/* �õ�CSN��ʹ��SPI���� */
	nRF24L01_CSN_0();
				
	/* ��������Ĵ����� */
	ucStatus = nRF24L01_WriteReadByte(_ucRegAddr);
		 
	 /* ��Ĵ���д������ */
	nRF24L01_WriteReadByte(_usValue); 
	          
	/* CSN���ߣ���� */	   
	nRF24L01_CSN_1();	
		
	/* ����״̬�Ĵ�����ֵ */
	return(ucStatus);
}

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_ReadReg
*	����˵��: ���ڴ�nRF24L01�ض��ļĴ�����������
*	��    ��: reg: nRF24L01������+�Ĵ�����ַ
*	�� �� ֵ: �Ĵ����е�����		        
*********************************************************************************************************
*/
uint8_t nRF24L01_ReadReg(uint8_t _ucRegAddr)
{
 	uint8_t usValue;

	nRF24L01_CE_0();
	
	/* �õ�CSN��ʹ��SPI���� */
 	nRF24L01_CSN_0();
				
  	 /* ���ͼĴ����� */
	nRF24L01_WriteReadByte(_ucRegAddr); 

	 /* ��ȡ�Ĵ�����ֵ */
	usValue = nRF24L01_WriteReadByte(NOP);
	            
   	/*CSN���ߣ����*/
	nRF24L01_CSN_1();		
   	
	return usValue;
}	

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_ReadBuf
*	����˵��: ���ڴ�nRF24L01�ļĴ����ж���һ������
*	��    ��: _ucRegAddr: nRF24L01������+�Ĵ�����ַ��
 		      _pBuf��     ���ݻ����ַ��
		      _ucLen:     _pBuf�ݳ���
*	�� �� ֵ: nRF24L01��status�Ĵ�����״̬		        
*********************************************************************************************************
*/
static uint8_t nRF24L01_ReadBuf(uint8_t _ucRegAddr, uint8_t *_pBuf, uint8_t _ucLen)
{
 	uint8_t ucStatus, i;

	nRF24L01_CE_0();
	
	/* �õ�CSN��ʹ��SPI���� */
	nRF24L01_CSN_0();
		
	/*���ͼĴ�����*/		
	ucStatus = nRF24L01_WriteReadByte(_ucRegAddr); 

 	/*��ȡ����������*/
	for(i = 0; i < _ucLen; i++)
	{
		_pBuf[i] = nRF24L01_WriteReadByte(NOP);
	}
	    
	/* CSN���ߣ���� */
	nRF24L01_CSN_1();	
		
 	return ucStatus;	
}

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_WriteBuf
*	����˵��: ������nRF24L01�ļĴ�����д��һ������
*	��    �Σ�_ucRegAddr: nRF24L01������+�Ĵ�����ַ��
 		      _pBuf��     ���ݻ����ַ��
		      _ucLen:     _pBuf�����ݳ��ȡ�
*	�� �� ֵ: NRF��status�Ĵ�����״̬��	        
*********************************************************************************************************
*/
static uint8_t nRF24L01_WriteBuf(uint8_t _ucRegAddr, uint8_t *_pBuf, uint8_t _ucLen)
{
	 uint8_t ucStatus,i;
	
	 nRF24L01_CE_0();
	
   	 /*�õ�CSN��ʹ��SPI����*/
	 nRF24L01_CSN_0();			

	 /*���ͼĴ�����*/	
  	 ucStatus = nRF24L01_WriteReadByte(_ucRegAddr); 
 	
  	  /*�򻺳���д������*/
	 for(i = 0; i < _ucLen; i++)
	{
		nRF24L01_WriteReadByte(*_pBuf++);
	}
	  	   
	/*CSN���ߣ����*/
	nRF24L01_CSN_1();			
  
  	return (ucStatus);	
}

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_RxMode
*	����˵��: ����nRF24L01�����ڽ���ģʽ
*	��    ��: ��
*	�� �� ֵ: ��		        
*********************************************************************************************************
*/
void nRF24L01_RxMode(void)
{
	nRF24L01_CE_0();
	nRF24L01_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);  /* дRX�ڵ��ַ */
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_AA, 0x01);               			/* ʹ��ͨ��0���Զ�Ӧ�� */    
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_RXADDR, 0x01);           			/* ʹ��ͨ��0�Ľ��յ�ַ */    
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_CH, CHANAL);             			/* ����RFͨ��Ƶ�� */    
	nRF24L01_WriteReg(NRF_WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);  			/* ѡ��ͨ��0����Ч���ݿ�� */      
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_SETUP, 0x0f); /* ����TX�������,0db����,2Mbps,���������濪�� */   
	nRF24L01_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);   /* ���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ */ 
	
	/*CE���ߣ��������ģʽ*/	
	nRF24L01_CE_1(); 
}    

void nRF24L01_Delay_us(u32 us)
{
	us=us*50;
	while(--us);
}

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_TxMode
*	����˵��: ����nRF24L01�����ڷ���ģʽ
*	��    ��: ��
*	�� �� ֵ: ��		        
*********************************************************************************************************
*/
void nRF24L01_TxMode(void)
{  
	nRF24L01_CE_0();
	nRF24L01_WriteBuf(NRF_WRITE_REG+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    /* дTX�ڵ��ַ */ 
	nRF24L01_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); /* ����TX�ڵ��ַ,��ҪΪ��ʹ��ACK */   
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_AA, 0x01);     /* ʹ��ͨ��0���Զ�Ӧ�� */    	
	nRF24L01_WriteReg(NRF_WRITE_REG+EN_RXADDR, 0x01); /* ʹ��ͨ��0�Ľ��յ�ַ */  	
	nRF24L01_WriteReg(NRF_WRITE_REG+SETUP_RETR, 0x0f);/* �����Զ��ط����ʱ��:250us + 86us;����Զ��ط�����:10�� */	
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_CH, CHANAL);   /* ����RFͨ��ΪCHANAL */	
	nRF24L01_WriteReg(NRF_WRITE_REG+RF_SETUP, 0x0f);  /* ����TX�������,0db����,2Mbps,���������濪�� */   	
	nRF24L01_WriteReg(NRF_WRITE_REG+CONFIG, 0x0e);    /* ���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж� */	
	
	/*CE���ߣ����뷢��ģʽ*/	
	nRF24L01_CE_1();
	nRF24L01_Delay_us(100);  /* CEҪ����һ��ʱ��Ž��뷢��ģʽ��ʱ�����10us */
}

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_ConnectCheck
*	����˵��: ��Ҫ����nRF24L01_��MCU�Ƿ���������
*	��    ��: ��
*	�� �� ֵ: 1 ��ʾ����������0 ��ʾ���Ӳ�����	        
*********************************************************************************************************
*/
uint8_t nRF24L01_ConnectCheck(void)
{
	uint8_t ucBuf[TX_ADR_WIDTH];

	/*д��TX_ADR_WIDTH���ֽڵĵ�ַ.  */  
	nRF24L01_WriteBuf(NRF_WRITE_REG+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);

	/*����д��ĵ�ַ */
	nRF24L01_ReadBuf(TX_ADDR, ucBuf, TX_ADR_WIDTH); 
	 
	/* ���ڵ���Ŀ�� */
//	printf("ucBuf[0] = %d, TX_ADDRESS[0] = %d\r\n", ucBuf[0], TX_ADDRESS[0]);
//	printf("ucBuf[1] = %d, TX_ADDRESS[1] = %d\r\n", ucBuf[1], TX_ADDRESS[1]);
//	printf("ucBuf[2] = %d, TX_ADDRESS[2] = %d\r\n", ucBuf[2], TX_ADDRESS[2]);
//	printf("ucBuf[3] = %d, TX_ADDRESS[3] = %d\r\n", ucBuf[3], TX_ADDRESS[3]);
//	printf("ucBuf[4] = %d, TX_ADDRESS[4] = %d\r\n", ucBuf[4], TX_ADDRESS[4]);
	
	/* �Ƚ�д������ݺͶ������Ƿ���ͬ */
	if(strncmp((char *)TX_ADDRESS, (char *)ucBuf, TX_ADR_WIDTH) == 0)
	{
		return 1;  /* ��ͬ */
	}
	else
	{
		return 0;  /* ����ͬ */
	}
}

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_TxData
*	����˵��: ������nRF24L01�ķ��ͻ�������д������
*	��    ��: _pTxBuf ���ݻ����ַ
*	�� �� ֵ: ���ͽ�����ɹ�����TX_DS, ʧ�ܷ���MAX_RT��0		        
*********************************************************************************************************
*/
uint8_t nRF24L01_TxData(uint8_t *_pTxBuf)
{
	uint8_t ucState;
	uint32_t ulCount = 0;   

	/*CEΪ�ͣ��������ģʽ1*/
	nRF24L01_CE_0();

	/*д���ݵ�_pTxBuf���32���ֽ�*/						
	nRF24L01_WriteBuf(WR_TX_PLOAD, _pTxBuf, TX_PLOAD_WIDTH);

	/*CEΪ�ߣ�_pTxBuf�ǿգ��������ݰ� */   
	nRF24L01_CE_1();
	  	
	/*
	  �ȴ���������ж�                            
   	  while(nRF24L01_IRQ_Read()!=0); 
      ѡ���������ַ�ʽ������Ч��ֹ������������ʱ���������״̬ 
	*/
	while((nRF24L01_IRQ_Read() != 0) && (ulCount < 65535))
	{
		ulCount++;
	}
	
	if(ulCount >= 65535) 
	{
		return 0;		
	}
	
	/* ��ȡ״̬�Ĵ�����ֵ */                              
	ucState = nRF24L01_ReadReg(STATUS);

	/*���TX_DS��MAX_RT�жϱ�־*/                  
	nRF24L01_WriteReg(NRF_WRITE_REG+STATUS, ucState); 	

	nRF24L01_WriteReg(FLUSH_TX,NOP);      /* ���TX FIFO�Ĵ��� */ 

	 /*�ж��ж�����*/ 
	/* �ﵽ����ط����� */
	if(ucState & MAX_RT)                     
	{
		return MAX_RT;
	}
	/* ������� */
	else if(ucState & TX_DS)
	{
		return TX_DS;
	} 
	/* ����ԭ����ʧ�� */	
	else
	{
		return 0;               
	}
} 

/*
*********************************************************************************************************
*	�� �� ��: nRF24L01_RxData
*	����˵��: ���ڴ�nRF24L01�Ľ��ջ������ж�������
*	��    ��: _pRxBuf ���ݻ����ַ
*	�� �� ֵ: ���ս�����ɹ�����RX_DS, ʧ�ܷ���0		        
*********************************************************************************************************
*/
uint8_t nRF24L01_RxData(uint8_t *_pRxBuf)
{
	uint8_t ucState;
	uint32_t ulCount = 0;  

	nRF24L01_CE_1();	  /* �������״̬ */
	
	/*
	  �ȴ������ж�
	  while(nRF24L01_IRQ_Read()!=0);
	  ѡ���������ַ�ʽ������Ч��ֹ������������ʱ���������״̬ 
	*/
	while((nRF24L01_IRQ_Read() != 0) && (ulCount < 65535))
	{
		ulCount++;
	}
	
	if(ulCount >= 65535) 
	{
		return 0;		
	}
	
	nRF24L01_CE_0();  	 /* �������״̬ */

	/*��ȡstatus�Ĵ�����ֵ  */               
	ucState=nRF24L01_ReadReg(STATUS);
	 
	/* ����жϱ�־*/      
	nRF24L01_WriteReg(NRF_WRITE_REG+STATUS, ucState);

	/*�ж��Ƿ���յ�����*/
	if(ucState & RX_DR)    /* ���յ����� */
	{
		nRF24L01_ReadBuf(RD_RX_PLOAD, _pRxBuf, RX_PLOAD_WIDTH); /* ��ȡ���� */
		nRF24L01_WriteReg(FLUSH_RX, NOP);                       /* ���RX FIFO�Ĵ��� */
		return RX_DR; 
	}
	else 
    {
		return 0;   /* û�յ��κ����� */
	}			
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
