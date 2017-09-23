#ifndef _APP_MESSAGE_H
#define _APP_MESSAGE_H

#include "stm32f10x.h"
#include "BSP_Uart.h"
#include "Common.h"

#define uint8 unsigned char
#define MB_SIZE 20


typedef enum
{
    RET_OK=0,
    RET_ERROR,
}RET_TAG;


int Robort_Receive_Frame(App_Robort_Dat_Tag *pdata);
void Robort_Send_Frame(void *pdata, uint16 len);
void Robort_Uart_Init(void);

#endif
