/**********************************************************************************************************
**** FileName：App_Protocol.c
**** 
**** FileDescription：Terminal & robort protocol parse
****		
**** ProtocolDescription:
****
****  ------------------------------------------------------------------------------------------------------------------     
****  |    Name            Header      SlaveAddr    MsgLSB(1B)    MsgMSB(1B)      Cmd      Data     CrcLSB     CrcMSB  |
****  |    STOP            0xff        0x01                                       0x00                                 |
****  |    FORWARD         0xff        0x01                                       0x01                                 |
****  |    BACK            0xff        0x01                                       0x02                                 |
****  |    LEFT            0xff        0x01                                       0x03                                 |
****  |    RIGHT           0xff        0x01                                       0x04                                 |
****  |    STEER1~STEER8   0xff        0x01                                       0x05                                 |
****  |    SPEED_L         0xff        0x01                                       0x06                                 |
****  |    SPEED_R         0xff        0x01                                       0x07                                 |
****  |    LIGHT_ON        0xff        0x01                                       0x08                                 |
****  |    LIGHT_OFF       0xff        0x01                                       0x09                                 |
****  |    ENERGY          0xff        0x02                                       0x0a                                 |
****  |    HUMIDITY        0xff        0x02                                       0x0b                                 |
****  |    TEMPERATURE     0xff        0x02                                       0x0c                                 |
****  |    POSITION        0xff        0x02                                       0x0d                                 |
****  |                                                                                                                |
****  ------------------------------------------------------------------------------------------------------------------
****
**** Author：Sandy
**** 
**** Version：2.0
**** 
**** Revision：
**** 
**** 
***********************************************************************************************************/

#include "App_Protocol.h"



Robort_Sensor_Indicator_Tag Indicator_Upload_Sensor = {0};

static unsigned short Resolve_Message_Data(App_Robort_Dat_Tag *pdata, uint8 *pDst)
{
	uint16 msg_len = 0;
	msg_len = Assemble_Message_Length(pdata);
	
	if (msg_len == 0)
		return 0;
	
	memcpy(pDst, pdata->pMsg, msg_len);
	
	return msg_len;
}


/* Get msg length */ 
static unsigned short Assemble_Message_Length(App_Robort_Dat_Tag *pdata)
{
	unsigned short len;
	len = (pdata->Msg_H << 8) | (pdata->Msg_L);
	
	return len;
}

/* Compare local addr & slave addr */ 
static uint8 Robort_Adress_Veritfy(App_Robort_Dat_Tag *pdata)
{
	return (pdata->Addr == ROBORT_LOCAL_ADDRESS) ;
}


/*************************************************************************************************
*****
***** 函数名：void  Process_Robort_Direction_Cmd()
*****
***** 入口参数：无
*****
***** 功能描述：将运动方向参数解析并送到motor控制程序
*****
***** 调用： Resolve_Message_Data()恢复数据信息
*****		 Robort_Direction_Control() 控制机器人运行方向
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****
****  版本：v2.0
****
**************************************************************************************************/
uint8 Process_Robort_Direction_Cmd(App_Robort_Dat_Tag *pdata)
{
	unsigned short msg_len = 0;
    uint8 speed = 0;
    
	if (pdata == NULL)
		return 0;
	
	msg_len = Resolve_Message_Data(pdata, &speed);
	if (msg_len == 0)
	{
		speed = ROBORT_SPEED_DEFAULT;
	}
	
	if (pdata->Cmd == APP_ROBORT_CMD_STOP)
	{
		Robort_Direction_Control(ROBORT_STOP, speed);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_FORWARD)
	{
		Robort_Direction_Control(ROBORT_FORWARD, speed);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_BACK)
	{
		Robort_Direction_Control(ROBORT_BACK, speed);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_LEFT)
	{
		Robort_Direction_Control(ROBORT_LEFT, speed);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_RIGHT)
	{
		Robort_Direction_Control(ROBORT_RIGHT, speed);
	}
	
	
	return 1;
}



/*************************************************************************************************
*****
***** 函数名：void  Process_Robort_Steer_Cmd()
*****
***** 入口参数：无
*****
***** 功能描述：将舵机转动方向参数解析并送到steer控制程序
*****
***** 调用： Resolve_Message_Data()恢复数据信息
*****		 Robort_Steer_Control() 控制舵机转动
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****
****  版本：v2.0
****
**************************************************************************************************/
static uint8 Process_Robort_Steer_Cmd(App_Robort_Dat_Tag *pdata)
{
	unsigned short msg_len = 0;
	uint8 angle = 0;
	
	if (pdata == NULL)
		return 0;
	
	msg_len = Resolve_Message_Data(pdata, &angle);
	if (msg_len == 0)
	{
		return 0;
	}
	
	if (pdata->Cmd == APP_ROBORT_CMD_STEER1)
	{
		Robort_Steer_Control(ROBORT_STEER1, angle);  //for cloud stage steer1
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER2)
	{
		Robort_Steer_Control(ROBORT_STEER2, angle);  //for cloud stage steer2
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER3)
	{
		Robort_Steer_Control(ROBORT_STEER3, angle);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER4)
	{
		Robort_Steer_Control(ROBORT_STEER4, angle);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER5)
	{
		Robort_Steer_Control(ROBORT_STEER5, angle);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER6)
	{
		Robort_Steer_Control(ROBORT_STEER6, angle);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER7)
	{
		Robort_Steer_Control(ROBORT_STEER7, angle);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_STEER8)
	{
		Robort_Steer_Control(ROBORT_STEER8, angle);
	}
	
	return 1;
}

