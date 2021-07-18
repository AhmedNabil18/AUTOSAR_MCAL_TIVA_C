 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi_PBCfg.c
 *
 * Description: Source file for Spi Module Post Build Configurations.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/
 
#include "Spi.h"
#include "Spi_Symbols.h"

/*
 * Module Version 1.0.0
 */
#define SPI_PBCFG_SW_MAJOR_VERSION              (1U)
#define SPI_PBCFG_SW_MINOR_VERSION              (0U)
#define SPI_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define SPI_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define SPI_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define SPI_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between SPI_PBcfg.c and SPI.h files */
#if ((SPI_PBCFG_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
 ||  (SPI_PBCFG_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
 ||  (SPI_PBCFG_AR_RELEASE_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the AR version of SPI.h"
#endif

/* Software Version checking between SPI_PBcfg.c and SPI.h files */
#if ((SPI_PBCFG_SW_MAJOR_VERSION != SPI_SW_MAJOR_VERSION)\
 ||  (SPI_PBCFG_SW_MINOR_VERSION != SPI_SW_MINOR_VERSION)\
 ||  (SPI_PBCFG_SW_PATCH_VERSION != SPI_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the SW version of SPI.h"
#endif

/* Notification Functions Externs */

/* HW Configurations */
const Spi_HWUnitConfigType  HWUnits_Configs[SPI_MAX_HW_UNITS]=
{
 {SPI_0,SPI_CLKSRC_PIOSC,HWUnit_ENABLE},
 {SPI_1,SPI_CLKSRC_PIOSC,HWUnit_ENABLE},
 {SPI_2,SPI_CLKSRC_PIOSC,HWUnit_ENABLE},
 {SPI_3,SPI_CLKSRC_PIOSC,HWUnit_ENABLE}
};


/* External Devices Configurations */
const Spi_ExternalDeviceConfigType  ExtDevices_Configs[SPI_EXTERNAL_DEVICES_NUM]=
{
 {SPI_0, 8000000, CS_ID_0, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_LEADING, SPI_CLOCK_IDLE_LOW, STD_ON},     /* SPH = 0 */
 {SPI_0, 4000000, CS_ID_1, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_TRAILING, SPI_CLOCK_IDLE_LOW, STD_ON},    /* SPH = 1 */
 {SPI_1, 8000000, CS_ID_2, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_LEADING, SPI_CLOCK_IDLE_HIGH, STD_ON},    /* SPH = 1 */
 {SPI_2, 4000000, CS_ID_3, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_TRAILING, SPI_CLOCK_IDLE_HIGH, STD_ON},   /* SPH = 0 */
 {SPI_3, 8000000, CS_ID_4, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_LEADING, SPI_CLOCK_IDLE_LOW, STD_ON},     /* SPH = 0 */
 {SPI_1, 4000000, CS_ID_5, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_TRAILING, SPI_CLOCK_IDLE_LOW, STD_ON},    /* SPH = 1 */
 {SPI_3, 8000000, CS_ID_6, CS_POLARITY_LOW, CS_VIA_GPIO, SPI_EDGE_LEADING, SPI_CLOCK_IDLE_HIGH, STD_ON}     /* SPH = 1 */
};

/* Channels' Buffer Configurations */
Spi_DataBufferType  Channel0_Tx_Buff[CHANNEL_0_LENGTH];
Spi_DataBufferType  Channel0_Rx_Buff[CHANNEL_0_LENGTH];

Spi_DataBufferType  Channel2_Tx_Buff[CHANNEL_2_LENGTH];
Spi_DataBufferType  Channel2_Rx_Buff[CHANNEL_2_LENGTH];

const Spi_ConfigType SpiConfigurations =
{
 /***************************Channels Configurations*****************************/
 {
  {CHANNEL_ID_0, SPI_IB, SPI_DATA_WIDTH_8Bits, 0xFF, CHANNEL_0_LENGTH, SPI_TRANSFER_START_MSB, {Channel0_Tx_Buff, Channel0_Rx_Buff}},
  {CHANNEL_ID_1, SPI_EB, SPI_DATA_WIDTH_8Bits, 0xFF, CHANNEL_1_LENGTH, SPI_TRANSFER_START_MSB, {NULL_PTR}},
  {CHANNEL_ID_2, SPI_IB, SPI_DATA_WIDTH_8Bits, 0xFF, CHANNEL_2_LENGTH, SPI_TRANSFER_START_MSB, {Channel2_Tx_Buff, Channel2_Rx_Buff}},
  {CHANNEL_ID_3, SPI_EB, SPI_DATA_WIDTH_8Bits, 0xFF, CHANNEL_3_LENGTH, SPI_TRANSFER_START_MSB, {NULL_PTR}}
 },
 /*****************************Jobs Configurations*******************************/
 {
  {JOB_ID_0, JOB_PRIORITY_0, NULL_PTR, EXTERNAL_DEVICE_ID_0, { {0,CHANNEL_ID_0}, {1,CHANNEL_ID_2} }},
  {JOB_ID_1, JOB_PRIORITY_1, NULL_PTR, EXTERNAL_DEVICE_ID_1, { {0,CHANNEL_ID_1}, {1,CHANNEL_ID_3} }},
  {JOB_ID_2, JOB_PRIORITY_2, NULL_PTR, EXTERNAL_DEVICE_ID_2, { {0,CHANNEL_ID_2}, {1,CHANNEL_ID_1} }},
  {JOB_ID_3, JOB_PRIORITY_3, NULL_PTR, EXTERNAL_DEVICE_ID_3, { {0,CHANNEL_ID_3}, {1,CHANNEL_ID_0} }}
 },
 /**************************Sequences Configurations*****************************/
 {
  {SEQUENCE_ID_0, NULL_PTR, 3, {JOB_ID_0, JOB_ID_2, JOB_ID_3}, SEQ_INTERRUPTIBLE     , SEQ_PRIORITY_0},
  {SEQUENCE_ID_1, NULL_PTR, 2, {JOB_ID_1, JOB_ID_3}          , SEQ_NON_INTERRUPTIBLE , SEQ_PRIORITY_3},
  {SEQUENCE_ID_2, NULL_PTR, 3, {JOB_ID_0, JOB_ID_1, JOB_ID_3}, SEQ_INTERRUPTIBLE     , SEQ_PRIORITY_1},
  {SEQUENCE_ID_3, NULL_PTR, 2, {JOB_ID_2, JOB_ID_3}          , SEQ_NON_INTERRUPTIBLE , SEQ_PRIORITY_2}
 }
};








