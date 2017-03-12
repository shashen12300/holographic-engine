#include "rtc.h"

u8 ls1[5];
/**************************实现函数********************************************
*函数原型:		void IIC_Init(void)
*功　　能:		初始化I2C对应的接口引脚。
*******************************************************************************/
void fnRTC_Init(void)
{
 
		GPIO_InitTypeDef  GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure; 
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

		RCC_APB2PeriphClockCmd(RTC_SDA_RCC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RTC_SDA_PIN;				 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(RTC_SDA_GPIOX, &GPIO_InitStructure);			

		RCC_APB2PeriphClockCmd(RTC_SCL_RCC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RTC_SCL_PIN;				 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(RTC_SCL_GPIOX, &GPIO_InitStructure);
		
		//定时器配置时间刷新
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
		/*TIM_Period--10000   TIM_Prescaler--71 -->中断周期为10ms*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=10000;		 								/* 自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (720 - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* 开启时钟 */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	

}



void fnRTC_GetTime(Stru_Time* Time)
{
	unsigned char temp[8];
	
	RTC_IIC_ReadBytes(RTC_ADDR,ADD_SECOND,7,temp);
	
	temp[0]&=0x7f;//去掉最高位
	temp[0]=((temp[0]>>4)*10+(temp[0]&0x0f));
	Time->Second=temp[0];
	
	temp[1]&=0x7f;//去掉最高位
	temp[1]=((temp[1]>>4)*10+(temp[1]&0x0f));
	Time->Minutes=temp[1];
	
	temp[2]&=0x3f;//去掉最高位
	temp[2]=((temp[2]>>4)*10+(temp[2]&0x0f));
	Time->Hour=temp[2];
	
	temp[3]&=0x3f;//去掉最高位
	temp[3]=((temp[3]>>4)*10+(temp[3]&0x0f));
	Time->Day=temp[3];
	
	temp[4]&=0x07;//去掉最高位
	temp[4]=((temp[4]>>4)*10+(temp[4]&0x0f));
	Time->Week=temp[4];
	
	temp[5]&=0x1f;//去掉最高位
	temp[5]=((temp[5]>>4)*10+(temp[5]&0x0f));
	Time->Month=temp[5];
	
	temp[6]=((temp[6]>>4)*10+(temp[6]&0x0f));
	Time->Year=temp[6];
	/*防止年大于100*/
	if(Time->Year<50)Time->Year+=2000;
	
}
void fnRTC_SetTime(Stru_Time su_Time)
{
	if(su_Time.Year>2000)
		su_Time.Year-=2000;
	/*转换为BCD格式*/
	su_Time.Second=((su_Time.Second/10)<<4)+(su_Time.Second%10);
	su_Time.Minutes=((su_Time.Minutes/10)<<4)+(su_Time.Minutes%10);
	su_Time.Hour=((su_Time.Hour/10)<<4)+(su_Time.Hour%10);
	su_Time.Day=((su_Time.Day/10)<<4)+(su_Time.Day%10);
	su_Time.Month=((su_Time.Month/10)<<4)+(su_Time.Month%10);
	su_Time.Year=((su_Time.Year/10)<<4)+(su_Time.Year%10);

	/*写入寄存器*/
	RTC_IIC_WriteByte(RTC_ADDR,ADD_SECOND,su_Time.Second);
	RTC_IIC_WriteByte(RTC_ADDR,ADD_MINUTES,su_Time.Minutes);
	RTC_IIC_WriteByte(RTC_ADDR,ADD_HOUR,su_Time.Hour);
	RTC_IIC_WriteByte(RTC_ADDR,ADD_DAY,su_Time.Day);
	RTC_IIC_WriteByte(RTC_ADDR,ADD_MONTH,su_Time.Month);
	RTC_IIC_WriteByte(RTC_ADDR,ADD_YEAR,su_Time.Year);

}

void RTC_IIC_SDA_Mode_IN_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;
	  	/*选择要控制的GPIOD引脚*/	
	  GPIO_InitStructure.GPIO_Pin = RTC_SDA_PIN;

	   /*设置引脚模式为浮空输入模式*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	
	  /*调用库函数，初始化GPIOD*/
	  GPIO_Init(RTC_SDA_GPIOX, &GPIO_InitStructure);	 
}

 void RTC_IIC_SDA_Mode_Out_OD(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	 	/*选择要控制的GPIOD引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = RTC_SDA_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化GPIOD*/
  	GPIO_Init(RTC_SDA_GPIOX, &GPIO_InitStructure);	 	 
}


/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Start(void)
*功　　能:		产生IIC起始信号
*******************************************************************************/
void RTC_IIC_Start(void)
{
	RTC_IIC_SDA_Mode_Out_OD();     //sda线输出
	RTC_SDA(1);	  	  
	RTC_SCL(1);
	RTC_Delay(4);
 	RTC_SDA(0);//START:when CLK is high,DATA change form high to low 
	RTC_Delay(4);
	RTC_SCL(0);//钳住I2C总线，准备发送或接收数据 
}

/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Stop(void)
*功　　能:	    //产生IIC停止信号
*******************************************************************************/	  
void RTC_IIC_Stop(void)
{
	RTC_IIC_SDA_Mode_Out_OD();//sda线输出
	RTC_SDA(0);
	RTC_SCL(0);//STOP:when CLK is high DATA change form low to high
 	RTC_Delay(4);
	RTC_SDA(1);
	RTC_SCL(1);//发送I2C总线结束信号
	RTC_Delay(4);							   	
}

/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_Wait_Ack(void)
*功　　能:	    等待应答信号到来 
//返回值：1，接收应答失败
//        0，接收应答成功
*******************************************************************************/
u8 RTC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	RTC_IIC_SDA_Mode_IN_IPU();      //SDA设置为输入
	RTC_SDA(1);RTC_Delay(1);	   
	RTC_SCL(1);RTC_Delay(1);	 
	while(IS_SDA)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			RTC_IIC_Stop();
			return 1;
		}
	  RTC_Delay(1);
	}
	RTC_SCL(0);//时钟输出0 	   
	return 0;  
} 

