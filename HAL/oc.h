//
// Created by bruno on 12/02/23.
//

#ifndef OC_H
#define OC_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define OC_CHANNEL_1                        (0)
#define OC_CHANNEL_2                        (1)
#define OC_CHANNEL_3                        (2)
#define OC_CHANNEL_4                        (3)
#define OC_CHANNEL_5                        (4)
#define OC_CHANNEL_6                        (5)
#define OC_CHANNEL_7                        (6)
#define OC_CHANNEL_8                        (7)
#define OC_CHANNEL_9                        (8)

#define OC_MDOE_PWM_FAULT_ENABLED           (0x0007)
#define OC_MODE_PWM                         (0x0006)
#define OC_MODE_32                          (0x0020)
#define OC_MODE_USE_TMR3                    (0x0008)
#define OC_MODE_USE_TMR2                    (0)

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

void        OC_initialize   (uint32_t ocChannel, uint32_t flags, uint32_t compareValue);
void        OC_enable       (uint32_t ocChannel);
void        OC_disable      (uint32_t ocChannel);
void        OC_compare_set  (uint32_t ocChannel, uint32_t compareValue);
uint32_t    OC_compare_get  (uint32_t ocChannel);
#ifdef __cplusplus
}
#endif
#endif

#endif //OC_H
