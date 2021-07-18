 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi_Irq.h
 *
 * Description: Header file for Spi Module Interrupt Requests.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef SPI_IRQ_H_
#define SPI_IRQ_H_

#include "Std_Types.h"
#include "Spi_Regs.h"

extern uint8 Spi_IRQNum[4];

STATIC void Spi_NVICEnable(uint8  Num)
{
    if(Num < 32)
        NVIC_EN0_R |= 1<<Num;
    else if((Num > 31) && (Num < 64))
        NVIC_EN1_R |= 1<<(Num-32);
    else if((Num > 63) && (Num < 96))
        NVIC_EN2_R |= 1<<(Num-64);
    else if((Num > 95) && (Num < 128))
        NVIC_EN3_R |= 1<<(Num-96);
}
STATIC void Spi_NVICDisable(uint8  Num)
{
    if(Num < 32)
        NVIC_EN0_R &= ~(1<<Num);
    else if((Num > 31) && (Num < 64))
        NVIC_EN1_R &= ~(1<<(Num-32));
    else if((Num > 63) && (Num < 96))
        NVIC_EN2_R &= ~(1<<(Num-64));
    else if((Num > 95) && (Num < 128))
        NVIC_EN3_R &= ~(1<<(Num-96));
}


#endif /* SPI_IRQ_H_ */
