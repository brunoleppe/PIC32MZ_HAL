#ifndef HAL_DEFS_H
#define HAL_DEFS_H

#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "hal_config.h"

#define HAL_SPI_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)
#define HAL_UART_PERIPHERAL_CLOCK           (HAL_SYSTEM_CLOCK/2)
#define HAL_GPIO_PERIPHERAL_CLOCK           (HAL_SYSTEM_CLOCK/2)
#define HAL_PWM_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)
#define HAL_TMR_PERIPHERAL_CLOCK            (HAL_SYSTEM_CLOCK/2)

typedef uint32_t WORD;

#define HAL_WEAK_FUNCTION               __attribute__(( weak ))
#endif
#endif //HAL_DEFS_H
