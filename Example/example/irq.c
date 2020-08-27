/*-------------------------------------------------------
��ƽ    ̨������i.MX RT1064���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2019��3��12��
��dev.env.��IAR8.30.1�����ϰ汾
��Target �� i.MX RT1064
��Crystal�� 24.000Mhz
��ARM PLL�� 1200MHz
��SYS PLL�� 600MHz
��USB PLL�� 480MHz
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
��ע   �⡿ �жϷ����� ��֪�����ֿ���ȥstartup_MIMXRT1064.s������
---------------------------------------------------------*/
#include "include_all.h"
#include "fsl_sdmmc_host.h"

extern void SDMMCHOST_CARD_DETECT_GPIO_INTERRUPT_HANDLER(void);
/*-----------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////����PIT�ж�����ʹ�øú���////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
------------------------------------------------------------------------------*/

/* ����PIT�жϲ��Ժ���ʹ�õı�־λ  */
extern volatile uint16_t pitIsrCnt0;
extern volatile uint16_t pitIsrCnt1;
extern volatile uint16_t pitIsrCnt2;
extern volatile uint16_t pitIsrCnt3;
uint8_t txt[20];

void LPUART1_IRQHandler(void)
{
	if((LPUART1->STAT) & kLPUART_RxDataRegFullFlag)         //�����ж�
	{
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART1));
	}
	__DSB();				                         //����ͬ������ָ��
}
void LPUART2_IRQHandler(void)
{
	if((LPUART2->STAT) & kLPUART_RxDataRegFullFlag)         //�����ж�
	{
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART2));
	}
	__DSB();				                         //����ͬ������ָ��
}
void LPUART5_IRQHandler(void)
{
	if((LPUART5->STAT) & kLPUART_RxDataRegFullFlag)         //�����ж�
	{
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART5));
	}
	__DSB();				                         //����ͬ������ָ��
}

/**
  * @brief    PIT�жϷ�����
  *
  * @param
  *
  * @return
  *
  * @note     ����PIT�ж�����ʹ�øú���
  *
  * @example
  *
  * @date     2019/6/4 ���ڶ�
  */
void PIT_IRQHandler(void)
{
    /* �ж�PITͨ��0�����ж�.*/
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_0)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        /* �����־λ.*/
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
        /*�û���������Ӵ���*/
        //pitIsrCnt0++;
    }

    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_1)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        /* �����־λ.*/
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
        /*�û���������Ӵ���*/
        pitIsrCnt1++;
    }

    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_2)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);

        /*�û���������Ӵ���*/
        pitIsrCnt2++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_3)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_3, kPIT_TimerFlag);

        /*�û���������Ӵ���*/
        pitIsrCnt3++;
    }
    __DSB();
}

void GPIO1_INT5_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 5))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 5);  //����жϱ�־λ
    }
}
void GPIO1_INT3_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 3))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 3);  //����жϱ�־λ
    }
}
void GPIO1_INT1_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 1))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 1);  //����жϱ�־λ
    }
}
void GPIO1_INT0_IRQHandler()
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 0))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 0);  //����жϱ�־λ
    }
}



void GPIO1_Combined_0_15_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 1))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 1);  //����жϱ�־λ
    }

    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 13))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 13);  //����жϱ�־λ
    }


    __DSB();				                            //����ͬ������ָ��
}


void GPIO1_Combined_16_31_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 20))     //�ж��Ƿ�ΪGPIO1_20�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 20);  //����жϱ�־λ
    }
    if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 29))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 29);  //����жϱ�־λ
    }
        if(GPIO_GetPinsInterruptFlags(GPIO1)&(1 << 23))     //�ж��Ƿ�ΪGPIO1_29�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO1, 1U << 23);  //����жϱ�־λ
    }
    __DSB();				                            //����ͬ������ָ��
}

void GPIO2_Combined_16_31_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO2)&(1 << 22))     //�ж��Ƿ�ΪGPIO2_27�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO2, 1U << 22);  //����жϱ�־λ
    }

    if(GPIO_GetPinsInterruptFlags(GPIO2)&(1 << 30))     //�ж��Ƿ�ΪGPIO2_30�ж�
    {
        /* �û����� */
        GPIO_PortClearInterruptFlags(GPIO2, 1U << 30);  //����жϱ�־λ
    }
    __DSB();				                            //����ͬ������ָ��
}
void GPIO3_Combined_0_15_IRQHandler(void)
{
    if(GPIO_GetPinsInterruptFlags(GPIO3)&(1 << 4))     //�ж��Ƿ�ΪGPIO3_4�ж�
    {
        /* �û����� */
        LED_ColorReverse(blue);
    }
    GPIO_PortClearInterruptFlags(GPIO3, 1U << 4);      //����жϱ�־λ

    __DSB();				                           //����ͬ������ָ��
}

void GPT1_IRQHandler()
{
    GPT_ClearStatusFlags(GPT1, kGPT_OutputCompare1Flag);
    __DSB();				                           //����ͬ������ָ��

}

void GPT2_IRQHandler()
{
    GPT_ClearStatusFlags(GPT2, kGPT_OutputCompare1Flag);
    LED_ColorReverse(red);
    __DSB();				                           //����ͬ������ָ��

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