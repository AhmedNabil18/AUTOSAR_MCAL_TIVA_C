 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi_Cfg.h
 *
 * Description: Header file for Spi Module Configurations.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef SPI_CFG_H_
#define SPI_CFG_H_

#include "Spi_Symbols.h"
#include "Dio.h"
/*
 * Module Version 1.0.0
 */
#define SPI_CFG_SW_MAJOR_VERSION              (1U)
#define SPI_CFG_SW_MINOR_VERSION              (0U)
#define SPI_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define SPI_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define SPI_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define SPI_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/************************************************************************************/
/*                         SPI General Configurations                               */
/************************************************************************************/
/* Switches the Spi_Cancel function ON or OFF */
#define SPI_CANCEL_API                        STD_ON
/*
 * Selects the SPI Driver JOB Buffers Usage allowed between
 * SPI_BUFF_USAGE_IB, SPI_BUFF_USAGE_EB or SPI_BUFF_USAGE_BOTH
 */
#define SPI_CHANNEL_BUFFERS_ALLOWED           SPI_BUFF_USAGE_BOTH

/* Switches the Development Error Detection ON or OFF */
#define SPI_DEV_ERROR_DETECT				  STD_ON

/* Switches the Spi_GetHWUnitStatus function ON or OFF */
#define SPI_HW_STATUS_API                     STD_ON

/*
 * Switches the Interruptible Sequences handling functionality ON or OFF
 * Only used for with Level 1 or 2
 */
#define SPI_INTERRUPTIBLE_SEQ_ALLOWED         STD_ON

/*
 * Selects the SPI Driver level of scalable functionality between
 * SPI_LEVEL_0, SPI_LEVEL_1 or SPI_LEVEL_2
 */
#define SPI_LEVEL_DELIVERED                   SPI_LEVEL_2

/*
 * Defines the periodic time of the function Spi_MainFunction_Handling
 * The unit time is defined in seconds
 * Parameter is used by upper layer modules not by this driver
 */
#define SPI_MAIN_FUNCTION_PERIOD              (1U) /* In Seconds */

/* Only in Level 0
 * Specifies whether the concurrent Spi_SyncTransmit()
 * calls for different sequences is accepted or not
 * Sequences must use different buses
 */
#define SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT  STD_ON

/* Switches the Spi_GetVersionInfo ON or OFF */
#define SPI_VERSION_INFO_API                  STD_ON

/*
 * Maps the SPI driver to zero or multiple ECUC partitions
 * to make the driver API available in the according partition
 */
#define SPI_ECUC_PARTITION_REF

/*
 * Maps the SPI kernel to zero or one ECUC partitions to assign the driver
 * kernel to a certain core. The ECUC partition referenced is a subset of the
 * ECUC partitions where the SPI driver is mapped to
 */
#define SPI_KERNEL_ECUC_PARTITION_REF
/************************************************************************************/

/************************************************************************************/
/*                          SPI Driver Configurations                               */
/************************************************************************************/
/* The Number of configured External Devices */
#define SPI_EXTERNAL_DEVICES_NUM              (7U)

/* The Number of Dio chip selects used */
#define SPI_CHIP_SELECTS_NUM                SPI_EXTERNAL_DEVICES_NUM

/* The Number of configured channels */
#define SPI_CONFIGURED_CHANNELS               (4U)

/* The Number of configured jobs */
#define SPI_CONFIGURED_JOBS                   (4U)

/* The Number of configured sequences */
#define SPI_CONFIGURED_SEQUENCES              (4U)


#define CS_ID_0         DioConf_SPI_CS0_CHANNEL_ID_INDEX
#define CS_ID_1         DioConf_SPI_CS1_CHANNEL_ID_INDEX
#define CS_ID_2         DioConf_SPI_CS2_CHANNEL_ID_INDEX
#define CS_ID_3         DioConf_SPI_CS3_CHANNEL_ID_INDEX
#define CS_ID_4         DioConf_SPI_CS4_CHANNEL_ID_INDEX
#define CS_ID_5         DioConf_SPI_CS5_CHANNEL_ID_INDEX
#define CS_ID_6         DioConf_SPI_CS6_CHANNEL_ID_INDEX

#define EXTERNAL_DEVICE_ID_0        (0U)
#define EXTERNAL_DEVICE_ID_1        (1U)
#define EXTERNAL_DEVICE_ID_2        (2U)
#define EXTERNAL_DEVICE_ID_3        (3U)
#define EXTERNAL_DEVICE_ID_4        (4U)
#define EXTERNAL_DEVICE_ID_5        (5U)
#define EXTERNAL_DEVICE_ID_6        (6U)

#define CHANNEL_ID_0        (0U)
#define CHANNEL_ID_1        (1U)
#define CHANNEL_ID_2        (2U)
#define CHANNEL_ID_3        (3U)

#define CHANNEL_0_LENGTH        (10U)
#define CHANNEL_1_LENGTH        (8U)
#define CHANNEL_2_LENGTH        (4U)
#define CHANNEL_3_LENGTH        (11U)

#define JOB_ID_0            (0U)
#define JOB_ID_1            (1U)
#define JOB_ID_2            (2U)
#define JOB_ID_3            (3U)

#define SEQUENCE_ID_0       (0U)
#define SEQUENCE_ID_1       (1U)
#define SEQUENCE_ID_2       (2U)
#define SEQUENCE_ID_3       (3U)


#endif


