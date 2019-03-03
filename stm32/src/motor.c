/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : motor.c
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : motor funcitons
  Function List :
              motor_gpio_init
              robot_pwm_init
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#include "motor.h"

static void motor_gpio_init(void)
{
	GPIO_InitTypeDef stGpio_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PB�˿�ʱ��
	stGpio_Init.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//�˿�����
	stGpio_Init.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	stGpio_Init.GPIO_Speed = GPIO_Speed_50MHz;     //50M
	GPIO_Init(GPIOB, &stGpio_Init);					      //�����趨������ʼ��GPIOB 
}
void robot_pwm_init(u16 arr,u16 psc)
{		 		
	GPIO_InitTypeDef stGpio_Init;
	TIM_TimeBaseInitTypeDef  stTimerBase_Init;
	TIM_OCInitTypeDef  stTimerOc_Init;
	
	motor_gpio_init();	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
   //���ø�����Ϊ�����������,���TIM1 CH1 CH4��PWM���岨��
	stGpio_Init.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; //TIM_CH1 //TIM_CH4
	stGpio_Init.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	stGpio_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &stGpio_Init);
	
	stTimerBase_Init.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	stTimerBase_Init.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	stTimerBase_Init.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	stTimerBase_Init.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &stTimerBase_Init); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	stTimerOc_Init.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	stTimerOc_Init.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	stTimerOc_Init.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
	stTimerOc_Init.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &stTimerOc_Init);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM1, &stTimerOc_Init);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
 
} 

