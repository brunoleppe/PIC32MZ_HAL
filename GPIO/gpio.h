#ifndef GPIO_H
#define GPIO_H

#include "gpio_config.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Función de inicialización de los puertos del procesador.
 * 
 * @param config Puntero a la tabla de configuraciones.
 * @code
 * const GPIO_Config *config = GPIO_GetConfig();
 *
 * GPIO_Init(config);
 * @endcode
 * @see GPIO_GetConfig
 */
void GPIO_Init(const GPIO_Config* config);
/**
 * @brief Activa o desactiva resistencias de pull-up en el pin seleccionado.
 * 
 * @param pin Pin Seleccionado
 * @param state Estado activado o desactivado de la resistencia de pull-up.
 */
void GPIO_PinPullupSet(GPIO_PIN pin, GPIO_PULLUP state);
/**
 * @brief Activa o desactiva resistencias de pull-down en el pin seleccionado.
 * 
 * @param pin Pin Seleccionado
 * @param state Estado activado o desactivado de la resistencia de pull-down.
 */
void GPIO_PinSetPullDown(GPIO_PIN pin, GPIO_PULLDOWN state);
/**
 * @brief Activa o desactiva la interrupción por cambio de estado en el pin.
 * 
 * @param pin Pin seleccionado.
 * @param state Estado activado o desactivado de la interrupción.
 */
void GPIO_PinIrqSet(GPIO_PIN pin, GPIO_INTERRUPT state);
/**
 * @brief Lee el estado lógico actual del pin.
 * 
 * @param pin Es el pin que se leerá, definido con el enumerador GPIO_PIN.
 * @return GPIO_STATE Es el estado lógico del pin como HIGH o LOW.
 */
GPIO_STATE GPIO_PinRead(GPIO_PIN pin);
/**
 * @brief Escribe un estado lógico al pin seleccionado.
 * 
 * @param pin  Es el pin que será escrito, definido con el enumerador GPIO_PIN.
 * @param state Es el estado lógico que se quiere escribir en el pin, HIGH o LOW.
 */
void GPIO_PinWrite(GPIO_PIN pin, GPIO_STATE state);
/**
 * @brief Invierte el estado lógico del pin seleccionado.
 * 
 */
void GPIO_PinToggle(GPIO_PIN pin);
/**
 * @brief Establece la dirección del pin como entrada o salida.
 * 
 * @param pin Es el pin al que se le cambiará la dirección.
 * @param direction Nueva dirección del pin, INPUT o OUTPUT.
 */
void GPIO_PinDirectionSet(GPIO_PIN pin, GPIO_DIRECTION direction);
/**
 * @brief Función utilizada para modificar un registro del perifperico GPIO.
 * 
 * @param address Dirección del registro.
 * @param val Valor que será escrito en el registro.
 */
void GPIO_RegisterWrite(uintptr_t address, TYPE val);
/**
 * @brief Función utilizada para leer el estado de un registro del periférico GPIO.
 * 
 * @param address Dirección del registro.
 * @return TYPE Estado del registro.
 */
TYPE GPIO_RegisterRead(uintptr_t address);
/**
 * @brief Función utilizada para registrar un callback para el pin especificado.
 * 
 * @param pin Pin del procesador.
 * @param callback Función que se ejecutará cuando se produzca una interrupción 
 * por cambio de estado en el pin especificado.
 * @param context Datos que serán pasados por la función de callback y la aplicación.
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