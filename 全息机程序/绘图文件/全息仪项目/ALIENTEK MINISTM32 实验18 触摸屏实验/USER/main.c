#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "touch.h"
#include "rtc.h" 
//Mini STM32开发板范例代码18
//触摸屏 实验	  
//正点原子@ALIENTEK
//技术论坛:www.openedv.com 
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(216,0,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}

 int main(void)
 {
	u8 key;
	u8 i=0;	
	Stru_Time time,getTime;
	 time.Year = 16;
	 time.Month = 12;
	 time.Day = 31;
	 time.Hour = 17;
	 time.Minutes = 7;
	 time.Second = 30;

	//SystemInit();
	delay_init(72);	     //延时初始化
	//NVIC_Configuration();
 	uart_init(9600);
//	E17_uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	fnRTC_Init();
//	fnRTC_SetTime(time);
	POINT_COLOR=RED;//设置字体为蓝色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"TOUCH TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");	
	LCD_ShowString(60,130,"Press KEY0 to Adjust");	
//	Touch_Init();
	delay_ms(1500);
	Load_Drow_Dialog();	  
	while(1)
	{	
		fnRTC_GetTime(&getTime); 			
		printf("你好");

		delay_ms(1000);
	 	key=KEY_Scan();

		if(key !=0)//KEY0按下,则执行校准程序
		{
			LED0=!LED0;	
//			printf("%d-%02d-%02d %02d:%02d:%02d    按键: KEY=%d 被按下\r\n",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second,key);
	//		E17_sendString("打印机串口测试");
//			LCD_Clear(WHITE);//清屏
//		    Touch_Adjust();  //屏幕校准 
//			Save_Adjdata();	 
//			Load_Drow_Dialog();
		}
	
	}	   
 }

