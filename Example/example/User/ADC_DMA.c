#include "ADC_DMA.h"

#define XBARA_INPUT_PITCH2 kXBARA1_InputPitTrigger2
#define XBARA_OUTPUT_ADC_ETC  kXBARA1_OutputAdcEtcXbar0Trig3


void my_ADC_Init(ADC_Type *base,uint8_t CH,uint32_t channelGroup,bool hardwareTrigger,bool enableDMA)
{
    ADC_PinInit(base, CH);

    adc_config_t adcConfigStruct;
    adc_channel_config_t adcChannelConfigStruct;


    ADC_GetDefaultConfig(&adcConfigStruct);
    adcConfigStruct.resolution=kADC_Resolution12Bit;    //采样率12位
    adcConfigStruct.enableHighSpeed= true;                     //高速模式

    ADC_Init(base, &adcConfigStruct);
    if(hardwareTrigger)
    ADC_EnableHardwareTrigger(base,true);       //使能硬件触发
     /* 传输通道 */
    adcChannelConfigStruct.channelNumber = CH;
    /* 关转换完成中断 */
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;
    ADC_SetChannelConfig(base, channelGroup, &adcChannelConfigStruct);
    /* 硬件平均 */
    ADC_SetHardwareAverageConfig(base, kADC_HardwareAverageCount32);
    /* 硬件校准 */
    ADC_DoAutoCalibration(base);
    if(enableDMA)
    ADC_EnableDMA(base,true);
}

uint16_t my_ADC_Read(ADC_Type *base,ADCn_Ch_e CH)
{

    adc_channel_config_t adcChannelConfigStruct;

    /* 传输通道 */
    adcChannelConfigStruct.channelNumber = CH;

    /* 关转换完成中断 */
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;

    /* 开始传输 */
    ADC_SetChannelConfig(base, 0, &adcChannelConfigStruct);

    /* 等待转换完成 */
    while (0U == ADC_GetChannelStatusFlags(base,0)){;}

    /* 返回转换结果 */
    return (ADC_GetChannelConversionValue(base,0));

}

void my_ADC_ETC_Init(ADC_ETC_Type *base,uint16_t ch,uint16_t chGroup,uint16_t triggerGroup,uint16_t chainGroup)
{
    adc_etc_config_t adcETCConfigStruct;
    adc_etc_trigger_config_t adcETCTriggerConfigStruct;
    adc_etc_trigger_chain_config_t adcETCTriggerChainConfigStruct;
    ADC_ETC_GetDefaultConfig(&adcETCConfigStruct);
    adcETCConfigStruct.enableTSCBypass=false;
    adcETCConfigStruct.XBARtriggerMask=1<<triggerGroup;
    //adcETCConfigStruct.dmaMode= true;
    ADC_ETC_Init(base,&adcETCConfigStruct);

    adcETCTriggerConfigStruct.enableSyncMode=false;
    adcETCTriggerConfigStruct.triggerChainLength=0;
    adcETCTriggerConfigStruct.enableSWTriggerMode=false;
    adcETCTriggerConfigStruct.triggerPriority=0;
    adcETCTriggerConfigStruct.initialDelay=0;
    adcETCTriggerConfigStruct.sampleIntervalDelay=0;
    ADC_ETC_SetTriggerConfig(base,triggerGroup,&adcETCTriggerConfigStruct);

    adcETCTriggerChainConfigStruct.ADCChannelSelect=ch;
    adcETCTriggerChainConfigStruct.enableB2BMode=true;
    adcETCTriggerChainConfigStruct.InterruptEnable=kADC_ETC_Done0InterruptEnable;
    adcETCTriggerChainConfigStruct.ADCHCRegisterSelect=1<<chainGroup;

    ADC_ETC_SetTriggerChainConfig(base,triggerGroup,chainGroup,&adcETCTriggerChainConfigStruct);

    ADC_ETC_EnableDMA(base,triggerGroup);
    NVIC_SetPriority(ADC_ETC_IRQ0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3,3));
    EnableIRQ(ADC_ETC_IRQ0_IRQn);

}



void my_PIT_Init(pit_chnl_t channel, uint32_t us)
{
    static uint8_t pit_count = 0;
    /* 防止PIT多次初始化 */
    if(pit_count == 0)
    {
        pit_count++;
        /* PIT初始化结构体 */
        pit_config_t pitConfig;
        /*
        * pitConfig.enableRunInDebug = false;
        */
        PIT_GetDefaultConfig(&pitConfig);   //获取默认参数
        pitConfig.enableRunInDebug = false;
        PIT_Init(PIT, &pitConfig);          //初始化PIT

    }
    /* 设置PIT通道和定时时间 PIT默认使用IPG时钟的二分频 75M时钟 */
    PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(us, CLOCK_GetFreq(kCLOCK_IpgClk)/2));
    //开启定时器
    PIT_StartTimer(PIT, channel);
}

void XBARA_ADC_DMA_Init()
{
    XBARA_Init(XBARA1);
    XBARA_SetSignalsConnection(XBARA1,XBARA_INPUT_PITCH2,XBARA_OUTPUT_ADC_ETC);
}
void Test_my_ADC()
{

    my_ADC_Init(ADC1,16,0,true,false);
    my_ADC_ETC_Init(ADC_ETC,0,0,3,0);
    XBARA_ADC_DMA_Init();
    my_PIT_Init(kPIT_Chnl_2,500000);
}






