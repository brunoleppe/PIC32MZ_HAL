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
#include "pic32mx_registers.h"
#include "evic.h"
#include <xc.h>
#include "system.h"
#include "dma.h"
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define SPI_BASE                                _SPI2_BASE_ADDRESS
#define SPI_NUMBER_OF_CHANNELS                  (3)
#define SPI_PERIPHERAL_INTERVAL                 (0x200)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define SPI_DESCRIPTOR(channel)                 (descriptors[channel])
#define SPI_RX_INTERRUPT_CHANNEL(channel)       (spiIRQBase[channel] + 1)
#define SPI_TX_INTERRUPT_CHANNEL(channel)       (spiIRQBase[channel] + 2)
#define SPI_FAULT_INTERRUPT_CHANNEL(channel)    (spiIRQBase[channel])
/**********************************************************************
* Module Typedefs
**********************************************************************/
typedef struct{
    bool            busy;
    void            *txBuffer;
    void            *rxBuffer;
    size_t          rxCount;
    size_t          txCount;
    size_t          rxSize;
    size_t          txSize;
    size_t          dummySize;
    SPI_Callback    callback;
    uintptr_t       context;
}SPI_Object;
/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static SPI_Object spiObjects[SPI_NUMBER_OF_CHANNELS];
static const EVIC_CHANNEL spiIRQBase[]={
        [SPI_CHANNEL_2] = EVIC_CHANNEL_SPI2_ERR,
        [SPI_CHANNEL_3] = EVIC_CHANNEL_SPI3_ERR,
        [SPI_CHANNEL_4] = EVIC_CHANNEL_SPI4_ERR,
};
static const SPI_Descriptor descriptors[] = {
    [SPI_CHANNEL_2] = (SPI_Descriptor)&SPI2CON,
    [SPI_CHANNEL_3] = (SPI_Descriptor)&SPI3CON,
    [SPI_CHANNEL_4] = (SPI_Descriptor)&SPI4CON,
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static uint32_t SPI_Baudrate_Get_(uint32_t baudrate);
/**********************************************************************
* Function Definitions
**********************************************************************/

int SPI_initialize(uint32_t spiChannel, uint32_t configFlags, uint32_t baudrate)
{
    EVIC_channel_clr(SPI_RX_INTERRUPT_CHANNEL(spiChannel));
    EVIC_channel_clr(SPI_TX_INTERRUPT_CHANNEL(spiChannel));
    EVIC_channel_clr(SPI_FAULT_INTERRUPT_CHANNEL(spiChannel));
    /*Clear Control register*/
    SPI_DESCRIPTOR(spiChannel)->spicon1.reg = 0;
    /*Clear RX FIFO*/
    uint32_t data = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
    (void)data;

    EVIC_channel_pending_clear(SPI_RX_INTERRUPT_CHANNEL(spiChannel));
    EVIC_channel_pending_clear(SPI_TX_INTERRUPT_CHANNEL(spiChannel));
    EVIC_channel_pending_clear(SPI_FAULT_INTERRUPT_CHANNEL(spiChannel));

    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI2STAT_SPIROV_MASK;
    if((configFlags & SPI_MASTER))//master
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_MSTEN_MASK;

    SPI_setup(spiChannel, configFlags, baudrate);

    /*SPI data bits configuration*/
    if(configFlags & SPI_DATA_BITS_16)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_MODE16_MASK;
    else if(configFlags & SPI_DATA_BITS_32)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_MODE32_MASK;
    /*SPI SS enable configuration*/
    if(configFlags & SPI_SS_ENABLE)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_SSEN_MASK;
    /*Turn on SPI peripheral*/


    SPI_DESCRIPTOR(spiChannel)->spicon1.set = 0x00000005 | _SPI2CON_ENHBUF_MASK;
    SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_ON_MASK;


    return 0;
}

void SPI_setup (SPI_Channel spiChannel, uint32_t configFlags, uint32_t baudrate)
{
    bool status = (SPI_DESCRIPTOR(spiChannel)->spicon1.reg & _SPI2CON_ON_MASK) == _SPI2CON_ON_MASK;
    SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI2CON_ON_MASK;
    uint32_t brg = SPI_Baudrate_Get_(baudrate);
    SPI_DESCRIPTOR(spiChannel)->spibrg.reg = brg;

    if(configFlags & SPI_SAMPLE_END)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_SMP_MASK;
    else
        SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI2CON_SMP_MASK;

    uint32_t cke = 1, ckp = 0;/*SPI_MODE_0*/
    if(configFlags & SPI_MODE_1) {
        cke = ckp = 0;
    }
    else if(configFlags & SPI_MODE_2){
        cke = ckp = 1;
    }
    else if(configFlags & SPI_MODE_3){
        cke = 0;
        ckp = 1;
    }
    SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI2CON_CKP_MASK | _SPI2CON_CKE_MASK;
    SPI_DESCRIPTOR(spiChannel)->spicon1.set = (cke << _SPI2CON_CKE_POSITION) | (ckp << _SPI2CON_CKP_POSITION);
    if(status)
        SPI_DESCRIPTOR(spiChannel)->spicon1.set = _SPI2CON_ON_MASK;
}

size_t SPI_transfer(uint32_t spiChannel, void *txBuffer, void *rxBuffer, size_t size)
{
    uint32_t receivedData;
    size_t rxSize = size;
    size_t txSize = size;
    if(spiObjects[spiChannel].busy || (txBuffer == NULL && rxBuffer == NULL) || size == 0)
        return 0;

    if(txBuffer == NULL)
        txSize = 0;
    if(rxBuffer == NULL)
        rxSize = 0;

    spiObjects[spiChannel].busy = true;
    spiObjects[spiChannel].rxBuffer = rxBuffer;
    spiObjects[spiChannel].txBuffer = txBuffer;
    spiObjects[spiChannel].rxCount = 0;
    spiObjects[spiChannel].txCount = 0;
    /*Transfer*/

    /*Overflow-bit clear*/
    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI2STAT_SPIROV_MASK;

    /*Empty RX FIFO*/
    while ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPIRBE_MASK) == false) {
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
        (void)receivedData;
    }
    /*Wait for TX FIFO to empty*/
    while((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPITBE_MASK) == false);

    while(size--){

        /*Write Byte*/
        if(spiObjects[spiChannel].txCount != txSize){
            SPI_DESCRIPTOR(
                    spiChannel)->spibuf.reg = ((uint8_t*)spiObjects[spiChannel].txBuffer)[spiObjects[spiChannel].rxCount];
        }
        else{
            SPI_DESCRIPTOR(spiChannel)->spibuf.reg = 0xFFFFFFFF;/*DUMMY*/
        }

        if(spiObjects[spiChannel].rxCount == rxSize){

        }
        /*Wait for RX FIFO*/
        while((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPIRBE_MASK) == _SPI2STAT_SPIRBE_MASK);

        /*Read RX FIFO*/
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
        if(rxBuffer != NULL){
            ((uint8_t*)spiObjects[spiChannel].rxBuffer)[spiObjects[spiChannel].rxCount] = receivedData;
        }
        spiObjects[spiChannel].rxCount++;
    }
    /*Wait for TX FIFO to empty*/
    while ((bool)((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SRMT_MASK) == false));
    spiObjects[spiChannel].busy = false;
    return spiObjects[spiChannel].rxCount;
}

