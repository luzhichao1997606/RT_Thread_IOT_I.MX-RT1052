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
File        : ID_SCREEN_Next.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_Next.h"

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
    ID_SCREEN_Next, 0,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
  },
  { WM_OBJECT_BOX_Create,
    ID_BOX_00, ID_SCREEN_Next,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
  },
  { WM_OBJECT_SLIDER_Create,
    ID_SLIDER_00, ID_SCREEN_Next,
    { { { DISPOSE_MODE_REL_PARENT, 300, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 392, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      200, 30, 0, 0, 0, 0
    },
  },
};

/*********************************************************************
*
*       _aSetup
*/
static const APPW_SETUP_ITEM _aSetup[] = {
  { ID_SCREEN_Next, APPW_SET_PROP_MOTIONH,      { ARG_VP(APPW_SWIPE_REPLACE, &ID_SCREEN_Test_RootInfo),
                                                  ARG_VP(0, NULL),
                                                  ARG_V(300) } },
  { ID_BOX_00,      APPW_SET_PROP_COLOR,        { ARG_V(0xffff115c) } },
  { ID_SLIDER_00,   APPW_SET_PROP_SBITMAPS,     { ARG_VP(0, acSliderLeftGreen_40x20),
                                                  ARG_VP(0, acSliderRightGray_40x20),
                                                  ARG_VP(0, acThumbDisabled_30x30),
                                                  ARG_VP(0, acThumbRight_30x30), } },
  { ID_SLIDER_00,   APPW_SET_PROP_COLORS,       { ARG_V(GUI_INVALID_COLOR),
                                                  ARG_V(GUI_INVALID_COLOR),
                                                  ARG_V(GUI_INVALID_COLOR) } },
  { ID_SLIDER_00,   APPW_SET_PROP_RANGE,        { ARG_V(0),
                                                  ARG_V(100) } },
};

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       ID_SCREEN_Next_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_Next_RootInfo = {
  ID_SCREEN_Next,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  NULL,  0,
  cbID_SCREEN_Next,
  0
};

/*************************** End of file ****************************/
