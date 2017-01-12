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
#include "GUI.h"
#include "key.h"
# include <stdio.h>
# include <stdlib.h>
 extern int rotate_flag;
 char *saveData[5] = {"男","35","未婚","正常","03"};
WM_HWIN hText1,hText2,hText3,hText4,hText5,hText6,hText7,hText13,hText14,hText15,hText16,hText17;
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
		
		{ TEXT_CreateIndirect,      "TEXT1",             GUI_ID_TEXT10,            5, 30, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT2",             GUI_ID_TEXT11,            5, 50, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT3",             GUI_ID_TEXT12,            5, 70, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT4",             GUI_ID_TEXT13,            5, 90, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT5",             GUI_ID_TEXT14,            5, 110, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT6",             GUI_ID_TEXT15,            41, 141, 30, 15, 0,0},

		{ TEXT_CreateIndirect,      ":",             GUI_ID_TEXT2,            35, 30, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT3,            35, 50, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT4,            35, 70, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT5,          35, 90, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT6,          35, 110, 5, 16, 0,0},
		
		{ TEXT_CreateIndirect,      "TEXT12",             GUI_ID_TEXT16,            60, 30, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT13",             GUI_ID_TEXT17,            60, 50, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT14",             GUI_ID_TEXT18,            60, 70, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT15",             GUI_ID_TEXT19,            60, 90, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT16",             GUI_ID_TEXT20,            60, 110, 30, 16, 0,0},




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
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10),0xffffff);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10),0x000000);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT10),GUI_TA_VCENTER|GUI_TA_CENTER);
		//
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT11),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT11),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT11),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//
    //GUI_ID_TEXT3
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT12),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT12),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT12),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//
		//GUI_ID_TEXT4
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT13),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT13),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT13),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//    
		//GUI_ID_TEXT5
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT14),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT14),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT14),GUI_TA_VCENTER|GUI_TA_CENTER);    
		//    
		//GUI_ID_TEXT6
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT15),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT15),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT15),GUI_TA_VCENTER|GUI_TA_CENTER);   
		//
				//    
		//GUI_ID_TEXT7
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT16),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT16),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT16),GUI_TA_VCENTER|GUI_TA_CENTER);   
				//    
		//GUI_ID_TEXT8
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT17),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT17),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT17),GUI_TA_VCENTER|GUI_TA_CENTER);   
				//    
		//GUI_ID_TEXT9
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT18),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT18),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT18),GUI_TA_VCENTER|GUI_TA_CENTER);   
				//    
		//GUI_ID_TEXT10
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT19),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT19),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT19),GUI_TA_VCENTER|GUI_TA_CENTER);  
    //GUI_ID_TEXT0
    //
		TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT20),0x000000);
	  TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT20),0xffffff);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT20),GUI_TA_VCENTER|GUI_TA_CENTER);		
				//    
		//GUI_ID_TEXT11
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT2),GUI_TA_VCENTER|GUI_TA_CENTER);   
						//    
		//GUI_ID_TEXT12
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT3),GUI_TA_VCENTER|GUI_TA_CENTER);   
				//    
		//GUI_ID_TEXT13
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT4),GUI_TA_VCENTER|GUI_TA_CENTER);   
						//    
		//GUI_ID_TEXT14
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT5),GUI_TA_VCENTER|GUI_TA_CENTER);   
				//    
		//GUI_ID_TEXT15
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT6),GUI_TA_VCENTER|GUI_TA_CENTER);     
	/*获得所有窗口的句柄*/
		hText1 = WM_GetDialogItem(hWin,GUI_ID_TEXT0);
		hText2 = WM_GetDialogItem(hWin,GUI_ID_TEXT15);
		
		hText3 = WM_GetDialogItem(hWin,GUI_ID_TEXT10);
		hText4 = WM_GetDialogItem(hWin,GUI_ID_TEXT11);
		hText5 = WM_GetDialogItem(hWin,GUI_ID_TEXT12);
		hText6 = WM_GetDialogItem(hWin,GUI_ID_TEXT13);
		hText7 = WM_GetDialogItem(hWin,GUI_ID_TEXT14);
		
		hText13 = WM_GetDialogItem(hWin,GUI_ID_TEXT16);
		hText14 = WM_GetDialogItem(hWin,GUI_ID_TEXT17);
		hText15 = WM_GetDialogItem(hWin,GUI_ID_TEXT18);
		hText16 = WM_GetDialogItem(hWin,GUI_ID_TEXT19);
		hText17 = WM_GetDialogItem(hWin,GUI_ID_TEXT20);	

		/*初始化所有控件*/		
		TEXT_SetFont(hText1,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText2,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText3,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText4,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText5,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText6,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText7,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText13,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText14,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText15,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText16,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText17,&GUI_FontHZ_SimSun_1515);

		TEXT_SetText(hText1,"信息设定");
		TEXT_SetText(hText2,"确认");

		TEXT_SetText(hText3,"性别");
		TEXT_SetText(hText4,"年龄");
		TEXT_SetText(hText5,"婚否");
		TEXT_SetText(hText6,"体型");
		TEXT_SetText(hText7,"模式");
		
		TEXT_SetText(hText13,saveData[0]);
		TEXT_SetText(hText14,saveData[1]);
		TEXT_SetText(hText15,saveData[2]);
		TEXT_SetText(hText16,saveData[3]);
		TEXT_SetText(hText17,saveData[4]);

}




