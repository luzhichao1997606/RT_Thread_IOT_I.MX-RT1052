/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : WIDGET_Graph.c
Purpose     : Demonstrates the use of the GRAPH widget
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "LISTVIEW.h"
#include <stdlib.h>
#include <string.h>
#include <rtthread.h>
#include "Application.h"
#include "DIALOG.h" 
#include "BUTTON.h"
#include "WIDGET_Progress.h"
#include "drv_gpio.h"
//extern SYS_HAL_DAT_t * sys_data; //whl

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
 
const static int Height = 50;
const static int Width = 405;
 

float progressValue = -70;
float referenceValue =0.00;

static WM_HWIN hDlgPopwin = 0;
static BUTTON_Handle hButton;
static GRAPH_DATA_Handle ahData;
static GRAPH_SCALE_Handle hScaleV;
//
// Dialog ressource
// 
#define ID_FRAMEWIN_0			(GUI_ID_USER + 0x06)
#define ID_BUTTON_0      	(GUI_ID_USER + 0x07)
#define ID_BUTTON_1      	(GUI_ID_USER + 0x08)
#define ID_BUTTON_2      	(GUI_ID_USER + 0x09)
#define ID_GRAPH_0      	(GUI_ID_USER + 0x0A)
#define ID_HEADER_0      	(GUI_ID_USER + 0x0B)
#define ID_MULTIPAGE_0		(GUI_ID_USER + 0x0C)
#define ID_PROGBAR_0      (GUI_ID_USER + 0x0F)
#define ID_DROPDOWN_0			(GUI_ID_USER + 0x10)
#define ID_SCROLLBAR_0		(GUI_ID_USER + 0x11)
#define ID_SLIDER_0      	(GUI_ID_USER + 0x12)
#define ID_TREEVIEW_0			(GUI_ID_USER + 0x13)
#define LED0_PIN					 GET_PIN(3,3)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "WIDGET_Main", ID_FRAMEWIN_0, 2, -1, 800, 480, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Forward", ID_BUTTON_0, 40, 400, 140, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Confirm", ID_BUTTON_1, 292, 400, 140, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "next", ID_BUTTON_2, 565, 400, 140, 40, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 206, 76, 357, 203, 0, 0x0, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_0, 0, 4, 800, 30, 0, 0x0, 0 },
  { MULTIPAGE_CreateIndirect, "Multipage", ID_MULTIPAGE_0, 624, 81, 124, 145, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 185, 349, 400, 10, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 37, 81, 106, 18, 0, 0x0, 0 },
  { SCROLLBAR_CreateIndirect, "Scrollbar", ID_SCROLLBAR_0, 46, 307, 657, 15, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 17, 129, 153, 31, 0, 0x0, 0 },
  { TREEVIEW_CreateIndirect, "Treeview", ID_TREEVIEW_0, 31, 180, 120, 96, 0, 0x0, 123 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       _cbCallback
*
* Function description
*   Callback function of the dialog
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
TREEVIEW_ITEM_Handle   hTreeItemCur;
  TREEVIEW_ITEM_Handle   hTreeItemNew;
  WM_HWIN                hItem;
  int                    NCode;
  int                    Id;
	int										 Value = 10; 
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Graph'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		/* 创建数据对象 *******************************************************/
		ahData = GRAPH_DATA_YT_Create(GUI_GREEN, 400, 0, 0);
		/* 数据对象添加到图形控件 */
		GRAPH_AttachData(hItem, ahData);
		/* 设置 Y 轴方向的栅格间距 */
		GRAPH_SetGridDistY(hItem, 20);
		/* 固定 X 轴方向的栅格 */
		GRAPH_SetGridFixedX(hItem, 1);
		/* 设置栅格可见 */
		GRAPH_SetGridVis(hItem, 1);
		/* 创建刻度对象 ***************************************************/
		hScaleV = GRAPH_SCALE_Create(20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20);
		/* 将垂直刻度对象添加到图形控件 */
		GRAPH_AttachScale(hItem, hScaleV);
		/* 用于设置比例刻度的因子 */
		GRAPH_SCALE_SetFactor(hScaleV, 0.5);
		/* 设置标签字体颜色 */
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED);
		
    GRAPH_SetBorder(hItem, 0, 0, 0, 0);
    //
    // Initialization of 'Header'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_0);
    HEADER_AddItem(hItem, 30, "hello", 14);
    //
    // Initialization of 'Multipage'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE_0);
    MULTIPAGE_AddEmptyPage(hItem, 0, "Page1");
    MULTIPAGE_AddEmptyPage(hItem, 0, "Page2");
    MULTIPAGE_AddEmptyPage(hItem, 0, "Page3");
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    DROPDOWN_AddString(hItem, "1");
    DROPDOWN_AddString(hItem, "2");
    DROPDOWN_SetListHeight(hItem, 50);
    //
    // Initialization of 'Treeview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TREEVIEW_0);
    hTreeItemCur = TREEVIEW_GetItem(hItem, 0, TREEVIEW_GET_LAST);
    hTreeItemNew = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE, "root", 0);
    TREEVIEW_AttachItem(hItem, hTreeItemNew, hTreeItemCur, TREEVIEW_INSERT_BELOW);
    hTreeItemCur = TREEVIEW_GetItem(hItem, 0, TREEVIEW_GET_LAST);
    hTreeItemNew = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE, "dev", 0);
    TREEVIEW_AttachItem(hItem, hTreeItemNew, hTreeItemCur, TREEVIEW_INSERT_BELOW);
    hTreeItemCur = TREEVIEW_GetItem(hItem, 0, TREEVIEW_GET_LAST);
    hTreeItemNew = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE, "main", 0);
    TREEVIEW_AttachItem(hItem, hTreeItemNew, hTreeItemCur, TREEVIEW_INSERT_BELOW);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Forward'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Confirm'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'next'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_HEADER_0: // Notifications sent by 'Header'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_MULTIPAGE_0: // Notifications sent by 'Multipage'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_DROPDOWN_0: // Notifications sent by 'Dropdown'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SCROLLBAR_0: // Notifications sent by 'Scrollbar'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_0: // Notifications sent by 'Slider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_TREEVIEW_0: // Notifications sent by 'Treeview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
	case WM_TIMER: //--------------（5） 
			hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0); 
			Value = PROGBAR_GetValue(hItem); //--------------（6）
			if (Value == 100)
			{
				PROGBAR_SetValue(hItem, 0); //--------------（7）
			}
			else
			{
				/* 每 1s 给绘图控件添加一次新的数据 */
				GRAPH_DATA_YT_AddValue(ahData, rand()%100);
				PROGBAR_SetValue(hItem, Value + 1); //--------------（8） 
			}
			WM_RestartTimer(pMsg->Data.v, 100); //--------------（9）
			break;
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
} 
/*********************************************************************
*
*       MainTask
*/
WM_HWIN CreateWIDGET_Button(void) 
{
  WM_HWIN hWin; 
	WM_HWIN	hItem;
	WM_HTIMER hTimer; 
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbCallback, WM_HBKWIN, 0, 0); 
	hTimer = WM_CreateTimer(WM_GetClientWindow(hWin),0,1000,0); 
	hItem = WM_GetDialogItem(hWin, ID_PROGBAR_0);  
	return hWin;
}

void freshProgress(float dbm)
{
	progressValue=dbm;
	WM_InvalidateWindow(hDlgPopwin);
}

void setRefValueZero() 
{
	referenceValue = 0.00;
	WM_InvalidateWindow(hDlgPopwin);
}

void setRefValue(float dbm)
{
	referenceValue = dbm;
	WM_InvalidateWindow(hDlgPopwin);
}
/*************************** End of file ****************************/