#ifndef __USER_DEFINE_H
#define __USER_DEFINE_H

#include "stm32f10x.h"

#define CLI()   __set_PRIMASK(1)		/* �ر����ж� */  
#define SEI() __set_PRIMASK(0)				/* �������ж� */

/* Ϊ��ʹ�ñ����д���㣬���弸������LED���صĺ� */
#define LED1_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_4);}	/* PF6 = 0 ����LED1 */
#define LED1_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_4);}		/* PF6 = 1 Ϩ��LED1 */

#define LED2_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_5);}	/* PF7 = 0 ����LED2 */
#define LED2_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_5);}		/* PF7 = 1 ����LED2 */

#define LED3_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_6);}	/* PF8 = 0 ����LED3 */
#define LED3_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_6);}		/* PF8 = 1 ����LED3 */

#define LED4_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_7);}	/* PF9 = 0 ����LED4 */
#define LED4_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_7);}		/* PF9 = 1 ����LED4 */

/************CAN������ض�����*************/
extern CanTxMsg TxMessage;    //CAN�������ݴ�Žṹ��          
extern CanRxMsg RxMessage;    //CAN�������ݴ�Žṹ��

//CAN���ݻ�����
extern unsigned char CAN_LCD_buffer[480];
/**********************************************/

/************LCD��ض�����*************/
extern unsigned char FontSize;//�����С  1.Ӣ��8*16������16*16  2.Ӣ��12*24������24*24 
/**********************************************/

extern unsigned char status_flag;

#endif
