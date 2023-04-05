//
// Created by bleppe on 17/03/23.
//

#ifndef UART_H
#define UART_H

/**********************************************************************
* Includes
**********************************************************************/

#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

#define UART_CHANNEL_1                                      0
#define UART_CHANNEL_2                                      1
#define UART_CHANNEL_3                                      2
#define UART_CHANNEL_4                                      3
#define UART_CHANNEL_5                                      4
#define UART_CHANNEL_6                                      5


#define UART_PARITY_NONE                                    0x0000
#define UART_PARITY_ODD                                     0x0001
#define UART_PARITY_EVEN                                    0x0002
#define UART_DATA_BITS_8                                    0x0000
#define UART_DATA_BITS_9                                    0x0008
#define UART_STOP_BITS_1                                    0x0000
#define UART_STOP_BITS_2                                    0x0010
#define UART_LOOP_BACK                                      0x0020
#define UART_RX_INVERTED                                    0x0040
#define UART_RX_DISABLED                                    0x0100
#define UART_TX_INVERTED                                    0x0080
#define UART_TX_DISABLED                                    0x0200

#define UART_CALLBACK_ENABLE_THRESHOLD                      0x0001
#define UART_CALLBACK_ENABLE_TERMINATION                    0x0002

/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

typedef enum{
    UART_CHANNEL_EVENT_BUFFER_FULL,
    UART_CHANNEL_EVENT_BYTE_RECEIVED,
    UART_CHANNEL_EVENT_READ_ERROR
}UART_CHANNEL_EVENT;

typedef enum
{
    UART_ERROR_NONE = 0,
    UART_ERROR_OVERRUN = 0x00000002,
    UART_ERROR_FRAMING = 0x00000004,
    UART_ERROR_PARITY  = 0x00000008
} UART_ERROR;

typedef int UART_Channel;
typedef uint32_t UART_Flags;
typedef void (*UART_Callback)(UART_Channel, UART_CHANNEL_EVENT event, uintptr_t context);
typedef struct{
    int fault;
    int tx;
    int rx;
}UART_IRQ_Vector;
/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

int         UART_initialize(UART_Channel channel, UART_Flags flags, int baudrate, uint8_t *rxBuffer, size_t bufferSize);
int         UART_setup(UART_Channel channel, UART_Flags flags, int baudrate);
size_t      UART_write(UART_Channel channel, uint8_t *txBuffer, size_t size);

size_t      UART_read(UART_Channel channel, uint8_t *rxBuffer, size_t size);
void        UART_read_start(UART_Channel channel);
void        UART_read_abort(UART_Channel channel);

uint8_t     UART_write_byte(UART_Channel channel, uint8_t data);
uint8_t     UART_read_byte(UART_Channel channel);
bool        UART_tx_ready(UART_Channel channel);
UART_ERROR  UART_error_get(UART_Channel channel);
void    UART_callback_register(UART_Channel channel, UART_Callback callback, uintptr_t context);

#ifdef __cplusplus
}
#endif
#endif



#endif //UART_H
