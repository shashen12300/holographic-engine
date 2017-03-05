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
//Mini STM32�����巶������18
//������ ʵ��	  
//����ԭ��@ALIENTEK
//������̳:www.openedv.com 
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(216,0,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
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
	delay_init(72);	     //��ʱ��ʼ��
	//NVIC_Configuration();
 	uart_init(9600);
//	E17_uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();
	fnRTC_Init();
//	fnRTC_SetTime(time);
	POINT_COLOR=RED;//��������Ϊ��ɫ	   
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
		printf("���");

		delay_ms(1000);
	 	key=KEY_Scan();

		if(key !=0)//KEY0����,��ִ��У׼����
		{
			LED0=!LED0;	
//			printf("%d-%02d-%02d %02d:%02d:%02d    ����: KEY=%d ������\r\n",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second,key);
	//		E17_sendString("��ӡ�����ڲ���");
//			LCD_Clear(WHITE);//����
//		    Touch_Adjust();  //��ĻУ׼ 
//			Save_Adjdata();	 
//			Load_Drow_Dialog();
		}
	
	}	   
 }

