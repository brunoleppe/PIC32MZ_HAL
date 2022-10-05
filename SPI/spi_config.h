/**
 * @file spi_config.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

/**********************************************************************
* Includes
**********************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define NUMBER_OF_SPI_CHANNELS              (6)
/**********************************************************************
* Typedefs
**********************************************************************/

typedef enum{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
}SPI_MODE;

typedef enum{
    SPI_MASTER,
    SPI_SLAVE,
}SPI_MASTER_MODE;

typedef enum{
    SPI_CHANNEL_1=0,
    SPI_CHANNEL_2,
    SPI_CHANNEL_3,
    SPI_CHANNEL_4,
    SPI_CHANNEL_5,
    SPI_CHANNEL_6,
    SPI_CHANNEL_MAX,
}SPI_CHANNEL;

typedef enum{
    SPI_SAMPLE_END,
    SPI_SAMPLE_MID        
}SPI_DATA_SAMPLE;
/**
 * @brief Tabla de configuraciones de los buses SPI del sistema.
 * 
 */
typedef struct{
    SPI_CHANNEL channel;
    SPI_MODE mode;
    SPI_MASTER_MODE mastermode;
    uint32_t baudrate;
    SPI_DATA_SAMPLE sample;
}SPI_Table;
/**
 * @brief Estructura de configuraciones SPI
 * 
 */
typedef struct{
    const SPI_Table * const table;
    const int tableSize;
}SPI_Config;

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
const SPI_Config* SPI_GetConfig();

#ifdef __cplusplus
}
#endif


#endif /*SPI_CONFIG_H*/