/*************************************************************************************************
*****
***** 函数名：void  Process_Robort_Speed_Cmd()
*****
***** 入口参数：无
*****
***** 功能描述：调整机器人运动速度
*****
***** 调用： Resolve_Message_Data()恢复数据信息
*****		 Robort_Speed_Control() 调整机器人速度
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****  版本：v2.0
****
**************************************************************************************************/
static uint8 Process_Robort_Speed_Cmd(App_Robort_Dat_Tag *pdata)
{
	uint8 speed = 0;
    unsigned short msg_len = 0;
    
    if (pdata == NULL)
		return 0;
	
	msg_len = Resolve_Message_Data(pdata, &speed);
	if (msg_len == 0)
	{
		return 0;
	}

    if (speed>100)
    {
        return 0;
    }
    
	if (pdata->Cmd == APP_ROBORT_CMD_SPEED_L)
	{
		Robort_Speed_Control(ROBORT_SPEED_L, speed);
	}
	else if (pdata->Cmd == APP_ROBORT_CMD_SPEED_R)
	{
		Robort_Speed_Control(ROBORT_SPEED_R, speed);
	}
    
    return 1;
}

/*************************************************************************************************
*****
***** 函数名：void  Process_Robort_Light_Cmd()
*****
***** 入口参数：无
*****
***** 功能描述：前照灯开启或关闭
*****
***** 调用： Resolve_Message_Data()恢复数据信息
*****		 Robort_Light_Control() 前照灯控制
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****  版本：v2.0
****
**************************************************************************************************/
static uint8 Process_Robort_Light_Cmd(App_Robort_Dat_Tag *pdata)
{
    uint8 lightNum = 0;
    unsigned short msg_len = 0;   

	if (pdata == NULL)
		return 0;
      
	msg_len = Resolve_Message_Data(pdata, &lightNum);
	if (msg_len == 0)
	{
		return 0;
	}

    if (lightNum ==  ROBORT_LIGHT_ONE)
    {
        if (pdata->Cmd == APP_ROBORT_CMD_LIGHT_ON)
        {
            Robort_Light_Control(ROBORT_LIGHT_ONE, ROBORT_LIGHT_ON);
        }
        else
        {
            Robort_Light_Control(ROBORT_LIGHT_ONE, ROBORT_LIGHT_OFF);
        }
    }
	else if (lightNum ==  ROBORT_LIGHT_TWO)
    {
        if (pdata->Cmd == APP_ROBORT_CMD_LIGHT_ON)
        {
            Robort_Light_Control(ROBORT_LIGHT_TWO, ROBORT_LIGHT_ON);
        }
        else
        {
            Robort_Light_Control(ROBORT_LIGHT_TWO, ROBORT_LIGHT_OFF);
        }
    }
    
    
	return 1;
}

/*************************************************************************************************
*****
***** 函数名：void  Process_Robort_Beep_Cmd()
*****
***** 入口参数：无
*****
***** 功能描述：前照灯开启或关闭
*****
***** 调用： Resolve_Message_Data()恢复数据信息
*****		 Robort_Beep_Control() 喇叭控制
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****  版本：v2.0
****
**************************************************************************************************/
static uint8 Process_Robort_Beep_Cmd(App_Robort_Dat_Tag *pdata)
{
	if (pdata == NULL)
		return 0;

	if (pdata->Cmd == APP_ROBORT_CMD_BEEP_ON)
	{
		Robort_Beep_Control(ROBORT_BEEP_ON);
	}
	else
	{
		Robort_Beep_Control(ROBORT_BEEP_OFF);
	}

	return 1;
}




/*************************************************************************************************
*****
***** 函数名：void  Process_Robort_GPS_Cmd()
*****
***** 入口参数：无
*****
***** 功能描述：设置GPS数据上传或关闭上传
*****
***** 调用： Resolve_Message_Data()恢复数据信息
*****		 Robort_Beep_Control() 喇叭控制
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****  版本：v2.0
****
**************************************************************************************************/
static void Process_Robort_GPS_Cmd(App_Robort_Dat_Tag *pdata)
{
	if (pdata->Cmd == APP_ROBORT_CMD_GPS_ON)
	{
		Indicator_Upload_Sensor.Indicator.B_GPS = 1;
	}
	else 
	{
		Indicator_Upload_Sensor.Indicator.B_GPS = 0;
	}

}


