/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : timer.c
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : timer3 functions
  Function List :
              read_distance
              tim3_cap_init
              TIM3_IRQHandler
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#include "timer.h"

/**************************************************************************
�������ܣ���ʱ��3ͨ��3���벶���ʼ��
��ڲ�������ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/
TIM_ICInitTypeDef  stTim3Ic_Init;
void tim3_cap_init(u16 arr,u16 psc)	
{	 
	
	GPIO_InitTypeDef stGpio_Init;
	TIM_TimeBaseInitTypeDef  stTimerBase_Init;
 	NVIC_InitTypeDef stNvic_Init;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��
	
	stGpio_Init.GPIO_Pin  = GPIO_Pin_0; 
	stGpio_Init.GPIO_Mode = GPIO_Mode_IPD; //PB0 ����  
	GPIO_Init(GPIOB, &stGpio_Init);
	
	stGpio_Init.GPIO_Pin  = GPIO_Pin_1;     
	stGpio_Init.GPIO_Mode = GPIO_Mode_Out_PP;     //PB1��� 
	stGpio_Init.GPIO_Speed = GPIO_Speed_2MHz;     //2M
	GPIO_Init(GPIOB, &stGpio_Init);
	
	//��ʼ����ʱ��3 TIM3	 
	stTimerBase_Init.TIM_Period = arr; //�趨�������Զ���װֵ 
	stTimerBase_Init.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	stTimerBase_Init.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	stTimerBase_Init.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &stTimerBase_Init); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM3���벶�����
	stTim3Ic_Init.TIM_Channel = TIM_Channel_3; //CC1S=03 	ѡ������� IC3ӳ�䵽TI1��
	stTim3Ic_Init.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	stTim3Ic_Init.TIM_ICSelection = TIM_ICSelection_DirectTI;
	stTim3Ic_Init.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	stTim3Ic_Init.TIM_ICFilter = 0x00;//���������˲��� ���˲�
	TIM_ICInit(TIM3, &stTim3Ic_Init);
	
	//�жϷ����ʼ��
	stNvic_Init.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	stNvic_Init.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	stNvic_Init.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�0��
	stNvic_Init.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&stNvic_Init);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 	
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC3IE�����ж�	
	TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3
}
/**************************************************************************
�������ܣ����������ջز�����
��ڲ�������
����  ֵ����
**************************************************************************/
u16 TIM3CH3_CAPTURE_STA,TIM3CH3_CAPTURE_VAL;
void read_distance(void)
{   
	PBout(1)=1;
	delay_us(15);  
	PBout(1)=0;	
	if(TIM3CH3_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
	{
		Distance=TIM3CH3_CAPTURE_STA&0X3F;
		Distance*=65536;					        //���ʱ���ܺ�
		Distance+=TIM3CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
		Distance=Distance*170/1000;
		//	printf("%d \r\n",Distance);
		TIM3CH3_CAPTURE_STA=0;			//������һ�β���
	}				
}
/**************************************************************************
�������ܣ��������ز������ȡ�ж�
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	u16 tsr;
	tsr=TIM3->SR;
	if((TIM3CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	    
			if(TIM3CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH3_CAPTURE_VAL=0XFFFF;
				}else 
					TIM3CH3_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x08)//����3���������¼�
		{	
			if(TIM3CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM3CH3_CAPTURE_VAL=TIM3->CCR3;	//��ȡ��ǰ�Ĳ���ֵ.
				TIM3->CCER&=~(1<<9);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH3_CAPTURE_STA=0;			//���
				TIM3CH3_CAPTURE_VAL=0;
				TIM3CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM3->CNT=0;					//���������
				TIM3->CCER|=1<<9; 				//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
	}
	TIM3->SR=0;//����жϱ�־λ 	     
}
