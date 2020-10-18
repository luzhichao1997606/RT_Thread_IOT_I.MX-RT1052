/*
 * @fileName: 
 * @description: 
 * @version: 
 * @author: lzc
 * @date: Do not edit
 * @lastEditors: lzc
 * @lastEditTime: Do not Edit
 */
#ifndef _DELAY_H
#define _DELAY_H
#include <sys.h>	 
/* ��ȡ�ں�ʱ��Ƶ�� */
#define GET_CPU_ClkFreq()       CLOCK_GetFreq(kCLOCK_CpuClk) 
#define SysClockFreq            (600000000)
/* Ϊ����ʹ�ã�����ʱ�����ڲ�����CPU_TS_TmrInit������ʼ��ʱ����Ĵ�����
   ����ÿ�ε��ú��������ʼ��һ�顣
   �ѱ���ֵ����Ϊ0��Ȼ����main����������ʱ����CPU_TS_TmrInit�ɱ���ÿ�ζ���ʼ�� */  

#define CPU_TS_INIT_IN_DELAY_FUNCTION   1  


/*******************************************************************************
 * ��������
 ******************************************************************************/
uint32_t CPU_TS_TmrRd(void);
bool HAL_InitTick(uint32_t TickPriority);

//ʹ�����º���ǰ�����ȵ���CPU_TS_TmrInit����ʹ�ܼ���������ʹ�ܺ�CPU_TS_INIT_IN_DELAY_FUNCTION
//�����ʱֵΪ8��
void CPU_TS_Tmr_Delay_US(uint32_t us);

#define FSL_Delay_us(us)        CPU_TS_Tmr_Delay_US(us) 
#define FSL_Delay_ms(ms)        CPU_TS_Tmr_Delay_US(ms*1000) 

#endif

