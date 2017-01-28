/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/
#include "time_dialog.h"
#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "delay.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "fengshi2.h"
#include "myFont16_21.h"
#include "GUI.h"
#include "key.h"
# include <stdio.h>
# include <stdlib.h>
#include "systemConfig.h"

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
		
		{ TEXT_CreateIndirect,      "TEXT1",             GUI_ID_TEXT10,            20, 20, 15, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT2",             GUI_ID_TEXT11,            20, 40, 15, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT3",             GUI_ID_TEXT12,            20, 60, 15, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT4",             GUI_ID_TEXT13,            20, 80, 15, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT5",             GUI_ID_TEXT14,            20, 100, 15, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT6",             GUI_ID_TEXT15,            20, 120, 15, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT7",             GUI_ID_TEXT16,            41, 141, 30, 15, 0,0},

		{ TEXT_CreateIndirect,      ":",             GUI_ID_TEXT2,            35, 20, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT3,            35, 40, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT4,            35, 60, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT5,          	35, 80, 5, 16, 0,0},
    { TEXT_CreateIndirect,      ":",             GUI_ID_TEXT6,          	35, 100, 5, 16, 0,0},
		{ TEXT_CreateIndirect,      ":",             GUI_ID_TEXT7,          	35, 120, 5, 16, 0,0},

		{ TEXT_CreateIndirect,      "TEXT12",             GUI_ID_TEXT17,            60, 20, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT13",             GUI_ID_TEXT18,            60, 40, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT14",             GUI_ID_TEXT19,            60, 60, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT15",             GUI_ID_TEXT20,            60, 80, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT16",             GUI_ID_TEXT21,            60, 100, 30, 16, 0,0},
		{ TEXT_CreateIndirect,      "TEXT17",             GUI_ID_TEXT22,            60, 120, 30, 16, 0,0},


};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void ClockPaintDialog(WM_MESSAGE * pMsg)
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

void ClockInitDialog(WM_MESSAGE * pMsg)
{
	WM_HWIN hText1,hText2,hText3,hText4,hText5,hText6,hText7,hText8,hText9,hText10,hText11,hText12,hText13,hText14,hText15,hText16;
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
		 //GUI_ID_TEXT0
    //
		TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT21),0x000000);
	  TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT21),0xffffff);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT21),GUI_TA_VCENTER|GUI_TA_CENTER);		
		//GUI_ID_TEXT0
    //
		TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT22),0x000000);
	  TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT22),0xffffff);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT22),GUI_TA_VCENTER|GUI_TA_CENTER);		
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
		//    
		//GUI_ID_TEXT15
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT7),0x000000);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT7),0xffffff);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT7),GUI_TA_VCENTER|GUI_TA_CENTER);  		
	/*获得所有窗口的句柄*/
		hText1 = WM_GetDialogItem(hWin,GUI_ID_TEXT0);
		
		hText2 = WM_GetDialogItem(hWin,GUI_ID_TEXT10);
		hText3 = WM_GetDialogItem(hWin,GUI_ID_TEXT11);
		hText4 = WM_GetDialogItem(hWin,GUI_ID_TEXT12);
		hText5 = WM_GetDialogItem(hWin,GUI_ID_TEXT13);
		hText6 = WM_GetDialogItem(hWin,GUI_ID_TEXT14);
		hText7 = WM_GetDialogItem(hWin,GUI_ID_TEXT15);

		hText8 = WM_GetDialogItem(hWin,GUI_ID_TEXT16);
		hText9 = WM_GetDialogItem(hWin,GUI_ID_TEXT17);
		hText10 = WM_GetDialogItem(hWin,GUI_ID_TEXT18);
		hText11 = WM_GetDialogItem(hWin,GUI_ID_TEXT19);
		hText12 = WM_GetDialogItem(hWin,GUI_ID_TEXT20);	
		hText13 = WM_GetDialogItem(hWin,GUI_ID_TEXT21);
		hText14 = WM_GetDialogItem(hWin,GUI_ID_TEXT22);
		/*初始化所有控件*/		
		TEXT_SetFont(hText1,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText2,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText3,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText4,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText5,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText6,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText7,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText8,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText9,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText10,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText11,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText12,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText13,&GUI_FontHZ_SimSun_1515);
		TEXT_SetFont(hText14,&GUI_FontHZ_SimSun_1515);
		
		TEXT_SetText(hText1,"时钟设定");
		TEXT_SetText(hText2,"年");
		TEXT_SetText(hText3,"月");
		TEXT_SetText(hText4,"日");
		TEXT_SetText(hText5,"时");
		TEXT_SetText(hText6,"分");
		TEXT_SetText(hText7,"秒");
		TEXT_SetText(hText8,"确定");
		TEXT_SetText(hText9,timeData[0]);
		TEXT_SetText(hText10,timeData[1]);
		TEXT_SetText(hText11,timeData[2]);
		TEXT_SetText(hText12,timeData[3]);
		TEXT_SetText(hText13,timeData[4]);
		TEXT_SetText(hText14,timeData[5]);
}




