/**
 *******************************************************************************
 * @file        processing_irq.h
 * @author      Gevorgyan Ovik
 * @brief       Header of processing_irq.с
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PROCESSING_IRQ_H__
#define __PROCESSING_IRQ_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported functions ------------------------------------------------------- */
/**
 * @brief       Get the current counter value
 *
 * @details     The timer is configured to interrupt once every 1 ms;
 *              when interrupted, the counter increases
 *
 * @return      Сounter value
 */

uint32_t getTick(void);

#endif /* __PROCESSING_IRQ_H__ */
