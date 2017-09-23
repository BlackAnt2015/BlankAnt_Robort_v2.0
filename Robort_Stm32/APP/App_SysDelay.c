#include "App_SysDelay.h"

void Robort_Delay_Init()
{
	delay_init();
}

void SysDelay_us(uint32 nus)
{
	delay_us(nus);
}


void SysDelay_ms(uint32 nms)
{
	while (nms--)
		delay_ms(1);
}

/******************* (C) COPYRIGHT 2015 X-SPACE *****END OF FILE****/

