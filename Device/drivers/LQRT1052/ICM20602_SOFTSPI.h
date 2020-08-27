#ifndef __ICM20602_SOFTSPI_H
#define __ICM20602_SOFTSPI_H

#include "LQ_GPIO_Cfg.h"
#include "fsl_common.h"
#include "LQ_GPIO.h"

/* 注意 ICM20602 时钟空闲时为高电平  在时钟第二个跳边沿传输数据  与NRF2401的不同，所以SPI不通用  */
/* 0: 时钟空闲时刻为低电平   1：时钟空闲时刻为高电平*/
#define CPOL  1

/* 0：时钟第一个跳边沿传输数据   1：时钟的第二个跳边沿传输数据 */
#define CPHA  1


// #define SOFT_SPI_SCK_PIN    DIR2_22
// #define SOFT_SPI_MISO_PIN   DIR1_4
// #define SOFT_SPI_MOSI_PIN   DIR2_25
// #define SOFT_SPI_CS_PIN     DIR2_24

// #define SOFT_SPI_SCK_PIN    DIR1_17       //K11 SCL
// #define SOFT_SPI_MISO_PIN   DIR1_26     //L13 SA
// #define SOFT_SPI_MOSI_PIN   DIR2_30     //C14 SDA
// #define SOFT_SPI_CS_PIN     DIR1_6     //E14  CS

#define SOFT_SPI_SCK_PIN    DIR1_27       //J13 SCL
#define SOFT_SPI_MISO_PIN   DIR1_17     //K11 SA
#define SOFT_SPI_MOSI_PIN   DIR1_25     //M13SDA
#define SOFT_SPI_CS_PIN     DIR1_20     //L12  CS

#if CPOL
#define SPI_SCK_IDLE      PT1_27 = 1
#define SPI_SCK_ACTIVE    PT1_27 = 0
#else
#define SPI_SCK_IDLE      PT1_17 = 0
#define SPI_SCK_ACTIVE    PT1_17 = 1
#endif

#define SPI_MOSI_OUT      PT1_25
#define SPI_MISO_IN       PT1_17
#define SPI_CS_OUT        PT1_20


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
void SPI_SoftInit(void);

/**
  * @brief    模拟SPI读写n 字节
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
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len);

#endif
