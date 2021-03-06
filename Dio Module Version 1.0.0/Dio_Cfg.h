 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for Dio Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "Dio_Symbols.h"

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)


/*******************************************************************************
 *                CHANNEL PRECOMPILE CONFIGURATIONS                            *
 *******************************************************************************/

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES             (12U)

/* DIO Configured Port ID's  */
#define DioConf_RED_PORT_NUM                 (Dio_PortType)DIO_PORT_F
#define DioConf_BLUE_PORT_NUM                (Dio_PortType)DIO_PORT_F
#define DioConf_GREEN_PORT_NUM               (Dio_PortType)DIO_PORT_F
#define DioConf_BUTTON1_PORT_NUM             (Dio_PortType)DIO_PORT_F
#define DioConf_BUTTON2_PORT_NUM             (Dio_PortType)DIO_PORT_F

#define DioConf_SPI_CS0_PORT_NUM             (Dio_PortType)DIO_PORT_A
#define DioConf_SPI_CS1_PORT_NUM             (Dio_PortType)DIO_PORT_A
#define DioConf_SPI_CS2_PORT_NUM             (Dio_PortType)DIO_PORT_A
#define DioConf_SPI_CS3_PORT_NUM             (Dio_PortType)DIO_PORT_B
#define DioConf_SPI_CS4_PORT_NUM             (Dio_PortType)DIO_PORT_B
#define DioConf_SPI_CS5_PORT_NUM             (Dio_PortType)DIO_PORT_B
#define DioConf_SPI_CS6_PORT_NUM             (Dio_PortType)DIO_PORT_B

/* DIO Configured Channel ID's */
#define DioConf_RED_CHANNEL_NUM              (Dio_ChannelType)DIO_CHANNEL_F_1
#define DioConf_BLUE_CHANNEL_NUM             (Dio_ChannelType)DIO_CHANNEL_F_2
#define DioConf_GREEN_CHANNEL_NUM            (Dio_ChannelType)DIO_CHANNEL_F_3
#define DioConf_BUTTON1_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_F_4
#define DioConf_BUTTON2_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_F_0

#define DioConf_SPI_CS0_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_A_3
#define DioConf_SPI_CS1_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_A_6
#define DioConf_SPI_CS2_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_A_7
#define DioConf_SPI_CS3_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_B_1
#define DioConf_SPI_CS4_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_B_2
#define DioConf_SPI_CS5_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_B_3
#define DioConf_SPI_CS6_CHANNEL_NUM          (Dio_ChannelType)DIO_CHANNEL_B_5

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_RED_CHANNEL_ID_INDEX         (uint8)0
#define DioConf_BLUE_CHANNEL_ID_INDEX        (uint8)1
#define DioConf_GREEN_CHANNEL_ID_INDEX       (uint8)2
#define DioConf_BUTTON1_CHANNEL_ID_INDEX     (uint8)3
#define DioConf_BUTTON2_CHANNEL_ID_INDEX     (uint8)4

#define DioConf_SPI_CS0_CHANNEL_ID_INDEX     (uint8)5
#define DioConf_SPI_CS1_CHANNEL_ID_INDEX     (uint8)6
#define DioConf_SPI_CS2_CHANNEL_ID_INDEX     (uint8)7
#define DioConf_SPI_CS3_CHANNEL_ID_INDEX     (uint8)8
#define DioConf_SPI_CS4_CHANNEL_ID_INDEX     (uint8)9
#define DioConf_SPI_CS5_CHANNEL_ID_INDEX     (uint8)10
#define DioConf_SPI_CS6_CHANNEL_ID_INDEX     (uint8)11

/*******************************************************************************
 *             CHANNEL GROUP PRECOMPILE CONFIGURATIONS                         *
 *******************************************************************************/
/* Number of the configured Dio Channel Groups */
#define DIO_CONFIGURED_CHANNEL_GROUPS       (2U)

/* Channel Group Index in the array of Dio_ChannelGroupType in Dio_PBcfg.c */
#define DioConf_LEDs_CHANNEL_GROUP_INDEX     (uint8)0x00
#define DioConf_BUTTONs_CHANNEL_GROUP_INDEX  (uint8)0x01

/*******************************************************************************
 *                  PORT PRECOMPILE CONFIGURATIONS                             *
 *******************************************************************************/

/* Number of the configured Dio Ports */
#define DIO_CONFIGURED_PORTS                (0U)

/* Port Index in the array of Dio_PortType in Dio_PBcfg.c */
#define DioConf_PORTD_PORT_ID_INDEX			 (uint8)0x00




#endif /* DIO_CFG_H */
