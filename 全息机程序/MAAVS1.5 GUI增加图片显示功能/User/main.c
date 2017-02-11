/* Includes ------------------------------------------------------------------*/
#include "user_include.h"
#include "user_define.h"
#include <stddef.h>
#include "GUI.h"
#include "LCD_Driver.h"
#include "my_win.h"
#include "RA8835.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "rtc.h" 
#include "adc.h"
#include "myFont16_21.h"
#include "fengshi2.h"
#include "feegnshi1.h"
#include "inputWindow.h"
#include "user_Dialog.h"
#include "menu_dialog.h"
#include "systemConfig.h"
#include "systemExplain.h"
#include "time_dialog.h"
#include "warning_dialog.h"
#include "draw_dialog.h"
#include "drawLine_dialog.h"
#include "report_dialog.h"
#include "healthDataReport.h"
#include <stdlib.h>
unsigned char status_flag=0;
int adcValue,time_flag;
extern int rotate_flag;
const unsigned char gImage_fegnshi[192] = { /* 0X00,0X01,0X30,0X00,0X20,0X00, */
0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X80,0X00,0X00,0X01,0X1F,0XF8,0X80,0X00,0X00,0X01,
0X10,0X08,0X80,0X00,0X00,0X01,0X10,0X08,0X80,0X00,0X00,0X01,0X14,0X28,0X80,0X0B,
0XE8,0X01,0X12,0X28,0X80,0X0B,0XE8,0X01,0X11,0X48,0X80,0X0B,0XE8,0X01,0X11,0X48,
0X80,0X1B,0XEC,0X01,0X10,0X88,0X80,0X33,0XE7,0X01,0X10,0X88,0X80,0X67,0XF1,0X81,
0X11,0X48,0X80,0XCF,0XF8,0X41,0X11,0X49,0X81,0X9F,0XFC,0X41,0X12,0X25,0X81,0X1F,
0XFC,0X41,0X24,0X25,0X81,0X07,0XE0,0X41,0X20,0X03,0X81,0X31,0X8C,0XC1,0X40,0X01,
0X80,0X9C,0X39,0X81,0X00,0X00,0X80,0X47,0XF6,0X01,0X13,0XFC,0X80,0X37,0XEC,0X01,
0X0A,0X04,0X80,0X1B,0XE8,0X01,0X0A,0X04,0X80,0X0B,0XE8,0X01,0X43,0XFC,0X80,0X0B,
0XE8,0X01,0X22,0X04,0X80,0X0B,0XE8,0X01,0X22,0X04,0X80,0X0B,0XE8,0X01,0X0B,0XFC,
0X80,0X0B,0XE8,0X01,0X08,0X90,0X80,0X0B,0XE8,0X01,0X10,0X90,0X80,0X0B,0XE8,0X01,
0X74,0X92,0X80,0X0B,0XE8,0X01,0X12,0X94,0X80,0X00,0X00,0X01,0X11,0X98,0X80,0X00,
0X00,0X01,0X10,0X90,0X80,0X00,0X00,0X01,0X17,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,
};

const unsigned char logo2[12]={
0x81,0x18,0x42,0x24,
0x44,0x81,0x12,0xff,
0xff,0xff,0xff,0xff
};


 void User_delay(unsigned int j)  //1ms delay volatile
{
    volatile unsigned int i;	
	  while(j--)
    for(i=6000000;i>0;i--);
}

