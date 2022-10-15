/**
 * @file spi.h
 * @author Bruno Leppe (bruno.leppe.dev@gmail.com)
 * @brief SPI peripheral definitions. 
 * @version 0.1
 * @date 2022-09-29
 */

/*******************************************************************************
* Copyright (c) 2022 Bruno Leppe
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
* 
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#ifndef SPI_H
#define SPI_H

/**********************************************************************
* Includes
**********************************************************************/

#include "hal.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**
 * Number of SPI peripherals of processor.
*/
#define NUMBER_OF_SPI_CHANNELS              (6)
/**********************************************************************
* Typedefs
**********************************************************************/
/**
 * @brief Struct that maps SPI peripheral registers. Hardware dependent.
*/
typedef struct _SPI_Instance volatile *SPI_Instance_t;
/**
 * @brief Struct that defines the data structure for SPI transfers.
 * 
 */
typedef struct _SPI_HANDLER SPI_Handler;
/**
 * @brief SPI callback functions definition
 * 
 */
typedef void (*SPI_Callback)(SPI_Handler*);

/**
 * @brief SPI error flags.
 * 
 */
typedef enum{
    /*Errores en la transferencia spi*/
    SPI_ERROR_NULL_BUFFERS = 1, ///<Both TX and RX buffers are NULL when calling SPI_Transfer.
    SPI_ERROR_ZERO_SIZE_BUFFER, ///<A buffer size of 0 was passed to a transfer function.     
    SPI_ERROR_BAUDRATE_TOO_LOW, ///<Specified baudrate too low, cannot configure baudrate generator.    
    SPI_ERROR_BAD_SPI_MODE,     ///<SPI mode not supported
    SPI_ERROR_CHANNEL_BUSY,     ///<SPI channel is busy.
}SPI_ERROR;
/**
 * @brief Possible SPI Modes for SPI channel.
 * 
 */
typedef enum{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
}SPI_MODE;
/**
 * @brief Possible SPI channel working mode.
 * 
 */
typedef enum{
    SPI_MASTER,
    SPI_SLAVE,
}SPI_MASTER_SLAVE;
/**
 * @brief Available SPI channel for current processor.
 * 
 */
typedef enum{
    SPI_CHANNEL_1=0,
    SPI_CHANNEL_2,
    SPI_CHANNEL_3,
    SPI_CHANNEL_4,
    SPI_CHANNEL_5,
    SPI_CHANNEL_6,
}SPI_CHANNEL;
/**
 * @brief Possible data sampling schemes for current processor.
 * 
 */
typedef enum{
    SPI_SAMPLE_END,
    SPI_SAMPLE_MID        
}SPI_DATA_SAMPLE;
/**
 * @brief Configuration table.
 * This table is used to configure SPI peripherals on initialization function.
 * 
 */
typedef struct{
    SPI_CHANNEL channel; ///<SPI channel to configure
    SPI_MODE mode; ///<SPI mode
    SPI_MASTER_SLAVE mastermode;///<SPI working mode
    uint32_t baudrate;///<SPI channel baudrate;
    SPI_DATA_SAMPLE sample;///<SPI channel sampling scheme
}SPI_Setup;
/**
 * @brief Structure that holds an array of SPI_Handler* and it's size.
 * Used to configure all SPI channels defined in the array of handlers. User must configure
 * SPI_Handlers beforehand. 
 * @see spi.c
 * 
 */
typedef struct{
    SPI_Handler ** const table; ///<Array of SPI_Handler*
    const int tableSize;///<Array size
}SPI_Config;

/**
 * @brief Struct that defines the data structure for SPI transfers.
 * 
 */
struct _SPI_HANDLER{
    const SPI_Instance_t      instance; ///<Structure that maps SPI peripheral registers.
    SPI_Setup           setup; ///<Configuration table of current SPI peripheral.
    
    uint8_t             *txBuffer; ///<Pointer to TX buffer.
    size_t              txSize; ///<Size of TX buffer.
    size_t              txCount; ///<Maintains the count of transfered bytes, when txCount == txSize all bytes are transmited.
    
    uint8_t             *rxBuffer; ///<Pointer to RX buffer.
    size_t              rxSize; ///<Size of RX buffer.
    size_t              rxCount; ///<Maintains the count of transfered bytes, when rxCount == rxSize all bytes are received.
    
    size_t              dummySize; ///<Member that specifies dummy bytes to transmit when a transfer is only receiving data.
    
    SPI_ERROR           error; ///<Contains the error.
    
    uint32_t            usDelay; ///<Time in us to wait between every transfered byte. Useful when dealing with QTouch comms. Used in blocking transfers.                               
    uint8_t             dummyByte;///<Value to transmit when a transfer is only receiving data.
    
    bool                busy; ///<Busy state of the SPI channel. True when a transfer is in progress.
    
