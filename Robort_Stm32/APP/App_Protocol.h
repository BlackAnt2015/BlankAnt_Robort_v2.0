#ifndef _APP_PROTOCOL_H
#define _APP_PROTOCOL_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "App_Motor.h"
#include "App_Steer.h"
#include "App_Light.h"
#include "App_Beep.h"
#include "App_Message.h"
#include "App_Sensor.h"
#include "App_GPS.h"
#include "App_SysDelay.h"

#include "stm32f10x.h"



#define ROBORT_LOCAL_ADDRESS 0X01
#define APP_TERMINAL_ADDRESS 0X02




typedef enum
{
	APP_ROBORT_CMD_STOP   		= 0x00, //direction
	APP_ROBORT_CMD_FORWARD		= 0x01,
	APP_ROBORT_CMD_BACK		= 0x02,
	APP_ROBORT_CMD_LEFT		= 0x03,
	APP_ROBORT_CMD_RIGHT		= 0x04,
	APP_ROBORT_CMD_STEER1		= 0x05, //steer engine
	APP_ROBORT_CMD_STEER2		= 0x06, //steer engine
	APP_ROBORT_CMD_STEER3		= 0x07, //steer engine
	APP_ROBORT_CMD_STEER4		= 0x08, //steer engine
	APP_ROBORT_CMD_STEER5		= 0x09, //steer engine
	APP_ROBORT_CMD_STEER6		= 0x0a, //steer engine
	APP_ROBORT_CMD_STEER7		= 0x0b, //steer engine
	APP_ROBORT_CMD_STEER8		= 0x0c, //steer engine
	APP_ROBORT_CMD_SPEED_L		= 0x0d, //speed
	APP_ROBORT_CMD_SPEED_R		= 0x0e, //speed
	APP_ROBORT_CMD_LIGHT_ON		= 0x0f, //light 
	APP_ROBORT_CMD_LIGHT_OFF	= 0x10,
    	APP_ROBORT_CMD_BEEP_ON		= 0x11, //beep
   	APP_ROBORT_CMD_BEEP_OFF		= 0x12,
	APP_ROBORT_CMD_GPS_ON		= 0x13,
	APP_ROBORT_CMD_GPS_OFF		= 0x14,
	APP_ROBORT_END
}APP_ROBORT_CMD_TYPE;




typedef enum
{
    ROBORT_APP_CMD_ENERGY = 0,
    ROBORT_APP_CMD_HUMIDITY,
    ROBORT_APP_CMD_TEMPERATURE,
    ROBORT_APP_CMD_POSITION,
    ROBORT_APP_CMD_DISTANCE,
    ROBORT_APP_CMD_GPS,
    ROBORT_APP_END
}ROBORT_APP_CMD_TYPE;


//报文的数据类型
typedef enum 
{
	MSG_DAT_SPEED = 0,	//速度
	MSG_DAT_ANGEL, 		//角度
	MSG_DAT_LIGHT_NO, 	//灯号
	MSG_DAT_BEEP_NO,	//喇叭号
}App_Robort_Msg_Tag;


typedef union 
{
	struct 
	{
		uint32 B_GPS	: 1;	
		uint32 B_HUM	: 1;	
		uint32 B_TEMP	: 1;	
		uint32 B_DIST	: 1;	
		uint32 RESERVED	: 28;	
	}Indicator;

	uint32 value;
}Robort_Sensor_Indicator_Tag;


extern Robort_Sensor_Indicator_Tag Indicator_Upload_Sensor;

uint8 Protocol_Parser(App_Robort_Dat_Tag *pdata);  //extern interface
int Protocol_Upload(void);


//static uint8 Process_Robort_Sensor_Cmd(App_Robort_Dat_Tag *pdata);
static uint8 Process_Robort_Light_Cmd(App_Robort_Dat_Tag *pdata);
static uint8 Process_Robort_Beep_Cmd(App_Robort_Dat_Tag *pdata);
static uint8 Process_Robort_Speed_Cmd(App_Robort_Dat_Tag *pdata);
static uint8 Process_Robort_Steer_Cmd(App_Robort_Dat_Tag *pdata);
static uint8 Process_Robort_Direction_Cmd(App_Robort_Dat_Tag *pdata);
static void Process_Robort_GPS_Cmd(App_Robort_Dat_Tag *pdata);

static uint8 Robort_Adress_Veritfy(App_Robort_Dat_Tag *pdata);
static unsigned short Assemble_Message_Length(App_Robort_Dat_Tag *pdata);
static unsigned short Resolve_Message_Data(App_Robort_Dat_Tag *pdata, uint8 *pDst);


	
#endif













