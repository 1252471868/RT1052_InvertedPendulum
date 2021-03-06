

/*  如果不知道自己需要包涵哪个头文件 可以直接包涵本头文件 */
/*  缺点，编译速度巨慢  最好就是自己使用了哪一个头文件 包涵对应的 */


#ifndef __INCLUDE_ALL_H
#define __INCLUDE_ALL_H

#include "stdio.h"
#include "math.h"
#include "stdlib.h"


#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "include.h"
#include "board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_adc.h"
#include "fsl_adc_etc.h"
#include "fsl_cache.h"
#include "fsl_camera.h"
#include "fsl_camera_device.h"
#include "fsl_camera_receiver.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_csi.h"
#include "fsl_csi_camera_adapter.h"
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#include "fsl_enc.h"
#include "fsl_flexspi.h"
#include "fsl_gpio.h"
#include "fsl_gpt.h"
#include "fsl_iomuxc.h"
#include "fsl_lpi2c.h"
#include "fsl_lpspi.h"
#include "fsl_lpuart.h"
#include "fsl_lpuart_edma.h"
#include "fsl_pit.h"
#include "fsl_pwm.h"
#include "fsl_qtmr.h"
#include "fsl_rtwdog.h"
#include "fsl_sccb.h"
#include "fsl_tempmon.h"
#include "fsl_trng.h"
#include "fsl_usdhc.h"
#include "fsl_video_common.h"
#include "fsl_wdog.h"
#include "fsl_xbara.h"
#include "fsl_xbarb.h"

#include "LQ_GPIO.h"
#include "ANO_DT.h"
#include "ICM20602_SOFTSPI.h"
#include "LQ_12864.h"
#include "LQ_ADC.h"
#include "LQ_Encoder.h"
#include "LQ_FLASH.h"
#include "LQ_GPIO_Cfg.h"
#include "LQ_GPT.h"
#include "LQ_ICM20602.h"
#include "LQ_IIC.h"
#include "LQ_KEY.h"
#include "LQ_LED.h"
#include "LQ_PIT.h"
#include "LQ_PWM.h"
#include "LQ_QTMR.h"
#include "LQ_Rtwdog.h"
#include "LQ_SDCard.h"
#include "LQ_SOFTIIC.h"
#include "LQ_SPI.h"
#include "LQ_SYSTICK.h"
#include "LQ_Tempmon.h"
#include "LQ_TRNG.h"
#include "LQ_UART.h"
#include "LQ_UART_DMA.h"
#include "LQ_W25Q128.h"
#include "LQ_WDog.h"


#include "include.h"
#include "ADC_DMA.h"
#include "GP2Y0A.h"
#endif
