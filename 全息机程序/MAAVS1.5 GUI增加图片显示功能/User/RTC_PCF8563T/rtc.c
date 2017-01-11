#include "rtc.h"

u8 ls1[5];
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Init(void)
*��������:		��ʼ��I2C��Ӧ�Ľӿ����š�
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
		
		//��ʱ������ʱ��ˢ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
		/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=1000;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* ����ʱ�� */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);		/*�ȹرյȴ�ʹ��*/   

}



void fnRTC_GetTime(Stru_Time* Time)
{
	unsigned char temp[8];
	
	RTC_IIC_ReadBytes(RTC_ADDR,ADD_SECOND,7,temp);
	
	temp[0]&=0x7f;//ȥ�����λ
	temp[0]=((temp[0]>>4)*10+(temp[0]&0x0f));
	Time->Second=temp[0];
	
	temp[1]&=0x7f;//ȥ�����λ
	temp[1]=((temp[1]>>4)*10+(temp[1]&0x0f));
	Time->Minutes=temp[1];
	
	temp[2]&=0x3f;//ȥ�����λ
	temp[2]=((temp[2]>>4)*10+(temp[2]&0x0f));
	Time->Hour=temp[2];
	
	temp[3]&=0x3f;//ȥ�����λ
	temp[3]=((temp[3]>>4)*10+(temp[3]&0x0f));
	Time->Day=temp[3];
	
	temp[4]&=0x07;//ȥ�����λ
	temp[4]=((temp[4]>>4)*10+(temp[4]&0x0f));
	Time->Week=temp[4];
	
	temp[5]&=0x1f;//ȥ�����λ
	temp[5]=((temp[5]>>4)*10+(temp[5]&0x0f));
	Time->Month=temp[5];
	
	temp[6]=((temp[6]>>4)*10+(temp[6]&0x0f));
	Time->Year=temp[6];
	/*��ֹ�����100*/
	if(Time->Year<50)Time->Year+=2000;
	
}
void fnRTC_SetTime(Stru_Time su_Time)
{
	if(su_Time.Year>2000)
		su_Time.Year-=2000;
	/*ת��ΪBCD��ʽ*/
	su_Time.Second=((su_Time.Second/10)<<4)+(su_Time.Second%10);
	su_Time.Minutes=((su_Time.Minutes/10)<<4)+(su_Time.Minutes%10);
	su_Time.Hour=((su_Time.Hour/10)<<4)+(su_Time.Hour%10);
	su_Time.Day=((su_Time.Day/10)<<4)+(su_Time.Day%10);
	su_Time.Month=((su_Time.Month/10)<<4)+(su_Time.Month%10);
	su_Time.Year=((su_Time.Year/10)<<4)+(su_Time.Year%10);

	/*д��Ĵ���*/
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
	  	/*ѡ��Ҫ���Ƶ�GPIOD����*/	
	  GPIO_InitStructure.GPIO_Pin = RTC_SDA_PIN;

	   /*��������ģʽΪ��������ģʽ*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	
	  /*���ÿ⺯������ʼ��GPIOD*/
	  GPIO_Init(RTC_SDA_GPIOX, &GPIO_InitStructure);	 
}

 void RTC_IIC_SDA_Mode_Out_OD(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	 	/*ѡ��Ҫ���Ƶ�GPIOD����*/															   
  	GPIO_InitStructure.GPIO_Pin = RTC_SDA_PIN;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*���ÿ⺯������ʼ��GPIOD*/
  	GPIO_Init(RTC_SDA_GPIOX, &GPIO_InitStructure);	 	 
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		void RTC_IIC_Start(void)
*��������:		����IIC��ʼ�ź�
*******************************************************************************/
void RTC_IIC_Start(void)
{
	RTC_IIC_SDA_Mode_Out_OD();     //sda�����
	RTC_SDA(1);	  	  
	RTC_SCL(1);
	RTC_Delay(4);
 	RTC_SDA(0);//START:when CLK is high,DATA change form high to low 
	RTC_Delay(4);
	RTC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void RTC_IIC_Stop(void)
*��������:	    //����IICֹͣ�ź�
*******************************************************************************/	  
void RTC_IIC_Stop(void)
{
	RTC_IIC_SDA_Mode_Out_OD();//sda�����
	RTC_SDA(0);
	RTC_SCL(0);//STOP:when CLK is high DATA change form low to high
 	RTC_Delay(4);
	RTC_SDA(1);
	RTC_SCL(1);//����I2C���߽����ź�
	RTC_Delay(4);							   	
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_Wait_Ack(void)
*��������:	    �ȴ�Ӧ���źŵ��� 
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
*******************************************************************************/
u8 RTC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	RTC_IIC_SDA_Mode_IN_IPU();      //SDA����Ϊ����
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
	RTC_SCL(0);//ʱ�����0 	   
	return 0;  
} 

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void RTC_IIC_Ack(void)
*��������:	    ����ACKӦ��
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
	
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void RTC_IIC_NAck(void)
*��������:	    ����NACKӦ��
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

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void RTC_IIC_Send_Byte(u8 txd)
*��������:	    IIC����һ���ֽ�
*******************************************************************************/		  
void RTC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	RTC_IIC_SDA_Mode_Out_OD(); 	
	RTC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
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
   
/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_Read_Byte(unsigned char ack)
*��������:	    //��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
*******************************************************************************/  
u8 RTC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	RTC_IIC_SDA_Mode_IN_IPU();//SDA����Ϊ����
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
        RTC_IIC_Ack(); //����ACK 
    else
        RTC_IIC_NAck();//����nACK  
    return receive;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		unsigned char RTC_IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
*��������:	    ��ȡָ���豸 ָ���Ĵ�����һ��ֵ
����	I2C_Addr  Ŀ���豸��ַ
		addr	   �Ĵ�����ַ
����   ��������ֵ
*******************************************************************************/ 
unsigned char RTC_IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
{
	unsigned char res=0;
	
	RTC_IIC_Start();	
	RTC_IIC_Send_Byte(I2C_Addr);	   //����д����
	res++;
	RTC_IIC_Wait_Ack();
	RTC_IIC_Send_Byte(addr); res++;  //���͵�ַ
	RTC_IIC_Wait_Ack();	  
	//RTC_IIC_Stop();//����һ��ֹͣ����	
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(I2C_Addr+1); res++;          //�������ģʽ			   
	RTC_IIC_Wait_Ack();
	res=RTC_IIC_Read_Byte(0);	   
    RTC_IIC_Stop();//����һ��ֹͣ����

	return res;
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_ReadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ����� length��ֵ
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫ�����ֽ���
		*data  ���������ݽ�Ҫ��ŵ�ָ��
����   ���������ֽ�����
*******************************************************************************/ 
u8 RTC_IIC_ReadBytes(u8 dev, u8 reg, u8 length, u8 *data)
{
    u8 count = 0;
	
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(dev);	   //����д����
	RTC_IIC_Wait_Ack();
	RTC_IIC_Send_Byte(reg);   //���͵�ַ
    RTC_IIC_Wait_Ack();	  
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(dev+1);  //�������ģʽ	
	RTC_IIC_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)data[count]=RTC_IIC_Read_Byte(1);  //��ACK�Ķ�����
		 	else  data[count]=RTC_IIC_Read_Byte(0);	 //���һ���ֽ�NACK
	}
    RTC_IIC_Stop();//����һ��ֹͣ����
    return count;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_WriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*��������:	    ������ֽ�д��ָ���豸 ָ���Ĵ���
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫд���ֽ���
		*data  ��Ҫд�����ݵ��׵�ַ
����   �����Ƿ�ɹ�
*******************************************************************************/ 
u8 RTC_IIC_WriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	RTC_IIC_Start();
	RTC_IIC_Send_Byte(dev);	   //����д����
	RTC_IIC_Wait_Ack();
	RTC_IIC_Send_Byte(reg);   //���͵�ַ
    RTC_IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		RTC_IIC_Send_Byte(data[count]); 
		RTC_IIC_Wait_Ack(); 
	 }
	RTC_IIC_Stop();//����һ��ֹͣ����

    return 1; //status == 0;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_ReadByte(u8 dev, u8 reg, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ�����һ��ֵ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		*data  ���������ݽ�Ҫ��ŵĵ�ַ
����   1
*******************************************************************************/ 
u8 RTC_IIC_ReadByte(u8 dev, u8 reg, u8 *data){
	*data=RTC_IIC_ReadOneByte(dev, reg);
    return 1;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		unsigned char RTC_IIC_WriteByte(unsigned char dev, unsigned char reg, unsigned char data)
*��������:	    д��ָ���豸 ָ���Ĵ���һ���ֽ�
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		data  ��Ҫд����ֽ�
����   1
*******************************************************************************/ 
unsigned char RTC_IIC_WriteByte(unsigned char dev, unsigned char reg, unsigned char data){
    return RTC_IIC_WriteBytes(dev, reg, 1, &data);
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_WriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �еĶ��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitStart  Ŀ���ֽڵ���ʼλ
		length   λ����
		data    ��Ÿı�Ŀ���ֽ�λ��ֵ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
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

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 RTC_IIC_writeBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �е�1��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitNum  Ҫ�޸�Ŀ���ֽڵ�bitNumλ
		data  Ϊ0 ʱ��Ŀ��λ������0 ���򽫱���λ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
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
