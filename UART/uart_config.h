/**
 * @file uart_config.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UART_CONFIG_H
#define UART_CONFIG_H

/**********************************************************************
* Includes
**********************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define NUMBER_OF_UART_CHANNELS              (6)
/**********************************************************************
* Typedefs
**********************************************************************/

typedef enum{
    PARITY_NONE,
    PARITY_EVEN,
    PARITY_ODD,
    PARITY_MAX,
}UART_PARITY;

typedef enum{
    STOP_BITS_1,
    STOP_BITS_2,
    STOP_BITS_MAX,
}UART_STOP_BITS;

typedef enum{
    DATA_BITS_8,
    DATA_BITS_9,
    DATA_BITS_MAX,
}UART_DATA_BITS;

typedef enum{
    UART_CHANNEL_1,
    UART_CHANNEL_2,
    UART_CHANNEL_3,
    UART_CHANNEL_4,
    UART_CHANNEL_5,
    UART_CHANNEL_6,
    UART_CHANNEL_MAX,
}UART_CHANNEL;
/**
 * @brief Tabla de configuraciones de los buses SPI del sistema.
 * 
 */
typedef struct{
    UART_CHANNEL channel;
    UART_PARITY parity;
    UART_STOP_BITS stopbits;
    UART_DATA_BITS databits;
    uint32_t baudrate;
}UART_Table;
/**
 * @brief Estructura de configuraciones SPI
 * 
 */
typedef struct{
    const UART_Table * const table;
    const int tableSize;
}UART_Config;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Devuelve un puntero a las configuraciones de buses SPI del sistema.
 * 
 * @return const SPI_Config* Configuraciones de buses SPI.
 */
const UART_Config* UART_GetConfig();

#ifdef __cplusplus
}
#endif


#endif /*UART_CONFIG_H*/