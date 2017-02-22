#include "report_dialog.h"
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
#include "reportFont.h"
#include "healthDataReport.h"
#include <string.h>
#include "WM.h"
#include "rtc.h"

int reportCount = 0;
int reportType = 0;
int currentPage=0;
char *healthData[25]={0};
double healthValue[25],d1,d2;

extern void printReport(void);
/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                        0,  39,  320,201,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "",             GUI_ID_TEXT10,            5, 5, 310, 16, 0,0},	
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT11,            5, 21, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT12,            5, 37, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT13,            5, 53, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT14,            5, 69, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT15,            5, 85, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT16,            5, 101, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT17,            5, 117, 310, 16, 0,0},	
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT18,            5, 133, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT19,            5,149, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT20,            5, 165, 310, 16, 0,0},
		{ TEXT_CreateIndirect,      "",             GUI_ID_TEXT21,            5, 181, 310, 16, 0,0},

};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void ReportPaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void ReportInitDialog(WM_MESSAGE * pMsg)
{
		WM_HWIN hText1,hText2,hText3,hText4,hText5,hText6,hText7,hText8,hText9,hText10,hText11,hText12;
	static char valueData1[7]={0},valueData2[7]={0};
	char *p;	
	Stru_Time getTime;
  static double distance,minValue,maxValue,resultValue;
		int i,sstrlen,j;
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
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10),0xffffff);
	  TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10),0x000000);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT10),GUI_TA_VCENTER|GUI_TA_LEFT);
	
		for(i=1;i<12;i++) {
			TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+i),0x000000);
			TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+i),0xffffff);
			TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT10+i),GUI_TA_VCENTER|GUI_TA_LEFT);  
		}
		//赋值
		switch(reportType){
			case 0:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData1[i]; 
				}break;
			case 1:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData2[i]; 
				}break;
			case 2:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData3[i]; 
				}break;	
			case 3:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData4[i]; 
				}break;
			case 4:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData5[i]; 
				}break;
			case 5:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData6[i]; 
				}break;
			case 6:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData7[i]; 
				}break;
			case 7:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData8[i]; 
				}break;	
			case 8:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData9[i]; 
				}break;
			case 9:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData10[i]; 
				}break;
			case 10:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData11[i]; 
				}break;
			case 11:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData12[i]; 
				}break;
			case 12:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData13[i]; 
				}break;	
			case 13:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData14[i]; 
				}break;
			case 14:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData15[i]; 
				}break;
			case 15:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData16[i]; 
				}break;
			case 16:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData17[i]; 
				}break;
			case 17:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData18[i]; 
				}break;	
			case 18:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData19[i]; 
				}break;
			case 19:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData20[i]; 
				}break;
			case 20:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData21[i]; 
				}break;
			case 21:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData22[i]; 
				}break;
			case 22:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData23[i]; 
				}break;	
			case 23:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData24[i]; 
				}break;
			case 24:
				for(i=0;i<reportLength[reportType];i++){
						healthData[i] = healthData25[i]; 
				}break;
		} 
			reportCount = reportLength[reportType];
			for(i=0;i<reportLength[reportType];i++){
					sstrlen = strlen(healthData[i]);
					for(j=0;j<5;j++){
						valueData1[j]=healthData[i][sstrlen-12+j];
						valueData2[j]=healthData[i][sstrlen-6+j];

					}
					d1=atof(valueData1);
					d2=atof(valueData2);
					if(d1==0||d2==0){
						printf("数据异常");
					}
					minValue=d1-(d2-d1)*0.1;
					maxValue=d2+(d2-d1)*0.1;
					distance= maxValue-minValue;
					printf("valueData1=%s valueData2=%s d1=%f d2=%f\r\n",valueData1,valueData2,d1,d2);
					fnRTC_GetTime(&getTime); 
					srand(getTime.Second);
					resultValue = d1+rand()%((int)(distance*1000))/1000.0;
					if (resultValue>1000) {
						resultValue=1000;
					}
					if(resultValue>d2||resultValue<d1){
					healthData[i][25] = '*';
					}
					healthValue[i]=resultValue;
				}

		if(isOrCheckLogo[logoCount]==0) {
			for(i=0;i<reportCount;i++) {
				char data[10];
				sprintf(data,"%.2f",healthValue[i]);
				sstrlen = strlen(data);
					for(j=0;j<sstrlen;j++) {
						healthData[i][25-sstrlen+j] = data[j];
					}
				}
				isOrCheckLogo[logoCount]=1;
		}