/*********************************************************************
*
*       Dialog callback routine
*/

void TimeSetting(WM_HWIN hWin) {  //信息设定
	static int messageType =0,lastMessageType=0,isSelectType=0,maxCount = 0,count=0;
			//旋转编码器
		if((rotate_flag == 1)&&(isSelectType==0)) {
			if(KEY_A == 0) {
						delay_us(20);
            if(KEY_B == 1)
            {
							messageType++;
							if(messageType==7) {
								messageType = 0;
							}
							printf("messageSetting :right\r\n");
            }else {
								messageType--;
								if(messageType < 0) {
									messageType = 6;
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
			int data[6] = {2100,12,31,24,60,60};
					if(rotateEnter_flag==1) {
						if (lastMessageType == 6) {
							
								WM_SelectWindow(hWin);
								GUI_EndDialog(hWin, 0);
								WM_SelectWindow(mainForm_hWin);
								myMessageType = MY_MESSAGE_ID_LOGO;
								WM_Exec();
							isOrSetClock = 1;
							//清除状态
							messageType =0;
							lastMessageType=0;
							isSelectType=0;
							maxCount = 0;
							count=0;
								return;	
						}
						isSelectType = 1;
						rotateEnter_flag = 0;
						maxCount = data[lastMessageType];
						messageType = lastMessageType + 7;	
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0x000000);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0xffffff);
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0xffffff);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0x000000);
						lastMessageType = messageType;
					}
		}else if((rotateEnter_flag==0)&&(isSelectType == 1)) {
					if((KEY_A == 0)&&(rotate_flag == 1)) {
						delay_us(20);
            if(KEY_B == 1)
            {
							count = 1;
							printf("clock:right\r\n");
            }else {
							if(KEY_B == 0) {
								count = - 1;
							printf(" clock :left\r\n");
							}

						}
					 if (lastMessageType == 7) {
							static int base1 = 2017;
							static char str[20];
							base1 +=count;
						 if(base1>2100) {
							 base1 = 2100;
						 }else if(base1<2017) {
							base1 = 2017;
						 }
							sprintf(str,"%04d",base1);
							timeData[lastMessageType-7] = str;
							TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),timeData[0]);
						}else if (lastMessageType == 8) {
							static int base2 = 1;
							static char str[20];
							base2+=count;
							if(base2>12) {
								base2 = 12;
						 }else if (base2<1) {
								base2 = 1;
						 }
							sprintf(str,"%02d",base2);
							timeData[lastMessageType-7] = str;
							TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),timeData[1]);
						}else if (lastMessageType == 9) { 
							static int base3 = 1;
							static char str[20];
							base3+=count;
							if(base3>31) {
								base3=31;
						 }else if(base3<1) {
							base3 = 1;
						 }
							sprintf(str,"%02d",base3);
							timeData[lastMessageType-7] = str;
							TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),timeData[2]);
						}else if (lastMessageType == 10) { 
							static int base4 = 8;
							static char str[20];
							base4+=count;
							if(base4>23) {
								base4 = 23;
						 }else if(base4<0) { 
							base4 = 0;
						 }
							sprintf(str,"%02d",base4);
							timeData[lastMessageType-7] = str;
							TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),timeData[3]);
						}
						else if (lastMessageType == 11) { 
							static int base5 = 30;
							static char str[20];
							base5+=count;
							if(base5>59) {
								base5 = 59;
						 }else if(base5 <0){
							base5 = 0;
						 }
							sprintf(str,"%02d",base5);
							timeData[lastMessageType-7] = str;
							TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),timeData[4]);
						}else if (lastMessageType == 12) { 
							static int base6 = 0;
							static char str[20];
							base6+=count;
							if(base6>59) {
								base6 = 59;
						 }else if(base6 <0){
							base6 = 0;
						 }
							sprintf(str,"%02d",base6);
							timeData[lastMessageType-7] = str;
							TEXT_SetText(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),timeData[5]);
						}	
					}						
		}else if((rotateEnter_flag==1)&&(isSelectType == 1)) {
						isSelectType = 0;
						rotateEnter_flag = 0;
						messageType = lastMessageType -7;
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0x000000);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0xffffff);
						TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0xffffff);
						TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0x000000);
						lastMessageType = messageType;
		}
		WM_Exec();
		rotate_flag = 0;
		selectEnd = 1;
}

static void _cbClockDialogCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
					ClockPaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            ClockInitDialog(pMsg);
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
										TimeSetting(hWin);
								}
								    break;
								case MY_MESSAGE_ID_ENTER:
								{
										TimeSetting(hWin);
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

void time_dialogTask(void) {
		myMessageType = MY_MESSAGE_ID_SYSTEM_TIME;
	clock_hWin	= GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbClockDialogCallback, root_hWin, 0, 0);
	printf("\r\n创建句柄: %d\r\n",clock_hWin);
	GUI_ExecCreatedDialog(clock_hWin);
}

