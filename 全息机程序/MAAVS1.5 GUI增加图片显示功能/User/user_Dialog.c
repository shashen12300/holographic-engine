/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
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
#include "my_win.h"
#include "fengshi2.h"
#include "User_Dialog.h"
#include "myFont16_21.h"



//EventsFunctionList
//EndofEventsFunctionList


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
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       103,  43,  112,160,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "TEXT0",             GUI_ID_TEXT0,            2, 3, 104, 15, 0,0},
		{ TEXT_CreateIndirect,      "TEXT1",             GUI_ID_TEXT1,            5, 30, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT2",             GUI_ID_TEXT2,            5, 50, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT3",             GUI_ID_TEXT3,            5, 70, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT4",             GUI_ID_TEXT4,            5, 90, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT5",             GUI_ID_TEXT5,            5, 110, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT6",             GUI_ID_TEXT6,            41, 141, 30, 15, 0,0},



};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    GUI_SetColor(0xffffff);
    GUI_DrawLine(1,1,108,1);
	  GUI_DrawLine(108,1,108,156);
    GUI_DrawLine(1,18,108,18);
    GUI_DrawLine(1,156,108,156);
	  GUI_DrawLine(1,139,108,139);
    GUI_DrawLine(1,1,1,156);
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
		WM_HWIN hText1,hText2,hText3,hText4,hText5,hText6,hText7;
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
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xffffff);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0x000000);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_VCENTER|GUI_TA_CENTER);
		//
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT2),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//
    //GUI_ID_TEXT3
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT3),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//
		//GUI_ID_TEXT4
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT4),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//    
		//GUI_ID_TEXT5
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0xffffff);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0x000000);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT5),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//    
		//GUI_ID_TEXT6
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0xffffff);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0x000000);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT6),GUI_TA_VCENTER|GUI_TA_CENTER);   
		//

	/*获得所有窗口的句柄*/
		hText1 = WM_GetDialogItem(hWin,GUI_ID_TEXT0);
		hText2 = WM_GetDialogItem(hWin,GUI_ID_TEXT1);
		hText3 = WM_GetDialogItem(hWin,GUI_ID_TEXT2);
		hText4 = WM_GetDialogItem(hWin,GUI_ID_TEXT3);
		hText5 = WM_GetDialogItem(hWin,GUI_ID_TEXT4);
		hText6 = WM_GetDialogItem(hWin,GUI_ID_TEXT5);
		hText7 = WM_GetDialogItem(hWin,GUI_ID_TEXT6);

		/*初始化所有控件*/		
		TEXT_SetFont(hText1,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText2,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText3,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText4,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText5,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText6,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText7,&GUI_FontHZ_SimSun_1515);

		TEXT_SetText(hText1,"信息设定");
		TEXT_SetText(hText2,"性别");
		TEXT_SetText(hText3,"年龄");
		TEXT_SetText(hText4,"婚否");
		TEXT_SetText(hText5,"体型");
		TEXT_SetText(hText6,"模式");
		TEXT_SetText(hText7,"确认");

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbDialogCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
					PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
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


/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
WM_HWIN Dialog_Task(void) 
{ 
	WM_HWIN dialog_hWin;
	 GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialogCallback, 0, 0, 0);
  dialog_hWin = WM_CreateWindowAsChild(100,0,120,160,hWin,WM_CF_HIDE,_cbDialogCallback,0); //弹窗
	
		return dialog_hWin;
}

void dialogTask(void) {
		 GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialogCallback, 0, 0, 0);

}

