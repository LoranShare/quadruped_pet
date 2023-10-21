/**
 *******************************************************************************
 * @file        debug.c
 * @author      Gevorgyan Ovik
 * @brief       This module provides functions, macros, etc. for debugging
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "debug.h"


/* Private functions ---------------------------------------------------------*/

void assert_failed(uint8_t* file, uint32_t line) {

  printf("Wrong parameters value: file %s on line %ld\r\n", file, line);

  while (1);

}
