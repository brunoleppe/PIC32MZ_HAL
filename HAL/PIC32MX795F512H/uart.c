/**
* @file uart.c
* @author Bruno Leppe
* @brief
* @version 0.1
* @date 2022-09-28
*
* @copyright Copyright (c) 2022
*
*/

/**********************************************************************
* Includes
**********************************************************************/
#include <xc.h>
#include "uart.h"
#include "pic32mx_registers.h"
#include "evic.h"
#include "system.h"
#include "hal_ring_buffer.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define UART_BASE                               _UART1_BASE_ADDRESS
#define UART_NUMBER_OF_CHANNELS                 (6)
#define UART_PERIPHERAL_INTERVAL                (0x200)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define UART_DESCRIPTOR(channel)                (descriptors[channel])
#define UART_RX_INTERRUPT_CHANNEL(channel)      (uartIRQBase[channel] + 1)
#define UART_TX_INTERRUPT_CHANNEL(channel)      (uartIRQBase[channel] + 2)
#define UART_FAULT_INTERRUPT_CHANNEL(channel)   (uartIRQBase[channel])
/**********************************************************************
* Module Typedefs
**********************************************************************/
typedef struct{
    bool            txBusy;
    bool            rxBusy;
    bool            threshold;
    bool            termination;


    UART_ERROR      error;

    uint8_t         *txBuffer;
    size_t          txCount;
    size_t          txSize;
    UART_Callback   callback;
    uintptr_t       context;
    RingBuffer      rxBuffer;
}UART_Object;
/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static UART_Object uartObjects[UART_NUMBER_OF_CHANNELS];
static const EVIC_CHANNEL uartIRQBase[UART_NUMBER_OF_CHANNELS]={
        EVIC_CHANNEL_UART1_ERR,
        EVIC_CHANNEL_UART2_ERR,
        EVIC_CHANNEL_UART3_ERR,
        EVIC_CHANNEL_UART4_ERR,
        EVIC_CHANNEL_UART5_ERR,
        EVIC_CHANNEL_UART6_ERR,
};
static const UART_Descriptor descriptors[]={
        [UART_CHANNEL_1] = (UART_Descriptor)&U1MODE,
        [UART_CHANNEL_2] = (UART_Descriptor)&U2MODE,
        [UART_CHANNEL_3] = (UART_Descriptor)&U3MODE,
        [UART_CHANNEL_4] = (UART_Descriptor)&U4MODE,
        [UART_CHANNEL_5] = (UART_Descriptor)&U5MODE,
        [UART_CHANNEL_6] = (UART_Descriptor)&U6MODE,
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static int UART_baudrate(UART_Channel channel, int baudrate);
static void  UART_error_clear(UART_Channel channel);
/**********************************************************************
* Function Definitions
**********************************************************************/
//
//#define UART_PARITY_NONE                                    0x0000
//#define UART_PARITY_ODD                                     0x0001
//#define UART_PARITY_EVEN                                    0x0002
//#define UART_DATA_BITS_8                                    0x0000
//#define UART_DATA_BITS_9                                    0x0008
//#define UART_STOP_BITS_1                                    0x0000
//#define UART_STOP_BITS_2                                    0x0010
//#define UART_LOOP_BACK                                      0x0020
//#define UART_RX_INVERTED                                    0x0040
//#define UART_RX_DISABLED                                    0x0100
//#define UART_TX_INVERTED                                    0x0080
//#define UART_TX_DISABLED                                    0x0200

int     UART_initialize(UART_Channel channel, UART_Flags flags, int baudrate, uint8_t *rxBuffer, size_t bufferSize)
{
    EVIC_channel_clr(UART_FAULT_INTERRUPT_CHANNEL(channel));
    EVIC_channel_clr(UART_RX_INTERRUPT_CHANNEL(channel));
    EVIC_channel_clr(UART_TX_INTERRUPT_CHANNEL(channel));

    ring_buffer_initialize(&uartObjects[channel].rxBuffer,bufferSize, rxBuffer);
    uartObjects[channel].txBusy = false;
    uartObjects[channel].rxBusy = false;

    UART_setup(channel, flags, baudrate);

    UART_DESCRIPTOR(channel)->umode.set = _U1MODE_ON_MASK;

    return 0;
}
int     UART_setup(UART_Channel channel, UART_Flags flags, int baudrate)
{
    UART_DESCRIPTOR(channel)->umode.reg = 0;
    int brg = UART_baudrate(channel, baudrate);
    if(brg < 0)
        return -1;
    UART_DESCRIPTOR(channel)->ubrg.reg = brg;

    if((flags & UART_PARITY_EVEN) == UART_PARITY_EVEN)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_PDSEL0_MASK;
    else if((flags & UART_PARITY_ODD) == UART_PARITY_ODD)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_PDSEL1_MASK;
    if((flags & UART_DATA_BITS_9) == UART_DATA_BITS_9)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_PDSEL_MASK;
    if((flags & UART_STOP_BITS_2) == UART_STOP_BITS_2)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_STSEL_MASK;
    if((flags & UART_LOOP_BACK) == UART_LOOP_BACK)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_LPBACK_MASK;

//    UART_DESCRIPTOR(channel)->usta.set =  _U1STA_URXEN_MASK | _U1STA_UTXEN_MASK;
    UART_DESCRIPTOR(channel)->usta.set = _U1STA_UTXEN_MASK;

    if((flags & UART_RX_INVERTED) == UART_RX_INVERTED)
        UART_DESCRIPTOR(channel)->umode.set = _U1MODE_RXINV_MASK;
    if((flags & UART_RX_DISABLED) == UART_RX_DISABLED)
        UART_DESCRIPTOR(channel)->usta.clr = _U1STA_URXEN_MASK;
    if((flags & UART_TX_INVERTED) == UART_TX_INVERTED)
        UART_DESCRIPTOR(channel)->usta.set = _U1STA_UTXINV_MASK;
    if((flags & UART_TX_DISABLED) == UART_TX_DISABLED)
        UART_DESCRIPTOR(channel)->usta.clr = _U1STA_UTXEN_MASK;
    return 0;
}

size_t  UART_write(UART_Channel channel, uint8_t *txBuffer, size_t size)
{
    size_t processedSize = 0;

    if(txBuffer == NULL || size == 0)
        return 0;

    uartObjects[channel].txBusy = true;

    while( size > processedSize )
    {
        /* Wait while TX buffer is full */
        while (UART_DESCRIPTOR(channel)->usta.reg & _U1STA_UTXBF_MASK);

        if (( UART_DESCRIPTOR(channel)->umode.reg & (_U1MODE_PDSEL0_MASK | _U1MODE_PDSEL1_MASK)) == (_U1MODE_PDSEL0_MASK | _U1MODE_PDSEL1_MASK))
        {
            /* 9-bit mode */
            UART_DESCRIPTOR(channel)->utxreg.reg = *(uint16_t*)txBuffer;
            txBuffer += 2;
        }
        else
        {
            /* 8-bit mode */
            UART_DESCRIPTOR(channel)->utxreg.reg = *txBuffer++;
        }

        processedSize++;
    }

    uartObjects[channel].txBusy = false;
    return processedSize;
}

void UART_read_start(UART_Channel channel)
{
    UART_error_clear(channel);
    UART_DESCRIPTOR(channel)->usta.set = _U1STA_URXEN_MASK;
    EVIC_channel_set(UART_RX_INTERRUPT_CHANNEL(channel));
    EVIC_channel_set(UART_FAULT_INTERRUPT_CHANNEL(channel));
}

size_t UART_read(UART_Channel channel, uint8_t *rxBuffer, size_t size)
{
    size_t bytesRead = 0;
    while (ring_buffer_pull(&uartObjects[channel].rxBuffer,rxBuffer++) && (bytesRead < size))
    {
        bytesRead++;
    }
    return bytesRead;
}
void        UART_read_abort(UART_Channel channel)
{
    UART_DESCRIPTOR(channel)->usta.clr = _U1STA_URXEN_MASK;
    EVIC_channel_clr(UART_RX_INTERRUPT_CHANNEL(channel));
    EVIC_channel_clr(UART_FAULT_INTERRUPT_CHANNEL(channel));
}

uint8_t UART_write_byte(UART_Channel channel, uint8_t data)
{
    while (UART_DESCRIPTOR(channel)->usta.reg & _U1STA_UTXBF_MASK);
    UART_DESCRIPTOR(channel)->utxreg.reg = data;
    return data;
}
uint8_t UART_read_byte(UART_Channel channel)
{
    return(UART_DESCRIPTOR(channel)->urxreg.reg);
}

bool    UART_tx_ready(UART_Channel channel)
{
    if(!(UART_DESCRIPTOR(channel)->usta.reg & _U1STA_UTXBF_MASK) && !uartObjects[channel].txBusy)
    {
        return true;
    }
    return false;
}

UART_ERROR  UART_error_get(UART_Channel channel)
{
    return uartObjects[channel].error;
}

bool    UART_write_isr(UART_Channel channel, uint8_t *txBuffer, size_t size)
{
    if(txBuffer == NULL || size == 0)
        return false;

    UART_Object *uartObj = &uartObjects[channel];

    if(uartObj->txBusy)
        return false;

    uartObj->txBuffer = txBuffer;
    uartObj->txSize = size;
    uartObj->txCount = 0;
    uartObj->txBusy = true;

    /* Initiate the transfer by writing as many bytes as we can */
    while((!(UART_DESCRIPTOR(channel)->usta.reg & _U2STA_UTXBF_MASK)) && (uartObj->txSize > uartObj->txCount) )
    {
        if (( UART_DESCRIPTOR(channel)->umode.reg & (_U2MODE_PDSEL0_MASK | _U2MODE_PDSEL1_MASK)) == (_U2MODE_PDSEL0_MASK | _U2MODE_PDSEL1_MASK))
        {
            /* 9-bit mode */
            UART_DESCRIPTOR(channel)->utxreg.reg = ((uint16_t*)uartObj->txBuffer)[uartObj->txCount++];
        }
        else
        {
            /* 8-bit mode */
            UART_DESCRIPTOR(channel)->utxreg.reg = uartObj->txBuffer[uartObj->txCount++];
        }
    }

    EVIC_channel_set(UART_TX_INTERRUPT_CHANNEL(channel));
    return true;
}

static void UART_rx_interrupt_handler (UART_Channel channel)
{
    /* Keep reading until there is a character availabe in the RX FIFO */
    while((UART_DESCRIPTOR(channel)->usta.reg & _U1STA_URXDA_MASK) == _U1STA_URXDA_MASK)
    {
        if (ring_buffer_push(&uartObjects[channel].rxBuffer , (uint16_t )(UART_DESCRIPTOR(channel)->urxreg.reg) ))
        {
            if( uartObjects[channel].callback != NULL )
            {
                if(ring_buffer_count(&uartObjects[channel].rxBuffer) == uartObjects[channel].rxBuffer.size)
                    uartObjects[channel].callback(channel, UART_CHANNEL_EVENT_BUFFER_FULL, uartObjects[channel].context);
                else
                    uartObjects[channel].callback(channel, UART_CHANNEL_EVENT_BYTE_RECEIVED, uartObjects[channel].context);
            }
        }
        else{

        }
    }
    /* Clear UART3 RX Interrupt flag */
    EVIC_channel_pending_clear(UART_RX_INTERRUPT_CHANNEL(channel));
}
static void UART_fault_interrupt_handler (UART_Channel channel)
{
    /* Save the error to be reported later */
    uartObjects[channel].error = (UART_ERROR)(U3STA & (_U3STA_OERR_MASK | _U3STA_FERR_MASK | _U3STA_PERR_MASK));

    UART_error_clear(channel);

    /* Client must call UARTx_ErrorGet() function to clear the errors */
    if( uartObjects[channel].callback != NULL )
    {
        uartObjects[channel].callback(channel, UART_CHANNEL_EVENT_READ_ERROR, uartObjects[channel].context);
    }
}

void UART_interrupt_handler (UART_Channel channel)
{
    if(EVIC_channel_pending_get(UART_RX_INTERRUPT_CHANNEL(channel)) &&
       EVIC_channel_get(UART_RX_INTERRUPT_CHANNEL(channel))){
        UART_rx_interrupt_handler(channel);
    }
    if(EVIC_channel_pending_get(UART_FAULT_INTERRUPT_CHANNEL(channel)) &&
       EVIC_channel_get(UART_FAULT_INTERRUPT_CHANNEL(channel))){
        UART_fault_interrupt_handler(channel);
    }
}

void    UART_callback_register(UART_Channel channel, UART_Callback callback, uintptr_t context)
{
    uartObjects[channel].callback = callback;
    uartObjects[channel].context = context;
}

UART_Descriptor UART_get_descriptor(UART_Channel channel)
{
    return UART_DESCRIPTOR(channel);
}

static void  UART_error_clear(UART_Channel channel)
{
    uartObjects[channel].error = 0;

    uartObjects[channel].error = (UART_ERROR)(U1STA & (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK));
    if(uartObjects[channel].error == UART_ERROR_NONE)
        return;

    if (UART_DESCRIPTOR(channel)->usta.reg & _U1STA_OERR_MASK) {
        UART_DESCRIPTOR(channel)->usta.clr = _U1STA_OERR_MASK;
    }

    uint8_t dummyData;
    while (UART_DESCRIPTOR(channel)->usta.reg & _U1STA_URXDA_MASK) {
        dummyData = UART_DESCRIPTOR(channel)->urxreg.reg;
        (void) dummyData;
    }

    EVIC_channel_pending_clear(UART_FAULT_INTERRUPT_CHANNEL(channel));
    EVIC_channel_pending_clear(UART_RX_INTERRUPT_CHANNEL(channel));

}

static int UART_baudrate(UART_Channel channel, int baudrate){
    int clock;
    int brg_lo;
    int brg_hi;
    int error_lo, error_hi;
    int brg;

    clock = (int)SYS_peripheral_clock_frequency_get(SYS_PERIPHERAL_CLOCK_2);
    brg_lo = ((clock/(int)baudrate)>>4)-1;
    brg_hi = ((clock/(int)baudrate)>>2)-1;
    if(brg_lo < 0)
        return brg_hi;
    if(brg_hi < 0)
        return -1;
    error_lo = (clock / ((brg_lo + 1)<<4)) - baudrate;
    brg = brg_lo;
    if((UART_DESCRIPTOR(channel)->umode.reg & _U1MODE_STSEL_MASK) == 0){
        error_hi = (clock / ((brg_lo + 1)<<2)) - baudrate;
        if(brg_hi < 65535 && error_hi < error_lo) {
            brg = brg_hi;
            UART_DESCRIPTOR(channel)->umode.set = _U1MODE_BRGH_MASK;
        }
    }
    if(brg > 65535)
        return -1;
    return brg;
}