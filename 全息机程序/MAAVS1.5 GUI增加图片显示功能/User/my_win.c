/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stdio.h>
#include "GUI.h"
#include "DIALOG.h"


//#include "BUTTON.h"
//#include "CHECKBOX.h"
//#include "DROPDOWN.h"
//#include "EDIT.h"
//#include "FRAMEWIN.h"
//#include "LISTBOX.h"
//#include "MULTIEDIT.h"
//#include "RADIO.h"
//#include "SLIDER.h"
//#include "TEXT.h"
//#include "PROGBAR.h"
//#include "SCROLLBAR.h"
//#include "LISTVIEW.h"
#include <stdlib.h> 
#include "fengshi2.h"
#include "my_win.h"
#include "rtc.h"
#include <stddef.h>
#include "key.h"
#include "user_Dialog.h"
#include "systemConfig.h"

//EventsFunctionList
//EndofEventsFunctionList

void _mainFormCallback(WM_MESSAGE * pMsg)
{
		int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
						GUI_Clear();
						GUI_DrawBitmap(&bmfengshi2,0,0);
						WM_SelectWindow(hWin);
						WM_SetFocus(mainForm_hWin);
						setOrLogoCount(lastCount,0);
						setOrLogoCount(logoCount,1);
						lastCount = logoCount;
            break;
				case WM_CREATE:
						WM_Exec();
            break;
        case WM_INIT_DIALOG:
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
								case MY_MESSAGE_ID_ENCODER0:
								{
									rotate();
								}break;
								case MY_MESSAGE_ID_ENTER:
								{
                   printf("key = enter\r\n");
								}break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;
						//WM_Exec();
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)

                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;	
        default:
            WM_DefaultProc(pMsg);
    }
	}

/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbMyCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            	GUI_DrawBitmap(&bmshijian,0,0);
            break;
				case WM_CREATE:
						WM_Exec();
            break;
        case WM_INIT_DIALOG:
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

//时间窗口回调函数
static void _cbTimeCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
				{
					   GUI_DrawBitmap(&bmshijian,0,0);

				}
            break;
				case WM_CREATE:
						WM_Exec();
            break;
        case WM_INIT_DIALOG:
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
								case MY_MESSAGE_ID_TIME:
								{		
										char displayTime[50];
										Stru_Time time,getTime;
										fnRTC_GetTime(&getTime); 	
										WM_SelectWindow(hWin);
										sprintf(displayTime,"%d/%02d/%02d %02d:%02d:%02d",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second);
										GUI_DispStringAt(displayTime,175,3);
                   printf("refresh time");
									printf("active window :%d \r\n",WM_GetActiveWindow());

									if(isOrRefreshMessage == 1) {
											isOrRefreshMessage = 0;
										GUI_Clear();
										WM_Paint(hWin);
										sprintf(displayTime,"%d/%02d/%02d %02d:%02d:%02d",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second);
										GUI_DispStringAt(displayTime,175,3);
										sprintf(displayTime,"   性别:%s 年龄:%s 婚否:%s 体型:%s    ",saveData[0],saveData[1],saveData[2],saveData[3]);
										GUI_DispStringAt(displayTime,2,20);
									}else if (isOrSetClock == 1) {
											Stru_Time time;
											isOrSetClock = 0;
											time.Year = atoi(timeData[0]);
											time.Month = atoi(timeData[1]);
											time.Day = atoi(timeData[2]);
											time.Hour = atoi(timeData[3]);
											time.Minutes = atoi(timeData[4]);
											time.Second = atoi(timeData[5]);
											fnRTC_SetTime(time);
									}
								}break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}
/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void MainTask(void) 
{ 
	
			WM_SetDesktopColor(GUI_BLACK);      /* Automacally update desktop window */
			WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
			root_hWin=WM_CreateWindow(0,0,320,240,WM_CF_SHOW,NULL,0);//根窗口
			time_hWin = WM_CreateWindowAsChild(0,0,320,37,root_hWin,WM_CF_SHOW,_cbTimeCallback,0);//时间窗口
			mainForm_hWin=WM_CreateWindowAsChild(0,37,320,203,root_hWin,WM_CF_SHOW,_mainFormCallback,0); //菜单窗口


}

