#include "LQ_GPIO_Cfg.h"
#include "ICM20602_SOFTSPI.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
/**
  * @brief    模拟SPI 延时函数
  *
  * @param
  *
  * @return
  *
  * @note
  *
  * @example
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftDelay(void)
{
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
}


/**
  * @brief    模拟SPI初始化
  *
  * @param
  *
  * @return
  *
  * @note
  *
  * @example
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftInit(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);          // IO口时钟使能

    // LQ_PinInit(K11,PIN_MODE_OUTPUT,0);
    // LQ_PinInit(L13,PIN_MODE_INPUT,0);
    // LQ_PinInit(C14,PIN_MODE_OUTPUT,0);
    // LQ_PinInit(E14,PIN_MODE_OUTPUT,0);
    // SOFT_SPI_SCK_PIN = 1;
    // SOFT_SPI_MISO_PIN = 0;
    // SOFT_SPI_MOSI_PIN = 1;
    // SOFT_SPI_CS_PIN = 1;

    LQ_PinInit(J13,PIN_MODE_OUTPUT,0);
    LQ_PinInit(K11,PIN_MODE_INPUT,0);
    LQ_PinInit(M13,PIN_MODE_OUTPUT,0);
    LQ_PinInit(L12,PIN_MODE_OUTPUT,0);
    SOFT_SPI_SCK_PIN = 1;
    SOFT_SPI_MISO_PIN = 0;
    SOFT_SPI_MOSI_PIN = 1;
    SOFT_SPI_CS_PIN = 1;

    //IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,1U);   //管脚F11 MISO
    // IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26,1U);

    SPI_SCK_IDLE;

}

/**
  * @brief    模拟SPI读写n 字节
  *
  * @param    buff[] 存放要写入的值 写入后存放读取的值
  *
  * @return
  *
  * @note
  *
  * @example
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len)
{
    SPI_CS_OUT = 0;
    SPI_SCK_IDLE;
//    SPI_SoftDelay();
#if CPHA    //第二个时钟跳边沿
    do
    {
        for(uint8_t i = 0; i < 8; i++)
        {
            SPI_MOSI_OUT = ((*buff) >= 0x80);
            SPI_SCK_ACTIVE;
            (*buff) = (*buff)<<1;

//            SPI_SoftDelay();
            SPI_SCK_IDLE;
//            SPI_SoftDelay();
            (*buff) |= SPI_MISO_IN;
        }
        buff++;
    }while(--len);
#else
    do
    {
        for(uint8_t i = 0; i < 8; i++)
        {

            SPI_MOSI_OUT = ((*buff) >= 0x80);
            (*buff) = (*buff)<<1;
            SPI_SCK_ACTIVE;
            SPI_SoftDelay();
            (*buff) |= SPI_MISO_IN;
            SPI_SCK_IDLE;
            SPI_SoftDelay();
        }
        buff++;
    }while(--len);


#endif
    SPI_SCK_IDLE;
    SPI_CS_OUT = 1;

}
