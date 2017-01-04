/* Includes ------------------------------------------------------------------*/
#include "user_include.h"
#include "user_define.h"
#include <stddef.h>
#include "GUI.h"
//#include "logo.h"
#include "LCD_Driver.h"
#include "User_win.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "RA8835.h"
#include "rtc.h" 
#include "adc.h"
unsigned char status_flag=0;
int adcValue;
 void User_delay(unsigned int j)  //1ms delay volatile
{
    volatile unsigned int i;	
	  while(j--)
    for(i=6000000;i>0;i--);
}
int main(void)
{
	u8 key;
	u8 i=0;
	Stru_Time time,getTime;
	char data[300]="串口测试数据\r\n";
//	unsigned int i=0;
//	unsigned char q=50;
	CLI();        //关总中断
	//LED_init();   //8个led的初始化
	//LCD_Setup();   //屏幕的端口初始化
	//CAN_init();
	//EXT_init();
	//TIM_init();
	SEI();        //开总中断
	//Dis_image(0,0,480,320,gImage_Logo);
	User_delay(2);
	MainTask();
//GUI_Init(); //GUI 
//GUI_Clear();
//GUI_SetBkColor(0x001f); //蓝
//GUI_SetColor(0xffff); //白
//GUI_SetFont(&GUI_Font24_1); 
//GUI_DispStringAt("----uC/GUI Manual----",35,7);
//GUI_SetFont(&GUI_Font24_1); //
//GUI_DispStringAt("Author: XQ_STM32",60,290); //
//	
//GUI_SetBkColor(0x001f); //蓝
//GUI_SetColor(0xf800); //红
//GUI_DrawCircle(120,110,50); //
//GUI_DrawCircle(95,100,5);
//GUI_DrawCircle(145,100,5);
//GUI_DrawArc(115, 128, 20, 6, -120, -10); //
//GUI_SetFont(&GUI_Font32_1); //????????
//GUI_DispStringAt("So, bad boy!",50,190);
	
	
	
	//GUI_DELAY();
//GUI_DELAY();
//GUI_DELAY();
//GUI_DELAY();
//GUIDEMO_main();

	
	 time.Year = 16;
	 time.Month = 12;
	 time.Day = 31;
	 time.Hour = 17;
	 time.Minutes = 7;
	 time.Second = 30;
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	LED_Init();
	KEY_Init();
	E11_init();
	fnRTC_Init();
	Adc_Init();
  uart_init(9600); 
	delay_ms(50);
	fnRTC_Init();
	E17_uart_init(9600);

while(1)
{
			fnRTC_GetTime(&getTime); 			
	 	key=KEY_Scan();
		adcValue = Get_Adc(0);
		if(key !=0)//KEY0按下,则执行校准程序
		{
			LED0=!LED0;	
			E17_sendString(data);
			printf("%d-%02d-%02d %02d:%02d:%02d  按键: KEY=%d 被按下  adc = %d\r\n",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second,key,adcValue);
		}
}
	
}
