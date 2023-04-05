#ifndef TIMER_H
#define TIMER_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define TMR_CHANNEL_2                   (0)
#define TMR_CHANNEL_3                   (1)
#define TMR_CHANNEL_4                   (2)
#define TMR_CHANNEL_5                   (3)
#define TMR_CHANNEL_6                   (4)
#define TMR_CHANNEL_7                   (5)
#define TMR_CHANNEL_8                   (6)
#define TMR_CHANNEL_9                   (7)

#define TMR_TCKPS_MASK                  (0x07)

/*FLAGS*/
#define TMR_PRESCALER_1                 (0x0000)
#define TMR_PRESCALER_2                 (0x0001)
#define TMR_PRESCALER_4                 (0x0002)
#define TMR_PRESCALER_8                 (0x0003)
#define TMR_PRESCALER_16                (0x0004)
#define TMR_PRESCALER_32                (0x0005)
#define TMR_PRESCALER_64                (0x0006)
#define TMR_PRESCALER_256               (0x0007)
#define TMR_GATED                       (0x0008)
#define TMR_EXTERNAL_SOURCE             (0x0010)
#define TMR_MODE_32                     (0x0020)
/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void        TMR_initialize(uint32_t channel, uint32_t flags, uint32_t period);
void        TMR_start(uint32_t channel);
void        TMR_stop(uint32_t channel);
void        TMR_period_set(uint32_t channel, uint16_t period);
void        TMR_prescaler_set(uint32_t channel, uint16_t prescaler);
uint32_t    TMR_count_get(uint32_t channel);
uint32_t    TMR_frequency_get(uint32_t channel);
void        TMR_frequency_set(uint32_t channel, uint32_t frequency);
void        TMR_interrupt_handler(uint32_t channel);
void        TMR_channel_interrupt_callback(uint32_t channel);

#ifdef __cplusplus
}
#endif

#endif

#endif //TIMER_H
