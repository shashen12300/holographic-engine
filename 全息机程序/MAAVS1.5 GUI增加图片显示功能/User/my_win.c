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

#include "fengshi2.h"
#include "my_win.h"
#include "rtc.h"
#include <stddef.h>
#include "key.h"
#include "user_Dialog.h"
#include "User_LinehWin.h"

//EventsFunctionList
//EndofEventsFunctionList
WM_HWIN hWin;
WM_HWIN mainForm_hWin;
WM_HWIN dialog_hWin;
WM_HWIN time_hWin;
WM_HWIN line_hWin;
void _mainFormCallback(WM_MESSAGE * pMsg)
{
		int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
						GUI_DrawBitmap(&bmfengshi2,0,0);
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
								}
										break;
								case MY_MESSAGE_ID_KEY1:
                   printf("key=%d\r\n",MY_MESSAGE_ID_KEY1 - GUI_ID_USER);
                    break;
								case MY_MESSAGE_ID_KEY2:
                   printf("key=%d\r\n",MY_MESSAGE_ID_KEY2 - GUI_ID_USER);
                    break;
								case MY_MESSAGE_ID_KEY3:
                   printf("key=%d\r\n",MY_MESSAGE_ID_KEY3 - GUI_ID_USER);
                    break;
								case MY_MESSAGE_ID_KEY4:
                   printf("key=%d\r\n",MY_MESSAGE_ID_KEY4 - GUI_ID_USER);
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
								case MY_MESSAGE_ID_TIME:
								{		
										char displayTime[20];
										Stru_Time time,getTime;
										fnRTC_GetTime(&getTime); 	
										WM_SelectWindow(hWin);
										sprintf(displayTime,"%d/%02d/%02d %02d:%02d:%02d",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second);
										GUI_DispStringAt(displayTime,175,3);
                   printf("time=%d\r\n",MY_MESSAGE_ID_TIME - GUI_ID_USER);
								}
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
				//GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
				hWin=WM_CreateWindow(0,0,320,240,WM_CF_SHOW,NULL,0);//根窗口
//			hWin = WM_GetDesktopWindow();
				time_hWin = WM_CreateWindowAsChild(0,0,320,203,hWin,WM_CF_SHOW,_cbTimeCallback,0);//时间窗口
				mainForm_hWin=WM_CreateWindowAsChild(0,37,320,203,hWin,WM_CF_SHOW,_mainFormCallback,0); //菜单窗口
				line_hWin= LineTask(); //曲线窗口
//				dialog_hWin =	Dialog_Task();//弹出窗口
//					dialogTask();
//			WM_SelectWindow(mainForm_hWin);

}