//		if(isOneCheck==1) {
//			isOrCheckLogo[logoCount]=1;
//		}else {
//			for(i=0;i<25;i++) {
//				isOrCheckLogo[i]=1;
//			}
//		}
		for(i=0;i<reportCount;i++){
			WM_HWIN	 hText;
			if(i>=12)break;
			hText = WM_GetDialogItem(hWin,GUI_ID_TEXT10+i);
			TEXT_SetFont(hText,&GUI_FontHZ_reportFont);
			TEXT_SetText(hText ,healthData[i]);
		}
		
		isOrPrintReport =1;
				if(isOneCheck==1){
				isOrAllowCheck =1;
			}else {
				isOrAllowCheck = 0;
			}
				rotateEnter_flag = 0;

		
}




/*********************************************************************
*
*       Dialog callback routine
*/

void SystemReport(WM_HWIN hWin) {  //信息设定
	static int messageType =0,lastMessageType=0,currentPageLength=0;
	int i;
			//旋转编码器
		if(rotateEnter_flag==1) {
				rotateEnter_flag = 0;
				WM_SelectWindow(hWin);
				GUI_EndDialog(hWin, 0);
				WM_SelectWindow(mainForm_hWin);
				myMessageType = MY_MESSAGE_ID_LOGO;
				messageType =0;
				lastMessageType=0;
				currentPageLength=0;
				currentPage=0;
				isOrPrintReport=0;
				selectEnd = 1;
				WM_Exec();
		}else	if((rotate_flag == 1)&&(selectEnd==0)) {
			if(KEY_A == 0) {
						delay_us(20);
            if(KEY_B == 1)
            {
							messageType++;
							if(messageType+currentPage*12<reportCount) {
								if(messageType==12){
									currentPage++;
									messageType = 0;
									
									for(i=0;i<12;i++){
										WM_HWIN	hText = WM_GetDialogItem(hWin,GUI_ID_TEXT10+i);
										if(i+currentPage*12<reportCount) {
											TEXT_SetText(hText ,healthData[i+currentPage*12]);
										}else {
											TEXT_SetText(hText ,"");
										}
									}
									
								}
							}else {
									messageType = reportCount-1-currentPage*12;
							}
							printf("report :right\r\n");
            }else {
								messageType--;
								if(messageType < 0) {
									if(currentPage>0) {
										currentPage--;
										messageType = 11;
										for(i=0;i<12;i++){
										WM_HWIN	hText = WM_GetDialogItem(hWin,GUI_ID_TEXT10+i);
											TEXT_SetText(hText ,healthData[i+currentPage*12]);
										}
									}else{
										messageType =0;
									}
								printf(" report :left\r\n");
							}
						
						}
					TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0x000000);
					TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+lastMessageType),0xffffff);
					TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0xffffff);
					TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT10+messageType),0x000000);
					lastMessageType = messageType;
					WM_Exec();
					}
		rotateEnter_flag=0;
		rotate_flag = 0;
		selectEnd = 1;
		}

}

static void _cbReportDialogCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
				case WM_CREATE:
						WM_Exec();
            break;
        case WM_PAINT:
					ReportPaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            ReportInitDialog(pMsg);
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
									SystemReport(hWin);
								}
								    break;
								case MY_MESSAGE_ID_ENTER:
								{
										SystemReport(hWin);
								}
								    break;
//								case MY_MESSAGE_ID_KEY3:
//								{
//										printReport();
//								}
//										break;
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
void report_dialogTask(void) {
	
		 if (strcmp(saveData[0],"男") == 0&&logoCount==5){
			return;
	 }
		myMessageType = MY_MESSAGE_ID_CHECK_REPORT;
		//	关闭定时器
		report_hWin	= GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbReportDialogCallback, root_hWin, 0, 0);
		printf("\r\nhandle: %d\r\n",report_hWin);
		GUI_ExecCreatedDialog(report_hWin);
	 	printf("\r\nhandle: %d  end\r\n",report_hWin);

}

