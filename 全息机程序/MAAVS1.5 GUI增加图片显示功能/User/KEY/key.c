#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "usart.h"
#include "WM.h"
#include "GUI.h"
#include "my_win.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//�������� ��������		   
//������̳:www.openedv.com
//�޸�����:2011/11/28 
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ALIENTEK  2009-2019
//All rights reserved
//********************************************************************************
 extern int rotate_flag;
 int logoCount =0;
 int selectEnd = 1;
 int myMessageType = MY_MESSAGE_ID_LOGO;

void KEY_Init(void) //IO��ʼ��
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	//init GPIOA  ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//PA.1 .2 .3 .4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
}


u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//�������ɿ���־	
 
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)
		{
				
			return 1;
		}
		else if(KEY1==0)
		{
	 	 
			return 2;
		}
		else if(KEY2==0)
		{
	 
			return 3;
		}
		else if(KEY3==0)
		{
	 
			return 4;
		}
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 
	return 0;// �ް�������
}



void E11_init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//init GPIOA  ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;//PA.11 .12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* EXTI line(PB0) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11|GPIO_PinSource15); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line11|EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void selectLogoCount(int count) {   //32
	int i=43,j=40;
	int row= count/5, rank = count%5;
				for (i=43+row*39;i<75+row*39;i++)
			{
				for (j=8+rank*64;j<40+rank*64;j++) {
					if(count == 9) 
						LCD_L0_XorPixel(j,i-1);
					else
						LCD_L0_XorPixel(j,i);

					
				}
			}
}

void rotate(void) {  //logoͼ��ѡ��
	static int lastCount=0;
			//��ת������
		if(rotate_flag == 1) {
			
			if(KEY_A == 0) {
					delay_us(20);
            if(KEY_B == 1)
            {
							logoCount++;
							if(logoCount==25) {
								logoCount = 0;
							}
							 printf("right\r\n");
            }else {
							if(KEY_B == 0) {
								logoCount--;
								if(logoCount == -1) {
									logoCount = 24;
								}
								printf("left\r\n");
							}

						}
						selectLogoCount(lastCount);
						selectLogoCount(logoCount);
						lastCount = logoCount;
						rotate_flag = 0;
					}
		}
		selectEnd = 1;

}

void send_rotate_message(void) {
	WM_HWIN activeHwin;
			//��ת������
		if(rotate_flag == 1) {
				selectEnd = 0;
			if (myMessageType == MY_MESSAGE_ID_LOGO) {
//						WM_SelectWindow(mainForm_hWin);
						WM_SetFocus(mainForm_hWin);
			//		GUI_StoreKeyMsg(MY_MESSAGE_ID_ENCODER0,1);
						GUI_SendKeyMsg(MY_MESSAGE_ID_ENCODER0,1);
			//		WM_SetFocus(mainForm_hWin);
			//		GUI_Clear();
			}else if (myMessageType == MY_MESSAGE_ID_MESSAGE_SETTING) {
							WM_SetFocus(dialog_hWin);
							GUI_SendKeyMsg(MY_MESSAGE_ID_ENCODER0,1);
			}else if (myMessageType == MY_MESSAGE_ID_SYSTEM_SETTING) {
							GUI_SendKeyMsg(MY_MESSAGE_ID_ENCODER0,1);
			}else if (myMessageType == MY_MESSAGE_ID_LINE) {
				//�����κβ���
			}else {
				printf("�߼���������");
			}
		}
}

//��ת����������ȷ�ϲ���
void send_enter_message(void) {
		if(KEY4 == 0) {
			delay_ms(10);
			if(KEY4== 0) {
				printf("enter\r\n");
				if (myMessageType == MY_MESSAGE_ID_LOGO) {
							//���û����
							WM_SetFocus(mainForm_hWin);
							GUI_SendKeyMsg(MY_MESSAGE_ID_ENTER,1);
				}else if (myMessageType == MY_MESSAGE_ID_MESSAGE_SETTING) {
								WM_SetFocus(dialog_hWin);
								GUI_SendKeyMsg(MY_MESSAGE_ID_ENTER,1);
				}else if (myMessageType == MY_MESSAGE_ID_SYSTEM_SETTING) {
								GUI_SendKeyMsg(MY_MESSAGE_ID_ENTER,1);
				}else if (myMessageType == MY_MESSAGE_ID_LINE) {
					//�����κβ���
				}else {
					printf("�߼���������");
				}
				return;
			}
		}
		
		rotateEnter_flag = 0;
}


