/************中断处理函数************/
#include "stm32f10x_it.h"
#include "user_define.h"
#include "user_include.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "WM.h"
#include "GUI.h"
#include "my_win.h"

int logoCount=0;
unsigned char CAN_LCD_buffer[480];
void USB_LP_CAN1_RX0_IRQHandler(void)   
{   
	unsigned int i;
	//unsigned char line_Start;
	//unsigned char line_End;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);   

	if(((RxMessage.ExtId&0xff000000)>>24)==0x01)  
	{   
		if((RxMessage.ExtId&0x00ff0000)==0x00110000)                     
		{
			for(i=0;i<8;i++)
			{
				CAN_LCD_buffer[i]=RxMessage.Data[i];
			}
			for(i=0;i<5;i++)
			{	
				//Lcd_write_char(480-i*92,100,*(CAN_LCD_buffer+i),0xf800, 0xffff);
				
			}
		}						
	}   
}	

void EXTI0_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line0);     //清除中断标志位
	  
	}  
}
void EXTI1_IRQHandler(void)  
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line1);     //清除中断标志位
	  
	} 
}
void EXTI2_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line2);     //清除中断标志位
	  
	} 
}
void EXTI3_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line3);     //清除中断标志位
	  
	} 
}
void EXTI4_IRQHandler(void)  
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line4);     //清除中断标志位
	  
	} 
}

void EXTI9_5_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line5);     //清除中断标志位
		status_flag=!status_flag;
	
  }
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
    EXTI_ClearITPendingBit(EXTI_Line6);     //清除中断标志位
		
  }
}
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  
		
	}		 	
	 	
}

void EXTI15_10_IRQHandler(void)
{	
//	EXTI_InitTypeDef EXTI_InitStructure;
//	static int lastCount=0;
//	WM_MESSAGE* pMsg;
//	pMsg->MsgId = MY_MESSAGE_ENCODER;
//	pMsg->hWinSrc = MY_MESSAGE_ID_ENCODER0;
      if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {

			EXTI_ClearITPendingBit(EXTI_Line14);     //清除中断标志位
//			GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11); 
//			EXTI_InitStructure.EXTI_Line = EXTI_Line11;
//			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
//			EXTI_InitStructure.EXTI_LineCmd = DISABLE;
//			EXTI_Init(&EXTI_InitStructure); 
//			delay_us(10);
//			if(KEY_A == 0) {
//            if(KEY_B == 1)
//            {
//							logoCount++;
//							if(logoCount==25) {
//								logoCount = 0;
//							}
////							 printf("正传\r\n");
//            }else {
//							if(KEY_B == 0) {
//								logoCount--;
//								if(logoCount == -1) {
//									logoCount = 24;
//								}
////								printf("反传\r\n");
//							}

//						}
//			pMsg->Data.v = logoCount;
////			selectLogoCount(lastCount);	
////			selectLogoCount(logoCount);	
////			lastCount = logoCount;
//			WM_SendMessage(timeForm_hWin,pMsg);
//					}


//			EXTI_InitStructure.EXTI_Line = EXTI_Line11;
//			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
//			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//			EXTI_Init(&EXTI_InitStructure); 			
				}
}

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
