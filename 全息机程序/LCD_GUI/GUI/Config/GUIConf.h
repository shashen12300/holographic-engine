/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIConf.h
Purpose     : Configures abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

#define GUI_OS                    (0)  /* 0 不支持操作系统 1 支持*/
#define GUI_SUPPORT_TOUCH         (0)  /* 是否支持触摸 */
#define GUI_SUPPORT_UNICODE       (1)  /* 是否支持混合的ASCII/UNICODE编码 */

#define GUI_DEFAULT_FONT          &GUI_Font8x8  //定义字体大小
#define GUI_ALLOC_SIZE         5000// 12500  /* 分配的动态空间大小*/

/*********************************************************************
*
*         Configuration of available packages
*/

#define GUI_WINSUPPORT            1  /* 是否支持窗口功能 */
#define GUI_SUPPORT_MEMDEV        0  /* 是否支持粗存器设备 */
#define GUI_SUPPORT_AA            0  /* 是否支持抗锯齿功能*/

#endif  /* Avoid multiple inclusion */



