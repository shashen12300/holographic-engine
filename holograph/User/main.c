/* Includes ------------------------------------------------------------------*/
#include "user_include.h"
#include "user_define.h"
#include <stddef.h>
#include "GUI.h"
//#include "logo.h"
#include "LCD_Driver.h"
#include "LCD_DriverConfig.h"
#include "User_win.h"
unsigned char status_flag=0;
unsigned char datas = 0;
unsigned char tab1[]={"�����д������ӿƼ����޹�˾רҵ����Һ����"};
 void User_delay(unsigned int j)  //1ms delay volatile
{
    volatile unsigned int i;	
	  while(j--)
    for(i=6000000;i>0;i--);
}
int main(void)
{

	CLI();        //�����ж�
	LCD_GPIO_Config();
	SEI();        //�����ж�
  delay_nms(10);   
  softrst();
  lcd_inital();  
//  clear();
// LCD_GotoXY(0x00,0x02);
while(1)
{
   //��Ļ��ʾ����  disp_off���high	
	
	//	LCD_GotoXY(0x00,0x00);   //�趨X,Y����λ�� 
	LED_OUT(1);
//	display_kuang();    //��ʾ��
//	LCD_CmdWrite(0x00);		//[00H] , Default --> 0x00
//	LCD_DataWrite(0x04); 
//	datas =	LCD_CmdRead(0x00);
//  display_ziku();     //ASCII��1
  delay_nms(500);
	LED_OUT(0);
  delay_nms(500);

 display_word(tab1,40);   //��ʾ��������
}
	
}
