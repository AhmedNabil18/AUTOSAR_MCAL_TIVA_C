 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi_Symbols.h
 *
 * Description: Header file for Spi Module Symbols.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef SPI_SYMBOLS_H_
#define SPI_SYMBOLS_H_

/**********************************************************************/
/*                   Symbols for SPI HWUnits ID                       */
/**********************************************************************/
#define SPI_0           0U
#define SPI_1           1U
#define SPI_2           2U
#define SPI_3           3U

/**********************************************************************/
/*                Symbols for SPI Channel Buffers Usage               */
/**********************************************************************/
/* SPI manages only Internal Channel Buffer */
#define SPI_BUFF_USAGE_IB       0x00U
/* SPI manages only External Channel Buffer */
#define SPI_BUFF_USAGE_EB       0x01U
/* SPI manages Both Types of Channel Buffer */
#define SPI_BUFF_USAGE_BOTH     0x02U

/**********************************************************************/
/*                  Symbols for SPI Level Delivered                   */
/**********************************************************************/
/* SPI Synchronous Level 0 */
#define SPI_LEVEL_0             0x00U
/* SPI Asynchronous Level 1 */
#define SPI_LEVEL_1             0x01U
/* SPI A/Synchronous Level 2 */
#define SPI_LEVEL_2             0x02U

/**********************************************************************/
/*                    Symbols for SPI Clock Source                    */
/**********************************************************************/
/* Using the system clock as a clock source for SPI */
#define SPI_CLKSRC_SYSCLK       0x0
/* Using the PIOSC as a clock source for SPI (Internal On Chip clock source 16MHz) */
#define SPI_CLKSRC_PIOSC        0x5
/**********************************************************************/
/*                     Symbols for SPI Registers                      */
/**********************************************************************/
/*
 * SSI Control 0 Register
 */
#define SPI_CR0_SCR             8U
#define SPI_CR0_SPH             7U
#define SPI_CR0_SPO             6U
#define SPI_CR0_FRF             4U
#define SPI_CR0_DSS             0U

/*
 * SSI Control 1 Register
 */
#define SPI_CR1_EOT             4U
#define SPI_CR1_MS              2U
#define SPI_CR1_SSE             1U
#define SPI_CR1_LBM             0U

/*
 * SSI Status Register
 */
#define SPI_SR_BSY              4U
#define SPI_SR_RFF              3U
#define SPI_SR_RNE              2U
#define SPI_SR_TNF              1U
#define SPI_SR_TFE              0U

/*
 * SSI Interrupt Mask Register
 */
#define SPI_IM_TXIM             3U
#define SPI_IM_RXIM             2U
#define SPI_IM_RTIM             1U
#define SPI_IM_RORIM            0U

/*
 * SSI Raw Interrupt Status Register
 */
#define SPI_RIS_TXRIS           3U
#define SPI_RIS_RXRIS           2U
#define SPI_RIS_RTRIS           1U
#define SPI_RIS_RORRIS          0U

/*
 * SSI Raw Interrupt Status Register
 */
#define SPI_MIS_TXMIS           3U
#define SPI_MIS_RXMIS           2U
#define SPI_MIS_RTMIS           1U
#define SPI_MIS_RORMIS          0U


#endif



















