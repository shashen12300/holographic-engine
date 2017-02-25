#include "systemConfig.h"
#include "GUI.h"
//¸ù´°¿Ú
WM_HWIN root_hWin;
//logoÍ¼±ê
WM_HWIN mainForm_hWin;
//ĞÅÏ¢Éè¶¨
WM_HWIN dialog_hWin;
//Ê±¼ä
WM_HWIN time_hWin;
//¼ì²âÇúÏß
WM_HWIN draw_hWin;
WM_HWIN drawLine_hWin;
//ÏµÍ³²Ëµ¥
WM_HWIN menu_hWin;
//ÏµÍ³ËµÃ÷
WM_HWIN explain_hWin;
//Ê±ÖÓÉè¶¨
WM_HWIN clock_hWin;
//¾¯¸æµ¯´°
WM_HWIN warning_hWin;
//±¨¸æÁĞ±í
WM_HWIN report_hWin;
//»î¶¯´°¿ÚÀàĞÍ
 int myMessageType = MY_MESSAGE_ID_LOGO;
//ÊÇ·ñÉèÖÃ¸öÈËĞÅÏ¢
int isOrSetMessage=0;
//ÊÇ·ñË¢ĞÂ¸öÈËĞÅÏ¢
int isOrRefreshMessage=0;
//Ğı×ª±àÂëÆ÷±êÖ¾Î»
int rotate_flag=0;
//Ğı×ª±àÂëÆ÷ÊÇ·ñ°´ÏÂ±êÖ¾Î»
int rotateEnter_flag=0;
//±£´æÓÃ»§ĞÅÏ¢
 char *saveData[5] = {"ÄĞ","35","Î´»é","Õı³£","03"};
//ÊÇ·ñÕ¹Ê¾ÏµÍ³ËµÃ÷
 int isOrShowExplain = 0;
 //ÊÇ·ñÕ¹Ê¾Ê±ÖÓÉè¶¨´°¿Ú
 int isOrShowSetTime = 0;
 //ÉèÖÃÊ±ÖÓ
 char *timeData[6] = {"2017","01","01","08","30","00"};
 //ÊÇ·ñÉèÖÃÊ±ÖÓ
 int isOrSetClock = 0;
 //ÊÇ·ñµ¥Ïî¼ì²â
 int isOneCheck = 0;
 //ÊÇ·ñÖØĞÂ¼ì²â
 int isRestartCheck = 1;
 //ÊÇ·ñ¿ªÊ¼¼ì²â
 int isBeginCheck = 0;
 //ÊÇ·ñ»­µã
 int isOrSetPoint = 0;
 //ÊÇ·ñÕ¹Ê¾±¨±í
 int isOrShowReport = 0;
 //Ñ¡ÔñµÄlogoÍ¼±êÎ»Ö
int logoCount =0;
 //ÉÏÒ»¸ö±»Ñ¡ÔñµÄlogoÍ¼±ê
int lastCount=0;
 //ÊÇ·ñ¿ÉÒÔ´òÓ¡±¨¸æ
 int isOrPrintReport=0;
 //ÊÇ·ñÔÊĞí¼ì²â
 int isOrAllowCheck=1;
 //ÊÇ·ñÍË³öÇúÏßÒ³Ãæ
 int isOrExitDrawLine=0;
 //ÅĞ¶ÏÃ¿Ò»ÏîÊÇ·ñÒÑ¾­¼ì²â
 char isOrCheckLogo[25]={0};
 //ÊÇ·ñÕıÔÚË¢ĞÂÊ±¼ä
 int isOrRefreshrTime=0;
 //ÊÇ·ñÆÁ±ÎÈ·ÈÏ¼ü
 int isOrCloseEnter=0;


