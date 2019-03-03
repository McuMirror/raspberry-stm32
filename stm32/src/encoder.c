/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : encoder.c
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : encoder speed
  Function List :
              encoder_init_tim2
              encoder_init_tim4
              read_encoder
              TIM2_IRQHandler
              TIM4_IRQHandler
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#include "encoder.h"

/**************************************************************************
�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void encoder_init_tim2(void)
{
	TIM_TimeBaseInitTypeDef stTimerBase_Init;  
	TIM_ICInitTypeDef stTimerIc_Init;  
	GPIO_InitTypeDef stGpio_Init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��

	stGpio_Init.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
	stGpio_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &stGpio_Init);					      //�����趨������ʼ��GPIOB

	TIM_TimeBaseStructInit(&stTimerBase_Init);
	stTimerBase_Init.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
	stTimerBase_Init.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
	stTimerBase_Init.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
	stTimerBase_Init.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM2, &stTimerBase_Init);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&stTimerIc_Init);
	stTimerIc_Init.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &stTimerIc_Init);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE); 
}
/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void encoder_init_tim4(void)
{
	TIM_TimeBaseInitTypeDef stTimerBase_Init;  
	TIM_ICInitTypeDef stTimerIc_Init;  
	GPIO_InitTypeDef stGpio_Init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��

	stGpio_Init.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
	stGpio_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOB, &stGpio_Init);					      //�����趨������ʼ��GPIOB

	TIM_TimeBaseStructInit(&stTimerBase_Init);
	stTimerBase_Init.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
	stTimerBase_Init.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
	stTimerBase_Init.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
	stTimerBase_Init.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM4, &stTimerBase_Init);
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&stTimerIc_Init);
	stTimerIc_Init.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &stTimerIc_Init);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4, ENABLE); 
}

/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int read_encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	{
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		default:  Encoder_TIM=0;
	}
	return Encoder_TIM;
}
/**************************************************************************
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
/**************************************************************************
�������ܣ�TIM2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}

