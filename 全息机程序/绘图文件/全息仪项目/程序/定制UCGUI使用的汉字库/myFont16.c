/* myFont16.c - myFont16 font for UCGUI font driver */ 
/********************************************************************************************************
*                                            UCGUI
*                                       http://www.ucgui.com
*
*                             (c) Copyright 2005-2006, UCGUI专业论坛, 学习交流UCGUI
*
*                               	ucgui@163.com 2005.07.31
*                                           作者: ucgui
*********************************************************************************************************
*/

#include "..\core\GUI.H" 
#ifndef GUI_FLASH 
	#define GUI_FLASH 
#endif 
extern GUI_FLASH const GUI_FONT GUI_FontHZ_myFont16;

GUI_FLASH  const unsigned char acFontHZmyFont16_bac3[63] = {	/* 好 0xbac3*/
________,________,________,
________,_XXX____,________,
__XX____,_XXX____,________,
__XXX___,__XX____,________,
__XXXX__,__XX____,________,
__XXXXX_,__XX____,________,
__XX__XX,XXXXXXXX,XXXX____,
__XX__X_,__XX____,_XXXX___,
__XX____,__XX____,_XXX____,
__XX____,__XX____,_XX_____,
__XX____,__XX____,_XX_____,
________,__XX____,XX______,
_____XXX,X______X,XX______,
_____XXX,XXXXX_XX,X_______,
_XX__XX_,___XXXXX,________,
XXXXXXX_,_____XXX,X_______,
___XXXXX,XX___XX_,XX______,
_____XX_,XXXXXXX_,_XX_____,
_____XX_,____XXX_,__XX____,
_____XX_,________,__XX____,
________,________,________,
};

GUI_FLASH  const unsigned char acFontHZmyFont16_c4e3[63] = {	/* 你 0xc4e3*/
________,________,________,
______XX,_______X,XX______,
_____XXX,_____XXX,X_______,
______XX,X___XXX_,________,
______XX,XX_XXX__,________,
______XX,__XX____,________,
______XX,XX______,________,
______XX,XXXXXXXX,XXXXX___,
__XX__XX,________,__XXX___,
_XXXXXXX,________,__XXX___,
___XXXXX,__XXX___,__XX____,
______XX,X__XXXX_,________,
________,XXX___XX,X_______,
__XX____,_XX_____,XX______,
_XXXXX__,________,_XX_____,
___XXXXX,XXXXXXXX,XXXXX___,
______XX,X_______,_XXXX___,
________,XXX_____,________,
________,_XXX____,________,
________,___XX___,________,
________,________,________,
};

GUI_FLASH const GUI_CHARINFO GUI_FontHZmyFont16_CharInfo[] = {
{ 21, 21, 3, (void GUI_FLASH *)&acFontHZmyFont16_bac3},/* 好 96 */
{ 21, 21, 3, (void GUI_FLASH *)&acFontHZmyFont16_c4e3},/* 你 97 */
};

/*你--你*/

GUI_FLASH const GUI_FONT_PROP GUI_FontHZmyFont16_Propc4e3= {
      0xc4e3,
      0xc4e3,
      &GUI_FontHZmyFont16_CharInfo[1],
      (void *)0 
};
/*好--好*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZmyFont16_Propbac3= {
      0xbac3,
      0xbac3,
      &GUI_FontHZmyFont16_CharInfo[0],
      (void *)&GUI_FontHZmyFont16_Propc4e3 
};
GUI_FLASH const GUI_FONT GUI_FontHZ_myFont16 = {
      GUI_FONTTYPE_PROP_SJIS, 
      21, 
      21, 
      1,  
      1,  
      (void GUI_FLASH *)&GUI_FontHZmyFont16_Propbac3
};
