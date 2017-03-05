#include "AD7705.h"
#include "includes.h"

char la;
void AD7705_Init(void)
{
	char i;
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(AD7705_CS_GPIO_CLK, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = AD7705_CS_GPIO_PIN;				 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
//	GPIO_Init(AD7705_CS_GPIO_PORT, &GPIO_InitStructure);		
//	AD7705_CS_OUT=1;
//	
//	AD7705_MCLK_1Mhz_Init();
//	AD7705_SPI2_Init();
//	
//	/*��λоƬ*/
//	for(i=0;i<5;i++)SPI2_ReadWriteByte(0xFF);
//	
//	//TM7705_ReadReg(REG_CLOCK);
//	
//	while(1)
//	{
//		AD7705_CS_OUT=0;
//		AD7705_Delay(2);
//		la=SPI2_ReadWriteByte(0x80);
//		AD7705_Delay(2);
//		AD7705_CS_OUT=1;
//		
//		AD7705_Delay(500);
//	}
	
}

u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}

void AD7705_SPI2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
		
}


void AD7705_Delay(u32 us)
{
	us=us*50;
	while(--us);
}


//end file
