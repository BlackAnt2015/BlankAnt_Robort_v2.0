#ifndef _COMMON_H_
#define _COMMON_H_

//***************************************头文件包含区***********************************************

#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BSP_Led.h"
#include "BSP_Timer.h"
#include "BSP_Systick.h"
#include "BSP_Uart.h"
#include "BSP_Pwm.h"
#include "BSP_Pantilt.h"
#include "BSP_ADC.h"


//***************************************变量类型定义 ***********************************************
#define uchar 	unsigned char
#define uint8 	unsigned char
#define uint16 	unsigned short
#define uint32 	unsigned int
#define uint  	unsigned int
#define ulong 	unsigned long


#define Set_Bit(val, off) ((val) |= (1<<(off)))
#define Reset_Bit(val, off) ((val) &= ~(1<<(off)))


#define FRAME_HEAD_SIZE		1 //1字节
#define LOCAL_ADDR_SIZE     1
#define MASSAGE_H_SIZE      1
#define MASSAGE_L_SIZE      1
#define CMD_TYPE_SIZE       1
#define CRC_H_SIZE			1
#define CRC_L_SIZE			1

#define FRAME_INFO_SIZE     (FRAME_HEAD_SIZE+LOCAL_ADDR_SIZE+MASSAGE_H_SIZE+MASSAGE_L_SIZE+\
							 CMD_TYPE_SIZE+CRC_H_SIZE+CRC_L_SIZE)\

/* The definition of protocol */
struct protocol
{
	uint8 Frame_Head;       //0xff
	uint8 Addr;             //robort local address
	uint8 Msg_L;            //Data[] length LSB
	uint8 Msg_H;            //Data[] length MSB
	uint8 Cmd;              //Command type
	uint8 *pMsg;    		//msg buffer size
	uint8 Crc_L;            //crc check LSB
	uint8 Crc_H;            //crc check MSB
};


typedef struct protocol App_Robort_Dat_Tag;
typedef struct protocol Robort_App_Dat_Tag;

int Crc16(uchar *ptr, int count);
void _NOP(void);
#endif

