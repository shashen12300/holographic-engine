#include "GUI.h"
#include "DIALOG.h"
#include "User_LinehWin.h"
#include "rtc.h"
#include "my_win.h"
#include "systemConfig.h"

void PaintLineDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
	  FRAMEWIN_SetClientColor(hWin,0xffffff);
    FRAMEWIN_SetTitleVis(hWin,0);
//		GUI_DispStringAt("2017-1-12 ",10,4);
//		GUI_DispStringAt("2017-1-13 ",10,35);
//		GUI_DispStringAt("2017-1-14 ",10,70);

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitLineDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetClientColor(hWin,0xffffff);
    FRAMEWIN_SetTitleVis(hWin,0);
    //
}

//时间窗口回调函数
static void _cbLineCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintLineDialog(pMsg);
            break;
				case WM_CREATE:
						WM_Exec();
            break;
        case WM_INIT_DIALOG:
            InitLineDialog(pMsg);
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
								case MY_MESSAGE_ID_LINE:
								{		
										char displayTime[20];
										Stru_Time time,getTime;
										fnRTC_GetTime(&getTime); 	
										sprintf(displayTime,"%d/%02d/%02d %02d:%02d:%02d",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second);
										GUI_DispStringAt(displayTime,175,4);
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

WM_HWIN LineTask(void) {
	
		WM_HWIN line_hWin;
		line_hWin = WM_CreateWindowAsChild(0,37,320,203,root_hWin,WM_CF_HIDE,_cbLineCallback,0); //曲线窗口
		return line_hWin;
}