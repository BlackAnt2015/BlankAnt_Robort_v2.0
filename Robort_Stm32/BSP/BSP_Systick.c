#include "Common.h"  
static u8  fac_us=0;//us��ʱ������
static u32 fac_ms=0;//ms��ʱ������
static u32 fac_systic = 0;


/*************************************************************************************************
*****
***** ������:void  delay_init()
*****
***** ��ڲ�������
*****
***** ��������������ϵͳʱ����Ϊ��ʱʱ�ӣ���ʼ��ϵͳʱ�ӣ�SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v1.0
****
**************************************************************************************************/
void delay_init()	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;	//system ticks per us
	fac_ms=(u32)fac_us*1000;//����ÿ��ms��Ҫ��systickʱ����   
	fac_systic = 1;
}								    


/*************************************************************************************************
*****
***** ������:void  delay_us()
*****
***** ��ڲ�����nus--��ʱ��us��
*****
***** ������������ʱn us
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v1.0
****
**************************************************************************************************/		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}


/*************************************************************************************************
*****
***** ������:void  delay_us()
*****
***** ��ڲ�����nms--��ʱ��nms��,SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=1864 
*****
***** ������������ʱn us
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v1.0
****
**************************************************************************************************/	
void delay_ms(u32 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
} 


void delay_systick()
{
	u32 temp;	    	 
	SysTick->LOAD=fac_systic; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}

/*********************************************END OF FILE**********************/
