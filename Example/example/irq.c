/*-------------------------------------------------------
【平    台】龙邱i.MX RT1064核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2019年3月12日
【dev.env.】IAR8.30.1及以上版本
【Target 】 i.MX RT1064
【Crystal】 24.000Mhz
【ARM PLL】 1200MHz
【SYS PLL】 600MHz
【USB PLL】 480MHz
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【注   意】 中断服务函数 不知道名字可以去startup_MIMXRT1064.s里面找
---------------------------------------------------------*/
#include "include_all.h"
#include "fsl_sdmmc_host.h"

extern void SDMMCHOST_CARD_DETECT_GPIO_INTERRUPT_HANDLER(void);
/*-----------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////测试PIT中断例程使用该函数////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
------------------------------------------------------------------------------*/

/* 声明PIT中断测试函数使用的标志位  */
extern volatile uint16_t pitIsrCnt0;
extern volatile uint16_t pitIsrCnt1;
extern volatile uint16_t pitIsrCnt2;
extern volatile uint16_t pitIsrCnt3;
uint8_t txt[20];

void LPUART1_IRQHandler(void)
{
	if((LPUART1->STAT) & kLPUART_RxDataRegFullFlag)         //接收中断
	{
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART1));
	}
	__DSB();				                         //数据同步屏蔽指令
}
void LPUART2_IRQHandler(void)
{
	if((LPUART2->STAT) & kLPUART_RxDataRegFullFlag)         //接收中断
	{
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART2));
	}
	__DSB();				                         //数据同步屏蔽指令
}
void LPUART5_IRQHandler(void)
{
	if((LPUART5->STAT) & kLPUART_RxDataRegFullFlag)         //接收中断
	{
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART5));
	}
	__DSB();				                         //数据同步屏蔽指令
}

/**
  * @brief    PIT中断服务函数
  *
  * @param
  *
  * @return
  *
  * @note     测试PIT中断例程使用该函数
  *
  * @example
  *
  * @date     2019/6/4 星期二
  */
void PIT_IRQHandler(void)
{
    /* 判断PIT通道0发生中断.*/
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_0)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        /* 清除标志位.*/
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
        /*用户可自行添加代码*/
        //pitIsrCnt0++;
    }

    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_1)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        /* 清除标志位.*/
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
        /*用户可自行添加代码*/
        pitIsrCnt1++;
    }

    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_2)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);

        /*用户可自行添加代码*/
        pitIsrCnt2++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_3)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_3, kPIT_TimerFlag);

        /*用户可自行添加代码*/
        pitIsrCnt3++;
    }
    __DSB();
}

void GPIO1_INT5_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 5))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 5);  //清除中断标志位
    }
}
void GPIO1_INT3_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 3))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 3);  //清除中断标志位
    }
}
void GPIO1_INT1_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 1))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 1);  //清除中断标志位
    }
}
void GPIO1_INT0_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 0))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 0);  //清除中断标志位
    }
}



void GPIO1_Combined_0_15_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 1))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 1);  //清除中断标志位
    }

    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 13))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 13);  //清除中断标志位
    }


    __DSB();				                            //数据同步屏蔽指令
}


void GPIO1_Combined_16_31_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 20))     //判断是否为GPIO1_20中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 20);  //清除中断标志位
    }
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 29))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 29);  //清除中断标志位
    }
        if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 23))     //判断是否为GPIO1_29中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 23);  //清除中断标志位
    }
    __DSB();				                            //数据同步屏蔽指令
}

void GPIO2_Combined_16_31_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO2)&(1 << 22))     //判断是否为GPIO2_27中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO2, 1U << 22);  //清除中断标志位
    }

    if(GPIO_GetPinsInterruptFlags(GPIO2)&(1 << 30))     //判断是否为GPIO2_30中断
    {
        /* 用户代码 */
        GPIO_PortClearInterruptFlags(GPIO2, 1U << 30);  //清除中断标志位
    }
    __DSB();				                            //数据同步屏蔽指令
}
void GPIO3_Combined_0_15_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO3)&(1 << 4))     //判断是否为GPIO3_4中断
    {
        /* 用户代码 */
        LED_ColorReverse(blue);
    }
    GPIO_PortClearInterruptFlags(GPIO3, 1U << 4);      //清除中断标志位

    __DSB();				                           //数据同步屏蔽指令
}

void GPT1_IRQHandler()
{
    GPT_ClearStatusFlags(GPT1, kGPT_OutputCompare1Flag);
    __DSB();				                           //数据同步屏蔽指令

}

void GPT2_IRQHandler()
{
    GPT_ClearStatusFlags(GPT2, kGPT_OutputCompare1Flag);
    LED_ColorReverse(red);
    __DSB();				                           //数据同步屏蔽指令

}

void ADC_ETC_IRQ0_IRQHandler()
{
    uint32_t result;
    uint8_t txt[20];
    volatile static uint32_t cnt=0;
    cnt++;

    ADC_ETC_ClearInterruptStatusFlags(ADC_ETC,(adc_etc_external_trigger_source_t)3,kADC_ETC_Done0StatusFlagMask);

    result=ADC_ETC_GetADCConversionValue(ADC_ETC,3, 0U);
    if(cnt%4==0)
    EDMA_EnableChannelRequest(DMA0,0);
    sprintf(txt," %d ",result);
    LCD_P6x8Str(1,5,txt);
}