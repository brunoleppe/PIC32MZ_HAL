/**
 * @file spi.c
 * @author Bruno Leppe (bleppe@solintece.com)
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
#include "spi.h"
#include "evic.h"
#include "pic32mz_registers.h"
#include <xc.h>

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define _USEC_          (HAL_SYSTEM_CLOCK/2000000)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define HANDLER_ERROR_CALLBACK(_handler) do{\
        if(_handler->errorCallback != NULL){\
            _handler->errorCallback(_handler);\
        }}while(0)
#define HANDLER_HALF_CALLBACK(_handler) do{\
        if(_handler->halfCallback != NULL){\
            _handler->halfCallback(_handler);\
        }}while(0)
#define HANDLER_CPLT_CALLBACK(_handler) do{\
        if(_handler->cpltCallback != NULL){\
            _handler->cpltCallback(_handler);\
        }}while(0)
/**********************************************************************
* Module Typedefs
**********************************************************************/
struct _SPI_Instance{
    struct _MemRegister spicon1;
    struct _MemRegister spistat;
    struct _MemRegister spibuf;
    struct _MemRegister spibrg;
    struct _MemRegister spicon2;
};
/*********************************************************************
* Module Variable Definitions
**********************************************************************/

static const struct _SPI_HANDLER spi2 = {
    .instance = (SPI_Instance_t)(&SPI2CON),
    .setup = {SPI_CHANNEL_2, SPI_MODE_3, SPI_MASTER, 20000000, SPI_SAMPLE_MID},
};

static const struct _SPI_HANDLER spi3 = {
    .instance = (SPI_Instance_t)(&SPI3CON),
    .setup = {SPI_CHANNEL_3, SPI_MODE_3, SPI_MASTER, 1000000 , SPI_SAMPLE_MID},
    .dummyByte = 0xFF,
    .usDelay = 160,
};

static const struct _SPI_HANDLER spi4 = {
    .instance = (SPI_Instance_t)(&SPI4CON),
    .setup = {SPI_CHANNEL_4, SPI_MODE_0, SPI_MASTER, 40000000, SPI_SAMPLE_END},
    .dummyByte = 0xFF,
};

static const SPI_Handler *handlers[NUMBER_OF_SPI_CHANNELS]={
    NULL, 
    (const SPI_Handler*)&spi2, 
    (const SPI_Handler*)&spi3, 
    (const SPI_Handler*)&spi4, 
    NULL, 
    NULL
};

static const SPI_Config config = {
    .table = (SPI_Handler**)handlers,
    .tableSize = sizeof(handlers)/sizeof(SPI_Handler*)
};


static uint32_t spi_fault_vector[NUMBER_OF_SPI_CHANNELS]={
    _SPI1_FAULT_VECTOR, _SPI2_FAULT_VECTOR, _SPI3_FAULT_VECTOR, 
    _SPI4_FAULT_VECTOR, _SPI5_FAULT_VECTOR, _SPI6_FAULT_VECTOR
};
static uint32_t spi_tx_vector[NUMBER_OF_SPI_CHANNELS]={
    _SPI1_TX_VECTOR, _SPI2_TX_VECTOR, _SPI3_TX_VECTOR, 
    _SPI4_TX_VECTOR, _SPI5_TX_VECTOR, _SPI6_TX_VECTOR
};
static uint32_t spi_rx_vector[NUMBER_OF_SPI_CHANNELS]={
    _SPI1_RX_VECTOR, _SPI2_RX_VECTOR, _SPI3_RX_VECTOR, 
    _SPI4_RX_VECTOR, _SPI5_RX_VECTOR, _SPI6_RX_VECTOR
};
/**********************************************************************
* Function Definitions
**********************************************************************/

