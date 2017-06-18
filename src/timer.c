/******************************************************************************
  File			: timer.c
  Description	: timer test
  Author		: Xiaoming Li
*******************************************************************************
  Modify List:
-------------------------------------------------------------------------------
  2014/8/5 21:00 PM	| Created
******************************************************************************/

#include "timer.h"
#include "led.h"
#include "delay.h"
/*
 * bit7 - �������
 * bit6 - ���񵽸ߵ�ƽ
 * bit5:0 - ����ߵ�ƽ��ʱ���������
 */
u8 TIM2CH1_CAP_STA = 0;	//���벶��״̬
u16 TIM2CH1_CAP_VAL;	//���벶��ֵ


/*-------------------------------------------------------------------
 * FUNC : timer2_init
 * DESC : timer 2 initial
 * PARM : arr - reload value
 * 		  psc - clock pre
 *		  cmd - 1: enable timer 0: don't enable timer
 * RET	: N/A
 *-----------------------------------------------------------------*/
void timer2_init(u16 arr, u16 psc, u8 cmd)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	if(cmd)
		TIM_Cmd(TIM2, ENABLE);
} 

void timer2_cap_init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM2_ICInitStructure;
	
	timer2_init(arr, psc, 0);
	TIM_ITConfig(TIM2, TIM_IT_Update|TIM_IT_CC1, ENABLE);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	
	TIM_Cmd(TIM2, ENABLE);
}

/*
void TIM2_IRQHandler(void)
{
	if((TIM2CH1_CAP_STA & 0x80) == 0){	//δ����ɹ�
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
			if(TIM2CH1_CAP_STA & 0x40){	//�Ѿ����񵽸ߵ�ƽ
				if((TIM2CH1_CAP_STA & 0x3f) == 0x3f){	//�ߵ�ƽʱ��̫��
					TIM2CH1_CAP_STA |=  0x80;
					TIM2CH1_CAP_VAL = 0xffff;
				}else
					TIM2CH1_CAP_STA++;
			}
		}
		if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){//����1���������¼�
			if(TIM2CH1_CAP_STA & 0x40){	//����һ���½���
				TIM2CH1_CAP_STA |= 0x80;	//��ǳɹ�����һ��������
				TIM2CH1_CAP_VAL = TIM_GetCapture1(TIM2);
				//����Ϊ�����ز���
				TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Rising);
			}else{	//��δ��ʼ����һ�β���������
				TIM2CH1_CAP_STA = 0;	//����
				TIM2CH1_CAP_VAL = 0;
				TIM_SetCounter(TIM2, 0);
				TIM2CH1_CAP_STA |= 0x40;
				//����Ϊ�½��ز���
				TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);
			}
		}
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update);
}
*/
