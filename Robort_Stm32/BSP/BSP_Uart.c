#include "Common.h" 

uchar Task_Uart1_Rx =0;
uchar Tx_Buffer[Tx_Array_Size];			     //���ͻ�����
uchar Rx_Buffer[Rx_Array_Size];			     //���ܻ�����
uchar Rx_Process_Buffer[Rx_Array_Size];	     //���ܴ�������
uchar Tx_Ptr,Rx_Ptr; 	 		             //���ͽ���ָ��
uchar Tx_Tail,Rx_Tail;    			   	     //���ͽ���βָ��
uchar Rx_Step=0;							 //���ղ���
uchar Tx_Count,Rx_Count;				     //���ͽ��ռ�ʱ
uchar Temp=0;
uchar i=0;
uchar DMA1_Uart_Status=0;



void UART2_Init(ulong bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 GPIO config */
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = bound;                //GPSģ��Ĭ��ʹ�ò����ʣ�9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure); 

	USART_Cmd(USART2, ENABLE);
}

/*************************************************************************************************
*****
***** ������:void  UART3_Init()
*****
***** ��ڲ�������
*****
***** ����������uart3��ʼ��, 9600B+StartBit+8BitsData+StopBit
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void UART3_Init(ulong bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* USART2 GPIO config */
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART2 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = bound;                //GPSģ��Ĭ��ʹ�ò����ʣ�9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure); 

	USART_Cmd(USART3, ENABLE);
}

/*************************************************************************************************
*****
***** ������:void  UART1_Init()
*****
***** ��ڲ�������
*****
***** ����������uart1��ʼ��, 9600B+StartBit+8BitsData+StopBit
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void UART1_Init( ulong bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	USART_DeInit(USART1);  //��λ����1
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

	//Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}

/*************************************************************************************************
*****
***** ������:void  STM32_UART_Init()
*****
***** ��ڲ�������
*****
***** ����������uart1, uart2, uart3�ĳ�ʼ��
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void STM32_UART_Init(void)
{
	UART1_Init(9600);
	//UART2_Init(9600);
	
	DMA_Uart1_Init();
}

/*************************************************************************************************
*****
***** ������:void  USART1_IRQHandler()
*****
***** ��ڲ�������
*****
***** ����������UART1���жϴ���
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Rx_Buffer[Rx_Ptr] =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		if(Rx_Ptr>(Rx_Array_Size-1)) Rx_Ptr=0;
		Rx_Ptr++;
		switch (Rx_Step)							//��ʼ��־
		{
			case 0x00:								//У��֡ͷ
				Rx_Count=0;
				if(Rx_Buffer[0]==0xFF) 
					Rx_Step++; 
   				else 
					Rx_Ptr=0;
				break;
			case 0x01:								//����ģ��ţ�0x01
				Rx_Count=0;
				if(Rx_Buffer[1]==0x01)
				{
					Rx_Step++;
				}	
				else 
				{           
					Rx_Ptr=0;
					Rx_Step=0;
				}
				break;
			case 0x02:											
			    Rx_Count=0;
				if(Rx_Ptr==4)
				{
					Temp=Rx_Buffer[2];
					Rx_Tail= ((u16)Rx_Buffer[3]<<8 | Temp) +7;			
					if (Rx_Tail>(Rx_Array_Size-1))			// ������Ч
					{
						Rx_Ptr=0;
						Rx_Step=0;
					}
					else 
					{
						Rx_Step++;
					}
				}
				break;
			case 0x03:										//��ȡ����
				Rx_Count=0;
				if(Rx_Ptr==Rx_Tail)
				{
					for ( i=0;i<Rx_Tail;i++)
					{
						Rx_Process_Buffer[i]=Rx_Buffer[i]; 
					}
					Rx_Ptr=0;
					Rx_Tail=0;
					Rx_Step=0;
					Task_Uart1_Rx=1;
				}
				break;
			default: break;  											// 
			}
	}
		
}


/*************************************************************************************************
*****
***** ������:void  STM32_UART_Write()
*****
***** ��ڲ�����uartNo--UART��; src--�û����뻺����; len--���ݳ���(����)
*****
***** ������������APP����ģ�鷢�����ݸ�UART
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void STM32_UART_Write(u8 uartNo, void *src, u16 len)
{
	u8 t=0;
	if( 1 ==uartNo)
	{
		for(t=0;t<len;t++)
		{
			USART1->DR =*((u8*)src+t);
			while((USART1->SR&0X40)==0);//��ѯ�����Ƿ����
		}
	}
	else if( 2==uartNo)
	{
		for(t=0;t<len;t++)
		{
			USART2->DR =*((u8*)src+t);
			while((USART2->SR&0X40)==0);//��ѯ�����Ƿ����
		}
	}
}


/*************************************************************************************************
*****
***** ������:void  STM32_UART_Read()
*****
***** ��ڲ�����uartNo--UART��; dst--�û����������; len--���ݳ���(����)
*****
***** ������������UART����ģ���ȡ���ݷ��ظ�APP����ģ��
*****
***** ���ã� ��
*****
***** ����ֵ��0--ʧ�ܣ�1--�ɹ���
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/

u8 STM32_UART_Read(u8 uartNo, void *dst, u16 len)
{
	u16 dat_len 	= 0;
	u16 crc_code 	= 0;
	u16 msg_len 	= 0; 
	App_Robort_Dat_Tag *pRecDat = (App_Robort_Dat_Tag *)dst;
	
	if( Task_Uart1_Rx)
	{
		//1. ������Ϣ�ĳ���
		msg_len = ((u16)Rx_Process_Buffer[3]<<8 | Rx_Process_Buffer[2]);
		
		//2. ����֡�ܳ���
		dat_len = msg_len + FRAME_INFO_SIZE;
		
		//3. CRCУ��
		crc_code=Crc16(&Rx_Process_Buffer[0], dat_len-2); 
		if (( (crc_code&0xff) != Rx_Process_Buffer[dat_len-1]) || 
			(((crc_code>>8)&0xff) != Rx_Process_Buffer[dat_len-2]))
		{
			//return 0;
		}		
		
		//4. ����֡��Ϣ����
		pRecDat->pMsg = (uint8 *)malloc(msg_len);
		
		//(1) copy frame info
		pRecDat->Frame_Head 	= Rx_Process_Buffer[0];
		pRecDat->Addr 			= Rx_Process_Buffer[1];
		pRecDat->Msg_L			= Rx_Process_Buffer[2];
		pRecDat->Msg_H			= Rx_Process_Buffer[3];
		pRecDat->Cmd 			= Rx_Process_Buffer[4];
		pRecDat->Crc_L 			= Rx_Process_Buffer[dat_len-2]; //CRC_L
		pRecDat->Frame_Head 	= Rx_Process_Buffer[dat_len-1]; //CRC_H
		
		//(2) copy message info
		memcpy(pRecDat->pMsg, &Rx_Process_Buffer[5], msg_len);
		
		Task_Uart1_Rx=0;
		return 1;
	}	

	return 0;
}

 

/*************************************************************************************************
*****
***** ������:void  DMA_Uart1_Init()
*****
***** ��ڲ�������
*****
***** ��������������UART1ΪDMA����
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
 void DMA_Uart1_Init( void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	DMA_DeInit(DMA1_Channel4);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Tx_Buffer;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = 10;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// DMA2 Channel Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�

	/*ʹ��DMA*/
	DMA_Cmd (DMA1_Channel4,ENABLE);		
    
  /* ���ô��� �� DMA����TX���� */
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}

