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
#include "delay.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "menu_dialog.h"
#include "myFont16_21.h"
#include "GUI.h"
#include "key.h"
# include <stdio.h>
# include <stdlib.h>
#include "systemConfig.h"
#include "systemExplain.h"
//EventsFunctionList
//EndofEventsFunctionList
 extern int rotate_flag;

/********************************************************************
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
		
		{ TEXT_CreateIndirect,      "TEXT1",             GUI_ID_TEXT1,            7, 30, 96, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT2",             GUI_ID_TEXT2,            7, 55, 96, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT3",             GUI_ID_TEXT3,            7, 80, 96, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT4",             GUI_ID_TEXT4,            7, 105, 96, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT6",             GUI_ID_TEXT5,            41, 140, 30, 16, 0,0},

};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void MenuPaintDialog(WM_MESSAGE * pMsg)
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

void MenuInitDialog(WM_MESSAGE * pMsg)
{
	WM_HWIN hText1,hText2,hText3,hText4,hText5,hText6,hText7,hText13,hText14,hText15,hText16,hText17;
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
	   //

    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_VCENTER|GUI_TA_CENTER);
		//
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT12),0x000000);
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

	/*获得所有窗口的句柄*/
		 hText1 = WM_GetDialogItem(hWin,GUI_ID_TEXT0);
		 hText2 = WM_GetDialogItem(hWin,GUI_ID_TEXT1);	
		 hText3 = WM_GetDialogItem(hWin,GUI_ID_TEXT2);
		 hText4 = WM_GetDialogItem(hWin,GUI_ID_TEXT3);
		 hText5 = WM_GetDialogItem(hWin,GUI_ID_TEXT4);
		 hText6 = WM_GetDialogItem(hWin,GUI_ID_TEXT5);

		/*初始化所有控件*/		
		TEXT_SetFont(hText1,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText2,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText3,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText4,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText5,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText6,&GUI_FontHZ_SimSun_1515);


		TEXT_SetText(hText1,"系统菜单");
		TEXT_SetText(hText2,"系统说明");

		TEXT_SetText(hText3,"时钟设定");
		if(isOneCheck == 0){
			TEXT_SetText(hText4,"多项检测");
		}else {
			TEXT_SetText(hText4,"单项检测");	
		}
		TEXT_SetText(hText5,"重新检测");
		TEXT_SetText(hText6,"确认");
		

}




/*********************************************************************
*
*       Dialog callback routine
*/

void SystemMenu(WM_HWIN hWin) {  //信息设定
	static int messageType =5,lastMessageType=5;
			//旋转编码器
		if((rotate_flag == 1)&&(rotateEnter_flag==0)) {
			if(KEY_A == 0) {
						delay_us(20);
            if(KEY_B == 1)
            {
							messageType++;
							if(messageType==6) {
								messageType = 1;
							}
							printf("menu :right\r\n");
            }else {
								messageType--;
								if(messageType < 1) {
									messageType = 5;
								printf(" menu :left\r\n");
							}

						}
						
					TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0+lastMessageType),0x000000);
					TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0+lastMessageType),0xffffff);
					TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0+messageType),0xffffff);
					TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0+messageType),0x000000);
					lastMessageType = messageType;
					rotate_flag = 0;
					selectEnd = 1;
					}
		}else if((rotate_flag == 0)&&(rotateEnter_flag==1)){
							switch (messageType) 
							{
								case 1:  //系统说明
								{
									WM_SelectWindow(hWin);
									GUI_EndDialog(hWin, 0);
									WM_SelectWindow(mainForm_hWin);
									myMessageType = MY_MESSAGE_ID_LOGO;
									WM_Exec();
									isOrShowExplain = 1;
									messageType =5;
									lastMessageType=5;
									printf("menu-1");
								}break;
								case 2:  //时钟设定
								{
									WM_SelectWindow(hWin);
									GUI_EndDialog(hWin, 0);
									WM_SelectWindow(mainForm_hWin);
									myMessageType = MY_MESSAGE_ID_LOGO;
									WM_Exec();
									isOrShowSetTime = 1;
									messageType =5;
									lastMessageType=5;
									printf("menu-2");
								}break;								
								case 3:  //单项/多项检测
								{
									if(isOneCheck == 1){
										isOneCheck = 0;
										TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT3),"多项检测");
										WM_Exec();
									}else {
										isOneCheck = 1;
										isOrAllowCheck = 1;
										TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT3),"单项检测");
									}

									printf("menu-3");
								}break;
								case 4: 
								{//重新检测
									isRestartCheck = 1;
									isOrAllowCheck = 1;
									WM_SelectWindow(hWin);
									GUI_EndDialog(hWin, 0);
									WM_SelectWindow(mainForm_hWin);
									myMessageType = MY_MESSAGE_ID_LOGO;
									WM_Exec();
									messageType =5;
									lastMessageType=5;
									printf("menu-4");
								}break;
								case 5:  //确认
								{
									WM_SelectWindow(hWin);
									GUI_EndDialog(hWin, 0);
									WM_SelectWindow(mainForm_hWin);
									myMessageType = MY_MESSAGE_ID_LOGO;
									WM_Exec();
									messageType =5;
									lastMessageType=5;
									printf("menu-5");
								}break;
								default:
											;
							}

		}
		rotateEnter_flag=0;
		rotate_flag = 0;
		selectEnd = 1;

}

static void _cbMenuDialogCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
					MenuPaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            MenuInitDialog(pMsg);
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
										SystemMenu(hWin);
								}
								    break;
								case MY_MESSAGE_ID_ENTER:
								{
										SystemMenu(hWin);
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


void menu_dialogTask(void) {
		myMessageType = MY_MESSAGE_ID_SYSTEM_SETTING;//系统菜单
		setOrLogoCount(logoCount,0);

		menu_hWin	= GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbMenuDialogCallback, root_hWin, 0, 0);
		printf("\r\nhandle: %d\r\n",menu_hWin);
		GUI_ExecCreatedDialog(menu_hWin);
}