static uint32_t _brg_get(uint32_t baudrate){
    uint32_t clock;
    uint32_t brg;
    uint32_t error;
    
    clock = HAL_SPI_PERIPHERAL_CLOCK;
    brg = ((clock/baudrate)/2)-1;
    
    error = (clock / (2 * (brg + 1)));
    if(error > baudrate)
        brg++;
    
    return brg;
    
}

static void _delay_us(uint32_t usec){
    uint32_t t_wait = _USEC_ * usec;
    uint32_t t_start = _CP0_GET_COUNT();
    t_start=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-t_start)<t_wait);
}

const SPI_Config* SPI_GetConfig( void ){
    return (const SPI_Config*)&config;
}

SPI_Handler* SPI_GetSpiHandler(SPI_CHANNEL channel)
{
    return (SPI_Handler*)handlers[channel];
}

void SPI_Init(const SPI_Config *config)
{
    int i;
    for(i=0;i<config->tableSize;i++){
        /*SPI channel not configured for use in application*/
        if(config->table[i]==NULL){
            continue;
        }
        
        uint32_t channel = config->table[i]->setup.channel;
        SPI_Handler *handler = config->table[i];
        
        /*Deshabilitar y limpiar interrupciones*/
        EVIC_IrqStateSet(spi_fault_vector[channel],IRQ_DISABLED);
        EVIC_IrqStateSet(spi_rx_vector[channel],   IRQ_DISABLED);
        EVIC_IrqStateSet(spi_tx_vector[channel],   IRQ_DISABLED);
        EVIC_IrqPendingClear(spi_fault_vector[channel]);
        EVIC_IrqPendingClear(spi_rx_vector[channel]);
        EVIC_IrqPendingClear(spi_tx_vector[channel]);
        
        /*Apagar SPI y resetear registro*/
        handler->instance->spicon1.reg = 0;

        /*Vaciar el buffer de recepción*/
        uint32_t data = handler->instance->spibuf.reg;
        data = data;
        
        /*Establecer el generador de baudios*/
        uint32_t brg = _brg_get(handler->setup.baudrate);
        if(brg>0x1FF){
            /*ERROR*/
            handler->error = SPI_ERROR_BAUDRATE_TOO_LOW;
            continue;
        }
        handler->instance->spibrg.reg = brg;
        
        /*Limpiar la bandera de overflow*/
        handler->instance->spistat.clr = _SPI1STAT_SPIROV_MASK;
        
        /*Configurar registros de control*/
        if(handler->setup.mastermode == SPI_MASTER)
            handler->instance->spicon1.set = _SPI1CON_MSTEN_MASK;
        if(handler->setup.sample == SPI_SAMPLE_END)
            handler->instance->spicon1.set = _SPI1CON_SMP_MASK;
        
        /*SPI MODE Configuration*/
        uint32_t cke=1, ckp=0;/*SPI_MODE_0*/
        switch(handler->setup.mode){
            case SPI_MODE_0: cke = 1; ckp = 0; break;
            case SPI_MODE_1: cke = ckp = 0; break;
            case SPI_MODE_2: cke = ckp = 1; break;
            case SPI_MODE_3: cke = 0; ckp = 1; break;
        }
        handler->instance->spicon1.set = (cke << _SPI1CON_CKE_POSITION) |
                (ckp << _SPI1CON_CKP_POSITION) | _SPI1CON_ENHBUF_MASK;
        
        
        /*Encender SPI*/
        handler->instance->spicon1.set = _SPI1CON_ON_MASK;
    }
}

