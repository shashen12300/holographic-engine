/************中断处理函数************/
#include "stm32f10x_it.h"
#include "user_define.h"
#include "user_include.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "user_Dialog.h"
#include "systemConfig.h"
#include "rtc.h"

unsigned char CAN_LCD_buffer[480];
extern int time_flag;
void refresh_time(void) ;

extern void printReport(void);
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
//void EXTI3_IRQHandler(void)  
//{
//  if(EXTI_GetITStatus(EXTI_Line3) != RESET) //确保是否产生了EXTI Line中断
//	{
//		EXTI_ClearITPendingBit(EXTI_Line3);     //清除中断标志位
//	  
//	} 
//}
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
		time_flag++;
		if(time_flag%10==5){
			if (myMessageType == MY_MESSAGE_ID_DRAW_LINE) {
								refresh_time();
			}
		}
		
		}	 	
	 	
}

void EXTI3_IRQHandler(void){
	
	EXTI_InitTypeDef EXTI_InitStructure;
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) {
				Stru_Time time,getTime;

			EXTI_ClearITPendingBit(EXTI_Line3);     //清除中断标志位
			
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3); 
			EXTI_InitStructure.EXTI_Line = EXTI_Line3;
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
			EXTI_InitStructure.EXTI_LineCmd = DISABLE;
			EXTI_Init(&EXTI_InitStructure); 
			//打印
			printReport();
		}
			//打开中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}
void EXTI15_10_IRQHandler(void)
{	
	//关闭中断
	EXTI_InitTypeDef EXTI_InitStructure;

      if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
			EXTI_ClearITPendingBit(EXTI_Line11);     //清除中断标志位
			
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11); 
				EXTI_InitStructure.EXTI_Line = EXTI_Line11;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
				EXTI_InitStructure.EXTI_LineCmd = DISABLE;
				EXTI_Init(&EXTI_InitStructure); 
			
			rotate_flag = 1;
			if(selectEnd == 1) {
				send_rotate_message();
			}

		}else if(EXTI_GetITStatus(EXTI_Line15) != RESET) {
			EXTI_ClearITPendingBit(EXTI_Line15);     //清除中断标志位
			
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15); 
				EXTI_InitStructure.EXTI_Line = EXTI_Line15;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
				EXTI_InitStructure.EXTI_LineCmd = DISABLE;
				EXTI_Init(&EXTI_InitStructure); 
			
			rotateEnter_flag = 1;
			send_enter_message();
		}
		
		//打开中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11|GPIO_PinSource15); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line11|EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
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