/*********************************************************************
*
*       Dialog callback routine
*/

void MessageSetting(WM_HWIN hWin) {  //信息设定
	static int messageType =0,lastMessageType=0,isSelectType=0,maxCount = 0;
			//旋转编码器
		if((rotate_flag == 1)&&(isSelectType==0)) {
			if(KEY_A == 0) {
            if(KEY_B == 1)
            {
							messageType++;
							if(messageType==6) {
								messageType = 0;
							}
							printf("messageSetting :right\r\n");
            }else {
							if(KEY_B == 0) {
								messageType--;
								if(messageType < 0) {
									messageType = 5;
								}
								printf(" messageSetting :left\r\n");
							}

						}
						
					TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0x000000);
					TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0xffffff);
					TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0xffffff);
					TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0x000000);
						lastMessageType = messageType;
					}
		}else if((rotate_flag == 0)&&(isSelectType==0)){
			char data[5] = {2,99,2,3,5};
					if(rotateEnter_flag==1) {
						isSelectType = 1;
						rotateEnter_flag = 0;
						maxCount = data[lastMessageType];
						messageType = lastMessageType + 6;	
						if (lastMessageType == 5) {
							GUI_EndDialog(hWin, 0);
								return;
						}
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0x000000);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0xffffff);
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0xffffff);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0x000000);
						lastMessageType = messageType;
					}
		}else if((rotateEnter_flag==0)&&(isSelectType == 1)) {
			static int count=0;
			char *data[10];
			
					if((KEY_A == 0)&&(rotate_flag == 1)) {
            if(KEY_B == 1)
            {
							count++;
							if(count == maxCount) {
								count = 0;
							}
							printf("messageSetting :right\r\n");
            }else {
							if(KEY_B == 0) {
								count--;
								if(count < 0) {
									count = maxCount-1;
								}
							printf(" messageSetting :left\r\n");
							}

						}
					 if (lastMessageType == 6) {
								data[0] = "男";
								data[1] = "女";
								saveData[lastMessageType-6] = data[count];
								TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),data[count]);
						}else if (lastMessageType == 7) {
							char str[20];
							static int base = 35;
							count +=base;
							base = 0;
//								itoa(count, str, 10);
							sprintf(str,"%d",count);
								TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),str);
								saveData[lastMessageType-6] = str;
						}else if (lastMessageType == 8) { 
								data[0] = "未婚";
								data[1] = "已婚";
								saveData[lastMessageType-6] = data[count];
								TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),data[count]);
							
						}else if (lastMessageType == 9) { 
								data[0] = "偏瘦";
								data[1] = "正常";
								data[2] = "偏旁";
								saveData[lastMessageType-6] = data[count];
								TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),data[count]);
						}
						else if (lastMessageType == 10) { 
								data[0] = "01";
								data[1] = "02";
								data[2] = "03";
								data[3] = "04";
								data[4] = "05";
								saveData[lastMessageType-6] = data[count];
								TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),data[count]);
						}

					}	
		}else if((rotateEnter_flag==1)&&(isSelectType == 1)) {
						delay_ms(10);
						isSelectType = 0;
						rotateEnter_flag = 0;
						messageType = lastMessageType -6;
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0x000000);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0xffffff);
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0xffffff);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0x000000);
						lastMessageType = messageType;
		}
		
		rotate_flag = 0;
		selectEnd = 1;
}

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
								case MY_MESSAGE_ID_ENCODER0:
								{
										MessageSetting(hWin);
								}
								    break;
								case MY_MESSAGE_ID_ENTER:
								{
										MessageSetting(hWin);
//									  GUI_EndDialog(hWin, 1);
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
//                case GUI_ID_TEXT10:
//                    if(NCode==WM_NOTIFICATION_CHILD_DELETED)
//												WM_DeleteWindow(pMsg->hWinSrc);
//                    break;
//								case GUI_ID_TEXT11:
//                    if(NCode==WM_NOTIFICATION_CHILD_DELETED)
//											WM_HideWindow(pMsg->hWinSrc);
//                    break;
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
		myMessageType = MY_MESSAGE_ID_MESSAGE_SETTING;
		 GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialogCallback, hWin, 1, 1);
//	dialog_hWin	= GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialogCallback, 0, 0, 0);
//	GUI_ExecCreatedDialog(dialog_hWin);
}

