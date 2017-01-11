#ifndef __KEY_H
#define __KEY_H	

#include "stm32f10x.h"
#include "sys.h"
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

#define KEY0 PCin(3)  //PC3
#define KEY1 PCin(2)	//PC2 
#define KEY2 PCin(1)	//PC1 
#define KEY3 PCin(0)	//PC0
#define KEY4 PCin(13)	//PC13

#define KEY_A PCin(15)	//PC15
#define KEY_B PCin(14)	//PC14
	 
void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  //按键扫描函数		
void E11_init();//旋转编码器
void selectLogoCount(int count);//选择图标
#endif
