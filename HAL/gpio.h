/**
 * @file gpio.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief GPIO Interface.
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GPIO_H
#define GPIO_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define GPIO_PORT_SHIFT             (16)
#define GPIO_PORT_MASK              (0xF0000)

#define GPIO_PORT_A                 (0x0)
#define GPIO_PORT_B                 (0x1)
#define GPIO_PORT_C                 (0x2)
#define GPIO_PORT_D                 (0x3)
#define GPIO_PORT_E                 (0x4)
#define GPIO_PORT_F                 (0x5)
#define GPIO_PORT_G                 (0x6)
#define GPIO_PORT_H                 (0x7)
#define GPIO_PORT_J                 (0x8)
#define GPIO_PORT_K                 (0x9)

#define GPIO_INPUT                  (0x0000)
#define GPIO_OUTPUT                 (0x0001)
#define GPIO_ANALOG                 (0x0002)
#define GPIO_PULLUP                 (0x0004)
#define GPIO_PULLDOWN               (0x0008)
#define GPIO_OPENDRAIN              (0x0010)
#define GPIO_SLOWEST                (0x0020)
#define GPIO_SLOW                   (0x0040)
#define GPIO_FAST                   (0x0080)
#define GPIO_FASTEST                (0x0100)
#define GPIO_IRQ                    (0x0200)

#define GPIO_INPUT_PULLUP           (GPIO_PULLUP)
#define GPIO_INPUT_PULLDOWN         (GPIO_PULLDOWN)
#define GPIO_OUTPUT_OD              (GPIO_OUTPUT | GPIO_OPENDRAIN)


#define GPIO_PIN_MASK               (0xFFFF)
#define GPIO_PIN_0                  (0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                  (0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                  (0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                  (0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                  (0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                  (0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                  (0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                  (0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                  (0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                  (0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                 (0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                 (0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                 (0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                 (0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                 (0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                 (0x8000)  /* Pin 15 selected   */
#define GPIO_ALL                    (0xFFFF)

#define GPIO_PIN_INVALID            (0xFFFFFFFF)

#define GPIO_LOW                    (0)
#define GPIO_HIGH                   (1)
/*********************************************************************
* Preprocessor Macros
**********************************************************************/
#define GPIO_PIN_MAP(port, pin)     ((port << GPIO_PORT_SHIFT) | pin)
/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)
typedef bool GPIO_STATE;
typedef bool GPIO_IRQ_STATE;

typedef uint32_t GPIO_Pin;
typedef uint32_t GPIO_Port;
typedef uint32_t GPIO_PinMap;

typedef uint32_t GPIO_ALTERNATE_FUNCTION;
typedef void (*GPIO_Callback)(GPIO_PinMap, uintptr_t context);

typedef struct{
    GPIO_PinMap pin;
    GPIO_Callback  callback;
    uintptr_t context;
}GPIO_CALLBACK_OBJECT;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
    
void        GPIO_pin_initialize             (GPIO_PinMap pin, int flags);
void        GPIO_pin_deinitialize           (GPIO_PinMap pin);
bool        GPIO_pin_read                   (GPIO_PinMap pin);
void        GPIO_pin_write                  (GPIO_PinMap pin, bool value);
void        GPIO_pin_toggle                 (GPIO_PinMap pin);
void        GPIO_pin_interrupt_set          (GPIO_PinMap pin, bool state);

void        GPIO_port_write                 (GPIO_Port port, uint32_t value, uint32_t mask);
uint32_t    GPIO_port_read                  (GPIO_Port port, uint32_t mask);
void        GPIO_port_toggle                (GPIO_Port port, uint32_t mask);

void        GPIO_pin_interrupt_callback     (GPIO_PinMap pin);
void        GPIO_interrupt_handler          (GPIO_Port port);


#ifdef __cplusplus
}
#endif

#endif


#endif