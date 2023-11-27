/**
 *******************************************************************************
 * @file        main.c
 * @author      Gevorgyan Ovik
 * @brief       This module contains the entry point and the main loop
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"

/* Private function prototypes -----------------------------------------------*/
static void initializeMCO(void);

/* Private functions ---------------------------------------------------------*/
int main(void) {
    /* Variable declaration */

    /* MCO Initialization */
    initializeMCO();

    /* Main loop */
    while (1) {
    }

    return 0;
}

/**
 * @brief       MCO Output Initialization
 *
 * @details		RCC is enabled and system clock is selected for output.
 *
 * @return      None
 */

void initializeMCO(void) {
    /* Select clock to output */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO_Msk, RCC_CFGR_MCO_SYSCLK);

    /* Enable RCC */
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

    /* Enable AF for MCO */
    MODIFY_REG(GPIOA->CRH, GPIO_CRH_MODE8_Msk, GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1);
    MODIFY_REG(GPIOA->CRH, GPIO_CRH_CNF8_Msk, GPIO_CRH_CNF8_1);
}
