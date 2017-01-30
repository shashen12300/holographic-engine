#ifndef __KEY_H
#define __KEY_H	

#include "stm32f10x.h"
#include "sys.h"
#include "GUI.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//按键输入 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/11/28 
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.1修改说明
//修改按键扫描函数，使整个代码可以支持SWD下载。
//////////////////////////////////////////////////////////////////////////////////	 
typedef enum 
{  
	Button_KEY0 = 0,
	Button_KEY1 = 1,
	Button_WAKEUP = 2
} Button_TypeDef;

typedef struct  
{   GPIO_TypeDef*       BUTTON_PORT ;
    uint16_t            BUTTON_PIN ;
    GPIOMode_TypeDef    BUTTON_MODE;
}Button_PinModeDef;	

#define KEY0 PAin(1)  //PA1
#define KEY1 PAin(2)	//PA2 
#define KEY2 PAin(3)	//PA3  
#define KEY3 PAin(4)	//PA4
#define KEY4 PAin(15)	//PA15

#define KEY_A PAin(11)	//PA11
#define KEY_B PAin(12)	//PA12
	
extern int logoCount;
extern int selectEnd;
extern int myMessageType;
extern int rotateEnter_flag;

void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  //按键扫描函数		
void E11_init(void);//旋转编码器
void rotate(void);//选择图标
void send_rotate_message(void);
void send_enter_message(void);
void selectLogoCount(int count);
void setOrLogoCount(int count,int flag);
#endif
