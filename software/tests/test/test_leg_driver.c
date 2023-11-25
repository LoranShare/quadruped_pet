/**
 *******************************************************************************
 * @file        test_leg_driver.c
 * @author      Gevorgyan Ovik
 * @brief       Unit test of a leg driver
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "unity.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include "leg_driver.h"
#include "service_fun.h"


/* Private define ------------------------------------------------------------*/
#define MAX_LEN                 ( 20.0f             )
#define NUMBER_OF_POINT         ( 1000              )


/* Private variables ---------------------------------------------------------*/
float g_coxa_len;
float g_femur_len;


/* Private functions ---------------------------------------------------------*/
void setUp(void) {
    srand(time(NULL));
    g_femur_len = getRandomFloat(0, MAX_LEN, false);
    g_coxa_len = getRandomFloat(0, MAX_LEN, false);
}

void tearDown(void) {
}


/**
 * @brief       Сhecking driver methods to handle null pointer
 *
 * @details     Methods where pointers are declared as arguments are supplied with NULL.
 *              The test is considered passed if an error is generated
 *
 */

void test_null_pointer(void) {

    /* Variable declaration */
    legStatus_t status;
    leg_t leg;
    point_t point;
    limb_t limb = LIMB_FEMUR;
    float float_val;

    /* Testing initleg func */
    status = initLeg(NULL, g_coxa_len, g_femur_len);
    TEST_ASSERT_EQUAL_INT(status, LEG_STATUS_BAD_PTR);

    /* Testing setCoordinate func */
    status = setCoordinate(NULL, &point, false);
    TEST_ASSERT_EQUAL_INT(status, LEG_STATUS_BAD_PTR);

    status = setCoordinate(&leg, NULL, false);
    TEST_ASSERT_EQUAL_INT(status, LEG_STATUS_BAD_PTR);

    /* Testing getAngle func */
    status = getAngle(NULL, limb, &float_val);
    TEST_ASSERT_EQUAL_INT(status, LEG_STATUS_BAD_PTR);

    status = getAngle(&leg, limb, NULL);
    TEST_ASSERT_EQUAL_INT(status, LEG_STATUS_BAD_PTR);
}


/**
 * @brief       Сhecking for invalid points
 *
 * @details     It is checked that the methods return an error for a set of
 *              points for which there is no solution in inverse kinematics problems
 *
 */

void test_unreachable_points(void) {

    /* Variable declaration */
    legStatus_t status;
    leg_t leg;
    float max_d, min_d, sq_d, sq_y, sq_x;
    char mess_string[200];
    char *p_mess_string = mess_string;
    point_t point;

    /* Driver initialization */
    status = initLeg(&leg, g_coxa_len, g_femur_len);
    TEST_ASSERT_EQUAL_INT(status, LEG_STATUS_SUCCESS);

    /* Сalculation of diameters for two cases,
    a circle inside a circle and a circle outside the circle */
    max_d = fabs(g_coxa_len - g_femur_len);
    min_d = fabs(g_coxa_len + g_femur_len);

    for (int i = 1; i < NUMBER_OF_POINT; ++i) {
        if(i >= NUMBER_OF_POINT / 2) {
            sq_d = getRandomFloat(0, max_d, false);
        } else {
            sq_d = getRandomFloat(min_d, min_d * 20, false);
        }

        sq_d = pow(sq_d, 2);
        sq_y = getRandomFloat(0, sq_d, true);
        sq_x = sq_d - sq_y;
        sq_y = sqrt(sq_y);
        sq_x = sqrt(sq_x);

        if(rand() % 2) {
            sq_y = -sq_y;
        }

        if(rand() % 2) {
            sq_x = -sq_x;
        }

        if(i == 0) {
            point.x = 0.0f;
            point.y = 0.0f;
        } else {
            point.x = sq_x;
            point.y = sq_y;
        }

        /* Preparing a message in case of an error */
        sprintf(p_mess_string, "This condition must not be violated for the test.");
        p_mess_string += strlen(p_mess_string);
        sprintf(p_mess_string, "Point.y: %f, Point.x: %f", point.y, point.x);

        /* Radius check for test */
        float temp = pow(point.x, 2) + pow(point.y, 2);
        if(i >= NUMBER_OF_POINT / 2) {
            TEST_ASSERT_TRUE_MESSAGE(temp < pow(max_d, 2), mess_string);
        } else {
            TEST_ASSERT_TRUE_MESSAGE(temp > pow(min_d, 2), mess_string);
        }

        p_mess_string = mess_string;
        sprintf(p_mess_string, "Point.y: %f, Point.x: %f", point.y, point.x);

        status = setCoordinate(&leg, &point, false);
        TEST_ASSERT_EQUAL_INT_MESSAGE(status, LEG_STATUS_SUCCESS, mess_string);
    }
}


/**
 * @brief       Сhecking for valid points
 *
 * @details     It is checked that the methods return a success for a set of valid
 *              points and correct angles
 *
 */

void test_reachable_points(void) {

    /* Variable declaration */
    legStatus_t leg_status;
    leg_t leg;
    char mess_string[200];
    char *p_mess_string = mess_string;
    bool status;
    float angle_femur, angle_coxa, angle_temp;
    point_t point;

    /* Driver initialization */
    leg_status = initLeg(&leg, g_coxa_len, g_femur_len);
    TEST_ASSERT_EQUAL_INT(leg_status, LEG_STATUS_SUCCESS);

    for (int i = 0; i < NUMBER_OF_POINT; ++i) {

        /* Direct kinematic calculation */
        angle_coxa = getRandomFloat(0.0f, 180.0f, true);
        angle_femur = getRandomFloat(0.0f, 360.0f, true);
        status = calculatePoint(g_femur_len, g_coxa_len, angle_femur, angle_coxa, &point);
        TEST_ASSERT_TRUE(status);

        /* Preparing a message in case of an error */
        p_mess_string = mess_string;
        sprintf(p_mess_string, "Coxa len: %f. ", g_coxa_len);
        p_mess_string += strlen(p_mess_string);

        sprintf(p_mess_string, "Femur len: %f. ", g_femur_len);
        p_mess_string += strlen(p_mess_string);

        sprintf(p_mess_string, "Coxa angle: %f. ", angle_coxa);
        p_mess_string += strlen(p_mess_string);

        sprintf(p_mess_string, "Femur angle: %f", angle_femur);
        p_mess_string += strlen(p_mess_string);

        /* Inverse kinematic calculation */
        leg_status = setCoordinate(&leg, &point, false);
        TEST_ASSERT_EQUAL_INT_MESSAGE(leg_status, LEG_STATUS_SUCCESS, mess_string);

        /* Get angles */
        leg_status = getAngle(&leg, LIMB_COXA, &angle_temp);
        TEST_ASSERT_EQUAL_INT_MESSAGE(leg_status, LEG_STATUS_SUCCESS, mess_string);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, angle_coxa, angle_temp, mess_string);

        leg_status = getAngle(&leg, LIMB_FEMUR, &angle_temp);
        TEST_ASSERT_EQUAL_INT_MESSAGE(leg_status, LEG_STATUS_SUCCESS, mess_string);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, angle_femur, angle_temp, mess_string);

    }
}
