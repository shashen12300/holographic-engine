/************�жϴ�����************/
#include "stm32f10x_it.h"
#include "user_define.h"
#include "user_include.h"
#include "key.h"
#include "delay.h"
#include "usart.h"


int rotate_flag=0;  //1��ʾ��ת
unsigned char CAN_LCD_buffer[480];
extern int time_flag;
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
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line0);     //����жϱ�־λ
	  
	}  
}
void EXTI1_IRQHandler(void)  
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line1);     //����жϱ�־λ
	  
	} 
}
void EXTI2_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line2);     //����жϱ�־λ
	  
	} 
}
void EXTI3_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line3);     //����жϱ�־λ
	  
	} 
}
void EXTI4_IRQHandler(void)  
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line4);     //����жϱ�־λ
	  
	} 
}

void EXTI9_5_IRQHandler(void)  
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line5);     //����жϱ�־λ
		status_flag=!status_flag;
	
  }
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
    EXTI_ClearITPendingBit(EXTI_Line6);     //����жϱ�־λ
		
  }
}
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  
		time_flag++;
		
	}		 	
	 	
}

void EXTI15_10_IRQHandler(void)
{	
      if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
			EXTI_ClearITPendingBit(EXTI_Line11);     //����жϱ�־λ
			rotate_flag = 1;
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
