/**
 *******************************************************************************
 * @file        service_fun.c
 * @author      Gevorgyan Ovik
 * @brief       Functions required for testing
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "service_fun.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Private functions ---------------------------------------------------------*/

float getRandomFloat(float min, float max, bool is_include) {
    float random;
    float range;

    if (min > max) {
        float temp = min;
        min = max;
        max = temp;
    }

    range = max - min;
    random = (float)rand() / RAND_MAX;

    if (is_include) {
        range -= FLT_EPSILON;
        min += FLT_EPSILON;
    }

    random = min + random * range;
    return random;
}

bool calculateAngle(float r1, float r2, const point_t *const point, point_t *intersec_point) {
    bool status = false;
    float distance, b_len, h;
    float temp;
    point_t temp_point;

    /* Checking input arguments */
    if (!point || !intersec_point) {
        return status;
    }

    /* Checking reachability point */
    distance = pow(point->x, 2) + pow(point->y, 2);
    distance = sqrt(distance);
    if (distance > (r1 + r2) || distance < abs(r1 - r2)) {
        return status;
    }

    ///@debug
    printf("distance %f\n", distance);

    /* Сalculation of the length of the segment */
    temp = pow(r2, 2);
    b_len = temp - pow(r1, 2) + pow(distance, 2);
    b_len = b_len / 2 / distance;

    ///@debug
    printf("b_len %f\n", b_len);

    /* Сalculation of perpendicular length */
    h = temp - pow(b_len, 2);
    h = sqrt(h);

    ///@debug
    printf("h %f\n", h);

    /* Finding the coordinates of a point on a segment */
    temp_point.x = (point->x) - b_len / distance * (point->x);
    temp_point.y = (point->y) - b_len / distance * (point->y);

    printf("X: %f\n", temp_point.x);
    printf("Y: %f\n", temp_point.y);

    /* Rotate vector clockwise */
    temp = h / b_len;
    intersec_point->x = temp_point.x - (point->y - temp_point.y) * temp;
    intersec_point->y = temp_point.y + (point->x - temp_point.x) * temp;

    printf("X: %f\n", intersec_point->x);
    printf("Y: %f\n", intersec_point->y);

    intersec_point->x = temp_point.x + (point->y - temp_point.y) * temp;
    intersec_point->y = temp_point.y - (point->x - temp_point.x) * temp;

    printf("X: %f\n", intersec_point->x);
    printf("Y: %f\n", intersec_point->y);

    return true;
}

bool calculatePoint(float femur_len, float coxa_len, float angle_f, float angle_c,
                    point_t *const point) {
    point_t point_b;
    float angle_temp;
    float radian;

    if (!point || (angle_c > 180.00)) {
        return false;
    }

    /* Find first coordinate */
    radian = angle_f * M_PI / 180;
    point_b.x = cos(radian) * femur_len;
    point_b.y = sin(radian) * femur_len;

    /* Find second coordinate */
    angle_temp = 180.0f - angle_c;
    angle_temp = angle_f - angle_temp;

    radian = angle_temp * M_PI / 180;
    point->x = cos(radian) * coxa_len;
    point->y = sin(radian) * coxa_len;

    /* Axis offset recalculation */
    point->x += point_b.x;
    point->y += point_b.y;

    return true;
}
