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

#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

#define SPI_CHANNEL_1                       (0)
#define SPI_CHANNEL_2                       (1)
#define SPI_CHANNEL_3                       (2)
#define SPI_CHANNEL_4                       (3)
#define SPI_CHANNEL_5                       (4)
#define SPI_CHANNEL_6                       (5)

/*Configuration Flags*/
#define SPI_MODE_0                          (0x0000)
#define SPI_MODE_1                          (0x0001)
#define SPI_MODE_2                          (0x0002)
#define SPI_MODE_3                          (0x0004)
#define SPI_SLAVE                           (0x0000)
#define SPI_MASTER                          (0x0010)
#define SPI_SAMPLE_MID                      (0x0000)
#define SPI_SAMPLE_END                      (0x0020)
#define SPI_DATA_BITS_8                     (0x0000)
#define SPI_DATA_BITS_16                    (0x0040)
#define SPI_DATA_BITS_32                    (0x0080)
#define SPI_SDO_DISABLE                     (0x0100)
#define SPI_SDI_DISABLE                     (0x0200)
#define SPI_SS_ENABLE                       (0x0400)
#define SPI_IRQ_ENABLE                      (0x0800)

#define SPI_DEFAULT                         (SPI_MODE_0 | SPI_MASTER | SPI_SAMPLE_MID | SPI_DATA_BITS_8)
/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

typedef uint32_t SPI_Channel;
typedef struct{
    uint32_t        usDelay;
    uint8_t         stopChar;
    bool            stopCharEnable;
}SPI_TransferSetup;
typedef void (*SPI_Callback)(SPI_Channel, uintptr_t);
typedef struct{
    int fault;
    int tx;
    int rx;
}SPI_IRQ_Vector;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

int         SPI_initialize              (uint32_t spiChannel, uint32_t configFlags, uint32_t baudrate);
size_t      SPI_transfer                (uint32_t spiChannel, void *txBuffer, void *rxBuffer, size_t size);
uint8_t     SPI_byte_transfer           (uint32_t spiChannel, uint8_t data);
bool        SPI_is_busy                 (uint32_t spiChannel);
void        SPI_callback_register       (SPI_Channel spiChannel, SPI_Callback callback, uintptr_t context);
bool        SPI_transfer_isr            (uint32_t spiChannel, void* txBuffer, void* rxBuffer, size_t size);
void        SPI_rx_interrupt_handler    (SPI_Channel spiChannel);
void        SPI_tx_interrupt_handler    (SPI_Channel spiChannel);
bool        SPI_write_dma               (SPI_Channel spiChannel, uint32_t dmaChannel, void *txBuffer, size_t size);
bool        SPI_read_dma                (SPI_Channel spiChannel, uint32_t dmaChannel, void *rxBuffer, size_t size);
void        SPI_setup                   (SPI_Channel spiChannel, uint32_t configFlags, uint32_t baudrate);


static inline
size_t      SPI_write           (uint32_t spiChannel, void *txBuffer, size_t size)
{
    return SPI_transfer(spiChannel, txBuffer, NULL, size);
}

static inline
size_t      SPI_read            (uint32_t spiChannel, void *rxBuffer, size_t size)
{
    return SPI_transfer(spiChannel, NULL, rxBuffer, size);
}

static inline
size_t      SPI_write_isr       (uint32_t spiChannel, void *txBuffer, size_t size)
{
    return SPI_transfer_isr(spiChannel, txBuffer, NULL, size);
}

static inline
size_t      SPI_read_isr        (uint32_t spiChannel, void *rxBuffer, size_t size)
{
    return SPI_transfer_isr(spiChannel, NULL, rxBuffer, size);
}

#ifdef __cplusplus
}
#endif
#endif
#endif /*SPI_H*/