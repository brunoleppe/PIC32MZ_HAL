#ifndef GPIO_H
#define GPIO_H

#include "gpio_config.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Funci�n de inicializaci�n de los puertos del procesador.
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
 * @brief Activa o desactiva la interrupci�n por cambio de estado en el pin.
 * 
 * @param pin Pin seleccionado.
 * @param state Estado activado o desactivado de la interrupci�n.
 */
void GPIO_PinIrqSet(GPIO_PIN pin, GPIO_INTERRUPT state);
/**
 * @brief Lee el estado l�gico actual del pin.
 * 
 * @param pin Es el pin que se leer�, definido con el enumerador GPIO_PIN.
 * @return GPIO_STATE Es el estado l�gico del pin como HIGH o LOW.
 */
GPIO_STATE GPIO_PinRead(GPIO_PIN pin);
/**
 * @brief Escribe un estado l�gico al pin seleccionado.
 * 
 * @param pin  Es el pin que ser� escrito, definido con el enumerador GPIO_PIN.
 * @param state Es el estado l�gico que se quiere escribir en el pin, HIGH o LOW.
 */
void GPIO_PinWrite(GPIO_PIN pin, GPIO_STATE state);
/**
 * @brief Invierte el estado l�gico del pin seleccionado.
 * 
 */
void GPIO_PinToggle(GPIO_PIN pin);
/**
 * @brief Establece la direcci�n del pin como entrada o salida.
 * 
 * @param pin Es el pin al que se le cambiar� la direcci�n.
 * @param direction Nueva direcci�n del pin, INPUT o OUTPUT.
 */
void GPIO_PinDirectionSet(GPIO_PIN pin, GPIO_DIRECTION direction);
/**
 * @brief Funci�n utilizada para modificar un registro del perifperico GPIO.
 * 
 * @param address Direcci�n del registro.
 * @param val Valor que ser� escrito en el registro.
 */
void GPIO_RegisterWrite(uintptr_t address, TYPE val);
/**
 * @brief Funci�n utilizada para leer el estado de un registro del perif�rico GPIO.
 * 
 * @param address Direcci�n del registro.
 * @return TYPE Estado del registro.
 */
TYPE GPIO_RegisterRead(uintptr_t address);
/**
 * @brief Funci�n utilizada para registrar un callback para el pin especificado.
 * 
 * @param pin Pin del procesador.
 * @param callback Funci�n que se ejecutar� cuando se produzca una interrupci�n 
 * por cambio de estado en el pin especificado.
 * @param context Datos que ser�n pasados por la funci�n de callback y la aplicaci�n.
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