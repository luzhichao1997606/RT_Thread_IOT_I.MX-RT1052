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
File        : ID_SCREEN_Test.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_Test.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aCreate
*/
static APPW_CREATE_ITEM _aCreate[] = {
  { WM_OBJECT_WINDOW_Create,
    ID_SCREEN_Test, 0,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
  },
  { WM_OBJECT_BOX_Create,
    ID_BOX_00, ID_SCREEN_Test,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
  },
  { WM_OBJECT_BUTTON_Create,
    ID_BUTTON_00, ID_SCREEN_Test,
    { { { DISPOSE_MODE_REL_PARENT, 300, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 372, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      200, 80, 0, 0, 0, 0
    },
  },
  { WM_OBJECT_TEXT_Create,
    ID_TEXT_00, ID_SCREEN_Test,
    { { { DISPOSE_MODE_REL_PARENT, 350, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 313, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      100, 32, 0, 0, 0, 0
    },
  },
};

/*********************************************************************
*
*       _aSetup
*/
static const APPW_SETUP_ITEM _aSetup[] = {
  { ID_SCREEN_Test, APPW_SET_PROP_MOTIONH,      { ARG_VP(APPW_SWIPE_REPLACE, &ID_SCREEN_Next_RootInfo),
                                                  ARG_VP(APPW_SWIPE_REPLACE, &ID_SCREEN_Next_RootInfo),
                                                  ARG_V(300) } },
  { ID_SCREEN_Test, APPW_SET_PROP_MOTIONV,      { ARG_VP(0, NULL),
                                                  ARG_VP(0, NULL),
                                                  ARG_V(300) } },
  { ID_SCREEN_Test, APPW_SET_PROP_PERSISTENT,   { ARG_V(0) } },
  { ID_BOX_00,      APPW_SET_PROP_COLOR,        { ARG_V(0xff2415ff) } },
  { ID_BUTTON_00,   APPW_SET_PROP_COLORS,       { ARG_V(GUI_INVALID_COLOR),
                                                  ARG_V(GUI_INVALID_COLOR),
                                                  ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_00,   APPW_SET_PROP_BKCOLORS,     { ARG_V(GUI_INVALID_COLOR),
                                                  ARG_V(GUI_INVALID_COLOR),
                                                  ARG_V(GUI_INVALID_COLOR) } },
  { ID_BUTTON_00,   APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acButton_round_basic_color_green_1_60),
                                                  ARG_VP(0, acButton_round_basic_color_red_1_60),
                                                  ARG_VP(0, acButton_round_basic_color_blue_1_60), } },
  { ID_BUTTON_00,   APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                  ARG_V(0),
                                                  ARG_V(0) } },
  { ID_BUTTON_00,   APPW_SET_PROP_TOGGLE,       { ARG_V(0) } },
  { ID_TEXT_00,     APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_00,     APPW_SET_PROP_TEXTID,       { ARG_V(Button_Key) } },
  { ID_TEXT_00,     APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                  ARG_V(0),
                                                  ARG_V(0) } },
  { ID_TEXT_00,     APPW_SET_PROP_FONT,         { ARG_VP(0, acNettoOT_32_Normal_EXT_AA4) } },
  { ID_TEXT_00,     APPW_SET_PROP_WRAP,         { ARG_V(0) } },
  { ID_TEXT_00,     APPW_SET_PROP_BKCOLOR,      { ARG_V(0xffff9114) } },
};

/*********************************************************************
*
*       _aAction
*/
static const APPW_ACTION_ITEM _aAction[] = {
  { ID_BUTTON_00,   WM_NOTIFICATION_CLICKED,          0,              APPW_JOB_NULL,           ID_SCREEN_Test__ID_BUTTON_00__WM_NOTIFICATION_CLICKED,
  },
};

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       ID_SCREEN_Test_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_Test_RootInfo = {
  ID_SCREEN_Test,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_Test,
  0
};

/*************************** End of file ****************************/
