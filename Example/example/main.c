//git test
//git test branches
/*------------------------------------------------------
LED灯
GPIO2_IO23  -------->  管脚B12   ----- >  核心板G灯
GPIO3_IO26  -------->  管脚A7    ----- >  核心板R灯
GPIO3_IO27  -------->  管脚C7    ----- >  核心板B灯

---------------------------------------------------------
按键

GPIO3_IO04 ------ 管脚D7   ----- >  母板按键K0
GPIO2_IO27 ------ 管脚D8  ----- >  母板按键K1
GPIO2_IO30 ------ 管脚D9  ----- >  母板按键k2
---------------------------------------------------------
串口
LPUART5_RX ------ 管脚D14
LPUART5_TX ------ 管脚D13
G
5V
---------------------------------------------------------
OLED
LCD_DC	   ------ 管脚E11
LCD_RST    ------ 管脚E12
LCD_SDA    ------ 管脚D12
LCD_SCL    ------ 管脚D11
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
电机
PWM1, kPWM_Module_3, kPWM_PwmA   L5     电机1接口   1
PWM1, kPWM_Module_3, kPWM_PwmB   M5     电机1接口
PWM2, kPWM_Module_0, kPWM_PwmA   A8     电机2接口
PWM2, kPWM_Module_0, kPWM_PwmB   A9     电机2接口
PWM2, kPWM_Module_1, kPWM_PwmA   B9     电机3接口
PWM2, kPWM_Module_1, kPWM_PwmB   C9     电机3接口
PWM2, kPWM_Module_2, kPWM_PwmB   A10    电机4接口
PWM1, kPWM_Module_1, kPWM_PwmA   J1     电机4接口
----------------------------------------------------------
编码器（ENC）
G13--A相或者LSB
F14--B相或者DIR

H2--A相或者LSB
J2--B相或者DIR

J3--A相或者LSB
K1--B相或者DIR

C11--A相或者LSB
B11--B相或者DIR
----------------------------------------------------------
IIC
SCL  ---  J11
SDA  ---  K11
----------------------------------------------------------
外部16MB flash
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

/* 中断优先级组 */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04
#define NVIC_Group4   0x03


/**
  * @brief    不精确延时
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @example  delayms(100);
  *
  * @date     2019/4/22 星期一
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
    BOARD_ConfigMPU();            /* 初始化内存保护单元 */
    BOARD_BootClockRUN();         /* 初始化开发板时钟   */
    BOARD_InitPins();             /* 串口管脚初始化     */
    BOARD_InitDebugConsole();     /* 初始化串口         */

	/*设置中断优先级组  0: 0个抢占优先级16位个子优先级
     *1: 2个抢占优先级 8个子优先级 2: 4个抢占优先级 4个子优先级
     *3: 8个抢占优先级 2个子优先级 4: 16个抢占优先级 0个子优先级
     */
    /* 配置优先级组 2: 4个抢占优先级 4个子优先级 */
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
