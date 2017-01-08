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


#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"

#include "fengshi2.h"
#include "User_win.h"
#include "my_win.h"
#include "rtc.h"
#include <stddef.h>
#include "key.h"

//EventsFunctionList
//EndofEventsFunctionList
WM_HWIN hWin;
WM_HWIN mainForm_hWin;
WM_HWIN timeForm_hWin;
WM_HWIN dialog_hWin;

/*********************************************************************
*
*       static data
*
**********************************************************************
*/



/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  320,240,FRAMEWIN_CF_MOVEABLE,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintMyDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitMyDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetClientColor(hWin,0x000000);
    //FRAMEWIN_SetTitleVis(hWin,0);

}

void _mainFormCallback(WM_MESSAGE * pMsg)
{
		int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            //PaintMyDialog(pMsg);
						GUI_DrawBitmap(&bmfengshi2,0,0);
            break;
				case WM_CREATE:
						WM_Exec();
            break;
        case WM_INIT_DIALOG:
            //InitMyDialog(pMsg);
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
				case MY_MESSAGE_ENCODER:
						Id = WM_GetId(pMsg->hWinSrc);
						NCode = pMsg->Data.v;  
					switch (Id)
					{
						case MY_MESSAGE_ID_ENCODER0:
						{
								static int lastCount = 0;
								selectLogoCount(lastCount);	
								selectLogoCount(NCode);	
							lastCount = NCode; 
						}
						break;
									
        default:
            WM_DefaultProc(pMsg);
    }
	}
}

/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{	
	char displayTime[20];
	unsigned short int value;
	Stru_Time time,getTime;
    int NCode, Id;
		WM_HWIN mainForm_hWin;
		WM_HWIN dialog_hWin;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
				case WM_PAINT:
						//GUI_SetBkColor(GUI_BLACK);
						//PaintMyDialog(pMsg);
//						mainForm_hWin=WM_CreateWindowAsChild(0,0,320,240,hWin,WM_CF_SHOW,_mainFormCallback,0); //主界面
//						dialog_hWin=WM_CreateWindowAsChild(100,43,120,160,hWin,WM_CF_SHOW/*WM_CF_HIDE*/,_dialogCallback,0); //弹窗
		fnRTC_GetTime(&getTime); 	
		sprintf(displayTime,"%d/%02d/%02d %02d:%02d:%02d",getTime.Year,getTime.Month,getTime.Day,getTime.Hour,getTime.Minutes,getTime.Second);
		GUI_DispStringAt(displayTime,160,5);
		GUI_DrawBitmap(&bmshijian,0,0);
					break;
        case WM_CREATE:
//						FRAMEWIN_SetClientColor(hWin,0x000000);
//						FRAMEWIN_SetTitleVis(hWin,0);
						WM_Exec();
            break;
//        case WM_INIT_DIALOG:
//            InitMyDialog(pMsg);
//            break;
//        case WM_KEY:
//            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
//            {
//                case GUI_KEY_ESCAPE:
//                    GUI_EndDialog(hWin, 1);
//                    break;
//                case GUI_KEY_ENTER:
//                    GUI_EndDialog(hWin, 0);
//                    break;
//            }
//            break;
//        case WM_NOTIFY_PARENT:
//            Id = WM_GetId(pMsg->hWinSrc); 
//            NCode = pMsg->Data.v;        
//            switch (Id) 
//            {
//                case GUI_ID_OK:
//                    if(NCode==WM_NOTIFICATION_RELEASED)
//                        GUI_EndDialog(hWin, 0);
//                    break;
//                case GUI_ID_CANCEL:
//                    if(NCode==WM_NOTIFICATION_RELEASED)
//                        GUI_EndDialog(hWin, 0);
//                    break;

//            }
//            break;
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

    //GUI_Init();
	
    //WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    //WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
		
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	while(1)
	{
				//GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
				hWin=WM_CreateWindow(0,0,320,240,WM_CF_SHOW,NULL,0);//根窗口
				timeForm_hWin = WM_CreateWindowAsChild(0,0,320,37,hWin,WM_CF_SHOW,_cbCallback,0); //时间窗口
				mainForm_hWin=WM_CreateWindowAsChild(0,37,320,203,hWin,WM_CF_SHOW,_mainFormCallback,0); //菜单窗口
//				dialog_hWin=WM_CreateWindowAsChild(100,43,120,160,hWin,WM_CF_HIDE,_dialogCallback,0); //弹窗
				//WM_Exec();
				
				//FRAMEWIN_Handle hFrame = FRAMEWIN_Create("Frame window",NULL,WM_CF_SHOW,0,0,320,240);
//				FRAMEWIN_SetFont(hFrame,&GUI_Font16B_ASCII);
//				FRAMEWIN_SetTextColor(hFrame,GUI_RED);
//				FRAMEWIN_SetBarColor(hFrame,0,GUI_GREEN);
//				FRAMEWIN_SetTextAlign(hFrame,GUI_TA_HCENTER);
//				hWin=WM_GetDesktopWindow();
//				mainForm_hWin=WM_CreateWindowAsChild(0,0,320,240,hWin,WM_CF_SHOW,_mainFormCallback,0); //主界面
//				dialog_hWin=WM_CreateWindowAsChild(100,43,120,160,hWin,WM_CF_HIDE/*WM_CF_HIDE*/,_dialogCallback,0); //弹窗
				
	}
}

