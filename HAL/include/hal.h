/**
 * @file hal.h
 * @author Bruno Leppe (bruno.leppe.dev@gmail.com)
 * @brief HAL global definitions 
 * @version 0.1
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**********************************************************************
* Includes
**********************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

#define HAL_SYSTEM_CLOCK                    (200000000UL)
#define HAL_SPI_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)
#define HAL_UART_PERIPHERAL_CLOCK           (HAL_SYSTEM_CLOCK/2)
#define HAL_GPIO_PERIPHERAL_CLOCK           (HAL_SYSTEM_CLOCK/2)
#define HAL_PWM_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)


/**********************************************************************
* Typedefs
**********************************************************************/

typedef struct _MemRegister volatile const * MemRegister;


