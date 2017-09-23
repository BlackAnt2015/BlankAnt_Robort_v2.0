/**********************************************************************************************************
**** 文件名：APP_light.c
****
**** 文件描述：控制两盏灯的状态（亮/灭）
****
**** 创建人：
****
**** 版本号：1.1
****
**** 修改记录：2017/8/28  By SunKang
****
****
****
***********************************************************************************************************/

#include "App_Light.h"


/*************************************************************************************************
***** 函数名：void Robort_Light_Control(ROBORT_LIGHT_NO_TAG light_no, ROBORT_LIGHT_TAG light_status)
*****
***** 入口参数：light_no：选择控制灯1或灯2，ROBORT_LIGHT_ONE = 0，ROBORT_LIGHT_TWO = 1
*****                  light_status:选择被控制灯的状态，ROBORT_LIGHT_ON = 0，ROBORT_LIGHT_OFF=1
*****
***** 功能描述：控制两个灯的点亮和熄灭
*****						light_no =	ROBORT_LIGHT_ONE 时，控制灯1的状态
*****						light_no =	ROBORT_LIGHT_TWO 时，控制灯2的状态
*****						light_status = ROBORT_LIGHT_ON 时，对应的灯被点亮
*****						light_status = ROBORT_LIGHT_OFF 时，对应的灯熄灭
*****
***** 返回值：无
*****
***** 作者：
**************************************************************************************************/

void Robort_Light_Control(ROBORT_LIGHT_NO_TAG light_no, ROBORT_LIGHT_TAG light_status)
{

    switch (light_no)
    {
        case ROBORT_LIGHT_ONE:
              Control_1stLight(light_status);
        break;

        case ROBORT_LIGHT_TWO:
              Control_2ndLight(light_status);
        break;

        default: break;
    }

}

/*************************************************************************************************
***** 函数名：void Control_1stLight(ROBORT_LIGHT_TAG light_status)
*****					void Control_2ndLight(ROBORT_LIGHT_TAG light_status)
*****
***** 入口参数：light_status：
*****
***** 功能描述：控制两个灯的点亮和熄灭（为函数Robort_Light_Control()的所调用）
*****						当入口参数为 ROBORT_LIGHT_ON （ROBORT_LIGHT_ON = 0）时，对应的灯点亮
*****						当入口参数为 ROBORT_LIGHT_OFF ROBORT_LIGHT_OFF = 1）时，对应的灯熄灭
*****
***** 返回值：无
*****
***** 作者：
**************************************************************************************************/
static void Control_1stLight(ROBORT_LIGHT_TAG light_status)
{
    (ROBORT_LIGHT_ON==light_status) ?
        STM32_GPIO_SetPin(U_GPIO_A, U_PIN_11, 1) : STM32_GPIO_SetPin(U_GPIO_A, U_PIN_11, 0);
}

static void Control_2ndLight(ROBORT_LIGHT_TAG light_status)
{

}


/*************************************************************************************************
***** 函数名：void Robort_Light_Init(void)
*****
***** 入口参数：无
*****
***** 功能描述：初始化Lihgt相关的GPIO，初始状态时灯为熄灭状态
*****
***** 返回值：无
*****
***** 作者：
**************************************************************************************************/
void Robort_Light_Init(void)
{
	STM32_GPIO_ConfgPin(U_GPIO_A, U_PIN_11, U_MODE_OUT_PP, U_SPEED_50M);

    STM32_GPIO_SetPin(U_GPIO_A, U_PIN_11, 0);             //GPIOA_Pin11设置为低
}

/******************* (C) COPYRIGHT 2015 X-SPACE *****END OF FILE****/