uint8_t SPI_byte_transfer(uint32_t spiChannel, uint8_t data)
{

    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI2STAT_SPIROV_MASK;

#ifdef SPI_EMPTY_RX_FIFO
    /*Empty RX FIFO*/
    while ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPIRBE_MASK) == false) {
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
//        (void)receivedData;
    }
#endif

#ifdef SPI_EMPTY_TX_FIFO
    /*Wait for TX FIFO to empty*/
    while((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPITBE_MASK) == false);
#endif

    SPI_DESCRIPTOR(spiChannel)->spibuf.reg = data;
    while(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPIRBE_MASK);
    return SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
}

static void DMA_callback(DMA_Channel dma, DMA_IRQ_CAUSE cause, SPI_Channel channel){
    spiObjects[channel].busy = false;
    if(spiObjects[channel].callback != NULL){
        spiObjects[channel].callback(channel, spiObjects[channel].context);
    }
}

bool        SPI_write_dma               (SPI_Channel spiChannel, uint32_t dmaChannel, void *txBuffer, size_t size)
{
    if(size == 0 || (txBuffer == NULL) || spiObjects[spiChannel].busy)
        return false;

    spiObjects[spiChannel].busy = true;

    DMA_CHANNEL_Config dmaConfig = {
            .startIrq = SPI_TX_INTERRUPT_CHANNEL(spiChannel),
            .cellSize = 1,
            .dstSize = 1,
            .dstAddress = (uint32_t)(&SPI_DESCRIPTOR(spiChannel)->spibuf.reg),
            .srcSize = size,
            .srcAddress = (uint32_t)(txBuffer),
    };
    DMA_channel_config(dmaChannel, &dmaConfig);
    DMA_callback_register(dmaChannel, DMA_callback, (uintptr_t)spiChannel);
    DMA_channel_transfer(dmaChannel);
    return true;
}
bool        SPI_read_dma                (SPI_Channel spiChannel, uint32_t dmaChannel, void *rxBuffer, size_t size)
{
    if(size == 0 || (rxBuffer == NULL) || spiObjects[spiChannel].busy)
        return false;

    spiObjects[spiChannel].busy = true;

    DMA_CHANNEL_Config dmaConfig = {
            .startIrq = SPI_TX_INTERRUPT_CHANNEL(spiChannel),
            .cellSize = 1,
            .dstSize = size,
            .dstAddress = (uint32_t)(rxBuffer),
            .srcSize = 1,
            .srcAddress = (uint32_t)(&SPI_DESCRIPTOR(spiChannel)->spibuf.reg),
    };
    DMA_channel_config(dmaChannel, &dmaConfig);
    DMA_callback_register(dmaChannel, DMA_callback, (uintptr_t)spiChannel);
    DMA_channel_transfer(dmaChannel);
    return true;
}

