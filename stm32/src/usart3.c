/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : usart3.c
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : UART3 Function
  Function List :
              uart3_init
              USART3_IRQHandler
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#include "usart3.h"
#include <string.h> 

u8 u8Recv;

/**************************************************************************
�������ܣ�����3��ʼ��
��ڲ����� bound:������
����  ֵ����
**************************************************************************/
void uart3_init(u32 bound)
{  	 
	//GPIO�˿�����
	GPIO_InitTypeDef stGpio_Init;
	USART_InitTypeDef stUart_Init;
	NVIC_InitTypeDef stNvic_Init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��UGPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
	//USART3_TX  
	stGpio_Init.GPIO_Pin = GPIO_Pin_10; //PB.10
	stGpio_Init.GPIO_Speed = GPIO_Speed_50MHz;
	stGpio_Init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &stGpio_Init);

	//USART3_RX	  
	stGpio_Init.GPIO_Pin = GPIO_Pin_11;//PB11
	stGpio_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &stGpio_Init);

	//Usart3 NVIC ����
	stNvic_Init.NVIC_IRQChannel = USART3_IRQn;
	stNvic_Init.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
	stNvic_Init.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
	stNvic_Init.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&stNvic_Init);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	//USART ��ʼ������
	stUart_Init.USART_BaudRate = bound;//���ڲ�����
	stUart_Init.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	stUart_Init.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	stUart_Init.USART_Parity = USART_Parity_No;//����żУ��λ
	stUart_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	stUart_Init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &stUart_Init);     //��ʼ������3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 
}

/**************************************************************************
�������ܣ�����3�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART3_IRQHandler(void)
{	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //���յ�����
	{	  
		s32 s32Recv_Tmp;
		static u8 Flag_PID,i,j,Receive[50];
		static float Data;
		s32Recv_Tmp=USART_ReceiveData(USART3); 
		u8Recv=s32Recv_Tmp;
	
		if(s32Recv_Tmp==0x59)  
			Flag_sudu=2;  //���ٵ���Ĭ��ֵ��
		if(s32Recv_Tmp==0x58)  
			Flag_sudu=1;  //���ٵ�
		
		if(s32Recv_Tmp>10)  //Ĭ��ʹ��
		{			
			if(s32Recv_Tmp==0x5A)	
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
			else if(s32Recv_Tmp==0x41)	
				Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ǰ
			else if(s32Recv_Tmp==0x45)	
				Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////��
			else if(s32Recv_Tmp==0x42||s32Recv_Tmp==0x43||s32Recv_Tmp==0x44)	
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //��
			else if(s32Recv_Tmp==0x46||s32Recv_Tmp==0x47||s32Recv_Tmp==0x48)	    //��
				Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
			else 
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
  		}
		if(s32Recv_Tmp<10)     //����appΪ��MiniBalanceV1.0  ��ΪMiniBalanceV1.0��ң��ָ��ΪA~H ��HEX��С��10
		{			
			Flag_sudu=1;//�л������ٵ�
			if(s32Recv_Tmp==0x00)
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
			else if(s32Recv_Tmp==0x01)	
				Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ǰ
			else if(s32Recv_Tmp==0x05)	
				Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////��
			else if(s32Recv_Tmp==0x02||s32Recv_Tmp==0x03||s32Recv_Tmp==0x04)	
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //��
			else if(s32Recv_Tmp==0x06||s32Recv_Tmp==0x07||s32Recv_Tmp==0x08)	    //��
				Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
			else 
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
		}	

		
		if(u8Recv==0x7B) 
			Flag_PID=1;   //APP����ָ����ʼλ

		if(u8Recv==0x7D) 
			Flag_PID=2;   //APP����ָ��ֹͣλ

		if(Flag_PID==1)  //�ɼ�����
		{
			Receive[i]=u8Recv;
			i++;
		}
		if(Flag_PID==2)  //��������
		{
			if(Receive[3]==0x50) 	 
				PID_Send=1;
			else  if(Receive[3]==0x57) 	 
				Flash_Send=1;
			else  if(Receive[1]!=0x23) 
			{								
				for(j=i;j>=4;j--)
				{
					Data+=(Receive[j-1]-48)*pow(10,i-j);
				}
				switch(Receive[1])
				{
					case 0x30:  Balance_Kp=Data/100;break;
					case 0x31:  Balance_Kd=Data/100;break;
					case 0x32:  Velocity_Kp=Data/100;break;
					case 0x33:  Velocity_Ki=Data/100;break;
					case 0x34:  break; //Ԥ��
					case 0x35:  break; //Ԥ��
					case 0x36:  break; //Ԥ��
					case 0x37:  break; //Ԥ��
					case 0x38:  break; //Ԥ��
				}
			}				 
			Flag_PID=0;
			i=0;
			j=0;
			Data=0;
			memset(Receive, 0, sizeof(u8)*50);//��������
		} 
	}  											 
} 
