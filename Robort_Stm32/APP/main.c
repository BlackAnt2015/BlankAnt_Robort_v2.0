#include "main.h"

App_Robort_Dat_Tag g_ProtocolData = {0}; //协议帧变量

extern Robort_Sensor_Indicator_Tag Indicator_Upload_Sensor;
/****************************************************************************************
// System clock is configured defaultly in /STARTUP/startup_stm32f10x_hd.s line 152,
// in the function SystemInit(), by define SYSCLK_FREQ_72MHz.
//                                                                 
//                                               -- GPIOA(PIN0~PIN3 motor speed; PIN11 Light; PIN12 Beep;)
//												|-- GPIOA(PA6~PA7 Steer0~Steer1)
//                                              |-- 
//                                              |
//                    --PreScale1 - APB2(72M) — |-- GPIOB(PB0~PB1 Steer2~Steer2)
//                   |                          |-- GPIOC(PIN6~PIN9 motor_dir)
//                   |                          
//                   |                           -- DIV8 - SYSClock(9M)
//                   |                          |
// HSE(8M)->PLL(9) - |--PreScale1 - HCLK(72M) - |
//                   |                          |
//                   |                          
//                   |                          -- 72M(2x) -- TIMER2
//                   |                         |
//                   |__PreScale2 - APB1(36M) -|
//
//
*****************************************************************************************/
int main(void)
{  
	//各模块初始化
	Robort_Delay_Init();
	Robort_Beep_Init();
	Robort_Light_Init();
	Robort_Motor_Init();
	Robort_Steer_Init();
	Robort_Uart_Init();
	Robort_GPS_Init();
	Robort_Sensor_Task_Init();
	
    while (1)
    {

	//如果开启测试则执行硬件测试程序，否则执行协议解析程序
#if _ENABLE_MODULE_1 | _ENABLE_MODULE_2 | _ENABLE_MODULE_3 | \
    _ENABLE_MODULE_4 | _ENABLE_MODULE_5 | _ENABLE_MODULE_6 | \
    _ENABLE_MODULE_7 			
		Hardware_Test();
#else
		if (Robort_Receive_Frame(&g_ProtocolData) == RET_OK)
		{
			Protocol_Parser(&g_ProtocolData);
			Resource_Release();
		}
		
		if (Indicator_Upload_Sensor.value != 0)
		{
			Protocol_Upload();
		}

#endif
    }
}

static void Resource_Release(void)
{
	free(g_ProtocolData.pMsg);
}


#if _ENABLE_MODULE_1 | _ENABLE_MODULE_2 | _ENABLE_MODULE_3 | \
    _ENABLE_MODULE_4 | _ENABLE_MODULE_5 | _ENABLE_MODULE_6 | \
    _ENABLE_MODULE_7					    		
static void Hardware_Test()
{

#ifdef _ENABLE_MODULE_1
	Robort_Debug_Func[MODULE_SYSTEM]();
#endif	
	
#ifdef _ENABLE_MODULE_2
	Robort_Debug_Func[MODULE_LIGHT]();
#endif

#ifdef _ENABLE_MODULE_3
	Robort_Debug_Func[MODULE_BEEP]();
#endif

#ifdef _ENABLE_MODULE_4	
	Robort_Debug_Func[MODULE_MOTOR]();
#endif
	
#ifdef _ENABLE_MODULE_5
	Robort_Debug_Func[MODULE_STEER]();
#endif	
	
#ifdef _ENABLE_MODULE_6
	Robort_Debug_Func[MODULE_GPS]();
#endif	

#ifdef _ENABLE_MODULE_7
	Robort_Debug_Func[MODULE_UART]();
#endif
	while(1);       
}
#endif

/*************************************************************************************************
*****
***** 函数名：void  Robort_System_Test()
*****
***** 入口参数：无
*****
***** 功能描述：系统测试，从App_Robort_Test_Item_Table[]中取出测试条目，依次解析执行
*****
***** 调用： Protocol_Parser()解析下行协议
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
****
****  版本：v1.0
****
**************************************************************************************************/
static void Robort_System_Test(void)
{
#ifdef 	_ENABLE_MODULE_1
	App_Robort_Dat_Tag app_robort = {0};
	uint16 Item_Idx = 0;
	uint16 Item_Num = sizeof(App_Robort_Test_Item_Table) / sizeof(App_Robort_Dat_Tag);
	
	for (Item_Idx=0; Item_Idx<Item_Num; Item_Idx++)
	{
		memcpy(&app_robort, &App_Robort_Test_Item_Table[Item_Idx],  sizeof(App_Robort_Dat_Tag));
		Protocol_Parser(&app_robort);
		SysDelay_ms(3000);
	}
#endif
}


/*************************************************************************************************
*****
***** 函数名：void  Robort_Light_Test()
*****
***** 入口参数：无
*****
***** 功能描述：Light module测试，点亮/熄灭灯
*****
***** 调用： Robort_Light_Control()灯控制
*****
***** 返回值：无
*****
***** 作者：Sandy
****		
****  版本：v1.0
**************************************************************************************************/
static void Robort_Light_Test(void)
{
	Robort_Light_Control( ROBORT_LIGHT_ONE, ROBORT_LIGHT_ON);
	SysDelay_ms(1000);
	Robort_Light_Control( ROBORT_LIGHT_ONE, ROBORT_LIGHT_OFF);
	SysDelay_ms(1000);
}

