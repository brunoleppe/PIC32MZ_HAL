#ifndef READER_EVIC_H
#define READER_EVIC_H
/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/
typedef enum{
    EVIC_CHANNEL_CORE_TIMER                          = 0,
    EVIC_CHANNEL_CORE_SOFTWARE_0                     = 1,
    EVIC_CHANNEL_CORE_SOFTWARE_1                     = 2,
    EVIC_CHANNEL_EXTERNAL_0                          = 3,
    EVIC_CHANNEL_TIMER_1                             = 4,
    EVIC_CHANNEL_INPUT_CAPTURE_1                     = 5,
    EVIC_CHANNEL_OUTPUT_COMPARE_1                    = 6,
    EVIC_CHANNEL_EXTERNAL_1                          = 7,
    EVIC_CHANNEL_TIMER_2                             = 8,
    EVIC_CHANNEL_INPUT_CAPTURE_2                     = 9,
    EVIC_CHANNEL_OUTPUT_COMPARE_2                    = 10,
    EVIC_CHANNEL_EXTERNAL_2                          = 11,
    EVIC_CHANNEL_TIMER_3                             = 12,
    EVIC_CHANNEL_INPUT_CAPTURE_3                     = 13,
    EVIC_CHANNEL_OUTPUT_COMPARE_3                    = 14,
    EVIC_CHANNEL_EXTERNAL_3                          = 15,
    EVIC_CHANNEL_TIMER_4                             = 16,
    EVIC_CHANNEL_INPUT_CAPTURE_4                     = 17,
    EVIC_CHANNEL_OUTPUT_COMPARE_4                    = 18,
    EVIC_CHANNEL_EXTERNAL_4                          = 19,
    EVIC_CHANNEL_TIMER_5                             = 20,
    EVIC_CHANNEL_INPUT_CAPTURE_5                     = 21,
    EVIC_CHANNEL_OUTPUT_COMPARE_5                    = 22,
    EVIC_CHANNEL_I2C3_BUS                            = 26,
    EVIC_CHANNEL_SPI3_ERR                            = 26,
    EVIC_CHANNEL_UART1_ERR                           = 26,
    EVIC_CHANNEL_I2C3_SLAVE                          = 27,
    EVIC_CHANNEL_SPI3_RX                             = 27,
    EVIC_CHANNEL_UART1_RX                            = 27,
    EVIC_CHANNEL_I2C3_MASTER                         = 28,
    EVIC_CHANNEL_SPI3_TX                             = 28,
    EVIC_CHANNEL_UART1_TX                            = 28,
    EVIC_CHANNEL_I2C1_BUS                            = 29,
    EVIC_CHANNEL_I2C1_SLAVE                          = 30,
    EVIC_CHANNEL_I2C1_MASTER                         = 31,
    EVIC_CHANNEL_CHANGE_NOTICE                       = 32,
    EVIC_CHANNEL_ADC                                 = 33,
    EVIC_CHANNEL_PMP                                 = 34,
    EVIC_CHANNEL_COMPARATOR_1                        = 35,
    EVIC_CHANNEL_COMPARATOR_2                        = 36,
    EVIC_CHANNEL_I2C4_BUS                            = 37,
    EVIC_CHANNEL_SPI2_ERR                            = 37,
    EVIC_CHANNEL_UART3_ERR                           = 37,
    EVIC_CHANNEL_I2C4_SLAVE                          = 38,
    EVIC_CHANNEL_SPI2_RX                             = 38,
    EVIC_CHANNEL_UART3_RX                            = 38,
    EVIC_CHANNEL_I2C4_MASTER                         = 39,
    EVIC_CHANNEL_SPI2_TX                             = 39,
    EVIC_CHANNEL_UART3_TX                            = 39,
    EVIC_CHANNEL_I2C5_BUS                            = 40,
    EVIC_CHANNEL_SPI4_ERR                            = 40,
    EVIC_CHANNEL_UART2_ERR                           = 40,
    EVIC_CHANNEL_I2C5_SLAVE                          = 41,
    EVIC_CHANNEL_SPI4_RX                             = 41,
    EVIC_CHANNEL_UART2_RX                            = 41,
    EVIC_CHANNEL_I2C5_MASTER                         = 42,
    EVIC_CHANNEL_SPI4_TX                             = 42,
    EVIC_CHANNEL_UART2_TX                            = 42,
    EVIC_CHANNEL_FAIL_SAFE_MONITOR                   = 46,
    EVIC_CHANNEL_RTCC                                = 47,
    EVIC_CHANNEL_DMA0                                = 48,
    EVIC_CHANNEL_DMA1                                = 49,
    EVIC_CHANNEL_DMA2                                = 50,
    EVIC_CHANNEL_DMA3                                = 51,
    EVIC_CHANNEL_DMA4                                = 52,
    EVIC_CHANNEL_DMA5                                = 53,
    EVIC_CHANNEL_DMA6                                = 54,
    EVIC_CHANNEL_DMA7                                = 55,
    EVIC_CHANNEL_FLASH_CONTROL                       = 56,
    EVIC_CHANNEL_USB                                 = 57,
    EVIC_CHANNEL_CAN1                                = 58,
    EVIC_CHANNEL_CAN2                                = 59,
    EVIC_CHANNEL_ETHERNET                            = 60,
    EVIC_CHANNEL_INPUT_CAPTURE_1_ERROR               = 61,
    EVIC_CHANNEL_INPUT_CAPTURE_2_ERROR               = 62,
    EVIC_CHANNEL_INPUT_CAPTURE_3_ERROR               = 63,
    EVIC_CHANNEL_INPUT_CAPTURE_4_ERROR               = 64,
    EVIC_CHANNEL_INPUT_CAPTURE_5_ERROR               = 65,
    EVIC_CHANNEL_PMP_ERROR                           = 66,
    EVIC_CHANNEL_UART4_ERR                           = 67,
    EVIC_CHANNEL_UART4_RX                            = 68,
    EVIC_CHANNEL_UART4_TX                            = 69,
    EVIC_CHANNEL_UART6_ERR                           = 70,
    EVIC_CHANNEL_UART6_RX                            = 71,
    EVIC_CHANNEL_UART6_TX                            = 72,
    EVIC_CHANNEL_UART5_ERR                           = 73,
    EVIC_CHANNEL_UART5_RX                            = 74,
    EVIC_CHANNEL_UART5_TX                            = 75,
}EVIC_CHANNEL;
typedef enum{
    EVIC_STATE_ENABLED = 0,
    EVIC_STATE_DISABLED
}EVIC_STATE;
typedef enum{
    EVIC_PRIORITY_0 = 0,
    EVIC_PRIORITY_1    ,
    EVIC_PRIORITY_2    ,
    EVIC_PRIORITY_3    ,
    EVIC_PRIORITY_4    ,
    EVIC_PRIORITY_5    ,
    EVIC_PRIORITY_6    ,
    EVIC_PRIORITY_7    ,

}EVIC_PRIORITY;
typedef enum{
    EVIC_SUB_PRIORITY_0 = 0,
    EVIC_SUB_PRIORITY_1,
    EVIC_SUB_PRIORITY_2,
    EVIC_SUB_PRIORITY_3,
}EVIC_SUB_PRIORITY;
/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
int         EVIC_init(void *data);
int         EVIC_channel_state_Set(
                EVIC_CHANNEL channel,
                EVIC_STATE state,
                EVIC_PRIORITY priority,
                EVIC_SUB_PRIORITY sub_priority
            );
void        EVIC_channel_priority(EVIC_CHANNEL channel, EVIC_PRIORITY, EVIC_SUB_PRIORITY);
void        EVIC_channel_set(EVIC_CHANNEL channel);
void        EVIC_channel_clr(EVIC_CHANNEL channel);
bool        EVIC_channel_get(EVIC_CHANNEL channel);
bool        EVIC_channel_pending_get(EVIC_CHANNEL channel);
void        EVIC_channel_pending_clear(EVIC_CHANNEL);
uint32_t    EVIC_enable_interrupts( void );
uint32_t    EVIC_disable_interrupts( void );
void        EVIC_restore_interrupts( uint32_t status );
#ifdef __cplusplus
}
#endif
#endif //READER_EVIC_H
