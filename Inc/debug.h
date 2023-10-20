/**
 *******************************************************************************
 * @file        debug.h
 * @author      Gevorgyan Ovik
 * @brief       Header of debug.c
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>


/* Exported macro ------------------------------------------------------------*/

    #define PRNT_DEBUG(...)     printf("[DEBUG][%s]: ",     __func__); printf(__VA_ARGS__)
    #define PRNT_INFO(...)      printf("[INFO][%s]: ",      __func__); printf(__VA_ARGS__)
    #define PRNT_ERROR(...)     printf("[ERROR][%s]: ",     __func__); printf(__VA_ARGS__)
    #define PRNT_WARNING(...)   printf("[WARNING][%s]: ",   __func__); printf(__VA_ARGS__)
    #define PRNT_STATS(...)     printf("[STATS][%s]: ",     __func__); printf(__VA_ARGS__)

    #ifdef USE_ASSERT

        /**
         * @brief  The assert_param macro is used for function's parameters check
         *
         * @param  expr: If expr is false, it calls assert_failed function
         *
         * @retval None
         */

        #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

    #else
        #define assert_param(expr) ((void)0U)
    #endif /* USE_ASSERT */


/* Exported functions ------------------------------------------------------- */
#ifdef USE_ASSERT
    void assert_failed(uint8_t* file, uint32_t line);
#endif /* USE_ASSERT */


#endif /* __DEBUG_H__ */
