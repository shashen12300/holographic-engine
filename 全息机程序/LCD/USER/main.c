#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "RA8835.h"
#include "spi.h"
#include "flash.h"
#include "touch.h"
#include "rtc.h" 
#include "adc.h"
//Mini STM32�����巶������18
//������ ʵ��	  
//����ԭ��@ALIENTEK
//������̳:www.openedv.com 

char data[300]="���ڲ�������\r\n",length;
int i,adcValue;
extern unsigned char tab1[];
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
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	LED_Init();
	KEY_Init();
	E11_init();
	fnRTC_Init();
	Adc_Init();
  uart_init(9600); 
	delay_ms(50);
//	LCD_RST_0;
//	delay_ms(50);
//	LCD_RST_1;
//	delay_ms(50);
//	lcm_init();
	fnRTC_Init();
	E17_uart_init(9600);
	//	fnRTC_SetTime(time);
	while(1)
	{
		
		fnRTC_GetTime(&getTime); 			
	 	key=KEY_Scan();
		adcValue = Get_Adc(0);
		if(key !=0)//KEY0����,��ִ��У׼����
		{
			LED0=!LED0;	
			E17_sendString(data);
			printf("%d-%02d-%02d %02d:%02d:%02d  ����: KEY=%d ������  adc = %d\r\n",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second,key,adcValue);
		}
		//��Ļ��ʾ
//		clr_ram();
//		DrawHLine(5,5,100,0x000000);
//		disp_graphics(tab1);
//		delay_n_ms(2000);
//		disp_lattice(0xff,0xff);
//		delay_n_ms(2000);

//		clr_ram();
//		disp_lattice(0xcc,0x33);
//		delay_n_ms(2000);
//		disp_lattice(0xaa,0xaa);
//		delay_n_ms(2000);
//		disp_lattice(0x55,0x55);
//		delay_n_ms(2000);
//		disp_lattice(0xff,0x00);
//		delay_n_ms(2000);
//		disp_lattice(0x00,0xff);
//		delay_n_ms(2000);
	
	}	

}


