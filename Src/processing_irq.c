/**
 *******************************************************************************
 * @file        processing_irq.c
 * @author      Gevorgyan Ovik
 * @brief       Main Interrupt Service Routines
 *              This file provides implementation for all exceptions handler
 *              and peripherals interrupt service routine.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "processing_irq.h"


/* Private variables ---------------------------------------------------------*/
static volatile uint32_t ticks_ms = 0;


/* Private functions ---------------------------------------------------------*/
/**
 * @brief       System timer interrupt handler
 *
 * @details     The timer is configured to interrupt once every 1 ms;
 *              when interrupted, the counter increases
 */

__attribute__ ((interrupt ("IRQ"))) void SysTick_Handler(void) {
    ++ticks_ms;
}


uint32_t getTick(void) {
    return ticks_ms;
}
