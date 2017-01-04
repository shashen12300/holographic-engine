/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
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

#define GUI_OS                    (0)  /* 0 ��֧�ֲ���ϵͳ 1 ֧��*/
#define GUI_SUPPORT_TOUCH         (0)  /* �Ƿ�֧�ִ��� */
#define GUI_SUPPORT_UNICODE       (1)  /* �Ƿ�֧�ֻ�ϵ�ASCII/UNICODE���� */

#define GUI_DEFAULT_FONT          &GUI_Font8x8  //���������С
#define GUI_ALLOC_SIZE         5000// 12500  /* ����Ķ�̬�ռ��С*/

/*********************************************************************
*
*         Configuration of available packages
*/

#define GUI_WINSUPPORT            1  /* �Ƿ�֧�ִ��ڹ��� */
#define GUI_SUPPORT_MEMDEV        0  /* �Ƿ�֧�ִִ����豸 */
#define GUI_SUPPORT_AA            0  /* �Ƿ�֧�ֿ���ݹ���*/

#endif  /* Avoid multiple inclusion */



