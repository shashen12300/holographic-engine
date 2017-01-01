#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "spi.h"
#include "flash.h"
#include "touch.h"
//Mini STM32�����巶������18
//������ ʵ��	  
//����ԭ��@ALIENTEK
//������̳:www.openedv.com 

char data[300];
int i;
extern unsigned char tab1[];
 int main(void)
 {
	u8 i=0;	
	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
	 
	//RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	 
 //	uart_init(9600);
	delay_ms(50);
	 LCD_RST_0;
	 delay_ms(50);
	 LCD_RST_1;
	 delay_ms(50);


	lcm_init();
	while(1)
	{
		clr_ram();
		disp_graphics(tab1);
		delay_n_ms(2000);
		disp_lattice(0xff,0xff);
		delay_n_ms(2000);
		//��� ��֧
		

		
		clr_ram();
		disp_lattice(0xcc,0x33);
		delay_n_ms(2000);
		disp_lattice(0xaa,0xaa);
		delay_n_ms(2000);
		disp_lattice(0x55,0x55);
		delay_n_ms(2000);
		disp_lattice(0xff,0x00);
		delay_n_ms(2000);
		disp_lattice(0x00,0xff);
		delay_n_ms(2000);
	}
}

