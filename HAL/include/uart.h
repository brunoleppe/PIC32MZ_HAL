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
#include "hal.h"
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
 * @param data Puntero a los datos de transmisi�n.
 * @param size Cantidad de datos.
 * 
 * @return Cantidad de datos env�ados. Si es menor que 0, se produjo un error.
 */
int UART_Write(UART_CHANNEL channel, void *data, size_t size);
/**
 * @brief Inicia una lectura por el canal UART.
 * La operaci�n de lectura contiene un puntero al b�ffer de lectura, el tama�o del b�ffer
 * y un caracter de terminaci�n. Cuando el caracter es 0 la lectura de UART se mantiene 
 * activa hasta que se llene el b�ffer.
 * 
 * @param channel Canal UART.
 * @param op Puntero a la estructura de operaci�n de lectura.
 * 
 * @return Cantidad de datos recibidos. Si es menor que 0, se prudojo un error.
 */
int UART_Read(UART_CHANNEL channel, UART_ReadOperation *op);

int UART_WriteByte(UART_CHANNEL channel, uint8_t data);

/**
 * @brief Funci�n para escribir en un registro del perif�rico UART.
 * 
 * @param address Direcci�n de memoria del registro.
 * @param val Valor a escribirse.
 */
void UART_RegisterWrite(uint32_t address, uint32_t val);
/**
 * @brief Funci�n para leer un registro del perif�rico UART.
 * 
 * @param address Direcci�n de memoria del registro
 * @return Valor le�do.
 */
uint32_t UART_RegisterRead(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif /*UART_H*/