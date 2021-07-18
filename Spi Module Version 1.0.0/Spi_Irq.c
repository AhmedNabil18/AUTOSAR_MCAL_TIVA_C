 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi_Irq.c
 *
 * Description: Source file for Spi Module Interrupt Requests.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#include "Spi_Irq.h"
#include "Spi_Symbols.h"
#include "Spi.h"

/*
 * Look Up Table for the IRQ numbers of the Timer modules in the NVIC table
 */
uint8 Spi_IRQNum[4] =
{
     7,   /* SPI0_IRQ */ /* Index 0 */
     34,  /* SPI1_IRQ */ /* Index 1 */
     57,  /* SPI2_IRQ */ /* Index 2 */
     58   /* SPI3_IRQ */ /* Index 3 */
};

STATIC void Spi_ISRHandler(Spi_HWUnitType hwunit_id)
{
	/* CallBack the notification function */
//	Timers_Configurations.Timer_Channels[Channel].notification_func_ptr();
}

 void Spi0_ISR(void){Spi_ISRHandler(SPI_0);}
 void Spi1_ISR(void){Spi_ISRHandler(SPI_1);}
 void Spi2_ISR(void){Spi_ISRHandler(SPI_2);}
 void Spi3_ISR(void){Spi_ISRHandler(SPI_3);}