bool SPI_transfer_isr (uint32_t spiChannel, void* pTransmitData, void* pReceiveData, size_t size)
{
    uint32_t dummyData = 0U;


    if(size == 0 || (pTransmitData == NULL && pReceiveData == NULL) || spiObjects[spiChannel].busy)
        return false;

    SPI_Object *spiObj = &spiObjects[spiChannel];
    spiObj->txBuffer = pTransmitData;
    spiObj->rxBuffer = pReceiveData;
    spiObj->rxCount = 0;
    spiObj->txCount = 0;
    spiObj->dummySize = 0;
    spiObj->txSize = 0;
    spiObj->rxSize = 0;

    if (pTransmitData != NULL)
        spiObj->txSize = size;
    if (pReceiveData != NULL)
        spiObj->rxSize = size;

    spiObj->busy = true;

    if (spiObj->rxSize > spiObj->txSize)
        spiObj->dummySize = spiObj->rxSize;

    /*Overflow-bit clear*/
    SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI2STAT_SPIROV_MASK;
    /*Empty RX FIFO*/
    while ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPIRBE_MASK) == false) {
        dummyData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;
        (void)dummyData;
    }



    /* Configure SPI to generate receive interrupt when receive buffer is empty (SRXISEL = '01')  and transmit interrupt
     * when the transmit shift register is empty (STXISEL = '00')*/
    SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI2CON_SRXISEL_MASK | _SPI2CON_STXISEL_MASK;
    SPI_DESCRIPTOR(spiChannel)->spicon1.set = 1;

    /* Disable the "receive" interrupt */
    EVIC_channel_clr(SPI_RX_INTERRUPT_CHANNEL(spiChannel));
    /* Disable the "transmit" interrupt */
    EVIC_channel_clr(SPI_TX_INTERRUPT_CHANNEL(spiChannel));
    /* Clear the "receive" interrupt flag */
    EVIC_channel_pending_clear(SPI_RX_INTERRUPT_CHANNEL(spiChannel));
    /* Clear the "transmit" interrupt flag */
    EVIC_channel_pending_clear(SPI_TX_INTERRUPT_CHANNEL(spiChannel));

    if (spiObj->txCount < spiObj->txSize)
    {
        SPI_DESCRIPTOR(spiChannel)->spibuf.reg = *((uint8_t*)spiObj->txBuffer);
        spiObj->txCount++;
    }
    else if (spiObj->dummySize > 0)
    {
        SPI_DESCRIPTOR(spiChannel)->spibuf.reg = (uint8_t)(0xff);
        spiObj->dummySize--;
    }


    if (spiObj->rxSize > 0)
    {
        /* Enable receive interrupt to complete the transfer in ISR context.
         * Keep the transmit interrupt disabled. Transmit interrupt will be
         * enabled later if txCount < txSize, when rxCount = rxSize.
         */
        EVIC_channel_set(SPI_RX_INTERRUPT_CHANNEL(spiChannel));
    }
    else
    {
        if (spiObj->txCount != spiObj->txSize)
        {

            /* Configure SPI to generate transmit buffer empty interrupt only if more than
             * data is pending (STXISEL = '01')  */
            SPI_DESCRIPTOR(spiChannel)->spicon1.set = 0x00000004;
        }
        /* Enable transmit interrupt to complete the transfer in ISR context */
        EVIC_channel_set(SPI_TX_INTERRUPT_CHANNEL(spiChannel));
    }
    return true;
}
bool SPI_is_busy (uint32_t spiChannel)
{
    return ( (spiObjects[spiChannel].busy) || ((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SRMT_MASK) == 0));
}
void SPI_callback_register (SPI_Channel spiChannel, SPI_Callback callback, uintptr_t context)
{
    spiObjects[spiChannel].callback = callback;
    spiObjects[spiChannel].context = context;
}

