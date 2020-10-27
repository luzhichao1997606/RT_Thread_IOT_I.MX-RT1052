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
File        : ID_SCREEN_Test_Slots.c
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_Test.h"
#include "rtthread.h"
#include "WIDGET_Progress.h"
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_Test
*/
void cbID_SCREEN_Test(WM_MESSAGE * pMsg) {
  GUI_USE_PARA(pMsg);
	WM_HWIN hItem;
		 
	switch (pMsg->MsgId) 
	{
			case WM_DELETE:
				rt_kprintf("WM_Test_Delete\r\n");
				break;
			case WM_CREATE: 
				rt_kprintf("WM_Test_Create\r\n"); 
				break;
			
			case WM_INIT_DIALOG:
				CreateWIDGET_Button(); 
				rt_kprintf("WM_Test_InitDialog\r\n"); 
				break;
	}
}

/*************************** End of file ****************************/