/*************************************************************************************************
*****
***** function：uint8  Protocol_Parser()
*****
***** input：pdata -- pointer to protocol command received
*****        
*****
***** output: none
*****
***** description：parse the protocol based on APP_ROBORT_CMD_TYPE
*****
*****
***** call：Process_Robort_Direction_Cmd() -- parse robort's direction cmd 
*****       Process_Robort_Steer_Cmd() -- parse robort's steer cmd
*****       Process_Robort_Light_Cmd() -- parse robort's light cmd
*****       Process_Robort_Beep_Cmd()  --  parse robort's beep cmd
*****       Process_Robort_Sensor_Cmd() -- parse robort's sensor cmd
*****       
*****   
*****
***** return:   0 -- error
*****           1 -- ok
*****
***** author：Sandy
*****	
***** version: 2.0
**************************************************************************************************/
uint8 Protocol_Parser(App_Robort_Dat_Tag *pdata)
{
	if (0 == Robort_Adress_Veritfy(pdata))
	{
		return 0;
	}
	
	switch (pdata->Cmd)
	{
		case APP_ROBORT_CMD_STOP:
		case APP_ROBORT_CMD_FORWARD:
		case APP_ROBORT_CMD_BACK:
		case APP_ROBORT_CMD_LEFT:
		case APP_ROBORT_CMD_RIGHT:
			Process_Robort_Direction_Cmd(pdata);
			break;
		case APP_ROBORT_CMD_STEER1:
		case APP_ROBORT_CMD_STEER2:
		case APP_ROBORT_CMD_STEER3:
		case APP_ROBORT_CMD_STEER4:
		case APP_ROBORT_CMD_STEER5:
		case APP_ROBORT_CMD_STEER6:
		case APP_ROBORT_CMD_STEER7:
		case APP_ROBORT_CMD_STEER8:
			Process_Robort_Steer_Cmd(pdata);
			break;
		case APP_ROBORT_CMD_SPEED_L:
		case APP_ROBORT_CMD_SPEED_R:
			Process_Robort_Speed_Cmd(pdata);
			break;
		case APP_ROBORT_CMD_LIGHT_ON:
		case APP_ROBORT_CMD_LIGHT_OFF:
			Process_Robort_Light_Cmd(pdata);
			break;
	        case APP_ROBORT_CMD_BEEP_ON:
		case APP_ROBORT_CMD_BEEP_OFF:
			Process_Robort_Beep_Cmd(pdata);
			break;
		//case APP_ROBORT_CMD_SENSOR:
			//Process_Robort_Sensor_Cmd(pdata); //暂时没用到
			//break;
		case APP_ROBORT_CMD_GPS_ON:
	       	case APP_ROBORT_CMD_GPS_OFF:
		       	Process_Robort_GPS_Cmd(pdata); 
			break;	
		default: return 0;
	}
	
	return 1;
}


/*************************************************************************************************
*****
***** 函数名：void  Protocol_Upload()
*****
***** 入口参数：无
*****
***** 功能描述：前照灯开启或关闭
*****
***** 调用： Robort_Fetch_GPS_Data()获取GPS数据
*****		 Robort_Send_Frame() 发送数据帧
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****  版本：v2.0
****
**************************************************************************************************/
int Protocol_Upload(void)
{
	void *pMsg 		= NULL;
	uint16 uMsgLen 		= 0;
	uint8 *pFrame 		= NULL;
	uint16 Frame_Length 	= 0;
	uint16 crc_code 	= 0;

	if (Indicator_Upload_Sensor.Indicator.B_GPS == 1)
	{		
		uMsgLen = Robort_Fetch_GPS_Data(&pMsg);
	}
	else if (Indicator_Upload_Sensor.Indicator.B_HUM == 1)
	{
	
	}
	else if (Indicator_Upload_Sensor.Indicator.B_TEMP == 1)
	{
	
	}
	else if (Indicator_Upload_Sensor.Indicator.B_DIST == 1)
	{
	
	}

	if (uMsgLen == 0) //There is no valid sensor data
		return 0; //upload fail

	Frame_Length = FRAME_INFO_SIZE + uMsgLen;
	pFrame = (uint8*) malloc(Frame_Length);
	if (pFrame == NULL) //Malloc fail!
		return 0;
	
	*pFrame 	= 0xff; 			        //Frame Head
	*(pFrame+1) = APP_TERMINAL_ADDRESS; 	//App Address
	*(pFrame+2)	= uMsgLen & 0xff;		    //Msg Length Low 
	*(pFrame+3)	= (uMsgLen>>8) & 0xff;		//Msg Length High 
	*(pFrame+4)	= ROBORT_APP_CMD_GPS;   	//Cmd type

	memcpy(pFrame+5, pMsg, sizeof(uint8)*uMsgLen);	//Copy message

	crc_code = Crc16(pFrame, Frame_Length-2); //Crc Calculation	
	
	*(pFrame+Frame_Length-2) = (crc_code>>8) & 0xff;//Crc high
	*(pFrame+Frame_Length-1) = crc_code & 0xff; 	//Crc low

	Robort_Send_Frame(pFrame, Frame_Length);
	SysDelay_ms(500);	//必须延时，否则释过快释放内存会导致发送数据不准确
	
	free(pFrame);		//Must do!!!
	
	return 1;
}


/******************* (C) COPYRIGHT 2015 X-SPACE *****END OF FILE****/


