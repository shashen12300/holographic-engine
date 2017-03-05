#include "BSP_PCF8563.h"
#include "includes.h"

u8 ls1[5];
/**************************实现函数********************************************
*函数原型:		void IIC_Init(void)
*功　　能:		初始化I2C对应的接口引脚。
*******************************************************************************/
void RTC_Init(void)
{
 
		GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RTC_IIC_SDA_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RTC_IIC_SDA_GPIO_PIN;				 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(RTC_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);			

		RCC_APB2PeriphClockCmd(RTC_IIC_SCL_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RTC_IIC_SCL_GPIO_PIN;				 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(RTC_IIC_SCL_GPIO_PORT, &GPIO_InitStructure);

}
void PCF8563_Init(void)
{
	RTC_Init();
}




RTC_TimeTypeDef PCF8563_Get_Time(void)
{
	RTC_TimeTypeDef Time;
	unsigned char temp[8];
	
	RTC_IIC_ReadBytes(PCF8563_Addr,VL_seconds,7,temp);
	
	temp[0]&=0x7f;//去掉最高位
	temp[0]=((temp[0]>>4)*10+(temp[0]&0x0f));
	Time.Second=temp[0];
	
	temp[1]&=0x7f;//去掉最高位
	temp[1]=((temp[1]>>4)*10+(temp[1]&0x0f));
	Time.Minute=temp[1];
	
	temp[2]&=0x3f;//去掉最高位
	temp[2]=((temp[2]>>4)*10+(temp[2]&0x0f));
	Time.Hour=temp[2];
	
	temp[3]&=0x3f;//去掉最高位
	temp[3]=((temp[3]>>4)*10+(temp[3]&0x0f));
	Time.Day=temp[3];
	
	temp[4]&=0x07;//去掉最高位
	temp[4]=((temp[4]>>4)*10+(temp[4]&0x0f));
	Time.Week=temp[4];
	
	temp[5]&=0x1f;//去掉最高位
	temp[5]=((temp[5]>>4)*10+(temp[5]&0x0f));
	Time.Month=temp[5];
	
	temp[6]=((temp[6]>>4)*10+(temp[6]&0x0f));
	Time.Year=temp[6];
	/*防止年大于100*/
	if(Time.Year>50)Time.Year=0;
	return Time;
}
void PCF8563_Set_Time(RTC_TimeTypeDef su_Time)
{
	
	/*转换为BCD格式*/
	su_Time.Second=((su_Time.Second/10)<<4)+(su_Time.Second%10);
	su_Time.Minute=((su_Time.Minute/10)<<4)+(su_Time.Minute%10);
	su_Time.Hour=((su_Time.Hour/10)<<4)+(su_Time.Hour%10);
	su_Time.Day=((su_Time.Day/10)<<4)+(su_Time.Day%10);
	su_Time.Month=((su_Time.Month/10)<<4)+(su_Time.Month%10);
	su_Time.Year=((su_Time.Year/10)<<4)+(su_Time.Year%10);

	/*写入寄存器*/
	RTC_IIC_WriteByte(PCF8563_Addr,VL_seconds,su_Time.Second);
	RTC_IIC_WriteByte(PCF8563_Addr,Minutes,su_Time.Minute);
	RTC_IIC_WriteByte(PCF8563_Addr,Hours,su_Time.Hour);
	RTC_IIC_WriteByte(PCF8563_Addr,Days,su_Time.Day);
	RTC_IIC_WriteByte(PCF8563_Addr,Century_months,su_Time.Month);
	RTC_IIC_WriteByte(PCF8563_Addr,Years,su_Time.Year);

}

void RTC_IIC_SDA_Mode_IN_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;
	  	/*选择要控制的GPIOD引脚*/	
	  GPIO_InitStructure.GPIO_Pin = RTC_IIC_SDA_GPIO_PIN;

	   /*设置引脚模式为浮空输入模式*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	
	  /*调用库函数，初始化GPIOD*/
	  GPIO_Init(RTC_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);	 
}

 void RTC_IIC_SDA_Mode_Out_OD(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	 	/*选择要控制的GPIOD引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = RTC_IIC_SDA_GPIO_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化GPIOD*/
  	GPIO_Init(RTC_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);	 	 
}


/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Start(void)
*功　　能:		产生IIC起始信号
*******************************************************************************/
void RTC_IIC_Start(void)
{
	RTC_IIC_SDA_Mode_Out_OD();     //sda线输出
	RTC_IIC_SDA_OUT=1;	  	  
	RTC_IIC_SCL_OUT=1;
	RTC_Delay(4);
 	RTC_IIC_SDA_OUT=0;//START:when CLK is high,DATA change form high to low 
	RTC_Delay(4);
	RTC_IIC_SCL_OUT=0;//钳住I2C总线，准备发送或接收数据 
}

/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Stop(void)
*功　　能:	    //产生IIC停止信号
*******************************************************************************/	  
void RTC_IIC_Stop(void)
{
	RTC_IIC_SDA_Mode_Out_OD();//sda线输出
	RTC_IIC_SCL_OUT=0;
	RTC_IIC_SDA_OUT=0;//STOP:when CLK is high DATA change form low to high
 	RTC_Delay(4);
	RTC_IIC_SCL_OUT=1; 
	RTC_IIC_SDA_OUT=1;//发送I2C总线结束信号
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
	RTC_IIC_SDA_OUT=1;RTC_Delay(1);	   
	RTC_IIC_SCL_OUT=1;RTC_Delay(1);	 
	while(RTC_IIC_SDA_IN())
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			RTC_IIC_Stop();
			return 1;
		}
	  RTC_Delay(1);
	}
	RTC_IIC_SCL_OUT=0;//时钟输出0 	   
	return 0;  
} 

/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Ack(void)
*功　　能:	    产生ACK应答
*******************************************************************************/
void RTC_IIC_Ack(void)
{
	RTC_IIC_SCL_OUT=0;
	RTC_IIC_SDA_Mode_Out_OD();
	RTC_IIC_SDA_OUT=0;
	RTC_Delay(2);
	RTC_IIC_SCL_OUT=1;
	RTC_Delay(2);
	RTC_IIC_SCL_OUT=0;
}
	
/**************************实现函数********************************************
*函数原型:		void RTC_IIC_NAck(void)
*功　　能:	    产生NACK应答
*******************************************************************************/	    
void RTC_IIC_NAck(void)
{
	RTC_IIC_SCL_OUT=0;
	RTC_IIC_SDA_Mode_Out_OD();
	RTC_IIC_SDA_OUT=1;
	RTC_Delay(2);
	RTC_IIC_SCL_OUT=1;
	RTC_Delay(2);
	RTC_IIC_SCL_OUT=0;
}					 				     

/**************************实现函数********************************************
*函数原型:		void RTC_IIC_Send_Byte(u8 txd)
*功　　能:	    IIC发送一个字节
*******************************************************************************/		  
void RTC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	RTC_IIC_SDA_Mode_Out_OD(); 	    
    RTC_IIC_SCL_OUT=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        RTC_IIC_SDA_OUT=(txd&0x80)>>7;
        txd<<=1; 	  
		RTC_Delay(2);   
		RTC_IIC_SCL_OUT=1;
		RTC_Delay(2); 
		RTC_IIC_SCL_OUT=0;	
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
        RTC_IIC_SCL_OUT=0; 
        RTC_Delay(2);
		RTC_IIC_SCL_OUT=1;
        receive<<=1;
        if(RTC_IIC_SDA_IN())receive++;   
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
