#ifndef _APP_SYSTICK_H
#define _APP_SYSTICK_H

#include <stdio.h>
#include "BSP_Systick.h" 
#include "Common.h"

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int

void Robort_Delay_Init(void);

void SysDelay_us(uint32 nus);
void SysDelay_ms(uint32 nms);

#endif


