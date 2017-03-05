#ifndef __USER_DEFINE_H
#define __USER_DEFINE_H

#include "stm32f10x.h"

#define CLI()   __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI() __set_PRIMASK(0)				/* 开放总中断 */

/* 为了使用编程书写方便，定义几个控制LED开关的宏 */
#define LED1_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_4);}	/* PF6 = 0 点亮LED1 */
#define LED1_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_4);}		/* PF6 = 1 熄灭LED1 */

#define LED2_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_5);}	/* PF7 = 0 点亮LED2 */
#define LED2_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_5);}		/* PF7 = 1 点亮LED2 */

#define LED3_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_6);}	/* PF8 = 0 点亮LED3 */
#define LED3_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_6);}		/* PF8 = 1 点亮LED3 */

#define LED4_ON()	{GPIO_ResetBits(GPIOA, GPIO_Pin_7);}	/* PF9 = 0 点亮LED4 */
#define LED4_OFF()	{GPIO_SetBits(GPIOA, GPIO_Pin_7);}		/* PF9 = 1 点亮LED4 */

/************CAN总线相关定义区*************/
extern CanTxMsg TxMessage;    //CAN发送数据存放结构体          
extern CanRxMsg RxMessage;    //CAN接收数据存放结构体

//CAN数据缓冲区
extern unsigned char CAN_LCD_buffer[480];
/**********************************************/

/************LCD相关定义区*************/
extern unsigned char FontSize;//字体大小  1.英文8*16，汉字16*16  2.英文12*24，汉字24*24 
/**********************************************/

extern unsigned char status_flag;

#endif
