/**
 *******************************************************************************
 * @file        service_fun.h
 * @author      Gevorgyan Ovik
 * @brief       Header of service_fun
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SERVICE_FUN_H__
#define __SERVICE_FUN_H__

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

#include "leg_driver.h"

/* Exported functions ------------------------------------------------------- */
/**
 * @brief       Return random float value in range [min, max]
 *
 * @param[in]   min limit of the minimum range
 * @param[in]   max limit of the maximum range
 * @param[in]   is_include include extreme points in range
 *
 * @return      Random value
 */

float getRandomFloat(float min, float max, bool is_include);

/**
 * @brief       Solving the problem of direct kinematics,
 * 				finding the coordinates of a point
 *
 * @param[in]   femur_len femur length
 * @param[in]   coxa_len coxa length
 * @param[in]   angle_femur angle between the x-axis and the femur
 * @param[in]   angle_coxa angle between the femur and the coxa
 * @param[out]  point limb contact coordinate
 *
 * @retval      true succes
 * @retval      false if a error occurred (null pointer, no intersection points)
 *
 * @return      Status of operation
 */

bool calculatePoint(float femur_len, float coxa_len, float angle_femur, float angle_coxa,
                    point_t *point);

/**
 * @brief       Calculate the intersection point of a circles
 *
 * @details     The center of the first circle is at the origin,
 *              and the second circle is at point @ref point
 *
 * @param[in]   r1 circle radius
 * @param[in]   r2 circle radius
 * @param[in]   point the centre of first circle
 * @param[out]  intersec_point the intersection point of circles
 *
 * @retval      true succes
 * @retval      false if a error occurred (null pointer, no intersection points)
 *
 * @return      Status of operation
 */

bool calculateAngle(float r1, float r2, const point_t *const point, point_t *intersec_point);

#endif /* __SERVICE_FUN_H__ */
