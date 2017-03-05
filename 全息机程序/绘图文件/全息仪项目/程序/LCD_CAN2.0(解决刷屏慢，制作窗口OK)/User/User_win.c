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
    { FRAMEWIN_CreateIndirect,  "??????",      0,                       0,  0,  240,320,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "temp",              GUI_ID_TEXT0,            13, 11, 51, 21, 0,0},
    { LISTBOX_CreateIndirect,    NULL,               GUI_ID_LISTBOX0,         0,  175,234,113,0,0},
    { PROGBAR_CreateIndirect,    NULL,               GUI_ID_PROGBAR0,         53, 294,57, 20, 0,0},
    { TEXT_CreateIndirect,      "count:",            GUI_ID_TEXT1,            0,  294,47, 20, 0,0}
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
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetBarColor(hWin,1,0x000000);
    FRAMEWIN_SetClientColor(hWin,0x000000);
    FRAMEWIN_SetTitleVis(hWin,0);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0xffffff);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_LISTBOX0
    //
    LISTBOX_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),0,0x000000);
    LISTBOX_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),0,0xffffff);
    LISTBOX_SetAutoScrollV(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),1);
    LISTBOX_SetAutoScrollH(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),1);
    LISTBOX_AddString(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),"ljsdk");
    LISTBOX_AddString(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),"lksdfjs");
    LISTBOX_AddString(WM_GetDialogItem(hWin,GUI_ID_LISTBOX0),"lsdjf");
    //
    //GUI_ID_PROGBAR0
    //
    PROGBAR_SetBarColor(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),0,0xffffff);
    PROGBAR_SetBarColor(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),1,0x000000);
    PROGBAR_SetText(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),"");
    PROGBAR_SetValue(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),10);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xffffff);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_VCENTER|GUI_TA_CENTER);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
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
void MainTask(void) 
{ 
    GUI_Init();
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
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
        GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
	}
}

