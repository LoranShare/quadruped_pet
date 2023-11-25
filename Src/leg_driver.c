/**
 *******************************************************************************
 * @file        FILE_NAME.c <---------------|       Put here file name
 * @author      Gevorgyan Ovik
 * @brief       BRIEF <---------------------|       Put here brief of module
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "leg_driver.h"


/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
legStatus_t initLeg(leg_t *const leg, float coxa_len, float femur_len) {
	return LEG_STATUS_ERROR;
}

legStatus_t setCoordinate(leg_t *const leg, const point_t *const point, bool truncated) {
	return LEG_STATUS_ERROR;
}

legStatus_t getAngle(const leg_t *const leg, const limb_t limb, float *value) {
	return LEG_STATUS_ERROR;
}
