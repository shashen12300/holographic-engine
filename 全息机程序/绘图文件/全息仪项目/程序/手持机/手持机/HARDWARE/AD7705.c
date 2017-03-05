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
//	/*复位芯片*/
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
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}

void AD7705_SPI2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI2, ENABLE); //使能SPI外设
		
}


void AD7705_Delay(u32 us)
{
	us=us*50;
	while(--us);
}


//end file
