#ifndef _ADC_DMA_H
#define _ADC_DMA_H
#include "include_all.h"



void XBARA_ADC_DMA_Init();
void my_PIT_Init(pit_chnl_t channel, uint32_t us);
void Test_my_ADC();
void my_ADC_ETC_Init(ADC_ETC_Type *base,uint16_t ch,uint16_t chGroup,uint16_t triggerGroup,uint16_t chainGroup);
void my_ADC_Init(ADC_Type *base,uint8_t CH,uint32_t channelGroup,bool hardwareTrigger,bool enableDMA);
void my_DMA_Init(uint8_t DMA_channel, uint32_t srcAddr, uint32_t destAddr, uint32_t len);
void my_ADC_DMA_Init(ADC_Type *base,uint8_t DMA_channel, uint32_t *destAddr, uint32_t len);
uint16_t my_ADC_Read(ADC_Type *base,ADCn_Ch_e CH);
void my_ADCETC_DMA_Init(uint8_t DMA_channel, uint32_t *destAddr,uint32_t len);
void EDMA_Callback(edma_handle_t *handle, void *param,  bool transferDone, uint32_t tcds);
#endif