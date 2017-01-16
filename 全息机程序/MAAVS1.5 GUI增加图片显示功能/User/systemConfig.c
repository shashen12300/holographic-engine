#include "systemConfig.h"
#include "GUI.h"
//根窗口
WM_HWIN root_hWin;
//logo图标
WM_HWIN mainForm_hWin;
//信息设定
WM_HWIN dialog_hWin;
//时间
WM_HWIN time_hWin;
//检测曲线
WM_HWIN draw_hWin;
WM_HWIN drawLine_hWin;
//系统菜单
WM_HWIN menu_hWin;
//系统说明
WM_HWIN explain_hWin;
//时钟设定
WM_HWIN clock_hWin;
//警告弹窗
WM_HWIN warning_hWin;
//报告列表
WM_HWIN report_hWin;
//活动窗口类型
 int myMessageType = MY_MESSAGE_ID_LOGO;
//是否设置个人信息
int isOrSetMessage=0;
//是否刷新个人信息
int isOrRefreshMessage=0;
//旋转编码器标志位
int rotate_flag=0;
//旋转编码器是否按下标志位
int rotateEnter_flag=0;
//保存用户信息
 char *saveData[5] = {"男","35","未婚","正常","03"};
//是否展示系统说明
 int isOrShowExplain = 0;
 //是否展示时钟设定窗口
 int isOrShowSetTime = 0;
 //设置时钟
 char *timeData[6] = {"2017","01","01","08","30","00"};
 //是否设置时钟
 int isOrSetClock = 0;
 //是否单项检测
 int isOneCheck = 0;
 //是否重新检测
 int isRestartCheck = 1;
 //是否开始检测
 int isBeginCheck = 0;
 //是否画点
 int isOrSetPoint = 0;
 //是否展示报表
 int isOrShowReport = 0;

