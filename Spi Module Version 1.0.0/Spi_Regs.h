 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi_Regs.h
 *
 * Description: Header file for Spi Module Registers.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef SPI_REGS_H_
#define SPI_REGS_H_

#include "Std_Types.h"
#include "Spi_Symbols.h"

#define     __I     volatile const       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */


#define NVIC_EN0_R              (*((volatile uint32 *)0xE000E100))
#define NVIC_EN1_R              (*((volatile uint32 *)0xE000E104))
#define NVIC_EN2_R              (*((volatile uint32 *)0xE000E108))
#define NVIC_EN3_R              (*((volatile uint32 *)0xE000E10C))
#define NVIC_EN4_R              (*((volatile uint32 *)0xE000E110))

#define SYSCTL_RCGCSSI_R        (*((volatile uint32 *)0x400FE61C))

#define SPIs_NUM        4U

#define SPI0_BASE_ADDRESS            0x40008000U
#define SPI1_BASE_ADDRESS            0x40009000U
#define SPI2_BASE_ADDRESS            0x4000A000U
#define SPI3_BASE_ADDRESS            0x4000B000U

static uint32 SPI_BaseAddressLut[SPIs_NUM] =
{   SPI0_BASE_ADDRESS,
    SPI1_BASE_ADDRESS,
    SPI2_BASE_ADDRESS,
    SPI3_BASE_ADDRESS
};

/*
 * Spi Registers
 */

typedef struct {                                    /*!< SSI0 Structure                                                        */
  __IO uint32  CR0;                               /*!< SSI Control 0                                                         */
  __IO uint32  CR1;                               /*!< SSI Control 1                                                         */
  __IO uint32  DR;                                /*!< SSI Data                                                              */
  __IO uint32  SR;                                /*!< SSI Status                                                            */
  __IO uint32  CPSR;                              /*!< SSI Clock Prescale                                                    */
  __IO uint32  IM;                                /*!< SSI Interrupt Mask                                                    */
  __IO uint32  RIS;                               /*!< SSI Raw Interrupt Status                                              */
  __IO uint32  MIS;                               /*!< SSI Masked Interrupt Status                                           */
  __O  uint32  ICR;                               /*!< SSI Interrupt Clear                                                   */
  __IO uint32  DMACTL;                            /*!< SSI DMA Control                                                       */
  __I  uint32  RESERVED0[1000];
  __IO uint32  CC;                                /*!< SSI Clock Configuration                                               */
} Spi_MapType;

#define SPI(ID)    ((Spi_MapType*)SPI_BaseAddressLut[ID])

#define SPI0_MAP      SPI(SPI_0)
#define SPI1_MAP      SPI(SPI_1)
#define SPI2_MAP      SPI(SPI_2)
#define SPI3_MAP      SPI(SPI_3)

#endif /* SPI_REGS_H_ */
