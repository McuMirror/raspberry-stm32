/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : adc.c
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : adc module fucntions
  Function List :
              adc_init
              get_adc
              get_battery_volt
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#include "adc.h"

/**************************************************************************
�������ܣ�ACD��ʼ����ص�ѹ���
��ڲ�������
����  ֵ����
**************************************************************************/
void  adc_init(void)
{    
 	ADC_InitTypeDef stAdc_Init; 
	GPIO_InitTypeDef stGpio_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	//����ģ��ͨ����������                         
	stGpio_Init.GPIO_Pin = GPIO_Pin_6;
	stGpio_Init.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &stGpio_Init);	
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	stAdc_Init.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	stAdc_Init.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	stAdc_Init.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	stAdc_Init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	stAdc_Init.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	stAdc_Init.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &stAdc_Init);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
}		

/**************************************************************************
�������ܣ�AD����
��ڲ�����ADC1 ��ͨ��
����  ֵ��ADת�����
**************************************************************************/
u16 get_adc(u8 ch)   
{
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


/**************************************************************************
�������ܣ���ȡ��ص�ѹ 
��ڲ�������
����  ֵ����ص�ѹ ��λMV
**************************************************************************/
int get_battery_volt(void)   
{  
	int Volt;//��ص�ѹ
	Volt=get_adc(Battery_Ch)*3.3*11*100/4096;	//�����ѹ���������ԭ��ͼ�򵥷������Եõ�	
	return Volt;
}