static void SPI_rx_interrupt_handler_private (SPI_Channel spiChannel)
{
    uint32_t receivedData = 0;

    /* Check if the "receive" buffer is empty or not */
    if ((bool)(SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPIRBE_MASK) == false)
    {
        SPI_Object *spiObj = &spiObjects[spiChannel];
        /* Receive buffer is not empty. Read the received data. */
        receivedData = SPI_DESCRIPTOR(spiChannel)->spibuf.reg;

        if (spiObj->rxCount < spiObj->rxSize)
        {

            ((uint8_t*)spiObj->rxBuffer)[spiObj->rxCount++] = receivedData;

            if ((spiObj->rxCount == spiObj->rxSize) && (spiObj->txCount < spiObj->txSize))
            {
                /* Disable the "receive" interrupt */
                EVIC_channel_clr(SPI_RX_INTERRUPT_CHANNEL(spiChannel));

                /* Generate TX interrupt when buffer is completely empty (STXISEL = '00') */
                SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI2CON_STXISEL_MASK;
                SPI_DESCRIPTOR(spiChannel)->spicon1.set = 0x00000004;

                /* Enable the transmit interrupt. Callback will be given from the
                 * transmit interrupt, when all bytes are shifted out. */
                EVIC_channel_set(SPI_TX_INTERRUPT_CHANNEL(spiChannel));
            }
        }
        if (spiObj->rxCount < spiObj->rxSize)
        {
            /* More bytes pending to be received .. */
            if (spiObj->txCount < spiObj->txSize)
            {
                SPI_DESCRIPTOR(spiChannel)->spibuf.reg = ((uint8_t*)spiObj->txBuffer)[spiObj->txCount++];
            }
            else if (spiObj->dummySize > 0)
            {
                SPI_DESCRIPTOR(spiChannel)->spibuf.reg = (uint8_t)(0xff);
                spiObj->dummySize--;
            }
        }
        else
        {
            if((spiObj->rxCount == spiObj->rxSize) && (spiObj->txCount == spiObj->txSize))
            {
                /* Clear receiver overflow error if any */
                SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI2STAT_SPIROV_MASK;

                /* Disable receive interrupt */
                EVIC_channel_clr(SPI_RX_INTERRUPT_CHANNEL(spiChannel));

                /* Transfer complete. Give a callback */
                spiObj->busy = false;

                if(spiObj->callback != NULL)
                {
                    spiObj->callback(spiChannel, spiObj->context);
                }
            }
        }
    }

    EVIC_channel_pending_clear(SPI_RX_INTERRUPT_CHANNEL(spiChannel));
}

