//
// Created by bleppe on 30/01/23.
//

#ifndef DMA_H
#define DMA_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define DMA_CHANNEL_0                                       (0)
#define DMA_CHANNEL_1                                       (1)
#define DMA_CHANNEL_2                                       (2)
#define DMA_CHANNEL_3                                       (3)
#define DMA_CHANNEL_4                                       (4)
#define DMA_CHANNEL_5                                       (5)
#define DMA_CHANNEL_6                                       (6)
#define DMA_CHANNEL_7                                       (7)

#define DMA_CHANNEL_PRIORITY_3                              (0x0003)
#define DMA_CHANNEL_PRIORITY_2                              (0x0002)
#define DMA_CHANNEL_PRIORITY_1                              (0x0001)
#define DMA_CHANNEL_PRIORITY_0                              (0x0000)

#define DMA_CHANNEL_ABORT_IRQ                               (0x0004)
#define DMA_CHANNEL_START_IRQ                               (0x0008)
#define DMA_CHANNEL_CHAIN_LOWER                             (0x0010)
#define DMA_CHANNEL_CHAIN_UPPER                             (0x0020)
#define DMA_CHANNEL_CHAINED                                 (0x0040)
/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

typedef uint32_t DMA_Channel;

typedef struct{
    uint8_t                 abortIrq;
    uint8_t                 startIrq;
    uint16_t                srcSize;
    uint16_t                dstSize;
    uint16_t                cellSize;
    uint32_t                srcAddress;
    uint32_t                dstAddress;
}DMA_CHANNEL_Config;
typedef enum{
    DMA_IRQ_CAUSE_TRANSFER_COMPLETE,
    DMA_IRQ_CAUSE_ABORT,
    DMA_IRQ_CAUSE_ERROR
}DMA_IRQ_CAUSE;

typedef void (*DMA_Callback)(DMA_Channel, DMA_IRQ_CAUSE, uintptr_t);

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

int DMA_init();
int DMA_channel_init(DMA_Channel channel, int configFlags);
int DMA_channel_config(DMA_Channel channel, DMA_CHANNEL_Config *config);
int DMA_channel_transfer(DMA_Channel channel);
void DMA_callback_register(DMA_Channel channel, DMA_Callback callback, uintptr_t context);

#ifdef __cplusplus
}
#endif

#endif
#endif //DMA_H
