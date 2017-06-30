#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f10x.h" 
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

#define ADC_CH_NUM		3	//Ҫת����adcͨ����
#define N 				10 //ÿͨ����10��
	 
void adc_init(void);
void get_adc(int16_t *ad_data);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
