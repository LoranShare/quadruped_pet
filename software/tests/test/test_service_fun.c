/**
 *******************************************************************************
 * @file        test_service_fun.c
 * @author      Gevorgyan Ovik
 * @brief       Unit test of a service functions
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "leg_driver.h"
#include "service_fun.h"
#include "unity.h"

/* Private define ------------------------------------------------------------*/
#define MAX_LEN (20.0f)
#define NUMBER_OF_POINT (1000)

/* Private variables ---------------------------------------------------------*/
float g_coxa_len;
float g_femur_len;

/* Private functions ---------------------------------------------------------*/
void setUp(void) {
    srand(time(NULL));
    g_femur_len = getRandomFloat(0, MAX_LEN, false);
    g_coxa_len = getRandomFloat(0, MAX_LEN, false);
}

void tearDown(void) {}

/**
 * @brief       Сhecking to handle null pointer
 *
 * @details     The forward kinematics function is checked.
 *              The test is considered passed if an error is generated
 *
 */

void test_null_pointer(void) {
    /* Variable declaration */
    bool status;
    float angle_c = getRandomFloat(0, 180, true);
    float angle_f = getRandomFloat(0, 360, true);
    point_t point = {.x = 0, .y = 0};

    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, NULL);
    TEST_ASSERT_FALSE(status);

    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
}

/**
 * @brief       Testing points along the x axis
 *
 * @details     The forward kinematics function is checked,
 *              which returns the point of tangency
 *
 */

void test_points_along_x(void) {
    /* Variable declaration */
    bool status;
    float angle_c;
    float angle_f;
    point_t point;

    char mess_string[200];
    char *p_mess_string = mess_string;

    /* Сheck along the x axis */
    angle_c = 180;
    angle_f = 0;

    sprintf(p_mess_string, "Along the x axis, femur angle %f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, g_coxa_len + g_femur_len, point.x, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.y, mess_string);

    angle_c = 0;
    angle_f = 0;

    sprintf(p_mess_string, "Along the x axis, femur angle %f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, (g_femur_len - g_coxa_len), point.x, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.y, mess_string);

    angle_c = 180;
    angle_f = 180;

    sprintf(p_mess_string, "Along the x axis, femur angle %f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, -(g_coxa_len + g_femur_len), point.x, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.y, mess_string);

    angle_c = 180;
    angle_f = 180;

    sprintf(p_mess_string, "Along the x axis, femur angle %02f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, -(g_coxa_len + g_femur_len), point.x, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.y, mess_string);
}

/**
 * @brief       Testing points along the y axis
 *
 * @details     The forward kinematics function is checked,
 *              which returns the point of tangency
 *
 */

void test_points_along_y(void) {
    /* Variable declaration */
    bool status;
    float angle_c;
    float angle_f;
    point_t point;

    char mess_string[200];
    char *p_mess_string = mess_string;

    /* Сheck along the y axis */
    angle_c = 180;
    angle_f = 90;

    sprintf(p_mess_string, "Along the y axis, femur angle %f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, g_coxa_len + g_femur_len, point.y, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.x, mess_string);

    angle_c = 0;
    angle_f = 90;

    sprintf(p_mess_string, "Along the y axis, femur angle %f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, (g_femur_len - g_coxa_len), point.y, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.x, mess_string);

    angle_c = 180;
    angle_f = 270;

    sprintf(p_mess_string, "Along the y axis, femur angle %f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, -(g_coxa_len + g_femur_len), point.y, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.x, mess_string);

    angle_c = 180;
    angle_f = 270;

    sprintf(p_mess_string, "Along the y axis, femur angle %02f coxa angle %f\n", angle_f, angle_c);
    status = calculatePoint(g_femur_len, g_coxa_len, angle_f, angle_c, &point);
    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, -(g_coxa_len + g_femur_len), point.y, mess_string);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 0, point.x, mess_string);
}