edma_handle_t   g_EDMA_handle;
bool g_Transfer_Done = false;
void EDMA_Callback(edma_handle_t *handle, void *param,  bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done = true;
    }

}
void my_DMA_Init(uint8_t DMA_channel, uint32_t srcAddr, uint32_t destAddr, uint32_t len)
{
    DMAMUX_Init(DMAMUX);
    DMAMUX_EnableAlwaysOn(DMAMUX,DMA_channel,true);
    DMAMUX_EnableChannel(DMAMUX,DMA_channel);

    edma_config_t  user_config;
    EDMA_GetDefaultConfig(&user_config);
    EDMA_Init(DMA0,&user_config);

    edma_transfer_config_t transfer_config;
    transfer_config.srcAddr = (uint32_t)srcAddr;  //源地址
    transfer_config.srcOffset = 1;                //源地址偏移
    transfer_config.srcTransferSize = kEDMA_TransferSize1Bytes;//源数据宽度

    transfer_config.destAddr = (uint32_t)destAddr;//目的地址
    transfer_config.destOffset = 1;               //目的地址偏移
    transfer_config.destTransferSize = kEDMA_TransferSize1Bytes;//目的数据宽度

    transfer_config.minorLoopBytes=1;
    transfer_config.majorLoopCounts=len;

    /*创建eDMA句柄*/
    EDMA_CreateHandle(&g_EDMA_handle,DMA0, DMA_channel);
/*设置传输完成回调函数*/
    EDMA_SetCallback(&g_EDMA_handle, EDMA_Callback, NULL);
/*提交eDAM传输请求*/
    EDMA_SubmitTransfer(&g_EDMA_handle, &transfer_config);
/*启动传输*/
    EDMA_StartTransfer(&g_EDMA_handle);
}

void my_ADC_DMA_Init(ADC_Type *base,uint8_t DMA_channel, uint32_t *destAddr, uint32_t len)
{

    my_ADC_Init(base,0,0,false,true);
    my_PIT_Init(kPIT_Chnl_0,50);

    DMAMUX_Init(DMAMUX);
    // DMAMUX_EnableAlwaysOn(DMAMUX,DMA_channel,true);

    DMAMUX_SetSource(DMAMUX,DMA_channel,kDmaRequestMuxADC1);
    DMAMUX_EnablePeriodTrigger(DMAMUX,DMA_channel);
    DMAMUX_EnableChannel(DMAMUX,DMA_channel);

    edma_config_t  user_config;
    EDMA_GetDefaultConfig(&user_config);
    // user_config.enableContinuousLinkMode=true;
    EDMA_Init(DMA0,&user_config);

    edma_transfer_config_t transfer_config;


    /*创建eDMA句柄*/
    EDMA_CreateHandle(&g_EDMA_handle,DMA0, DMA_channel);
/*设置传输完成回调函数*/
    EDMA_SetCallback(&g_EDMA_handle, EDMA_Callback, NULL);

    EDMA_PrepareTransfer(&transfer_config,\
                                            (uint32_t *)&base->R[0],
                                            sizeof(uint32_t),\
                                            destAddr,\
                                            sizeof(uint32_t),\
                                            4,\
                                            16,\
                                            kEDMA_PeripheralToMemory);
    // EDMA_PrepareTransferConfig(&transfer_config, (void *) &base->R[0], 4U, 0, (void *) destAddr, 1U, 4, 4U, 4U);
/*提交eDAM传输请求*/
    EDMA_SubmitTransfer(&g_EDMA_handle, &transfer_config);
/*启动传输*/
    EDMA_StartTransfer(&g_EDMA_handle);

}

void my_ADCETC_DMA_Init(uint8_t DMA_channel, uint32_t *destAddr,uint32_t len)
{
    DMAMUX_Init(DMAMUX);
    DMAMUX_SetSource(DMAMUX,DMA_channel,kDmaRequestMuxADC_ETC);
    DMAMUX_EnableChannel(DMAMUX,DMA_channel);

    edma_config_t  user_config;
    EDMA_GetDefaultConfig(&user_config);
    EDMA_Init(DMA0,&user_config);

    edma_transfer_config_t transfer_config;

    /*创建eDMA句柄*/
    EDMA_CreateHandle(&g_EDMA_handle,DMA0, DMA_channel);
/*设置传输完成回调函数*/
    EDMA_SetCallback(&g_EDMA_handle, EDMA_Callback, NULL);

    EDMA_PrepareTransfer(&transfer_config,\
                                            (uint32_t *)&ADC_ETC->TRIG[3].TRIGn_RESULT_1_0,
                                            sizeof(uint32_t),\
                                            destAddr,\
                                            sizeof(uint32_t),\
                                            4,\
                                            len,\
                                            kEDMA_PeripheralToMemory);
    // EDMA_PrepareTransferConfig(&transfer_config, (void *) &base->R[0], 4U, 0, (void *) destAddr, 1U, 4, 4U, 4U);
/*提交eDAM传输请求*/
    EDMA_SubmitTransfer(&g_EDMA_handle, &transfer_config);
/*目标位置最终调整*/
    DMA0->TCD[0].DLAST_SGA=-len;
/*启动传输*/
    my_PIT_Init(kPIT_Chnl_2,500000);
}