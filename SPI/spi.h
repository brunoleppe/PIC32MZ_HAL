/**
 * @file spi.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SPI_H
#define SPI_H

/**********************************************************************
* Includes
**********************************************************************/
#include "spi_config.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

typedef enum{
    /*Errores en la transferencia spi*/
    SPI_ERROR_NULL_BUFFERS = -1,
    SPI_ERROR_ZERO_SIZE_BUFFER = -2,
            
    SPI_ERROR_CHANNEL_OUT_OF_BOUNDS = -3,
       
    SPI_ERROR_BAUDRATE_TOO_LOW = -4,     
    SPI_ERROR_BAD_SPI_MODE = -5,
}SPI_ERROR;

typedef struct{
    SPI_MODE mode;
    SPI_DATA_SAMPLE sample;
    uint32_t baudrate;
    uint8_t dummyByte;
}SPI_Setup;

typedef struct{
    uint8_t dummyData;
    void *txBuffer;
    void *rxBuffer;
    uint32_t usDelay;
    size_t size;
    
}SPI_TransferParam;
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
void SPI_Init(const SPI_Config *config);
/**
 * @brief Inicia una transferencia de datos por el canal SPI establecido.
 * 
 * @param channel Canal SPI
 * @param txBuffer Búffer de transmisión de datos.
 * @param rxBuffer Búffer de recepción de datos.
 * @param size Cantidad de bytes que se van a transmitir.
 * 
 * @return La cantidad de bytes enviados. Si el resultado es menor a 0 hubo un
 * error.
 */
//int SPI_Transfer(SPI_CHANNEL channel, void *txBuffer, void *rxBuffer, size_t size);
int SPI_Transfer(SPI_CHANNEL channel, SPI_TransferParam *transfer);
/**
 * 
 * @param channel
 * @param data
 * @return 
 */
uint8_t SPI_TransferByte(SPI_CHANNEL channel, uint8_t data);
/**
 * @brief Configura el canal SPI con los parámetros proporionados
 * 
 * @param channel Canal SPI.
 * @param setup Estructura de parámetros para la configuración del canal.
 * 
 * @return Cero si se pudo configurar el canal. Si el resultado es menor a 0 hubo
 * un error.
 */
int SPI_TrasferSetup(SPI_CHANNEL channel, SPI_Setup *setup);
/**
 * @brief Escribe en un registro del periférico SPI.
 * 
 * @param address Dirección de memoria del registro.
 * @param value Valor que será escrito en el registro.
 */
void SPI_RegisterWrite(uint32_t address, uint32_t value);
/**
 * @brief Lee el contenido de un registro del periférico  SPI.
 * 
 * @param address Dirección de memoria del registro.
 * @return uint32_t Contenido del registro.
 */
uint32_t SPI_RegisterRead(uint32_t address);


#ifdef __cplusplus
}
#endif

#endif /*SPI_H*/