//刷新时间
void refresh_time(void) {
	if (time_flag > 100) {
			time_flag = 0;
			printf("active window :%d \r\n",WM_GetActiveWindow());
			WM_SetFocus(time_hWin);
			GUI_SendKeyMsg(MY_MESSAGE_ID_TIME,1);
			if (myMessageType == MY_MESSAGE_ID_LOGO) {
					WM_SetFocus(mainForm_hWin);
//					GUI_SendKeyMsg(MY_MESSAGE_ID_ENCODER0,1);
			}else if (myMessageType == MY_MESSAGE_ID_MESSAGE_SETTING) {
					WM_SetFocus(dialog_hWin);
			}else if (myMessageType == MY_MESSAGE_ID_SYSTEM_SETTING) {
						WM_SetFocus(mainForm_hWin);
			}else if (myMessageType == MY_MESSAGE_ID_DRAW_LINE) {
						WM_SetFocus(drawLine_hWin);
				if(isOrSetPoint==1) {
						GUI_SendKeyMsg(MY_MESSAGE_ID_DRAW_POINT,1);
				}else if(isOrExitDrawLine==1) {
						isOrExitDrawLine = 0;
						rotateEnter_flag = 1;
						GUI_SendKeyMsg(MY_MESSAGE_ID_ENTER,1);
				}
			}else if(myMessageType == MY_MESSAGE_ID_CHECK_REPORT) {
						WM_SetFocus(report_hWin);
			}else {
				printf("逻辑出问题了");
			}
	}else {
	
		if(isOrShowExplain == 1) {
			isOrShowExplain = 0;
			explain_dialogTask();
		}else if (isOrShowSetTime == 1) {
			isOrShowSetTime = 0;
			time_dialogTask();
		}else if(isBeginCheck == 1){ 
				isBeginCheck = 0;
				if(isOrSetMessage==0) {
				//提示个人信息不能为空
				warning_dialogTask();
				}else {
					rotateEnter_flag = 0;
					isOrSetPoint = 1;
				drawLine_dialogTask();
				}
		}else if(isOrShowReport==1) {
			 isOrShowReport =0;
			reportType = logoCount;
			report_dialogTask();
		}
	}
}
int main(void)
{
	GUI_RECT rect;
	u8 key,i,length;
	unsigned short int value;
	Stru_Time time,getTime;
	char data[400]="串口测试数据\r\n";
	time.Year = 16;
	time.Month = 12;
	time.Day = 31;
	time.Hour = 17;
	time.Minutes = 7;
	time.Second = 30;
	SystemInit();
	delay_init(72);	     //延时初始化
	LED_Init();
	KEY_Init();
	E11_init();
	fnRTC_Init();
	Adc_Init();
  uart_init(9600); 
	fnRTC_Init();
	E17_uart_init(9600);
	GUI_Init();
	clr_ram();
	GUI_SetFont(&GUI_FontHZ_SimSun_1515);
	//绘制时间框
		MainTask();
	GUI_DrawBitmap(&bmshijian,0,0);

while(1)
{

		
printf("开始测试\r\n");
//	changeDir(0);
//	readDataByAddress(0x0000,0x2800,mydata); 
//	UART1_Tx(mydata,0x2800);
//	readDataByAddress(0x2800,0x2800,mydata); 
//	UART1_Tx(mydata,0x2800);
//	readDataByAddress(0x5000,0x2800,mydata); 
//	UART1_Tx(mydata,0x2800);
	while(1) {
	 	key=KEY_Scan();
		
		if(selectEnd == 1) {
			refresh_time();
			send_rotate_message();
		}
		adcValue = Get_Adc(0);
		if(key !=0)//KEY0按下,则执行校准程序
		{
			printf("按键: KEY=%d 被按下  adc = %d\r\n",key,adcValue);
			if(key == 1) { //信息设定
				if (myMessageType == MY_MESSAGE_ID_LOGO) {
						dialogTask();
				}
			}else if (key == 2) {  //进入检测
				if(isOrSetMessage==0) {
					//提示个人信息不能为空
					warning_dialogTask();
				}else {
						drawLine_dialogTask();
				}
			}else if (key == 3) {   //打印
				if(isOrPrintReport==1) {
					char displayTime[50],length;
					Stru_Time getTime;
					fnRTC_GetTime(&getTime); 	
					length = reportLength[reportType];
					E17_FontConfig();
					for(i=1;i<=length;i++) {
						E17_sendString(healthData[length-i]);
						E17_sendString("\r\n");
						delay_ms(100);
					}
					sprintf(data,"检测时间:%02d/%02d/%02d %02d:%02d:%02d\r\n",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second);
					E17_sendString2(data);
					delay_ms(100);
					sprintf(data,"性别:%s 年龄:%s 婚否:%s 体型:%s\r\n",saveData[0],saveData[1],saveData[2],saveData[3]);//saveData[0],saveData[1],saveData[2],saveData[3]
					E17_sendString2(data);
					delay_ms(100);
					sprintf(data,"        健康评估打印报告单\r\n\r\n");
					E17_sendString2(data);
					
					isOrPrintReport =0;
					isOrAllowCheck =0;
				}
			}else if (key == 4) {   //系统菜单
				menu_dialogTask();
			}else {  //确认按键，或进入检测
				printf("错误按键按下\r\n");
			}
//				E17_sendString(data);
				LED0=!LED0;	
		}

	}
}

}



