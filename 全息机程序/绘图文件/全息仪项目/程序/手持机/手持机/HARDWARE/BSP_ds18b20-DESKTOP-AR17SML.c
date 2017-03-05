#include "bsp_ds18b20.h"
#include "includes.h"

/*
 * 函数名：DS18B20_GPIO_Config
 * 描述  ：配置DS18B20用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
static void DS18B20_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启DS18B20_PORT的外设时钟*/
	RCC_APB2PeriphClockCmd(DS18B20_CLK, ENABLE); 

	/*选择要控制的DS18B20_PORT引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化DS18B20_PORT*/
  	GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(DS18B20_PORT, DS18B20_PIN);	 
}

/*
 * 函数名：DS18B20_Mode_IPU
 * 描述  ：使DS18B20-DATA引脚变为输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DS18B20_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*选择要控制的DS18B20_PORT引脚*/	
	  GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;

	   /*设置引脚模式为浮空输入模式*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	

	  /*调用库函数，初始化DS18B20_PORT*/
	  GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}


/*
 * 函数名：DS18B20_Mode_Out_PP
 * 描述  ：使DS18B20-DATA引脚变为输出模式
 * 输入  ：无
 * 输出  ：无
 */
static void DS18B20_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*选择要控制的DS18B20_PORT引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化DS18B20_PORT*/
  	GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

/*
 *主机给从机发送复位脉冲
 */
static void DS18B20_Rst(void)
{
	/* 主机设置为推挽输出 */
	DS18B20_Mode_Out_PP();
	
	DS18B20_DATA_OUT(LOW);
	/* 主机至少产生480us的低电平复位信号 */
	DS18B20_Delay_us(750);
	
	/* 主机在产生复位信号后，需将总线拉高 */
	DS18B20_DATA_OUT(HIGH);
	
	/*从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲*/
	DS18B20_Delay_us(15);
}

/*
 * 检测从机给主机返回的存在脉冲
 * 0：成功
 * 1：失败
 */
static uint8_t DS18B20_Presence(void)
{
	uint8_t pulse_time = 0;
	
	/* 主机设置为上拉输入 */
	DS18B20_Mode_IPU();
	
	/* 等待存在脉冲的到来，存在脉冲为一个60~240us的低电平信号 
	 * 如果存在脉冲没有来则做超时处理，从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲
	 */
	while( DS18B20_DATA_IN() && pulse_time<100 )
	{
		pulse_time++;
		DS18B20_Delay_us(1);
	}	
	/* 经过100us后，存在脉冲都还没有到来*/
	if( pulse_time >=100 )
		return 1;
	else
		pulse_time = 0;
	
	/* 存在脉冲到来，且存在的时间不能超过240us */
	while( !DS18B20_DATA_IN() && pulse_time<240 )
	{
		pulse_time++;
		DS18B20_Delay_us(1);
	}	
	if( pulse_time >=240 )
		return 1;
	else
		return 0;
}

/*
 * 从DS18B20读取一个bit
 */
static uint8_t DS18B20_Read_Bit(void)
{
	uint8_t dat;
	
	/* 读0和读1的时间至少要大于60us */	
	DS18B20_Mode_Out_PP();
	/* 读时间的起始：必须由主机产生 >1us <15us 的低电平信号 */
	DS18B20_DATA_OUT(LOW);
	DS18B20_Delay_us(10);
	
	/* 设置成输入，释放总线，由外部上拉电阻将总线拉高 */
	DS18B20_Mode_IPU();
	//DS18B20_Delay_us(2);
	
	if( DS18B20_DATA_IN() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* 这个延时参数请参考时序图 */
	DS18B20_Delay_us(45);
	
	return dat;
}

/*
 * 从DS18B20读一个字节，低位先行
 */
uint8_t DS18B20_Read_Byte(void)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = DS18B20_Read_Bit();		
		dat = (dat) | (j<<i);
	}
	
	return dat;
}

/*
 * 写一个字节到DS18B20，低位先行
 */
void DS18B20_Write_Byte(uint8_t dat)
{
	uint8_t i, testb;
	DS18B20_Mode_Out_PP();
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* 写0和写1的时间至少要大于60us */
		if (testb)
		{			
			DS18B20_DATA_OUT(LOW);
			/* 1us < 这个延时 < 15us */
			DS18B20_Delay_us(8);
			
			DS18B20_DATA_OUT(HIGH);
			DS18B20_Delay_us(58);
		}		
		else
		{			
			DS18B20_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			DS18B20_Delay_us(70);
			
			DS18B20_DATA_OUT(HIGH);			
			/* 1us < Trec(恢复时间) < 无穷大*/
			DS18B20_Delay_us(2);
		}
	}
}

void DS18B20_Start(void)
{
	DS18B20_Rst();	   
	DS18B20_Presence();	 
	DS18B20_Write_Byte(0XCC);		/* 跳过 ROM */
	DS18B20_Write_Byte(0X44);		/* 开始转换 */
}

uint8_t DS18B20_Init(void)
{
	uint8_t re;
	
	CPU_SR_ALLOC();
	
	OS_CRITICAL_ENTER();	//进入临界区	

	DS18B20_GPIO_Config();
	DS18B20_Rst();
	
	re=DS18B20_Presence();
	
	OS_CRITICAL_EXIT();	//退出临界区	
	
	return re;
}

/*
 * 存储的温度是16 位的带符号扩展的二进制补码形式
 * 当工作在12位分辨率时，其中5个符号位，7个整数位，4个小数位
 *
 *         |---------整数----------|-----小数 分辨率 1/(2^4)=0.0625----|
 * 低字节  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |
 *
 *
 *         |-----符号位：0->正  1->负-------|-----------整数-----------|
 * 高字节  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
 *
 * 
 * 温度 = 符号位 + 整数 + 小数*0.0625
 */
float DS18B20_Get_Temp(void)
{
	//CPU_SR_ALLOC();
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	//OS_CRITICAL_ENTER();	//进入临界区	
	
	DS18B20_Rst();	   
	DS18B20_Presence();	 
	DS18B20_Write_Byte(0XCC);				/* 跳过 ROM */
	DS18B20_Write_Byte(0X44);				/* 开始转换 */
	
	DS18B20_Rst();
  DS18B20_Presence();
	DS18B20_Write_Byte(0XCC);				/* 跳过 ROM */
  DS18B20_Write_Byte(0XBE);				/* 读温度值 */
	
	tplsb = DS18B20_Read_Byte();		 
	tpmsb = DS18B20_Read_Byte(); 
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	if( s_tem < 0 )		/* 负温度 */
		f_tem = (~s_tem+1) * 0.0625;	
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
	//OS_CRITICAL_EXIT();	//退出临界区	
}

void DS18B20_Delay_us(u32 nus)
{
	u32 fac_us=9;
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;					//LOAD的值	    	 
	ticks=nus*fac_us; 							//需要的节拍数	  		 
	tcnt=0;
	//delay_osschedlock();						//阻止OS调度，防止打断us延时
	told=SysTick->VAL;        					//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;		//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;				//时间超过/等于要延迟的时间,则退出.
		}  
	};
	//delay_osschedunlock();						//恢复OS调度		
}

/*************************************END OF FILE******************************/
