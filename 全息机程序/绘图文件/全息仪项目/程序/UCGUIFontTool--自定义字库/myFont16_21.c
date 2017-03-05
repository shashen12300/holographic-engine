/* myFont16_21.c - myFont16_21 font for UCGUI font driver */ 
/********************************************************************************************************
*                                            UCGUI
*                                       http://www.ucgui.com
*
*                             (c) Copyright 2005-2006, UCGUI专业论坛, 学习交流UCGUI
*
*                               	ucgui@16.com 2005.07.31
*                                           作者: ucgui
*********************************************************************************************************
*/

#include "..\core\GUI.H" 
#ifndef GUI_FLASH 
	#define GUI_FLASH 
#endif 
extern GUI_FLASH const GUI_FONT GUI_FontHZ_myFont16_21;

GUI_FLASH  const unsigned char acFontHZmyFont16_21_bac3[63] = {	/* 好 0xbac3*/
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
_______X,XXXXXXXX,XX______,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
______XX,________,X_______,
________,XXXX____,________,
________,_____XX_,________,
__XX____,_______X,________,
____XXXX,________,________,
________,__XX____,________,
________,________,________,
________,________,________,
________,________,________,
};

GUI_FLASH  const unsigned char acFontHZmyFont16_21_c4e3[63] = {	/* 你 0xc4e3*/
________,________,________,
________,________,X_______,
______X_,_______X,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,_XXXXXXX,XXXX____,
________,________,________,
___X____,________,________,
_____X__,___X____,________,
_______X,_____X__,________,
________,_______X,________,
________,________,________,
___X____,________,________,
_____X__,XXXXXXXX,XXXX____,
_______X,________,__XX____,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
};

GUI_FLASH const GUI_CHARINFO GUI_FontHZmyFont16_21_CharInfo[] = {
{ 21, 21, 3, (void GUI_FLASH *)&acFontHZmyFont16_21_bac3},/* 好 96 */
{ 21, 21, 3, (void GUI_FLASH *)&acFontHZmyFont16_21_c4e3},/* 你 97 */
};

/*你--你*/

GUI_FLASH const GUI_FONT_PROP GUI_FontHZmyFont16_21_Propc4e3= {
      0xc4e3,
      0xc4e3,
      &GUI_FontHZmyFont16_21_CharInfo[1],
      (void *)0 
};
/*好--好*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZmyFont16_21_Propbac3= {
      0xbac3,
      0xbac3,
      &GUI_FontHZmyFont16_21_CharInfo[0],
      (void *)&GUI_FontHZmyFont16_21_Propc4e3 
};
GUI_FLASH const GUI_FONT GUI_FontHZ_myFont16_21 = {
      GUI_FONTTYPE_PROP_SJIS, 
      21, 
      21, 
      1,  
      1,  
      (void GUI_FLASH *)&GUI_FontHZmyFont16_21_Propbac3
};
