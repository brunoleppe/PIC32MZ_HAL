/**
 * @file gpio.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief GPIO Interface.
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GPIO_H
#define GPIO_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal.h"
#include "gpio_config.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief GPIO Peripheral initialization function.
 * 
 * @param config Configuration table.
 * @code
 * const GPIO_Config *config = GPIO_GetConfig();
 *
 * GPIO_Init(config);
 * @endcode
 * @see GPIO_GetConfig
 */
void GPIO_Init(const GPIO_Config* config);
/**
 * @brief Function used to enable or disable internal pull-up resistors on current pin.
 * Pull-up resistors can only be used when pin is configured as igital input.
 * 
 * @param pin Current pin.
 * @param state PULLUP_ENABLE or PULLUP_DISABLE to enable or disable internal pull-up resistors.
 */
void GPIO_PinPullupSet(GPIO_PIN pin, GPIO_PULLUP state);
/**
 * @brief Function used to enable or disable internal pull-down resistors on current pin.
 * Pull-down resistors can only be used when pin is configured as igital input.
 * 
 * @param pin Current pin.
 * @param state PULLDOWN_ENABLE or PULLDOWN_DISABLE to enable or disable internal pull-up resistors.
 */
void GPIO_PinSetPullDown(GPIO_PIN pin, GPIO_PULLDOWN state);
/**
 * @brief Function used to enable or disable state change interrupt on current pin.
 * This function configures GPIO peripheral IRQ registers only, aditional configuration
 * of processor's interrupt controller may be required.
 * 
 * @param pin Current pin.
 * @param state GPIO_IRQ_ENABLE or GPIO_IRQ_DISABLE to modify interrupt registers
 */
void GPIO_PinIrqSet(GPIO_PIN pin, GPIO_INTERRUPT state);
/**
 * @brief Funtion used to read the current pin state.
 * This function can be used to read a pin configured as digital input or digital output.
 * 
 * @param Current pin.
 * @return HIGH on high level, LOW on low level.
 */
GPIO_STATE GPIO_PinRead(GPIO_PIN pin);
/**
 * @brief Function used to write a desired level on the current pin.
 * This function only affects pins configured as digital outputs. Input pins are silently ingonred.
 * 
 * @param pin  Current pin
 * @param state HIGH or LOW to modify pin level.
 */
void GPIO_PinWrite(GPIO_PIN pin, GPIO_STATE state);
/**
 * @brief Function used to toggle pin state.
 * This function only affects pins configured as digital outputs. Input pins are silently ingonred.
 * 
 */
void GPIO_PinToggle(GPIO_PIN pin);
/**
 * @brief Function used to set pin direction.
 * 
 * @param pin Current pin.
 * @param direction D_INPUT, D_OUTPUT or A_INPUT to modify pin as digital input, digital output or
 * analog input.
 */
void GPIO_PinDirectionSet(GPIO_PIN pin, GPIO_DIRECTION direction);
/**
 * @brief Function used to write to specific GPIO registers.
 * Use this function to modify special registers that aren't managed by the HAL.
 * This function is considered "expert mode".
 * @param address Memory address of register to be modified.
 * @param val Value to be written to the register.
 */
void GPIO_RegisterWrite(uintptr_t address, TYPE val);
/**
 * @brief Function used to read a specific GPIO register state.
 * Use this function to read special registers that aren't managed by the HAL.
 * This function is considered "expert mode".
 * 
 * @param address Memory address of register to be read.
 * @return TYPE Value read form register.
 */
TYPE GPIO_RegisterRead(uintptr_t address);
/**
 * @brief Function used to register a callback function for stata change interrupts.
 * The callback function will be executed whenever a state change interrupt is triggered on
 * the specified PIN. User can register data to be passed to the callback function.
 * 
 * @param pin Specified pin of the callback function.
 * @param callback Callback function.
 * @param context User defined data to be passed to the callback function.
 */
void GPIO_CallbackRegister(
        GPIO_PIN pin, 
        GPIO_CallbackFunction callback, 
        uintptr_t context
);

#ifdef __cplusplus
}
#endif

#endif