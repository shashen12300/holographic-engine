#include "stm32f10x.h"
#include "CAN_function.h"
#include "user_define.h"
CanTxMsg TxMessage;    //CAN�������ݴ�Žṹ��          
CanRxMsg RxMessage;    //CAN�������ݴ�Žṹ��

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
 
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);   //��ռ���ȼ�1λ�������ȼ�3λ
 
   NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; //USB�����ȼ���CAN����0�ж�
     
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //NVIC_IRQChannel�е���ռ���ȼ�
  
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   //NVIC_IRQChannel�еĴ����ȼ�
  
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//NVIC_IRQChannel�е�ͨ���ж�ʹ��   
   NVIC_Init(&NVIC_InitStructure); 
}

void  CAN_Mode_Config()
{
     CAN_InitTypeDef    CAN_InitStructure;   
 
     CAN_DeInit(CAN1);   //������CAN��ȫ���Ĵ�������Ϊȱʡֵ
     CAN_StructInit(&CAN_InitStructure);   //��CAN_StructInit�е�ÿһ��������ȱʡֵ����
 
     CAN_InitStructure.CAN_TTCM=DISABLE;  //ʧ��ʱ�䴥��ͨ��ģʽ          
  
     CAN_InitStructure.CAN_ABOM=ENABLE;     //�Զ����߹���        
   
     CAN_InitStructure.CAN_AWUM=ENABLE;      //�Զ�����ģʽ      
 
     CAN_InitStructure.CAN_NART=DISABLE;     //ʧ�ܷ��Զ��ش���ģʽ       
  
     CAN_InitStructure.CAN_RFLM=DISABLE;       //ʧ�ܽ���FIFO����ģʽ     

    
     CAN_InitStructure.CAN_TXFP=DISABLE;      //ʧ�ܷ���FIFO���ȼ�      

     CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //����������ģʽ
   
     CAN_InitStructure.CAN_SJW=CAN_SJW_2tq;      //����ͬ����Ծ���2��ʱ�䵥λ����ÿλ�п����ӳ������̵�ʱ�䵥λ����   
  
     CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;      //ʱ���1��ʱ�䵥λ��Ŀ   Ϊ5��ʱ�䵥λ
  
     CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;        // ʱ���2��ʱ�䵥λ��Ŀ   Ϊ3��ʱ�䵥λ
   
     CAN_InitStructure.CAN_Prescaler =8;         //�趨ʱ�䵥λ���ȣ�ȡֵ1~1024  
    
		 CAN_Init(CAN1, &CAN_InitStructure);
}


void CAN_Filter_Config()
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;   

	CAN_FilterInitStructure.CAN_FilterNumber=0;      //����ʼ���Ĺ�����

	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;  //����������ʼ������ģʽ����ʶ������λģʽ

	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;  //������λ��һ��32λ������
	
	//CAN_FilterIdHigh�趨��������ʶ����32λ��ʱΪ��߶�λ��16λ��ʱΪ��һ������Χ0x0000~0xffff
	CAN_FilterInitStructure.CAN_FilterIdHigh= (((u32)0x01000000<<3)&0xFFFF0000)>>16;  
	//CAN_FilterIdLow�趨��������ʶ����32λ��ʱΪ��Ͷ�λ��16λ��ʱΪ�ڶ�������Χ0x0000~0xffff
	CAN_FilterInitStructure.CAN_FilterIdLow= (((u32)0x01000000<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;	
	
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xf800;  //�趨���������α�ʶ�������������ʶ����(32λ��ʱΪ��߶�λ��16λλ��ʱΪ��һ��)��Χ0x0000~0xffff   
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;  //�趨���������α�ʶ�������������ʶ����(32λ��ʱΪ��Ͷ�λ��16λλ��ʱΪ�ڶ���)��Χ0x0000~0xffff         

	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;   //�趨ָ���������FIFO
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;     //ʧ�ܻ�ʹ�ܹ�����

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

/***************����һ����Ϣ***************/
void CAN_SetMsg(unsigned int ID,unsigned char *array)   
{        
   //TxMessage.StdId=0x00;           //�����趨��׼��ʶ��  0~0x7ff            
    TxMessage.ExtId=ID;                    //�����趨��չ��ʶ��  0~0x3ffff
    TxMessage.IDE=CAN_ID_EXT;                  //�趨��ʶ�������� 1.CAN_ID_STD�趨��׼��ʶ��  2.CAN_ID_EXTʹ�ñ�׼��ʶ��+��չ��ʶ��
    TxMessage.RTR=CAN_RTR_DATA;                //�趨��������Ϣ��֡���� 1.CAN_RTR_DATA����֡  2.CAN_RTR_REMOTEԶ��֡
    TxMessage.DLC=8;                           //�趨��������Ϣ��֡���� 0~0x8

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
