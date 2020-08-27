//git test
//git test branches
/*------------------------------------------------------
LED��
GPIO2_IO23  -------->  �ܽ�B12   ----- >  ���İ�G��
GPIO3_IO26  -------->  �ܽ�A7    ----- >  ���İ�R��
GPIO3_IO27  -------->  �ܽ�C7    ----- >  ���İ�B��

---------------------------------------------------------
����

GPIO3_IO04 ------ �ܽ�D7   ----- >  ĸ�尴��K0
GPIO2_IO27 ------ �ܽ�D8  ----- >  ĸ�尴��K1
GPIO2_IO30 ------ �ܽ�D9  ----- >  ĸ�尴��k2
---------------------------------------------------------
����
LPUART5_RX ------ �ܽ�D14
LPUART5_TX ------ �ܽ�D13
G
5V
---------------------------------------------------------
OLED
LCD_DC	   ------ �ܽ�E11
LCD_RST    ------ �ܽ�E12
LCD_SDA    ------ �ܽ�D12
LCD_SCL    ------ �ܽ�D11
----------------------------------------------------------
---------------------------------------------------------
ADC
ADC1_CH2        L14
ADC1_CH8        M12
ADC1_CH3        G12
ADC2_CH2        H11
ADC2_CH1        H12
ADC2_CH1        K14
ADC2_CH3        H14
---------------------------------------------------------
PWM
���
PWM1, kPWM_Module_3, kPWM_PwmA   L5     ���1�ӿ�   1
PWM1, kPWM_Module_3, kPWM_PwmB   M5     ���1�ӿ�
PWM2, kPWM_Module_0, kPWM_PwmA   A8     ���2�ӿ�
PWM2, kPWM_Module_0, kPWM_PwmB   A9     ���2�ӿ�
PWM2, kPWM_Module_1, kPWM_PwmA   B9     ���3�ӿ�
PWM2, kPWM_Module_1, kPWM_PwmB   C9     ���3�ӿ�
PWM2, kPWM_Module_2, kPWM_PwmB   A10    ���4�ӿ�
PWM1, kPWM_Module_1, kPWM_PwmA   J1     ���4�ӿ�
----------------------------------------------------------
��������ENC��
G13--A�����LSB
F14--B�����DIR

H2--A�����LSB
J2--B�����DIR

J3--A�����LSB
K1--B�����DIR

C11--A�����LSB
B11--B�����DIR
----------------------------------------------------------
IIC
SCL  ---  J11
SDA  ---  K11
----------------------------------------------------------
�ⲿ16MB flash
QSPI_DQS --  N3
QSPI_SS0 --  L3
QSPI_CLK --  L4
QSPI_D0  --  P3
QSPI_D1  --  N4
QSPI_D2  --  P4
QSPI_D3  --  P5
----------------------------------------------------------
ULTRASONIC

--------------------------------------------------------*/

#include "include_all.h"

/* �ж����ȼ��� */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04
#define NVIC_Group4   0x03


/**
  * @brief    ����ȷ��ʱ
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @example  delayms(100);
  *
  * @date     2019/4/22 ����һ
*/
void delayms(uint16_t ms)
{
	volatile uint32_t i = 0;
	while(ms--)
	{
		for (i = 0; i < 20000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}
}


void IRQHandler_Init();

/*!
 * @brief Main function
 */

extern bool g_Transfer_Done;

int main(void)
{
    BOARD_ConfigMPU();            /* ��ʼ���ڴ汣����Ԫ */
    BOARD_BootClockRUN();         /* ��ʼ��������ʱ��   */
    BOARD_InitPins();             /* ���ڹܽų�ʼ��     */
    BOARD_InitDebugConsole();     /* ��ʼ������         */

	/*�����ж����ȼ���  0: 0����ռ���ȼ�16λ�������ȼ�
     *1: 2����ռ���ȼ� 8�������ȼ� 2: 4����ռ���ȼ� 4�������ȼ�
     *3: 8����ռ���ȼ� 2�������ȼ� 4: 16����ռ���ȼ� 0�������ȼ�
     */
    /* �������ȼ��� 2: 4����ռ���ȼ� 4�������ȼ� */
    NVIC_SetPriorityGrouping(NVIC_Group2);
/*------------------------------------systime-----------------------------*/
    systime.init();
/*-----------------------------------LED----------------------------------*/
    LED_Init();
    LED_Color(cyan);
/*------------------------------------KEY-------------------------------*/
    KEY_Init();
/*------------------------------------OLED-----------------------------------*/
    LCD_Init();
    LCD_P6x8Str(0,0,"success");
/*-----------------------------------UART------------------------------------*/
    // LQ_UART_DMA_Init(LPUART1, 31250, 0, 1);
    LQ_UART_Init(LPUART1,115200);
    uint8_t txt[20],note[3]={0x90,0,0};
    uint32_t srcData[4]={1,2,3,4},destData[4]={0},cnt=0;
    uint32_t result;
    // my_ADC_Init(ADC1,16,0,true,false);
    // my_ADC_ETC_Init(ADC_ETC,0,0,3,0);
    // XBARA_ADC_DMA_Init();
    // my_ADCETC_DMA_Init(ADC1,0,destData);
    GP2Y0A_Init();
    while(1)
    {
        // if(g_Transfer_Done==true)
        // {
        //     cnt++;
        //     g_Transfer_Done=false;
        //     for(int i=0;i<4;i++)
        //     {
        //         srcData[i]++;
        //         sprintf(txt,"%d",destData[i]);
        //         LCD_P6x8Str(0,i,txt);
        //     }

        // }
        for(int i=0;i<128;i++)
        {
            note[1]=i;
            note[2]=0x45;
            sprintf(txt," %d ",note[1]);
            LCD_P6x8Str(0,0,txt);
            UART_PutBuff(LPUART1,note,3);
            systime.delay_ms(200);
            note[2]=0x00;
            UART_PutBuff(LPUART1,note,3);
            systime.delay_ms(200);
        }
    }
}

void IRQHandler_Init()
{

}
