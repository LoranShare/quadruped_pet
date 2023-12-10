/**
 *******************************************************************************
 * @file        leg_driver.h
 * @author      Gevorgyan Ovik
 * @brief       Header of leg_driver.c
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEG_DRIVER_H__
#define __LEG_DRIVER_H__

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
    LEG_STATUS_SUCCESS,
    LEG_STATUS_BAD_PTR,
    LEG_STATUS_BAG_ARG,
    LEG_STATUS_ERROR
} legStatus_t;

typedef struct {
    float x;
    float y;
} point_t;

typedef struct {
    float femur_len;    ///< Femur limb length in cm
    float coxa_len;     ///< Coxa limb length in cm
    float femur_angle;  ///< Femur angle in degrees [0:180]
    float coxa_angle;   ///< Coxa angle in degrees [0:180]
    point_t point;
} leg_t;

typedef enum { LIMB_COXA, LIMB_FEMUR } limb_t;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
legStatus_t initLeg(leg_t *const leg, float coxa_len, float femur_len);
legStatus_t setCoordinate(leg_t *const leg, const point_t *const point, bool truncated);
legStatus_t getAngle(const leg_t *const leg, const limb_t limb, float *value);

/* ########################## Module Selection ############################## */

/** @defgroup NVMe_commands Commands from NVMe to SysMon
 * @{
 */

/** @}*/

#endif /* __LEG_DRIVER_H__ */
