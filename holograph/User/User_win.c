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
    { FRAMEWIN_CreateIndirect,  "Data monitor",      0,                       0,  0,  480,320,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "Data1",             GUI_ID_TEXT0,            0,  37, 54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT0,            54, 37, 119,24, 0,0},
    { TEXT_CreateIndirect,      "Run normal",        GUI_ID_TEXT7,            14, 7,  98, 24, 0,0},
    { TEXT_CreateIndirect,      "......",            GUI_ID_TEXT8,            96, 7,  37, 24, 0,0},
    { TEXT_CreateIndirect,      "Data2",             GUI_ID_TEXT1,            0,  67, 54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT1,            54, 67, 119,24, 0,0},
    { TEXT_CreateIndirect,      "Data3",             GUI_ID_TEXT2,            0,  97, 54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT2,            54, 97, 119,24, 0,0},
    { TEXT_CreateIndirect,      "Data4",             GUI_ID_TEXT3,            0,  127,54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT3,            54, 127,119,24, 0,0},
    { TEXT_CreateIndirect,      "Data5",             GUI_ID_TEXT4,            0,  157,54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT4,            54, 157,119,24, 0,0},
    { TEXT_CreateIndirect,      "Data6",             GUI_ID_TEXT5,            0,  187,54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT5,            54, 187,119,24, 0,0},
    { TEXT_CreateIndirect,      "Data7",             GUI_ID_TEXT6,            0,  217,54, 24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT6,            54, 217,119,24, 0,0}
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
    FRAMEWIN_SetBarColor(hWin,1,0x9edd);
    FRAMEWIN_SetClientColor(hWin,0xdcdcdc);
    FRAMEWIN_SetTextColor(hWin,0x000000);
    FRAMEWIN_SetFont(hWin,&GUI_Font8x16);
    FRAMEWIN_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_LEFT);
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_SetTitleHeight(hWin,16);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT0
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT0),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT0),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT0),"2354");
    //
    //GUI_ID_TEXT7
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT7),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT7),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT7),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT8
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT8),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT8),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT8),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT1
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT1),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT1),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT1),"8978");
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT2),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT2
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT2),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT2),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT2),"7876");
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT3),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT3
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT3),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT3),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT3),"8767");
    //
    //GUI_ID_TEXT4
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT4),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT4
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT4),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT4),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT4),"eredv");
    //
    //GUI_ID_TEXT5
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT5),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT5),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT5
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT5),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT5),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT5),"43fg");
    //
    //GUI_ID_TEXT6
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0xdcdcdc);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT6),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT6),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT6
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT6),&GUI_Font16_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT6),GUI_TA_VCENTER|GUI_TA_LEFT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT6),"$%&^");

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