/*************************************************************************************************
*****
***** 函数名：void  Robort_Beep_Test()
*****
***** 入口参数：无
*****
***** 功能描述：Beep module测试，使能/不使能喇叭
*****
***** 调用： Robort_Beep_Control()- 喇叭控制
*****
***** 返回值：无
*****
***** 作者：Sandy
****	
****  版本：v1.0
****
**************************************************************************************************/
static void Robort_Beep_Test(void)
{
	Robort_Beep_Control(ROBORT_BEEP_ON);
	SysDelay_ms(3000);
	Robort_Beep_Control(ROBORT_BEEP_OFF);
	SysDelay_ms(3000);	
}

/*************************************************************************************************
*****
***** 函数名：void  Robort_Motor_Test()
*****
***** 入口参数：无
*****
***** 功能描述：电机测试
*****
***** 调用： Robort_Direction_Control()- 方向设定
*****        Robort_Speed_Control() - 速度设定
*****
***** 返回值：无
*****
***** 作者：Sandy
****		
****  版本：v1.0
**************************************************************************************************/
static void Robort_Motor_Test(void)
{	
	Robort_Direction_Control(ROBORT_STOP, 0);
	SysDelay_ms(5000);

	Robort_Direction_Control(ROBORT_BACK, 50);
	SysDelay_ms(5000);
	
	Robort_Direction_Control(ROBORT_FORWARD, 60);
	SysDelay_ms(5000);

	Robort_Direction_Control(ROBORT_LEFT, 50);
	SysDelay_ms(5000);

	Robort_Direction_Control(ROBORT_RIGHT, 50);
	SysDelay_ms(5000);

	Robort_Direction_Control(ROBORT_STOP, 0);
	SysDelay_ms(5000);
	
	//加速到40
	Robort_Speed_Control(ROBORT_SPEED_L, 40);
	Robort_Speed_Control(ROBORT_SPEED_R, 40);
	
	Robort_Direction_Control(ROBORT_FORWARD, 60);
	SysDelay_ms(5000);
	
	Robort_Direction_Control(ROBORT_BACK, 50);
	SysDelay_ms(5000);
	
	//加速到60
	Robort_Speed_Control(ROBORT_SPEED_L, 60);
	Robort_Speed_Control(ROBORT_SPEED_R, 60);
	
	Robort_Direction_Control(ROBORT_FORWARD, 60);
	SysDelay_ms(5000);
	
	Robort_Direction_Control(ROBORT_BACK, 50);
	SysDelay_ms(5000);
	
	Robort_Direction_Control(ROBORT_STOP, 0);
	SysDelay_ms(2000);
}

/*************************************************************************************************
*****
***** 函数名：void  Robort_Steer_Test()
*****
***** 入口参数：无
*****
***** 功能描述：电机测试
*****
***** 调用： Robort_Steer_Control()- 舵机转动控制
*****
***** 返回值：无
*****
***** 作者：Sandy
****				
**************************************************************************************************/
static void Robort_Steer_Test(void)
{
	Robort_Steer_Control(ROBORT_STEER1,  0); //Stay 0 angle
	Robort_Steer_Control(ROBORT_STEER2,  0); //Stay 0 angle
	delay_ms(5000);

	Robort_Steer_Control(ROBORT_STEER1,  30); //Stay 30 angle
	Robort_Steer_Control(ROBORT_STEER2,  30); //Stay 30 angle
	delay_ms(5000);
	
	Robort_Steer_Control(ROBORT_STEER1,  60); //Stay 60 angle
	Robort_Steer_Control(ROBORT_STEER2,  60); //Stay 60 angle
	delay_ms(5000);
	
	
	Robort_Steer_Control(ROBORT_STEER1,  90); //Stay 90 angle
	Robort_Steer_Control(ROBORT_STEER2,  90); //Stay 90 angle
	delay_ms(5000);

	Robort_Steer_Control(ROBORT_STEER1,  150); //Stay 150 angle
	Robort_Steer_Control(ROBORT_STEER2,  150); //Stay 150 angle
	delay_ms(5000);
	
	
	Robort_Steer_Control(ROBORT_STEER1,  180); //Stay 180 angle
	Robort_Steer_Control(ROBORT_STEER2,  180); //Stay 180 angle
	delay_ms(5000);
}

static void Robort_GPS_Test(void)
{
	void * pGPSInfo = NULL;
	uint16 uGPSInfoLen = 0;
	while (1)
	{
		uGPSInfoLen = Robort_Fetch_GPS_Data(&pGPSInfo);
	
		delay_ms(2000);
	}
}

static void Robort_UART_Test(void)
{
	//char Test_Table[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	char Test_Table[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	Robort_Send_Frame(Test_Table, sizeof(Test_Table)/sizeof(char));
	
	Robort_Send_Frame(Test_Table, sizeof(Test_Table)/sizeof(char));
	
	Robort_Send_Frame(Test_Table, sizeof(Test_Table)/sizeof(char));
}

/******************* (C) COPYRIGHT 2015 X-SPACE *****END OF FILE*********************/
