
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

//EventsFunctionList
//EndofEventsFunctionList
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
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  320,240,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "TEXT0",             GUI_ID_TEXT0,            5, 5, 310, 20, 0,0},	
		{ TEXT_CreateIndirect,      "TEXT1",             GUI_ID_TEXT1,            5, 30, 310, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT2",             GUI_ID_TEXT2,            5, 55, 310, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT3",             GUI_ID_TEXT3,            5, 80, 310, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT4",             GUI_ID_TEXT4,            5, 105, 310, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT5",             GUI_ID_TEXT5,            5, 130, 310, 20, 0,0},
		{ TEXT_CreateIndirect,      "TEXT6",             GUI_ID_TEXT6,            5, 200, 310, 20, 0,0},

};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void ExplainPaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
//    GUI_SetColor(0xffffff);
//    GUI_DrawLine(1,1,108,1);
//	  GUI_DrawLine(108,1,108,156);
//    GUI_DrawLine(1,18,108,18);
//    GUI_DrawLine(1,156,108,156);
//	  GUI_DrawLine(1,139,108,139);
//    GUI_DrawLine(1,1,1,156);
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void ExplainInitDialog(WM_MESSAGE * pMsg)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		WM_HWIN hText1,hText2,hText3,hText4,hText5,hText6,hText7;
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
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT4),GUI_TA_VCENTER|GUI_TA_LEFT);    
		//    
		//GUI_ID_TEXT5
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT5),GUI_TA_VCENTER|GUI_TA_LEFT);    
		//    
		//GUI_ID_TEXT6
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT6),GUI_TA_VCENTER|GUI_TA_CENTER);    
	/*������д��ڵľ��*/
		 hText1 = WM_GetDialogItem(hWin,GUI_ID_TEXT0);
		 hText2 = WM_GetDialogItem(hWin,GUI_ID_TEXT1);	
		 hText3 = WM_GetDialogItem(hWin,GUI_ID_TEXT2);
		 hText4 = WM_GetDialogItem(hWin,GUI_ID_TEXT3);
		 hText5 = WM_GetDialogItem(hWin,GUI_ID_TEXT4);
		 hText6 = WM_GetDialogItem(hWin,GUI_ID_TEXT5);
		 hText7 = WM_GetDialogItem(hWin,GUI_ID_TEXT6);

		/*��ʼ�����пؼ�*/		
		TEXT_SetFont(hText1,&GUI_FontHZ_SimSun_1616);
		TEXT_SetFont(hText2,&GUI_FontHZ_SimSun_1616);
		TEXT_SetFont(hText3,&GUI_FontHZ_SimSun_1616);
		TEXT_SetFont(hText4,&GUI_FontHZ_SimSun_1616);
		TEXT_SetFont(hText5,&GUI_FontHZ_SimSun_1616);
		TEXT_SetFont(hText6,&GUI_FontHZ_SimSun_1616);
		TEXT_SetFont(hText7,&GUI_FontHZ_SimSun_1616);


		TEXT_SetText(hText1,"ϵͳ˵��");
		TEXT_SetText(hText2,"1.Ϊ�˼���׼ȷ��,���ñ�������ڼ��ǰ");

		TEXT_SetText(hText3,"��Ϣ5����,���Ե缫�Ӵ�Ƥ�����,��Ҫʱ");
		TEXT_SetText(hText4,"ͿĨ��ʿ��������Ƥ���Ӵ���λ�ĵ�����!");
		TEXT_SetText(hText5,"2.�������漰�ĵ�λ��Ϊ(΢��/ŷķ)");
		TEXT_SetText(hText6,"3.�������������б�������ο�!");
		TEXT_SetText(hText7,"����������������ҽѧ�о�Ժ   ������Ʒ");

//			//���ж�
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11|GPIO_PinSource15); 
//		EXTI_InitStructure.EXTI_Line = EXTI_Line11|EXTI_Line15;
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
//		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//		EXTI_Init(&EXTI_InitStructure); 

}




/*********************************************************************
*
*       Dialog callback routine
*/

void SystemExplain(WM_HWIN hWin) {  //��Ϣ�趨
	static int messageType =5,lastMessageType=5;
			//��ת������
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

static void _cbExplainDialogCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
					ExplainPaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            ExplainInitDialog(pMsg);
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
								}
								    break;
								case MY_MESSAGE_ID_ENTER:
								{
										SystemExplain(hWin);
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


void explain_dialogTask(void) {
	
		myMessageType = MY_MESSAGE_ID_SYSTEM_EXPLAIN;
		explain_hWin	= GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbExplainDialogCallback, root_hWin, 0, 0);
		printf("\r\nhandle: %d\r\n",explain_hWin);
		GUI_ExecCreatedDialog(explain_hWin);
}

