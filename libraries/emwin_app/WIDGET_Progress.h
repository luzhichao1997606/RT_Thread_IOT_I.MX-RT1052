/*
----------------------------------------------------------------------
File        : WIDGET_Popwin.h
Purpose     : Content to be managed by customer
---------------------------END-OF-HEADER------------------------------
*/

#ifndef WIDGET_PROGRESS_H
#define WIDGET_PROGRESS_H

#include "WM.h"
extern float referenceValue;
WM_HWIN CreateWIDGET_Button(void) ; 
void freshProgress(float dbm);
void setRefValueZero();
void setRefValue(float dbm);
/*************************** End of file ****************************/

#endif  // RESOURCE_H
