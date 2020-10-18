/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "delay.h"
#include "sys.h" 
#include "tftlcd.h" 
#include "string.h"
/* DS1,GPIO3_IO03,GPIO_SD_B1_03 */
#define LED0_PIN               GET_PIN(3,3)

int main(void)
{
	u8 x=0;
	u8 lcd_id[12]; 
    /* set LED0 pin mode to output */
	rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT); 
	LCD_Init();                 //初始化LCD
	POINT_COLOR=RED; 
	rt_kprintf("Clock freq is %d \r\n",GET_CPU_ClkFreq()); 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
	while(1) 
	{		 
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break; 
			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
		LCD_ShowString(10,40,240,32,32,"PIONEER RT1052"); 	
		LCD_ShowString(10,80,240,24,24,"TFTLCD TEST");
		LCD_ShowString(10,110,240,16,16,"ATOM@ALIENTEK");
 		LCD_ShowString(10,130,240,16,16,lcd_id);		//显示LCD ID	      					 
		LCD_ShowString(10,150,240,12,12,"2018/4/1");	      					 
		x++;
		if(x==12)x=0; 
		rt_pin_write(LED0_PIN, PIN_HIGH); 
		rt_thread_mdelay(500);
		rt_pin_write(LED0_PIN, PIN_LOW); 
		rt_thread_mdelay(500);
	}  
}