/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Ack(void)
*功　　能:	    产生ACK应答
*******************************************************************************/
void RTC_IIC_Ack(void)
{
	RTC_SCL(0);
	RTC_IIC_SDA_Mode_Out_OD();
	RTC_SDA(0);
	RTC_Delay(2);
	RTC_SCL(1);
	RTC_Delay(2);
	RTC_SCL(0);
}
	
/**************************实现函数********************************************
*函数原型:		void RTC_IIC_NAck(void)
*功　　能:	    产生NACK应答
*******************************************************************************/	    
void RTC_IIC_NAck(void)
{
	RTC_SCL(0);
	RTC_IIC_SDA_Mode_Out_OD();
	RTC_SDA(1);
	RTC_Delay(2);
	RTC_SCL(1);
	RTC_Delay(2);
	RTC_SCL(0);
}					 				     

/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Send_Byte(u8 txd)
*功　　能:	    IIC发送一个字节
*******************************************************************************/		  
void RTC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	RTC_IIC_SDA_Mode_Out_OD(); 	
	RTC_SCL(0);//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{              
		RTC_SDA((txd>>7)&0x01);
		txd<<=1; 	  
		RTC_Delay(2);   
		RTC_SCL(1);
		RTC_Delay(2);   
		RTC_SCL(0);
		RTC_Delay(2);
	}	 
} 	 
   
/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_Read_Byte(unsigned char ack)
*功　　能:	    //读1个字节，ack=1时，发送ACK，ack=0，发送nACK 
*******************************************************************************/  
u8 RTC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	RTC_IIC_SDA_Mode_IN_IPU();//SDA设置为输入
    for(i=0;i<8;i++ )
	{  
		RTC_SCL(0);
    RTC_Delay(2);  
		RTC_SCL(1);
        receive<<=1;
        if(IS_SDA)receive++;   
		RTC_Delay(2); 
    }					 
    if (ack)
        RTC_IIC_Ack(); //发送ACK 
    else
        RTC_IIC_NAck();//发送nACK  
    return receive;
}

