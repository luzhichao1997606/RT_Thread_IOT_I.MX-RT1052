/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2020  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : Resource.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include "AppWizard.h"

/*********************************************************************
*
*       Text
*/
#define Button_Key 0
#define Open_Text 1
#define Close_Text 2
#define One_Text 3
#define Two_Text 4

#define APPW_MANAGE_TEXT APPW_MANAGE_TEXT_EXT

extern const unsigned char acAPPW_Language_0[];
extern const unsigned char acAPPW_Language_1[];

/*********************************************************************
*
*       Fonts
*/
extern const unsigned char acNettoOT_32_Normal_EXT_AA4[];

/*********************************************************************
*
*       Images
*/

/*********************************************************************
*
*       Screens
*/
#define ID_SCREEN_Test (GUI_ID_USER + 4096)
#define ID_SCREEN_Next (GUI_ID_USER + 4097)

extern APPW_ROOT_INFO ID_SCREEN_Test_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_Next_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_Test_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "C:/Users/DELL/AppData/Local/AppWizard/Project/Test"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
