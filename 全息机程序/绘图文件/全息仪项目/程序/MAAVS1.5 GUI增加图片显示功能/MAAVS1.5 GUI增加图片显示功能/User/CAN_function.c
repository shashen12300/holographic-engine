#include "stm32f10x.h"
#include "CAN_function.h"
#include "user_define.h"
CanTxMsg TxMessage;    //CAN发送数据存放结构体          
CanRxMsg RxMessage;    //CAN接收数据存放结构体

void	CAN_GPIO_Config()
{
   GPIO_InitTypeDef GPIO_InitStructure;   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);   
 
  
       
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
   GPIO_Init(GPIOA, &GPIO_InitStructure);   
       
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
   GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
}
	
void 	CAN_NVIC_Config()
{
   NVIC_InitTypeDef NVIC_InitStructure;   
 
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);   //先占优先级1位，从优先级3位
 
   NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; //USB低优先级或CAN接收0中断
     
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //NVIC_IRQChannel中的先占优先级
  
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   //NVIC_IRQChannel中的从优先级
  
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//NVIC_IRQChannel中的通道中断使能   
   NVIC_Init(&NVIC_InitStructure); 
}

void  CAN_Mode_Config()
{
     CAN_InitTypeDef    CAN_InitStructure;   
 
     CAN_DeInit(CAN1);   //将外设CAN的全部寄存器重设为缺省值
     CAN_StructInit(&CAN_InitStructure);   //把CAN_StructInit中的每一个参数按缺省值填入
 
     CAN_InitStructure.CAN_TTCM=DISABLE;  //失能时间触发通信模式          
  
     CAN_InitStructure.CAN_ABOM=ENABLE;     //自动离线管理        
   
     CAN_InitStructure.CAN_AWUM=ENABLE;      //自动唤醒模式      
 
     CAN_InitStructure.CAN_NART=DISABLE;     //失能非自动重传输模式       
  
     CAN_InitStructure.CAN_RFLM=DISABLE;       //失能接收FIFO锁定模式     

    
     CAN_InitStructure.CAN_TXFP=DISABLE;      //失能发送FIFO优先级      

     CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //工作在正常模式
   
     CAN_InitStructure.CAN_SJW=CAN_SJW_2tq;      //重新同步跳跃宽度2个时间单位，即每位中可以延长或缩短的时间单位上限   
  
     CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;      //时间段1的时间单位数目   为5个时间单位
  
     CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;        // 时间段2的时间单位数目   为3个时间单位
   
     CAN_InitStructure.CAN_Prescaler =8;         //设定时间单位长度，取值1~1024  
    
		 CAN_Init(CAN1, &CAN_InitStructure);
}


void CAN_Filter_Config()
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;   

	CAN_FilterInitStructure.CAN_FilterNumber=0;      //待初始化的过滤器

	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;  //过滤器被初始化到的模式，标识符屏蔽位模式

	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;  //过滤器位宽，一个32位过滤器
	
	//CAN_FilterIdHigh设定过滤器标识符，32位宽时为其高段位，16位宽时为第一个，范围0x0000~0xffff
	CAN_FilterInitStructure.CAN_FilterIdHigh= (((u32)0x01000000<<3)&0xFFFF0000)>>16;  
	//CAN_FilterIdLow设定过滤器标识符，32位宽时为其低段位，16位宽时为第二个，范围0x0000~0xffff
	CAN_FilterInitStructure.CAN_FilterIdLow= (((u32)0x01000000<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;	
	
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xf800;  //设定过滤器屏蔽标识符，或过滤器标识符，(32位宽时为其高段位，16位位宽时为第一个)范围0x0000~0xffff   
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;  //设定过滤器屏蔽标识符，或过滤器标识符，(32位宽时为其低段位，16位位宽时为第二个)范围0x0000~0xffff         

	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;   //设定指向过滤器的FIFO
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;     //失能或使能过滤器

	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  
}


void CAN_init(void)
{
   CAN_GPIO_Config();   
   CAN_NVIC_Config();   
   CAN_Mode_Config();   
   CAN_Filter_Config();
}

/***************传输一个消息***************/
void CAN_SetMsg(unsigned int ID,unsigned char *array)   
{        
   //TxMessage.StdId=0x00;           //用来设定标准标识符  0~0x7ff            
    TxMessage.ExtId=ID;                    //用来设定扩展标识符  0~0x3ffff
    TxMessage.IDE=CAN_ID_EXT;                  //设定标识符的类型 1.CAN_ID_STD设定标准标识符  2.CAN_ID_EXT使用标准标识符+扩展标识符
    TxMessage.RTR=CAN_RTR_DATA;                //设定待传输消息的帧类型 1.CAN_RTR_DATA数据帧  2.CAN_RTR_REMOTE远程帧
    TxMessage.DLC=8;                           //设定待传输消息的帧长度 0~0x8

    TxMessage.Data[0]=array[0];      
    TxMessage.Data[1]=array[1];   
	  TxMessage.Data[2]=array[2]; 
    TxMessage.Data[3]=array[3];   
    TxMessage.Data[4]=array[4];   
    TxMessage.Data[5]=array[5];   
    TxMessage.Data[6]=array[6];   
    TxMessage.Data[7]=array[7]; 

	  CAN_Transmit(CAN1, &TxMessage);
}
