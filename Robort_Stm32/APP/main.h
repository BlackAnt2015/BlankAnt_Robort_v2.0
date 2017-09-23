#ifndef _APP_MAIN_H
#define _APP_MAIN_H

#include "Common.h" 
#include "stm32f10x.h"           
#include "misc.h"
#include "stm32f10x_exti.h" 
#include "stm32f10x_conf.h"
#include "App_Protocol.h"
#include "App_Message.h"
#include "APP_GPS.H"
#include "App_SysDelay.h"
/******************************/
#include "BSP_GPS.h"
#include <string.h>
#include <stdio.h>

//用户定义测试开关选项，如果去掉
//注释，则相应的测试开启

//#define _ENABLE_MODULE_1  1
//#define _ENABLE_MODULE_2  0
//#define _ENABLE_MODULE_3  0
//#define _ENABLE_MODULE_4  0
//#define _ENABLE_MODULE_5  0
//#define _ENABLE_MODULE_6  1
//#define _ENABLE_MODULE_7  1 

//Module序号
typedef enum Module_Tag
{
	MODULE_SYSTEM = 0,
	MODULE_LIGHT,
	MODULE_BEEP,
	MODULE_MOTOR,
	MODULE_STEER,
	MODULE_GPS,
	MODULE_UART,
	MODULE_END
}ROBORT_MODULE_TAG;

//硬件测试函数
static void Hardware_Test(void);

//系统资源释放
static void Resource_Release(void);

//Module测试函数
static void Robort_Light_Test(void);
static void Robort_Beep_Test(void);
static void Robort_Motor_Test(void);
static void Robort_Steer_Test(void);
static void Robort_System_Test(void);
static void Robort_GPS_Test(void);
static void Robort_UART_Test(void);

//Module测试函数地址列表
typedef void (* P_DEBUG_FUNC)(void);
static P_DEBUG_FUNC Robort_Debug_Func[MODULE_END] = 
{
	Robort_System_Test,
	Robort_Light_Test, 
	Robort_Beep_Test,
	Robort_Motor_Test,
	Robort_Steer_Test,
	Robort_GPS_Test,
	Robort_UART_Test,
};

//系统测试样例
#ifdef 	_ENABLE_MODULE_1
static uint8 Msg_Data[8] = {0};
static uint8 SPEED 		 = 40;
 uint8 ANGLE1		 	= 30;
 uint8 ANGLE2		 	= 90;
 uint8 ANGLE3		 	= 120;
 uint8 ANGLE4		 	= 150;
static App_Robort_Dat_Tag App_Robort_Test_Item_Table[] = 
{

/* head          addr           msg_l  msg_h          cmd                pMsg     crc_l  crc_h*/
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_BEEP_ON,   Msg_Data, 0X18,  0XB8}, //BEEP ON
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_BEEP_OFF,  Msg_Data, 0X4D,  0XED}, //BEEP OFF
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_FORWARD,   &SPEED,   0X6B,  0XBB}, //MOVE FOWARD
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_RIGHT,     &SPEED,   0X9E,  0X44}, //MOVE RIGHT
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_LEFT,      &SPEED,   0X09,  0XDD}, //MOVE LEFT
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_BACK,      &SPEED,   0X38,  0XEE}, //MOVE BACK
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_STOP,      &SPEED,   0X5A,  0X88}, //MOVE STOP
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_STEER1,    &ANGLE1,  0X00,  0X00}, //TURN ANGLE
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_STEER1,    &ANGLE2,  0X00,  0X00}, //TURN ANGLE
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_STEER1,    &ANGLE3,  0X00,  0X00}, //TURN ANGLE
	{0XFF, ROBORT_LOCAL_ADDRESS,  0x01,  0x00,  APP_ROBORT_CMD_STEER1,    &ANGLE4,  0X00,  0X00}, //TURN ANGLE

};
#endif

#endif






