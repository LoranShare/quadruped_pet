/**
 *******************************************************************************
 * @file        leg_driver.c
 * @author      Gevorgyan Ovik
 * @brief       Inverse kinematics driver
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "leg_driver.h"

#include <string.h>

#include "debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define IS_LEG_LIMB(LIMB) ((LIMB == LIMB_COXA) || (LIMB == LIMB_FEMUR))
#define IS_LEG_LIMB_LEN

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
legStatus_t initLeg(leg_t *const leg, float coxa_len, float femur_len) {
    if (!leg) {
        PRNT_ERROR("Null pointer");
        return LEG_STATUS_BAD_PTR;
    }

    // assert_param(IS_LEG_LIMB_LEN(coxa_len));
    // assert_param(IS_LEG_LIMB_LEN(femur_len));

    memset(leg, 0, sizeof(*leg));
    leg->femur_len = femur_len;
    leg->coxa_len = coxa_len;

    return LEG_STATUS_SUCCESS;
}

legStatus_t setCoordinate(leg_t *const leg, const point_t *const point, bool truncated) {
    if (!leg || !point) {
        PRNT_ERROR("Null pointer");
        return LEG_STATUS_BAD_PTR;
    }

    return LEG_STATUS_ERROR;
}

legStatus_t getAngle(const leg_t *const leg, const limb_t limb, float *value) {
    if (!leg || !value) {
        PRNT_ERROR("Null pointer");
        return LEG_STATUS_BAD_PTR;
    }

    assert_param(IS_LEG_LIMB(limb));

    return LEG_STATUS_ERROR;
}
