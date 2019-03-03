#include "led.h"

/**************************************************************************
�������ܣ�LED�ӿڳ�ʼ��
��ڲ������� 
����  ֵ����
**************************************************************************/
void led_init(void)
{
	GPIO_InitTypeDef stGpio_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
	stGpio_Init.GPIO_Pin = GPIO_Pin_4;	            //�˿�����
	stGpio_Init.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	stGpio_Init.GPIO_Speed = GPIO_Speed_50MHz;     //50M
	GPIO_Init(GPIOA, &stGpio_Init);				   //�����趨������ʼ��GPIOA 
}

/**************************************************************************
�������ܣ�LED��˸
��ڲ�������˸Ƶ�� 
����  ֵ����
**************************************************************************/
void led_flash(u16 u16Time)
{
	static s32 S32tTemp;
	if(0 == u16Time) 
		LED=0;
	else if(++S32tTemp == u16Time)	
		LED=~LED,S32tTemp=0;
}
