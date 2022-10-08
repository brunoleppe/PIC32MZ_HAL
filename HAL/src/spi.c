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
#include "definitions.h"
#include "pic32mz_registers.h"
#include <xc.h>

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define _USEC_          (CPU_CLOCK_FREQUENCY/2000000)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/


/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static MemRegister spicon1[NUMBER_OF_SPI_CHANNELS]={
    (MemRegister)&SPI1CON, (MemRegister)&SPI2CON, (MemRegister)&SPI3CON, 
    (MemRegister)&SPI4CON, (MemRegister)&SPI5CON, (MemRegister)&SPI6CON,
};
static MemRegister spicon2[NUMBER_OF_SPI_CHANNELS]={
    (MemRegister)&SPI1CON2, (MemRegister)&SPI2CON2, (MemRegister)&SPI3CON2, 
    (MemRegister)&SPI4CON2, (MemRegister)&SPI5CON2, (MemRegister)&SPI6CON2,
};
static MemRegister spistat[NUMBER_OF_SPI_CHANNELS]={
    (MemRegister)&SPI1STAT, (MemRegister)&SPI2STAT, (MemRegister)&SPI3STAT, 
    (MemRegister)&SPI4STAT, (MemRegister)&SPI5STAT, (MemRegister)&SPI6STAT,
};
static MemRegister spibuf[NUMBER_OF_SPI_CHANNELS]={
    (MemRegister)&SPI1BUF, (MemRegister)&SPI2BUF, (MemRegister)&SPI3BUF, 
    (MemRegister)&SPI4BUF, (MemRegister)&SPI5BUF, (MemRegister)&SPI6BUF,
};
static MemRegister spibrg[NUMBER_OF_SPI_CHANNELS]={
    (MemRegister)&SPI1BRG, (MemRegister)&SPI2BRG, (MemRegister)&SPI3BRG, 
    (MemRegister)&SPI4BRG, (MemRegister)&SPI5BRG, (MemRegister)&SPI6BRG,
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
    
    clock = CPU_CLOCK_FREQUENCY/((PB1DIV&_PB1DIV_PBDIV_MASK)+1);
    brg = ((clock/baudrate)/2)-1;
    
    error = (clock / (2 * (brg + 1)));
    if(error > baudrate)
        brg++;
    
    return brg;
    
}
/**
 * Función para registro de errores.
 * @param type tipo de error.
 * @todo Implementar la función
 */
static void _error(uint32_t type){
    
}

static void _delay_us(uint32_t usec){
    uint32_t t_wait = _USEC_ * usec;
    uint32_t t_start = _CP0_GET_COUNT();
    t_start=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-t_start)<t_wait);
}

void SPI_Init(const SPI_Config *config)
{
    int i;
    for(i=0;i<config->tableSize;i++){
        uint32_t channel = config->table[i].channel;
        /*Deshabilitar y limpiar interrupciones*/
        EVIC_ChannelStateSet(spi_fault_vector[channel],IRQ_DISABLED);
        EVIC_ChannelStateSet(spi_rx_vector[channel],   IRQ_DISABLED);
        EVIC_ChannelStateSet(spi_tx_vector[channel],   IRQ_DISABLED);
        EVIC_IrqPendingClear(spi_fault_vector[channel]);
        EVIC_IrqPendingClear(spi_rx_vector[channel]);
        EVIC_IrqPendingClear(spi_tx_vector[channel]);
        
        /*Apagar SPI y resetear registro*/
        spicon1[channel]->reg = 0;
        /*Vaciar el buffer de recepción*/
        uint32_t data = spibuf[channel]->reg;
        data = data;
        
        /*Establecer el generador de baudios*/
        uint32_t brg = _brg_get(config->table[i].baudrate);
        if(brg>0x1FF){
            /*ERROR*/
            continue;
        }
        spibrg[channel]->reg = brg;
        
        /*Limpiar la bandera de overflow*/
        spistat[channel]->clr = _SPI1STAT_SPIROV_MASK;
        
        /*Configurar registros de control*/
        if(config->table[i].mastermode == SPI_MASTER)
            spicon1[channel]->set = _SPI1CON_MSTEN_MASK;
        if(config->table[i].sample == SPI_SAMPLE_END)
            spicon1[channel]->set = _SPI1CON_SMP_MASK;
        
        uint32_t cke=1, ckp=0;/*SPI_MODE_0*/
        switch(config->table[i].mode){
            case SPI_MODE_0: cke = 1; ckp = 0; break;
            case SPI_MODE_1: cke = ckp = 0; break;
            case SPI_MODE_2: cke = ckp = 1; break;
            case SPI_MODE_3: cke = 0; ckp = 1; break;
        }
        spicon1[channel]->set = (cke << _SPI1CON_CKE_POSITION) |
                (ckp << _SPI1CON_CKP_POSITION) | _SPI1CON_ENHBUF_MASK;
        
        
        /*Encender SPI*/
        spicon1[channel]->set = _SPI1CON_ON_MASK;
    }
}