/*���� UART1-DMAΪ��*/
void DMA1_DATA_Trans_Task_ON()
{
	DMA1_Uart_Status=1;
}

/*���� UART1-DMAΪ�ر�*/
void DMA1_DATA_Trans_Task_OFF()
{
	DMA1_Uart_Status=0;
}

u8 DMA1_Uart1_Status_Get( void)
{
	return DMA1_Uart_Status;
}

/*************************************************************************************************
*****
***** ������:void  STM32_UART1_Write()
*****
***** ��ڲ�����Tx_Buff--�������ݻ�������
*****           Data_Len--�������ݵĳ���
*****
***** ����������UART1���ͺ���
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void STM32_UART1_Write(uint8* Tx_Buff,uint16 Data_Len)
{
	DMA1_Channel4->CCR&=~(1<<0);
	DMA1_Channel4->CMAR=(u32)Tx_Buff;
	DMA1_Channel4->CNDTR=Data_Len;
	DMA1_Channel4->CCR|=(1<<0);
	DMA1_DATA_Trans_Task_ON();
}

/*************************************************************************************************
*****
***** ������:void  Upload_ProcessDMAIRQ()
*****
***** ��ڲ�������
*****
***** ����������UART1�ϴ����ݽ����ж�
*****
***** ���ã� ��
*****
***** ����ֵ��
*****
***** ����:Sandy
****	
****  �汾��v2.0
****
**************************************************************************************************/
void Upload_ProcessDMAIRQ( void)
{
	if( DMA_GetITStatus(DMA1_IT_TC4))
	{
		DMA1_DATA_Trans_Task_OFF();
		DMA_ClearFlag(DMA1_FLAG_TC4);//���ͨ��4������ɱ�־
	}
}
 
/******************* (C) COPYRIGHT 2015 X-SPACE *****END OF FILE*********************/