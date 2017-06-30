/******************************************************************************
  File			: dma.c
  Description	: dma test
  Author		: Xiaoming Li
*******************************************************************************
  Modify List:
-------------------------------------------------------------------------------
  2014/8/16 21:00 PM	| Created
******************************************************************************/

#include "DMA.h"

u16 DMA1_MEN_LEN;

/*-------------------------------------------------------------------
 * FUNC : DMA_Config
 * DESC : DMA_Configrate
 * PARM : DMA_CHx - DMA channle
 *		  paddr	  - peripheral address
 *	      saddr   - store address
 *   	  trscnt  - transfer count
 * RET	: N/A
 *-----------------------------------------------------------------*/
void DMA_Config(DMA_Channel_TypeDef *DMA_CHx, u32 paddr, u32 saddr, u16 trscnt)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA_CHx);
	DMA1_MEN_LEN = trscnt;
	DMA_InitStruct.DMA_PeripheralBaseAddr = paddr;	//DMA����ADC����ַ
	DMA_InitStruct.DMA_MemoryBaseAddr = saddr;	//DMA�ڴ����ַ
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;	//�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStruct.DMA_BufferSize = trscnt;	//DMAͨ����DMA����Ĵ�С
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��Ϊ16λ
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;	//������ѭ������ģʽ
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;//DMAͨ�� xӵ�и����ȼ�
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;	//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStruct);
}

/*-------------------------------------------------------------------
 * FUNC : DMA_Enable
 * DESC : DMA_Enable
 * PARM : DMA_CHx - DMA channle
 * RET	: N/A
 *-----------------------------------------------------------------*/
void DMA_Enable(DMA_Channel_TypeDef *DMA_CHx)
{
	DMA_Cmd(DMA_CHx, DISABLE);
	DMA_SetCurrDataCounter(DMA_CHx, DMA1_MEN_LEN);
	DMA_Cmd(DMA_CHx, ENABLE);
}
