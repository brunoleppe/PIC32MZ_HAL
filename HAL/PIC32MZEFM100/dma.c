//
// Created by bleppe on 30/01/23.
//
/**********************************************************************
* Includes
**********************************************************************/
#include "dma.h"
#include "evic.h"
#include "pic32mz_registers.h"
#include <xc.h>
#include <sys/kmem.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define DMA_NUMBER_OF_CHANNELS                  8
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define DMA_DESCRIPTOR(channel)                 ((DMA_Descriptor)(((uint8_t*)(&DCH0CON)) + 0xC0*(channel)))
#define DMA_EVIC_CHANNEL(channel)               (EVIC_CHANNEL_DMA0 + channel)
/**********************************************************************
* Module Typedefs
**********************************************************************/
typedef struct{
    DMA_Callback callback;
    uintptr_t context;
}DMA_Object;
/**********************************************************************
* Module Variable Definitions
**********************************************************************/
static DMA_Object dmaObjs[DMA_NUMBER_OF_CHANNELS];
/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
int DMA_init()
{
    DMACONSET = _DMACON_ON_MASK;
    return 0;
}
int DMA_channel_init(DMA_Channel channel, int configFlags)
{
    DMA_DESCRIPTOR(channel)->dchcon.reg = 0x03 & configFlags;
    DMA_DESCRIPTOR(channel)->dchecon.reg = 0;
    DMA_DESCRIPTOR(channel)->dchint.reg = 0;
    if((configFlags & DMA_CHANNEL_ABORT_IRQ) == DMA_CHANNEL_ABORT_IRQ) {
        DMA_DESCRIPTOR(channel)->dchecon.set = _DCH0ECON_AIRQEN_MASK;
        DMA_DESCRIPTOR(channel)->dchint.set = _DCH0INT_CHTAIE_MASK;
    }
    if((configFlags & DMA_CHANNEL_START_IRQ) == DMA_CHANNEL_START_IRQ) {
        DMA_DESCRIPTOR(channel)->dchecon.set = _DCH0ECON_SIRQEN_MASK;
        DMA_DESCRIPTOR(channel)->dchint.set = _DCH0INT_CHBCIE_MASK;
    }
    if((configFlags & DMA_CHANNEL_CHAINED) == DMA_CHANNEL_CHAINED){
        DMA_DESCRIPTOR(channel)->dchcon.set = _DCH1CON_CHCHNS_MASK;
    }
    if((configFlags & DMA_CHANNEL_CHAIN_LOWER) == DMA_CHANNEL_CHAIN_LOWER){
        DMA_DESCRIPTOR(channel)->dchcon.set = _DCH1CON_CHCHNS_MASK;
    }
    else if((configFlags & DMA_CHANNEL_CHAIN_UPPER) == DMA_CHANNEL_CHAIN_UPPER){
        DMA_DESCRIPTOR(channel)->dchcon.clr = _DCH1CON_CHCHNS_MASK;
    }
    DMA_DESCRIPTOR(channel)->dchint.set = _DCH0INT_CHERIE_MASK;
    dmaObjs[channel].callback = NULL;
    return 0;
}
int DMA_channel_config(DMA_Channel channel, DMA_CHANNEL_Config *config)
{
    DMA_DESCRIPTOR(channel)->dchssa.reg = KVA_TO_PA(config->srcAddress);
    DMA_DESCRIPTOR(channel)->dchdsa.reg = KVA_TO_PA(config->dstAddress);
    DMA_DESCRIPTOR(channel)->dchssiz.reg = config->srcSize;
    DMA_DESCRIPTOR(channel)->dchdsiz.reg = config->dstSize;
    DMA_DESCRIPTOR(channel)->dchcsiz.reg = config->cellSize;
    DMA_DESCRIPTOR(channel)->dchecon.set = config->startIrq << _DCH0ECON_CHSIRQ_POSITION;
    DMA_DESCRIPTOR(channel)->dchecon.set = config->abortIrq << _DCH0ECON_CHAIRQ_POSITION;
    DMA_DESCRIPTOR(channel)->dchint.clr = 0x000000ff;
    return 0;
}
int DMA_channel_transfer(DMA_Channel channel)
{

    DMA_DESCRIPTOR(channel)->dchcon.set = _DCH0CON_CHEN_MASK;
    if((DMA_DESCRIPTOR(channel)->dchcon.reg & _DCH0CON_CHBUSY_MASK) != _DCH0CON_CHBUSY_MASK){
        DMA_DESCRIPTOR(channel)->dchecon.set = _DCH0ECON_CFORCE_MASK;
    }

    return 0;
}

void DMA_callback_register(DMA_Channel channel, DMA_Callback callback, uintptr_t context)
{
    dmaObjs[channel].callback = callback;
    dmaObjs[channel].context = context;
}

void DMA_interrupt_handler(DMA_Channel channel){
    DMA_IRQ_CAUSE cause = 0;
    if((DMA_DESCRIPTOR(channel)->dchint.reg & _DCH0INT_CHBCIF_MASK) == _DCH0INT_CHBCIF_MASK){
        cause = DMA_IRQ_CAUSE_TRANSFER_COMPLETE;
        DMA_DESCRIPTOR(channel)->dchint.clr = _DCH0INT_CHBCIF_MASK;
    }
    else if((DMA_DESCRIPTOR(channel)->dchint.reg & _DCH0INT_CHTAIF_MASK) == _DCH0INT_CHTAIF_MASK){
        cause = DMA_IRQ_CAUSE_ABORT;
        DMA_DESCRIPTOR(channel)->dchint.clr = _DCH0INT_CHTAIF_MASK;
    }
    else if((DMA_DESCRIPTOR(channel)->dchint.reg & _DCH0INT_CHERIF_MASK) == _DCH0INT_CHERIF_MASK){
        cause = DMA_IRQ_CAUSE_ERROR;
        DMA_DESCRIPTOR(channel)->dchint.clr = _DCH0INT_CHERIF_MASK;
    }
    if(dmaObjs[channel].callback != NULL){
        dmaObjs[channel].callback(channel, cause, dmaObjs[channel].context);
    }

    EVIC_channel_pending_clear(DMA_EVIC_CHANNEL(channel));
}