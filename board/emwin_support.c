/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "GUI.h"
#include "WM.h"
#include "rtthread.h"
#include "emwin_support.h"
#include "GUIDRV_Lin.h"
#include "sdram_port.h"
#include "touch.h"

#include "tftlcd.h"
#include "fsl_elcdif.h"
#include "fsl_lpi2c.h"
#include "fsl_gpt.h"
/*
*********************************************************************************************************
*                                         GLOBAL VARIABLES
*********************************************************************************************************
*/


//static int        KeyPressed;
//static char       KeyIsInited;

static rt_sem_t DispSem;

static rt_sem_t EventSem;

static rt_sem_t KeySem;

static int      KeyPressed;
static char     KeyIsInited;


/* Memory address definitions */ 
//AT_NONCACHEABLE_SECTION_ALIGN(uint8_t s_gui_memory[GUI_NUMBYTES * LCD_BYTES_PER_PIXEL], FRAME_BUFFER_ALIGN);
//
//uint8_t s_gui_memory[GUI_NUMBYTES * LCD_BYTES_PER_PIXEL] __attribute__((at(0X80000000 + 0x200000))); 
uint8_t s_gui_memory[GUI_NUMBYTES * LCD_BYTES_PER_PIXEL] SECTION("NonCacheable");
#define GUI_MEMORY_ADDR ((void *)s_gui_memory) 

#define VRAM_ADDR       (SDK_SIZEALIGN(s_vram_buffer, FRAME_BUFFER_ALIGN))
static volatile int32_t s_LCDpendingBuffer = -1;
rt_uint32_t *my_sdram = (rt_uint32_t *)SDRAM_BANK_ADDR; /* SDRAM start address. */
/*******************************************************************************
 * Implementation of PortAPI for emWin LCD driver
 ******************************************************************************/

/* Enable interrupt. */
void BOARD_EnableLcdInterrupt(void)
{
    EnableIRQ(LCDIF_IRQn);
}

void APP_LCDIF_IRQHandler(void)
{
    //uint32_t intStatus;
    //
    //intStatus = ELCDIF_GetInterruptStatus(APP_ELCDIF);
    //
    //ELCDIF_ClearInterruptStatus(APP_ELCDIF, intStatus);
    //
    //if (intStatus & kELCDIF_CurFrameDone)
    //{
    //    if (s_LCDpendingBuffer >= 0)
    //    {
    //        /* Send a confirmation that the given buffer is visible */
    //        GUI_MULTIBUF_Confirm(s_LCDpendingBuffer);
    //        s_LCDpendingBuffer = -1;
    //    }
    //}
    //SDK_ISR_EXIT_BARRIER;
}

void LCDIF_IRQHandler(void)
{
    APP_LCDIF_IRQHandler();
}

void APP_ELCDIF_Init(void)
{

    My_LCD_Init();
    //const elcdif_rgb_mode_config_t config = {
    //    .panelWidth    = APP_IMG_WIDTH,
    //    .panelHeight   = APP_IMG_HEIGHT,
    //    .hsw           = APP_HSW,
    //    .hfp           = APP_HFP,
    //    .hbp           = APP_HBP,
    //    .vsw           = APP_VSW,
    //    .vfp           = APP_VFP,
    //    .vbp           = APP_VBP,
    //    .polarityFlags = APP_POL_FLAGS,
    //    .bufferAddr    = VRAM_ADDR,
    //    .pixelFormat   = ELCDIF_PIXEL_FORMAT,
    //    .dataBus       = APP_LCDIF_DATA_BUS,
    //};
    //ELCDIF_RgbModeInit(APP_ELCDIF, &config);
    //
    //BOARD_EnableLcdInterrupt();
    //ELCDIF_EnableInterrupts(APP_ELCDIF, kELCDIF_CurFrameDoneInterruptEnable);
    //NVIC_EnableIRQ(LCDIF_IRQn);
    //ELCDIF_RgbModeStart(APP_ELCDIF);
}

/*******************************************************************************
 * Implementation of communication with the touch controller
 ******************************************************************************/

/* Touch driver handle. */
//static ft5406_rt_handle_t touchHandle;

static void BOARD_Touch_Init(void)
{		
		tp_dev.init();                  //触摸屏初始化
    //lpi2c_master_config_t masterConfig = {0};
    ///*
    // * masterConfig.debugEnable = false;
    // * masterConfig.ignoreAck = false;
    // * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
    // * masterConfig.baudRate_Hz = 100000U;
    // * masterConfig.busIdleTimeout_ns = 0;
    // * masterConfig.pinLowTimeout_ns = 0;
    // * masterConfig.sdaGlitchFilterWidth_ns = 0;
    // * masterConfig.sclGlitchFilterWidth_ns = 0;
    // */
    //LPI2C_MasterGetDefaultConfig(&masterConfig);
    //
    ///* Change the default baudrate configuration */
    //masterConfig.baudRate_Hz = BOARD_TOUCH_I2C_BAUDRATE;
    //
    ///* Initialize the LPI2C master peripheral */
    //LPI2C_MasterInit(BOARD_TOUCH_I2C, &masterConfig, BOARD_TOUCH_I2C_CLOCK_FREQ);
    //
    ///* Initialize the touch handle. */
    //FT5406_RT_Init(&touchHandle, BOARD_TOUCH_I2C);
		
}

void BOARD_Touch_Deinit(void)
{
    //LPI2C_MasterDeinit(BOARD_TOUCH_I2C);
}