/**************************实现函数********************************************
*函数原型:		unsigned char RTC_IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
*功　　能:	    读取指定设备 指定寄存器的一个值
输入	I2C_Addr  目标设备地址
		addr	   寄存器地址
返回   读出来的值
*******************************************************************************/ 
unsigned char RTC_IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
{
	unsigned char res=0;
	
	RTC_IIC_Start();	
	RTC_IIC_Send_Byte(I2C_Addr);	   //发送写命令
	res++;
	RTC_IIC_Wait_Ack();
	RTC_IIC_Send_Byte(addr); res++;  //发送地址
	RTC_IIC_Wait_Ack();	  
	//RTC_IIC_Stop();//产生一个停止条件	
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(I2C_Addr+1); res++;          //进入接收模式			   
	RTC_IIC_Wait_Ack();
	res=RTC_IIC_Read_Byte(0);	   
    RTC_IIC_Stop();//产生一个停止条件

	return res;
}


/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_ReadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*功　　能:	    读取指定设备 指定寄存器的 length个值
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要读的字节数
		*data  读出的数据将要存放的指针
返回   读出来的字节数量
*******************************************************************************/ 
u8 RTC_IIC_ReadBytes(u8 dev, u8 reg, u8 length, u8 *data)
{
    u8 count = 0;
	
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(dev);	   //发送写命令
	RTC_IIC_Wait_Ack();
	RTC_IIC_Send_Byte(reg);   //发送地址
    RTC_IIC_Wait_Ack();	  
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(dev+1);  //进入接收模式	
	RTC_IIC_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)data[count]=RTC_IIC_Read_Byte(1);  //带ACK的读数据
		 	else  data[count]=RTC_IIC_Read_Byte(0);	 //最后一个字节NACK
	}
    RTC_IIC_Stop();//产生一个停止条件
    return count;
}

/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_WriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*功　　能:	    将多个字节写入指定设备 指定寄存器
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要写的字节数
		*data  将要写的数据的首地址
返回   返回是否成功
*******************************************************************************/ 
u8 RTC_IIC_WriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(dev);	   //发送写命令
	RTC_IIC_Wait_Ack();
	RTC_IIC_Send_Byte(reg);   //发送地址
    RTC_IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		RTC_IIC_Send_Byte(data[count]); 
		RTC_IIC_Wait_Ack(); 
	 }
	RTC_IIC_Stop();//产生一个停止条件

    return 1; //status == 0;
}

/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_ReadByte(u8 dev, u8 reg, u8 *data)
*功　　能:	    读取指定设备 指定寄存器的一个值
输入	dev  目标设备地址
		reg	   寄存器地址
		*data  读出的数据将要存放的地址
返回   1
*******************************************************************************/ 
u8 RTC_IIC_ReadByte(u8 dev, u8 reg, u8 *data){
	*data=RTC_IIC_ReadOneByte(dev, reg);
    return 1;
}

/**************************实现函数********************************************
*函数原型:		unsigned char RTC_IIC_WriteByte(unsigned char dev, unsigned char reg, unsigned char data)
*功　　能:	    写入指定设备 指定寄存器一个字节
输入	dev  目标设备地址
		reg	   寄存器地址
		data  将要写入的字节
返回   1
*******************************************************************************/ 
unsigned char RTC_IIC_WriteByte(unsigned char dev, unsigned char reg, unsigned char data){
    return RTC_IIC_WriteBytes(dev, reg, 1, &data);
}

/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_WriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*功　　能:	    读 修改 写 指定设备 指定寄存器一个字节 中的多个位
输入	dev  目标设备地址
		reg	   寄存器地址
		bitStart  目标字节的起始位
		length   位长度
		data    存放改变目标字节位的值
返回   成功 为1 
 		失败为0
*******************************************************************************/ 
u8 RTC_IIC_WriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{

    u8 b;
    if (RTC_IIC_ReadByte(dev, reg, &b) != 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return RTC_IIC_WriteByte(dev, reg, b);
    } else {
        return 0;
    }
}

/**************************实现函数********************************************
*函数原型:		u8 RTC_IIC_writeBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*功　　能:	    读 修改 写 指定设备 指定寄存器一个字节 中的1个位
输入	dev  目标设备地址
		reg	   寄存器地址
		bitNum  要修改目标字节的bitNum位
		data  为0 时，目标位将被清0 否则将被置位
返回   成功 为1 
 		失败为0
*******************************************************************************/ 
u8 RTC_IIC_writeBit(u8 dev, u8 reg, u8 bitNum, u8 data){
    u8 b;
    RTC_IIC_ReadByte(dev, reg, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return RTC_IIC_WriteByte(dev, reg, b);
}

void RTC_Delay(u32 us)
{
	us=us*50;
	while(--us);
}

//end file