//int  SPI_Transfer(SPI_CHANNEL channel, void *txBuffer, void *rxBuffer, size_t size)
int SPI_Transfer(SPI_CHANNEL channel, SPI_TransferParam *transfer)
{
    size_t txCount = 0;
    size_t rxCount = 0;
    size_t receivedData;
    void *txBuffer = transfer->txBuffer;
    void *rxBuffer = transfer->rxBuffer;
    size_t size = transfer->size;
    
    
    
    /*Error handling*/
    if(((uint32_t)channel) >= SPI_CHANNEL_MAX){
        /*ERROR Channel out of bounds*/
        return SPI_ERROR_CHANNEL_OUT_OF_BOUNDS;
    }
    if(txBuffer == NULL && rxBuffer == NULL){
        /*ERROR NULL buffers*/
        return SPI_ERROR_NULL_BUFFERS;
    }
    if(size == 0){
        /*ERROR size is 0*/
        return SPI_ERROR_ZERO_SIZE_BUFFER;
    }
    
    /*Transferencia*/
    
    /*Limpiar bandera de overflow*/
    spistat[channel]->clr = _SPI1STAT_SPIROV_MASK;

    /*Vaciar FIFO de recepción*/
    while ((bool)(spistat[channel]->reg & _SPI1STAT_SPIRBE_MASK) == false)
        receivedData = spibuf[channel]->reg;

    
    /*Esperar que el FIFO de transmisión esté vacío*/
    while((bool)(spistat[channel]->reg & _SPI1STAT_SPITBE_MASK) == false);
    
    while(size--){
        
        /*Escritura de bytes*/
        if(txBuffer != NULL)
            spibuf[channel]->reg = ((uint8_t*)txBuffer)[txCount++];
        else
            spibuf[channel]->reg = transfer->dummyData;/*DUMMY*/
        
        /*Recepción*/
        /*Esperar a que el buffer de RX se llene con bytes*/
        while((spistat[channel]->reg & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);
        /*Leer el FIFO RX*/
        receivedData = spibuf[channel]->reg;
        if(rxBuffer != NULL)
            ((uint8_t*)rxBuffer)[rxCount++] = receivedData;
        
        
        if(transfer->usDelay != 0){
            _delay_us(transfer->usDelay);
        }
        
    }
    
    /*Esperar que el registro de desplazamiento esté vacío*/
    while ((bool)((SPI1STAT & _SPI1STAT_SRMT_MASK) == false));
    return txCount;
}

uint8_t SPI_TransferByte(SPI_CHANNEL channel, uint8_t data)
{
    
}

int SPI_TrasferSetup(SPI_CHANNEL channel, SPI_Setup *setup)
{
    uint32_t brg = _brg_get(setup->baudrate);
    if(brg > 0x1FF){
        /*ERROR*/
        return SPI_ERROR_BAUDRATE_TOO_LOW;
    }
    
    spibrg[channel]->reg = brg;
    
    spicon1[channel]->clr = _SPI1CON_SMP_MASK;
    if(setup->sample == SPI_SAMPLE_END)
            spicon1[channel]->set = _SPI1CON_SMP_MASK;
    uint32_t cke,ckp;
    switch(setup->mode){
        case SPI_MODE_0: cke = 1; ckp = 0; break;
        case SPI_MODE_1: cke = ckp = 0; break;
        case SPI_MODE_2: cke = ckp = 1; break;
        case SPI_MODE_3: cke = 0; ckp = 1; break;
        default: return SPI_ERROR_BAD_SPI_MODE; 
        }
    spicon1[channel]->clr = _SPI1CON_CKP_MASK | _SPI1CON_CKE_MASK;
    spicon1[channel]->set = (cke << _SPI1CON_CKE_POSITION) |
                (ckp << _SPI1CON_CKP_POSITION);
    
    return 0;
}
void SPI_RegisterWrite(uint32_t address, uint32_t value)
{

}

uint32_t SPI_RegisterRead(uint32_t address)
{
    
}