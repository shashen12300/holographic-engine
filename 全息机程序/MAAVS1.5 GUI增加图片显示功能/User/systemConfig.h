#ifndef __SYSTEMCONFIG_H__
#define __SYSTEMCONFIG_H__
#include "WM.h"

extern WM_HWIN root_hWin;
extern WM_HWIN mainForm_hWin;
extern WM_HWIN dialog_hWin;
extern WM_HWIN time_hWin;
extern WM_HWIN line_hWin;
extern WM_HWIN menu_hWin;
extern WM_HWIN explain_hWin;
extern WM_HWIN clock_hWin;

extern int isOrSetMessage;
extern int rotate_flag;
extern int rotateEnter_flag;
extern char *saveData[5];
extern int isOrRefreshMessage;
extern int isOrShowExplain;
extern int isOrShowSetTime;
extern char *timeData[6];
extern int isOrSetClock;

#endif