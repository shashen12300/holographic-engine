#include "includes.h"
#include "KD_CH4.h"
#include "LCD_DXDCG8448.h"
#include "delay.h"

uint16_t ADC_ConvertedValue[ADC_ConBuffLen];

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(BSP_LED1_GPIO_CLK, ENABLE);	 //使能端口时钟
 GPIO_InitStructure.GPIO_Pin = BSP_LED1_GPIO_PIN;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(BSP_LED1_GPIO_PORT, &GPIO_InitStructure);		

 RCC_APB2PeriphClockCmd(BSP_LED2_GPIO_CLK, ENABLE);	 //使能端口时钟
 GPIO_InitStructure.GPIO_Pin = BSP_LED2_GPIO_PIN;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(BSP_LED2_GPIO_PORT, &GPIO_InitStructure);		
}
void BSP_Get_CPUID(uint8_t *data)
{
	u8 *unique_ID,i; 
	
	unique_ID=(u8*)(0x1FFFF7E8);
	for(i=0;i<12;i++)data[i]=unique_ID[i];
	
}

void Buzzer_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BSP_BUZZER_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_BUZZER_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_BUZZER_GPIO_PORT, &GPIO_InitStructure);	
	BSP_BUZZER_OUT=0;	
}

void Motor_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BSP_MOTOR_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_MOTOR_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_MOTOR_GPIO_PORT, &GPIO_InitStructure);		
	BSP_MOTOR_OUT=0;	
}

void Power_Init(void)
{
	
//	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BSP_AVDD_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_AVDD_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_AVDD_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(BSP_DVDD_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_DVDD_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_DVDD_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(BSP_EN_POWER_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_EN_POWER_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_EN_POWER_GPIO_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(BSP_5V_IN_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_5V_IN_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_5V_IN_GPIO_PORT, &GPIO_InitStructure);	
	
	/*高电平，关闭主电源*/
	BSP_EN_POWER_OUT=1;
	
	#ifndef  DEBUG
	/*延时2S*/
	HW_Delay_ms(800);
	#endif
	
	//低电平打开
	BSP_EN_POWER_OUT=0;
	
	BSP_AVDD_OUT=1;
	BSP_DVDD_OUT=1;
	
	/*ADC初始化*/
	
	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	RCC_APB2PeriphClockCmd(BSP_ADC_BATT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = BSP_ADC_BATT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(BSP_ADC_BATT_GPIO_PORT, &GPIO_InitStructure);
	
	/* DMA channel1 configuration */
//	DMA_DeInit(DMA1_Channel1);
//	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 			//ADC地址
//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	//内存地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = ADC_ConBuffLen;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						//外设地址固定
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  										//内存地址增量
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;															//循环传输
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//	
//	/* Enable DMA channel1 */
//	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	/* ADC1 configuration */	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;			//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	 				//禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;			//开启连续转换模式，即不停地进行ADC转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不使用外部触发转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 								//要转换的通道数目1
	ADC_Init(ADC1, &ADC_InitStructure);
	
	/*配置ADC时钟，为PCLK2的8分频，即9MHz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	
	/*配置ADC1的通道 序列为1 */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);

	/* Enable ADC1 DMA */
	//ADC_DMACmd(ADC1, ENABLE);
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	
	/*复位校准寄存器 */   
	ADC_ResetCalibration(ADC1);
	/*等待校准寄存器复位完成 */
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	/* ADC校准 */
	ADC_StartCalibration(ADC1);
	/* 等待校准完成*/
	while(ADC_GetCalibrationStatus(ADC1));
	
	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void Power_Off(void)
{

//	OS_ERR err;
	
	LCD_clear();
	
	LCD_Printf_GB2312_12x12((84-(4*13))/2,(48-12)/2,"正在关机");
	
	HW_Delay_ms(500);
	
	/*关闭电源*/
	BSP_EN_POWER_OUT=1;
	
	/*关闭背光*/
	LCD_BL_OUT=0;
	
	LCD_clear();
	BSP_LED1_OUT=1;
	BSP_LED2_OUT=1;
	
}
void Key_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BSP_KEY_FUN_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_KEY_FUN_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_KEY_FUN_GPIO_PORT, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(BSP_KEY_UP_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_KEY_UP_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_KEY_UP_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(BSP_KEY_LOW_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_KEY_LOW_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_KEY_LOW_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(BSP_KEY_POW_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_KEY_POW_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_KEY_POW_GPIO_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(BSP_KEY_STORE_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_KEY_STORE_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_KEY_STORE_GPIO_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(BSP_KEY_SEND_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = BSP_KEY_SEND_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(BSP_KEY_SEND_GPIO_PORT, &GPIO_InitStructure);
	
}


//获取电池电量
uint16_t GetBatt(void)
{
	//st
	//u32 BattNum=0;
	uint32_t ADC_VAL=0;
	uint16_t  BAT;
	
	float f_Vref=3.3,f_FullRange=4096,f_Voltage;
	
	
	
	//求和
	//for(i=0;i<ADC_ConBuffLen;i++)BattNum+=ADC_ConvertedValue[i];
	//求均值
	//ADC_VAL=BattNum/ADC_ConBuffLen;
	ADC_VAL=ADC_GetConversionValue(ADC1);
	
	//计算电池电压
	f_Voltage=f_Vref/f_FullRange*ADC_VAL*2;
	
	//转换为mV
	ADC_VAL=(u16)(f_Voltage*1000);
	
	if(ADC_VAL<=3400)
	{
		BAT=0;
	}
	else if(ADC_VAL>3400 && ADC_VAL<=3680)
	{
		BAT=(ADC_VAL-3400)/((3680-3400)/10);
	}
	else
	{
		BAT=(ADC_VAL-3680)/((4220-3680)/90)+10;
	}
	
	if(BAT>100)BAT=100;
	if(BAT<3)BAT=0;
	
	#ifdef NUN_BAT
		BAT=100;
	#endif 
	return BAT;
}

//获取电池电压
uint16_t GetBatt_Voltage(void)
{
//	u32 BattNum=0;
	uint32_t ADC_VAL=0;
//	uint16_t  BAT;
	
	float f_Vref=3.3,f_FullRange=4096,f_Voltage;
	
//	//求和
//	for(i=0;i<ADC_ConBuffLen;i++)BattNum+=ADC_ConvertedValue[i];
//	//求均值
//	ADC_VAL=BattNum/ADC_ConBuffLen;
	
	ADC_VAL=ADC_GetConversionValue(ADC1);
	
	//计算电池电压
	f_Voltage=f_Vref/f_FullRange*ADC_VAL*2;
	
	//转换为mV
	ADC_VAL=(u16)(f_Voltage*1000);
	
	return ADC_VAL;
}
void Buzzer_out(void)
{
	OS_ERR err;
	BSP_BUZZER_OUT=1;
	OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //延时
	BSP_BUZZER_OUT=0;
}
void Motor_out(void)
{
	OS_ERR err;
	BSP_MOTOR_OUT=1;
	OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //延时
	BSP_MOTOR_OUT=0;
	
}

void HW_Delay_ms(u32 us)
{
	us=us*1000;
	HW_Delay_us(us);
}

void HW_Delay_us(u32 us)
{
	us=us*10;
	while(--us);
}

//end file