int BOARD_Touch_Poll(void)
{
		int touch_x;
    int touch_y;
    static GUI_PID_STATE pid_state;
    static int isTouched;
	
		tp_dev.scan(0);
		if ((tp_dev.sta) &  (1 << 0) )
		{
			pid_state.x       = tp_dev.x[0];
			pid_state.y       = tp_dev.y[0];
			pid_state.Pressed = 1;
			GUI_TOUCH_StoreStateEx(&pid_state);
			isTouched = 1;
			//rt_kprintf("Pressed!!!\r\n");
		}
		else if (isTouched && (!((tp_dev.sta) &  (1 << 0))))
		{
			isTouched         = 0;
			pid_state.Pressed = 0;
			GUI_TOUCH_StoreStateEx(&pid_state);
			//rt_kprintf("DisPressed\r\n");
			
		}
    //touch_event_t touch_event;
    //int touch_x;
    //int touch_y;
    //static GUI_PID_STATE pid_state;
    //static int isTouched;
    //
    //if (kStatus_Success != FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))
    //{
    //    return 0;
    //}
    //else
    //{
    //    if ((touch_event == kTouch_Contact))
    //    {
    //        pid_state.x       = touch_y;
    //        pid_state.y       = touch_x;
    //        pid_state.Pressed = 1;
    //        GUI_TOUCH_StoreStateEx(&pid_state);
    //        isTouched = 1;
    //    }
    //    else if (isTouched && (touch_event == kTouch_Up))
    //    {
    //        isTouched         = 0;
    //        pid_state.Pressed = 0;
    //        GUI_TOUCH_StoreStateEx(&pid_state);
    //    }
    //}
    return 1;
}

/*********************************************************************
 *
 *       _ClearCache
 */
static void _ClearCache(U32 v)
{
    GUI_USE_PARA(v);
    SCB_CleanInvalidateDCache();
}

/*******************************************************************************
 * Application implemented functions required by emWin library
 ******************************************************************************/
void LCD_X_Config(void)
{
    GUI_MULTIBUF_Config(GUI_BUFFERS);
    GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
    LCD_SetSizeEx(0, LCD_WIDTH, LCD_HEIGHT);
    LCD_SetVSizeEx(0, LCD_WIDTH, LCD_HEIGHT); 
    rt_kprintf("LCD_X_Config !\r\n");
    GUI_DCACHE_SetClearCacheHook(_ClearCache);
}

int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *p)
{
    GUI_USE_PARA(LayerIndex);

    uint32_t addr;
    int result = 0;
    LCD_X_SHOWBUFFER_INFO *pData;
    switch (Cmd) {
    case LCD_X_INITCONTROLLER: {
        APP_ELCDIF_Init();
				BOARD_Touch_Init();
        break;
    }
    case LCD_X_SHOWBUFFER: {
        pData = (LCD_X_SHOWBUFFER_INFO *)p;
        //
        // Remember buffer index to be used by ISR
        //
        s_LCDpendingBuffer = pData->Index;
        while (s_LCDpendingBuffer >= 0)
            ;
        return 0;
    }
    default:
        result = -1;
        break;
    }

    return result;
}

void GUI_X_Config(void)
{
    void *aMemory = RT_NULL; /* 内存块的指针 */ 
    aMemory = rt_malloc(GUI_NUMBYTES); 
    GUI_ALLOC_AssignMemory((void*)aMemory, GUI_NUMBYTES);
	
		/* Assign work memory area to emWin */
    //GUI_ALLOC_AssignMemory(GUI_MEMORY_ADDR, GUI_NUMBYTES);
	
    GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
    /* Assign work memory area to emWin */ 
    /* Select default font */
    GUI_SetDefaultFont(GUI_FONT_6X8);
}

void GUI_X_Init(void)
{
    KeySem = rt_sem_create("Key_SEM", 0, RT_IPC_FLAG_FIFO);
}

/* Dummy RTOS stub required by emWin */
void GUI_X_InitOS(void)
{

    DispSem = rt_sem_create("Disp_SEM", 1, RT_IPC_FLAG_FIFO);

    EventSem = rt_sem_create("Event_SEM", 0, RT_IPC_FLAG_FIFO);
}

/* Dummy RTOS stub required by emWin */
void GUI_X_Lock(void)
{
    rt_sem_take(DispSem, 0);
}

/* Dummy RTOS stub required by emWin */
void GUI_X_Unlock(void)
{
    rt_sem_release(DispSem);
}

/* Dummy RTOS stub required by emWin */
U32 GUI_X_GetTaskId(void)
{

    return (U32)rt_thread_self();
}

void GUI_X_ExecIdle(void)
{
    GUI_X_Delay(1);
}

GUI_TIMER_TIME GUI_X_GetTime(void)
{

    return rt_tick_get();
}

void GUI_X_Delay(int Period)
{
    rt_thread_delay(Period);
    BOARD_Touch_Poll();
}

void *emWin_memcpy(void *pDst, const void *pSrc, long size)
{
    return memcpy(pDst, pSrc, size);
}
/*
*********************************************************************************************************
*                                        GUI_X_WaitEvent()
*                                        GUI_X_SignalEvent()
*********************************************************************************************************
*/

void GUI_X_WaitEvent(void)
{
    rt_sem_take(EventSem, 0);
}

void GUI_X_SignalEvent(void)
{
    rt_sem_release(EventSem);
}