    SPI_Callback        errorCallback; ///<Function to be called when an error occurs.
    SPI_Callback        cpltCallback; ///<Function to be called when a byte has been transfered.
    SPI_Callback        halfCallback; ///<Function to be called when a transfer is completed.
};

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/**
 * @brief Function to get the configuration table of the SPI peripherals of current processor.
 * 
 * @return const SPI_Config* Pointer to the configuration table.
 */
const SPI_Config* SPI_GetConfig();
/**
 * @brief Function that returns the handler associated to the specific SPI channel.
 * 
 * @param channel SPI channel.
 * @return const SPI_Handler_t The handler object associated to the SPI channel. 
 */
SPI_Handler* SPI_GetSpiHandler(SPI_CHANNEL channel);
/**
 * @brief Function used to initialize the SPI perihperals.
 * Example:
 * @code
 * SPI_Init(SPI_GetConfig());
 * @endcode
 * @param config Configuration table.
 */
void SPI_Init(const SPI_Config *config);
/**
 * @brief Function used to start a blocking SPI transfer.
 * 
 * @param handler Handler of SPI channel.
 * @param txBuffer Transmit buffer, can be NULL if rxBuffer is not NULL
 * @param rxBuffer Receive Buffer, can be NULL if txBuffer is not NULL
 * @param size Number of bytes to transmit and receive.
 * @return int Number of bytes transfered. Returns -1 in case of error.
 */
int SPI_Transfer(SPI_Handler *handler, void *txBuffer, void *rxBuffer, size_t size);
/**
 * @brief Function used to start a blocking SPI transmition.
 * 
 * @param handler Handler of SPI channel.
 * @param txBuffer Transmit buffer.
 * @param size Number of bytes to transmit and receive.
 * @return int Number of bytes transfered. Returns -1 in case of error.
 */
static inline int SPI_Write(SPI_Handler *handler, void *txBuffer, size_t size){
    return SPI_Transfer(handler,txBuffer,NULL,size);
}
/**
 * @brief Function used to start a blocking SPI reception.
 * 
 * @param handler Handler of SPI channel.
 * @param rxBuffer Receive buffer.
 * @param size Number of bytes to transmit and receive.
 * @return int Number of bytes transfered. Returns -1 in case of error.
 */
static inline int SPI_Read(SPI_Handler *handler, void *rxBuffer, size_t size){
    return SPI_Transfer(handler,NULL,rxBuffer,size);
}
/**
 * @brief Function used to start a non blocking SPI transfer.
 * Transfer is done by interrupt handlers. If not NULL, callback functions are called.
 * 
 * @param handler Handler of SPI channel.
 * @param txBuffer Transmit buffer, can be NULL if rxBuffer is not NULL
 * @param rxBuffer Receive Buffer, can be NULL if txBuffer is not NULL
 * @param size Number of bytes to transmit and receive.
 * @return True when no transfer was initiated. False on failure. 
 */
bool SPI_TransferAsync(SPI_Handler *handler, void *txBuffer, void *rxBuffer, size_t size);
/**
 * @brief Function used to trasmit and receive a single byte.
 * Use this function to quickly send and receive a byte without the overhead of a full transfer. 
 * 
 * @param handler Handler of SPI channel.
 * @param data byte to transmit
 * @return uint8_t byte received.
 */
uint8_t SPI_TransferByte(SPI_Handler *handler, uint8_t data);
/**
 * @brief Function used to reconfigure the SPI peripheral specified by the handler.
 * 
 * @param handler Handler of SPI channel.
 * @param setup Pointer to the steup structure.
 * @return bool True on success, false on failure.
 */
bool SPI_TransferSetup(SPI_Handler *handler, SPI_Setup *setup);

/**
 * @brief Function used to register a function to be called when an error occurs.
 * 
 * @param handler Handler of SPI channel.
 * @param callback callback function
 */
static inline
void SPI_ErrorCallbackRegister(SPI_Handler *handler,SPI_Callback callback)
{
    handler->errorCallback = callback;
}
/**
 * @brief Function used to register a function to be called when a byte has been transfered.
 * 
 * @param handler Handler of SPI channel.
 * @param callback callback function
 */
static inline
void SPI_CpltCallbackRegister(SPI_Handler *handler,SPI_Callback callback)
{
    handler->cpltCallback = callback;
}
/**
 * @brief Function used to register a function to be called when a transfer is completed.
 * 
 * @param handler Handler of SPI channel.
 * @param callback callback function
 */
static inline
void SPI_HalfCpltcallbackRegister(SPI_Handler *handler,SPI_Callback callback)
{
    handler->halfCallback = callback;
}

/**
 * @brief Function used to write a value to a specific register of the SPI perihperal.
 * Expert mode function.
 * 
 * @param address address of register.
 * @param value Value to write to register.
 */
void SPI_RegisterWrite(uint32_t address, uint32_t value);
/**
 * @brief Funciton used to read a vuela of a specific register of the SPI perihperal.
 * Expert mode function.
 * 
 * @param address address of register.
 * @return value of register.
 */
uint32_t SPI_RegisterRead(uint32_t address);


#ifdef __cplusplus
}
#endif

#endif /*SPI_H*/