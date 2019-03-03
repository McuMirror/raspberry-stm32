/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : exti.c
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : exit int functions
  Function List :
              robot_exit_init
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#include "exti.h"

/**************************************************************************
�������ܣ��ⲿ�жϳ�ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void robot_exit_init(void)
{  
	GPIO_InitTypeDef stGpio_Init;
	EXTI_InitTypeDef stExit_Init;
	NVIC_InitTypeDef stNvic_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIO�˿�ʱ��
	stGpio_Init.GPIO_Pin = GPIO_Pin_12;	            //�˿�����
	stGpio_Init.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_Init(GPIOA, &stGpio_Init);					      //�����趨������ʼ��GPIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
	stExit_Init.EXTI_Line=EXTI_Line12;
	stExit_Init.EXTI_Mode = EXTI_Mode_Interrupt;	
	stExit_Init.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	stExit_Init.EXTI_LineCmd = ENABLE;
	EXTI_Init(&stExit_Init);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	stNvic_Init.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	stNvic_Init.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	stNvic_Init.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
	stNvic_Init.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&stNvic_Init); 
}










