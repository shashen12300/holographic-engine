
/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/
#include "systemExplain.h"
#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "delay.h"
#include "WM.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "my_win.h"
#include "myFont16_21.h"
#include "GUI.h"
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include "systemConfig.h"
#include "SimSun_1616.h"

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  50,  200,150,FRAMEWIN_CF_MOVEABLE,0},
		{ TEXT_CreateIndirect,      "TEXT1",             GUI_ID_TEXT10,            75, 23, 30, 16, 0,0},


};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void DrawPaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
	
	    GUI_SetColor(0xffffff);
    GUI_DrawLine(1,1,176,1);
	  GUI_DrawLine(176,1,176,41);
	  GUI_DrawLine(1,41,176,41);
    GUI_DrawLine(1,1,1,41);
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void DrawInitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetBarColor(hWin,1,0x000000);
    FRAMEWIN_SetClientColor(hWin,0x000000);
    FRAMEWIN_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_CENTER);
    FRAMEWIN_SetTitleVis(hWin,0);
    FRAMEWIN_SetTitleHeight(hWin,0);
       //
    //GUI_ID_TEXT0
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0x000000);
	  TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0xffffff);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);

}




/*********************************************************************
*
*       Dialog callback routine
*/

void SystemDraw(WM_HWIN hWin) {  //????
	static int messageType =5,lastMessageType=5;
			//?????
		if(rotateEnter_flag==1) {
				rotateEnter_flag = 0;
				WM_SelectWindow(hWin);
				GUI_EndDialog(hWin, 0);
				WM_SelectWindow(mainForm_hWin);
				myMessageType = MY_MESSAGE_ID_LOGO;
				WM_Exec();
				isOrRefreshMessage =1;
		}

}

void _cbDrawDialogCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
					DrawPaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            DrawInitDialog(pMsg);
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
										SystemDraw(hWin);
								}
								    break;
								case MY_MESSAGE_ID_ENTER:
								{
										SystemDraw(hWin);
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
                        GUI_EndDialog(hWin, 1);
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


void Draw_dialogTask(void) {
	
		myMessageType = MY_MESSAGE_ID_DRAW_LINE;
		draw_hWin	= GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDrawDialogCallback, root_hWin, 0, 0);
		printf("\r\nhandle: %d\r\n",draw_hWin);
		GUI_ExecCreatedDialog(draw_hWin);
}

