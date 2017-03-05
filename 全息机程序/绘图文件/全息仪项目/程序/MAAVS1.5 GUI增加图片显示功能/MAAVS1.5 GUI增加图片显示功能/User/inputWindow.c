#include "GUI.h"
#include "inputWindow.h"
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
#include "feegnshi1.h"
#include "myFont16_21.h"

extern WM_HWIN WM__ahDesktopWin[10];
static void windowCallback(WM_MESSAGE * pMsg) {
	    //
 const WM_KEY_INFO* pKeyInfo;
  switch (pMsg->MsgId) {
  case WM_KEY:
    pKeyInfo = (const WM_KEY_INFO*)pMsg->Data.p;
    if (pKeyInfo->PressedCnt == 1) {
      GUI_StoreKey(pKeyInfo->Key);
    }
    break;
  case WM_PAINT:
    {
      int LayerIndex;
      #if GUI_NUM_LAYERS > 1
        LayerIndex = _DesktopHandle2Index(pMsg->hWin);
      #else
        LayerIndex = 0;
      #endif
        GUI_Clear();
    }
  default:
    WM_DefaultProc(pMsg);
  }

}


void windowTask(void) {
		WM_CreateWindow(100,10,180,100,WM_CF_SHOW,&windowCallback,0);
	
	   WM__ahDesktopWin[0] = WM_CreateWindow(0, 0, GUI_XMAX, GUI_YMAX, WM_CF_SHOW, windowCallback, 0);
	   WM__ahDesktopWin[1] = WM_CreateWindow(0, 0, GUI_XMAX, GUI_YMAX, WM_CF_SHOW, windowCallback, 1);
	   WM__ahDesktopWin[2] = WM_CreateWindow(0, 0, GUI_XMAX, GUI_YMAX, WM_CF_SHOW, windowCallback, 2);

    WM_InvalidateWindow(WM__ahDesktopWin[2]); 
    WM_SelectWindow(WM__ahDesktopWin[0]); 
}