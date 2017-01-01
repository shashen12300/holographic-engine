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

char data[300];
int i;
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
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	LED_Init();
	KEY_Init();
	fnRTC_Init();
 uart_init(9600); 
	delay_ms(50);
	 LCD_RST_0;
	 delay_ms(50);
	 LCD_RST_1;
	 delay_ms(50);
	lcm_init();
	fnRTC_Init();
	//	fnRTC_SetTime(time);
	while(1)
	{
		fnRTC_GetTime(&getTime); 			

	 	key=KEY_Scan();

		if(key !=0)//KEY0按下,则执行校准程序
		{
			LED0=!LED0;	
			printf("%d-%02d-%02d %02d:%02d:%02d    按键: KEY=%d 被按下\r\n",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second,key);
	//		E17_sendString("打印机串口测试");
//			LCD_Clear(WHITE);//清屏
//		    Touch_Adjust();  //屏幕校准 
//			Save_Adjdata();	 
//			Load_Drow_Dialog();
		}
	
	}	
//		clr_ram();
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
//	}
}

