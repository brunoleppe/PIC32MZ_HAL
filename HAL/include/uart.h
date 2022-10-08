/**
 * @file uart.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UART_H
#define UART_H

/**********************************************************************
* Includes
**********************************************************************/
#include "uart_config.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/
enum UART_ERROR{
    UART_BAD_BAUDRATE = 1,
    UART_BAD_PARITY,
    UART_BAD_STOPBITS,
    UART_BAD_CHANNEL,
    UART_BAD_DATABITS,
            
};

typedef struct{
    void *rxBuffer;
    size_t bufferSize;
    uint8_t endCharacter;
}UART_ReadOperation;
/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Inicializa el controlador de interrupciones con las configuraciones 
 * proporcionadas.
 * 
 * @param config Configuraciones del controlador.
 */
int UART_Init(const UART_Config *config);
/**
 * @brief Inicia una escritura de datos en el canal UART.
 * 
 * @param channel Canal UART.
 * @param data Puntero a los datos de transmisión.
 * @param size Cantidad de datos.
 * 
 * @return Cantidad de datos envíados. Si es menor que 0, se produjo un error.
 */
int UART_Write(UART_CHANNEL channel, void *data, size_t size);
/**
 * @brief Inicia una lectura por el canal UART.
 * La operación de lectura contiene un puntero al búffer de lectura, el tamaño del búffer
 * y un caracter de terminación. Cuando el caracter es 0 la lectura de UART se mantiene 
 * activa hasta que se llene el búffer.
 * 
 * @param channel Canal UART.
 * @param op Puntero a la estructura de operación de lectura.
 * 
 * @return Cantidad de datos recibidos. Si es menor que 0, se prudojo un error.
 */
int UART_Read(UART_CHANNEL channel, UART_ReadOperation *op);

int UART_WriteByte(UART_CHANNEL channel, uint8_t data);

/**
 * @brief Función para escribir en un registro del periférico UART.
 * 
 * @param address Dirección de memoria del registro.
 * @param val Valor a escribirse.
 */
void UART_RegisterWrite(uint32_t address, uint32_t val);
/**
 * @brief Función para leer un registro del periférico UART.
 * 
 * @param address Dirección de memoria del registro
 * @return Valor leído.
 */
uint32_t UART_RegisterRead(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif /*UART_H*/