static void SPI_tx_interrupt_handler_private (SPI_Channel spiChannel)
{
    /* If there are more words to be transmitted, then transmit them here and keep track of the rxCount */
    if((SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SPITBE_MASK) == _SPI2STAT_SPITBE_MASK)
    {

        SPI_Object *spiObj = &spiObjects[spiChannel];
        if (spiObj->txCount < spiObj->txSize)
        {
            SPI_DESCRIPTOR(spiChannel)->spibuf.reg = ((uint8_t*)spiObj->txBuffer)[spiObj->txCount++];


            if (spiObj->txCount == spiObj->txSize)
            {
                /* All bytes are submitted to the SPI module. Now, enable transmit
                 * interrupt when the shift register is empty (STXISEL = '00')*/
                SPI_DESCRIPTOR(spiChannel)->spicon1.clr = _SPI2CON_STXISEL_MASK;
            }
        }
        else if ((spiObj->txCount == spiObj->txSize) && (SPI_DESCRIPTOR(spiChannel)->spistat.reg & _SPI2STAT_SRMT_MASK))
        {
            /* This part of code is executed when the shift register is empty. */

            /* Clear receiver overflow error if any */
            SPI_DESCRIPTOR(spiChannel)->spistat.clr = _SPI2STAT_SPIROV_MASK;

            /* Disable transmit interrupt */
            EVIC_channel_clr(SPI_TX_INTERRUPT_CHANNEL(spiChannel));

            /* Transfer complete. Give a callback */
            spiObj->busy = false;

            if(spiObj->callback != NULL)
            {
                spiObj->callback(spiChannel, spiObj->context);
            }
        }
    }
    /* Clear the transmit interrupt flag */
    EVIC_channel_pending_clear(SPI_TX_INTERRUPT_CHANNEL(spiChannel));
}

static void SPI_interrupt_handler(SPI_Channel spiChannel)
{
    if(EVIC_channel_pending_get(SPI_RX_INTERRUPT_CHANNEL(spiChannel)) &&
    EVIC_channel_get(SPI_RX_INTERRUPT_CHANNEL(spiChannel))){
        SPI_rx_interrupt_handler_private(spiChannel);
    }
    if(EVIC_channel_pending_get(SPI_TX_INTERRUPT_CHANNEL(spiChannel)) &&
       EVIC_channel_get(SPI_TX_INTERRUPT_CHANNEL(spiChannel))){
        SPI_tx_interrupt_handler_private(spiChannel);
    }
}

void        SPI_rx_interrupt_handler    (SPI_Channel spiChannel)
{
    SPI_interrupt_handler(spiChannel);
}
void        SPI_tx_interrupt_handler    (SPI_Channel spiChannel)
{
    SPI_interrupt_handler(spiChannel);
}

SPI_IRQ_Vector* SPI_get_irq_vector_base          (SPI_Channel spiChannel)
{
    static SPI_IRQ_Vector v;
    v.fault = spiIRQBase[spiChannel];
    v.rx = spiIRQBase[spiChannel]+1;
    v.tx = spiIRQBase[spiChannel] +2;
    return &v;
}
SPI_Descriptor SPI_get_descriptor      (SPI_Channel channel)
{
    return SPI_DESCRIPTOR(channel);
}

static uint32_t SPI_Baudrate_Get_(uint32_t baudrate){
    uint32_t clock;
    uint32_t brg;
    uint32_t error;

    clock = SYS_peripheral_clock_frequency_get(SYS_PERIPHERAL_CLOCK_2);
    brg = ((clock/baudrate)/2)-1;

    error = (clock / (2 * (brg + 1)));
    if(error > baudrate)
        brg++;

    return brg;
}