//int  SPI_Transfer(SPI_CHANNEL channel, void *txBuffer, void *rxBuffer, size_t size)
int SPI_Transfer(SPI_Handler *handler, void *txBuffer, void *rxBuffer, size_t size)
{
    size_t txCount = 0;
    size_t rxCount = 0;
    uint8_t receivedData;
    
    /*Error handling*/
    if(handler == NULL)
        return -1;
    if(txBuffer == NULL && rxBuffer == NULL){
        /*ERROR NULL buffers*/
        handler->error = SPI_ERROR_NULL_BUFFERS;
        if(handler->errorCallback != NULL){
            handler->errorCallback(handler);
        }
        return -1;
    }
    if(size == 0){
        /*ERROR size is 0*/
        return 0;
    }
    
    /*Transferencia*/
    
    /*Limpiar bandera de overflow*/
    handler->instance->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(handler->instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false)
        receivedData = handler->instance->spibuf.reg;

    
    /*Esperar que el FIFO de transmisión esté vacío*/
    while((bool)(handler->instance->spistat.reg & _SPI1STAT_SPITBE_MASK) == false);
    
    while(size--){
        
        /*Escritura de bytes*/
        if(txBuffer != NULL){
            handler->instance->spibuf.reg = ((uint8_t*)txBuffer)[txCount++];
        }
        else{
            handler->instance->spibuf.reg = handler->dummyByte;/*DUMMY*/
        }
        
        /*Recepción*/
        
        /*Esperar a que el buffer de RX se llene con bytes*/
        while((handler->instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);
        
        /*Leer el FIFO RX*/
        receivedData = handler->instance->spibuf.reg;
        if(rxBuffer != NULL){
            ((uint8_t*)rxBuffer)[rxCount++] = receivedData;
        }
        
        /*Byte transmit delay, useful for QTouch comms*/
        if(handler->usDelay != 0){
            _delay_us(handler->usDelay);
        }
        
    }
    
    /*Esperar que el registro de desplazamiento esté vacío*/
    while ((bool)((handler->instance->spistat.reg & _SPI1STAT_SRMT_MASK) == false));
    return txCount;
}

uint8_t SPI_TransferByte(SPI_Handler *handler, uint8_t data)
{
    uint8_t receivedData;
    
    if(handler == NULL)
        return 0;
    
    /*Limpiar bandera de overflow*/
    handler->instance->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(handler->instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false)
        receivedData = handler->instance->spibuf.reg;

    /*Esperar que el FIFO de transmisión esté vacío*/
    while((bool)(handler->instance->spistat.reg & _SPI1STAT_SPITBE_MASK) == false);
    
    /*Enviar el byte*/
    handler->instance->spibuf.reg = data;
    
    /*Esperar a que el buffer de RX se llene con bytes*/
    while((handler->instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);
        
    /*Leer el FIFO RX*/
    receivedData = handler->instance->spibuf.reg;
    
    return receivedData;
}

int SPI_TransferAsync(SPI_Handler *handler, void *txBuffer, void *rxBuffer, size_t size)
{
    uint8_t receivedData;
    /*Error handling*/
    if(handler == NULL)
        return -1;
    if(handler->busy){
        handler->error = SPI_ERROR_CHANNEL_BUSY;
        HANDLER_ERROR_CALLBACK(handler);
        return -1;
    }
    if(txBuffer == NULL && rxBuffer == NULL){
        /*ERROR NULL buffers*/
        handler->error = SPI_ERROR_NULL_BUFFERS;
        HANDLER_ERROR_CALLBACK(handler);
        return -1;
    }
    if(size == 0){
        /*ERROR size is 0*/
        return 0;
    }
    
    /*Initialize handler*/
    handler->txBuffer = (uint8_t*)txBuffer;
    handler->txSize = txBuffer!=NULL?size:0;
    handler->txCount = 0;
    handler->rxBuffer = (uint8_t*)rxBuffer;
    handler->rxSize = rxBuffer!=NULL?size:0;
    handler->rxCount = 0;
    handler->dummySize = txBuffer!=NULL?0:size;
    /*Update busy flag*/
    handler->busy = true;
    
    /*Limpiar bandera de overflow*/
    handler->instance->spistat.clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(handler->instance->spistat.reg & _SPI1STAT_SPIRBE_MASK) == false)
        receivedData = handler->instance->spibuf.reg;
    
    /* Configure SPI to generate receive interrupt when receive buffer is empty*/
    /* Configure SPI to generate transmit interrupt when the transmit shift register is empty (STXISEL = '00')*/
    handler->instance->spicon1.clr = _SPI1CON_SRXISEL_MASK | _SPI2CON_STXISEL_MASK;
    handler->instance->spicon1.set = 1;

    /* Disable the receive interrupt */
    EVIC_IrqStateSet(spi_rx_vector[handler->setup.channel],IRQ_DISABLED);

    /* Disable the transmit interrupt */
    EVIC_IrqStateSet(spi_tx_vector[handler->setup.channel],IRQ_DISABLED);

    /* Clear the receive interrupt flag */
    EVIC_IrqPendingClear(spi_rx_vector[handler->setup.channel]);

    /* Clear the transmit interrupt flag */
    EVIC_IrqPendingClear(spi_tx_vector[handler->setup.channel]);
    
    /*Write first bytes*/
    if(txBuffer != NULL){
        handler->instance->spibuf.reg = ((uint8_t*)handler->txBuffer)[handler->txCount++];
    }
    else{
        handler->instance->spibuf.reg = handler->dummyByte;/*DUMMY*/
    }
    
    if (handler->rxSize > 0)
    {
        /* Enable receive interrupt to complete the transfer in ISR context.
         * Keep the transmit interrupt disabled. Transmit interrupt will be
         * enabled later if txCount < txSize, when rxCount = rxSize.
         */
        EVIC_IrqStateSet(spi_rx_vector[handler->setup.channel],IRQ_ENABLED);
    }
    else
    {
        if (handler->txCount != handler->txSize)
        {
            /* Configure SPI to generate transmit buffer empty interrupt only if more than
             * data is pending (STXISEL = '01')  */
            handler->instance->spicon1.set = 0x00000004;
        }
        /* Enable transmit interrupt to complete the transfer in ISR context */
        EVIC_IrqStateSet(spi_tx_vector[handler->setup.channel],IRQ_ENABLED);
    }
    return 1;
}

void SPI_RX_InterruptHandler (SPI_Handler *handler)
{
    uint32_t receivedData = 0;

    /* Check if the receive buffer is empty or not */
    if(handler->instance->spistat.reg & _SPI1STAT_SPIRBE_MASK){
        goto SPI_RX_END;
    }
    
    /* Receive buffer is not empty. Read the received data. */
    receivedData = SPI2BUF;
    if(handler->rxCount < handler->rxSize){
        handler->rxBuffer[handler->rxCount++] = receivedData;
    }
    
    /*Write to buffer*/
    if(handler->txCount < handler->txSize){
        handler->instance->spibuf.reg = handler->txBuffer[handler->txCount++];
    }
    else if(handler->dummySize > 0){
        handler->instance->spibuf.reg = handler->dummyByte;
        handler->dummySize--;
    }
    
    /*Transfer done*/
    if(handler->rxCount == handler->rxSize){
        /* Clear receiver overflow error if any */
        handler->instance->spistat.clr = _SPI1STAT_SPIROV_MASK;
        /* Disable receive interrupt */
        EVIC_IrqStateSet(spi_rx_vector[handler->setup.channel],IRQ_DISABLED);
        handler->busy = false;
        
        if(handler->cpltCallback!=NULL){
            handler->cpltCallback(handler);
        }
    }
    
SPI_RX_END:
    EVIC_IrqPendingClear(spi_rx_vector[handler->setup.channel]);
}

void SPI_TX_InterruptHandler (SPI_Handler *handler)
{
    /* If there are more words to be transmitted, then transmit them here and keep track of the count */
    if((handler->instance->spistat.reg & _SPI1STAT_SPITBE_MASK) != _SPI1STAT_SPITBE_MASK)
        return;
    
    if(handler->txCount < handler->txSize){
        handler->instance->spibuf.reg = handler->txBuffer[handler->txCount++];
        if (handler->txCount == handler->txSize)
        {
            /* All bytes are submitted to the SPI module. Now, enable transmit
             * interrupt when the shift register is empty (STXISEL = '00')*/
            handler->instance->spicon1.clr = _SPI1CON_STXISEL_MASK;
        }
    }
    else if((handler->txCount == handler->txSize) && 
            (handler->instance->spistat.reg & _SPI2STAT_SRMT_MASK)){
        /* Clear receiver overflow error if any */
            handler->instance->spistat.clr = _SPI2STAT_SPIROV_MASK;

            /* Disable transmit interrupt */
            EVIC_IrqStateSet(spi_rx_vector[handler->setup.channel],IRQ_DISABLED);
            /* Transfer complete. Give a callback */
            handler->busy = false;

        if(handler->cpltCallback!=NULL){
            handler->cpltCallback(handler);
        }
    }
    
    /* Clear the transmit interrupt flag */
    EVIC_IrqPendingClear(spi_rx_vector[handler->setup.channel]);
}

int SPI_TransferSetup(SPI_Handler *handler, SPI_Setup *setup)
{
    if(handler == NULL)
        return -1;
    
    uint32_t brg = _brg_get(setup->baudrate);
    if(brg > 0x1FF){
        /*ERROR*/
        handler->error = SPI_ERROR_BAUDRATE_TOO_LOW;
        return -1;
    }
    
    handler->instance->spibrg.reg = brg;
    
    handler->instance->spicon1.clr = _SPI1CON_SMP_MASK;
    if(setup->sample == SPI_SAMPLE_END)
            handler->instance->spicon1.set = _SPI1CON_SMP_MASK;
    uint32_t cke,ckp;
    switch(setup->mode){
        case SPI_MODE_0: cke = 1; ckp = 0; break;
        case SPI_MODE_1: cke = ckp = 0; break;
        case SPI_MODE_2: cke = ckp = 1; break;
        case SPI_MODE_3: cke = 0; ckp = 1; break;
        default: return SPI_ERROR_BAD_SPI_MODE; 
        }
    handler->instance->spicon1.clr = _SPI1CON_CKP_MASK | _SPI1CON_CKE_MASK;
    handler->instance->spicon1.set = (cke << _SPI1CON_CKE_POSITION) |
                (ckp << _SPI1CON_CKP_POSITION);
    handler->setup = *setup;
    return 0;
}






void SPI_RegisterWrite(uint32_t address, uint32_t value)
{

}

uint32_t SPI_RegisterRead(uint32_t address)
{
    
}


/**********************************************************************
* Interrupt Handlers
**********************************************************************/
void SPI2_RX_InterruptHandler(void);

void SPI2_RX_InterruptHandler (void)
{
    SPI_RX_InterruptHandler(SPI_GetSpiHandler(SPI_CHANNEL_2));
}

void SPI2_TX_InterruptHandler(void);

void SPI2_TX_InterruptHandler (void)
{
    SPI_TX_InterruptHandler(SPI_GetSpiHandler(SPI_CHANNEL_2));
}

void SPI3_RX_InterruptHandler(void);

void SPI3_RX_InterruptHandler (void)
{
    SPI_RX_InterruptHandler(SPI_GetSpiHandler(SPI_CHANNEL_3));
}

void SPI3_TX_InterruptHandler(void);

void SPI3_TX_InterruptHandler (void)
{
    SPI_TX_InterruptHandler(SPI_GetSpiHandler(SPI_CHANNEL_3));
}

void SPI4_RX_InterruptHandler(void);

void SPI4_RX_InterruptHandler (void)
{
    SPI_RX_InterruptHandler(SPI_GetSpiHandler(SPI_CHANNEL_4));
}

void SPI4_TX_InterruptHandler(void);

void SPI4_TX_InterruptHandler (void)
{
    SPI_TX_InterruptHandler(SPI_GetSpiHandler(SPI_CHANNEL_4));
}