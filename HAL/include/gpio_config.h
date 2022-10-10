/**
 * @file gpio_config.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief Definitions for GPIO peripheral configuration.
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

/**********************************************************************
* Includes
**********************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**********************************************************************
* Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

/**
 * @brief Defines number of pins per port of current processor.
 * This definition is not used in the current implementation as peripheral configuration
 * is achieved with a configuration table of fixed size.
 * 
 */
#define NUMBER_OF_CHANNELS_PER_PORT (16U)
/**
 * @brief Define port count of current processor.
 * This definition is not used in the current implementation as peripheral configuration
 * is achieved with a configuration table of fixed size.
 */
#define NUMBER_OF_PORTS             (7)
/**
 * @brief Define interrupt count for current application. 
 * Modify this macro to suit application pin interrupt needs. 
 * This macro is used to statically allocate an array of interrupt callback objects per pin.
 * If only one pin is configured to trigger an interrupt, NUMBER_OF_INTERRUPTS should be set to 1, etc.
 */
#define NUMBER_OF_INTERRUPTS        (1)
/**
 * @brief Defines word length of current processor.
 * 
 */
#define TYPE                        uint32_t

#ifdef __cplusplus
extern "C"{
#endif
/**
 * @brief Possible states for digital pin configured as output.
 * 
 */
typedef enum{
    LOW=0,///<Low level on pin
    HIGH,///<High level on pin
}GPIO_STATE;

/**
 * @brief Possible pin directions.
 * 
 */
typedef enum{
    D_INPUT,///<Digital input pin
    D_OUTPUT,///<Digital output pin
    A_INPUT,///<Analog input pin
}GPIO_DIRECTION;

/**
 * @brief Possible states for pin internal pull-up resistors. 
 * 
 */
// typedef enum{
//     PULLUP_ENABLE,///<Internal pull-up resistors enabled.
//     PULLUP_DISABLE,///<Internal pull-up resistors disabled.
// }GPIO_PULLUP;
typedef bool GPIO_PULLUP;

/**
 * @brief Possible states for pin internal pull-down resistors. 
 * 
 */
// typedef enum{
//     PULLDOWN_ENABLE,///<Internal pull-down resistors enabled.
//     PULLDOWN_DISABLE,///<Internal pull-down resistors disabled.
// }GPIO_PULLDOWN;
typedef bool GPIO_PULLDOWN;

/**
 * @brief Possible slew rate states.
 * 
 */
typedef enum{
    SR_SLOWEST,///<Slowest slew rate
    SR_SLOW,///<Slow slew rate
    SR_FAST,///<Fast/Default slew rate 
    SR_FASTEST,///<Fastest slew rate
}GPIO_SLEW_RATE;

/**
 * @brief Possible open drain output states.
 * 
 */
// typedef enum{
//     OD_ENABLE,///<Open drain output enabled.
//     OD_DISABLE,///<Open drain output disabled.
// }GPIO_OPEN_DRAIN;
typedef bool GPIO_OPEN_DRAIN;

/**
 * @brief Possible state changed interrupt states.
 * 
 */
// typedef enum{
//     GPIO_IRQ_ENABLE,///<Enable state changed pin interrupt
//     GPIO_IRQ_DISABLE,///<Disable state changed pin interrupt
// }GPIO_INTERRUPT;
typedef bool GPIO_INTERRUPT;

/**
 * @brief Current processor PORT definition.
 * 
 */
typedef enum{
    GPIO_PORTA = 0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTF,
    GPIO_PORTG,
    GPIO_PORTH,
    GPIO_PORTJ,
    GPIO_PORTK,
}GPIO_PORT;

/**
 * @brief Current processor PIN definition.
 * Each pin is assigned a corresponding bit value on the current port.
 * Example: PORTB_1 belongs to PORTB (Pin bit val = 1, PORT val = 1) =>
 * PORTX_Y = Y | (X << 4), therefor PORTB_1 = 1 | (1<<4) = 17.
 * 
 */
typedef enum
{
    PORTA_0 = 0,
    PORTA_1 = 1,
    PORTA_2 = 2,
    PORTA_3 = 3,
    PORTA_4 = 4,
    PORTA_5 = 5,
    PORTA_6 = 6,
    PORTA_7 = 7,
    PORTA_9 = 9,
    PORTA_10 = 10,
    PORTA_14 = 14,
    PORTA_15 = 15,
    PORTB_0 = 16,
    PORTB_1 = 17,
    PORTB_2 = 18,
    PORTB_3 = 19,
    PORTB_4 = 20,
    PORTB_5 = 21,
    PORTB_6 = 22,
    PORTB_7 = 23,
    PORTB_8 = 24,
    PORTB_9 = 25,
    PORTB_10 = 26,
    PORTB_11 = 27,
    PORTB_12 = 28,
    PORTB_13 = 29,
    PORTB_14 = 30,
    PORTB_15 = 31,
    PORTC_1 = 33,
    PORTC_2 = 34,
    PORTC_3 = 35,
    PORTC_4 = 36,
    PORTC_12 = 44,
    PORTC_13 = 45,
    PORTC_14 = 46,
    PORTC_15 = 47,
    PORTD_0 = 48,
    PORTD_1 = 49,
    PORTD_2 = 50,
    PORTD_3 = 51,
    PORTD_4 = 52,
    PORTD_5 = 53,
    PORTD_9 = 57,
    PORTD_10 = 58,
    PORTD_11 = 59,
    PORTD_12 = 60,
    PORTD_13 = 61,
    PORTD_14 = 62,
    PORTD_15 = 63,
    PORTE_0 = 64,
    PORTE_1 = 65,
    PORTE_2 = 66,
    PORTE_3 = 67,
    PORTE_4 = 68,
    PORTE_5 = 69,
    PORTE_6 = 70,
    PORTE_7 = 71,
    PORTE_8 = 72,
    PORTE_9 = 73,
    PORTF_0 = 80,
    PORTF_1 = 81,
    PORTF_2 = 82,
    PORTF_3 = 83,
    PORTF_4 = 84,
    PORTF_5 = 85,
    PORTF_8 = 88,
    PORTF_12 = 92,
    PORTF_13 = 93,
    PORTG_0 = 96,
    PORTG_1 = 97,
    PORTG_6 = 102,
    PORTG_7 = 103,
    PORTG_8 = 104,
    PORTG_9 = 105,
    PORTG_12 = 108,
    PORTG_13 = 109,
    PORTG_14 = 110,
    PORTG_15 = 111,

    
    PIN_NONE = -1

}GPIO_PIN;

/**
 * @brief Input map register definitions for PIC32MZ family. 
 * Each element contains the address of the corresponding input map register.
 * Refer to PIC32MZ datasheet.
 * 
 * This definition should only be included in PIC32MZ family configurations.
 * 
 */
typedef enum{
    MAP_INT1R=0x1404,
    MAP_INT2R=0x1408,
    MAP_INT3R=0x140C,
    MAP_INT4R=0x1410,
    MAP_T2CKR=0x1418,
    MAP_T3CKR=0x141C,
    MAP_T4CKR=0x1420,
    MAP_T5CKR=0x1424,
    MAP_T6CKR=0x1428,
    MAP_T7CKR=0x142C,
    MAP_T8CKR=0x1430,
    MAP_T9CKR=0x1434,
    MAP_IC1R=0x1438,
    MAP_IC2R=0x143C,
    MAP_IC3R=0x1440,
    MAP_IC4R=0x1444,
    MAP_IC5R=0x1448,
    MAP_IC6R=0x144C,
    MAP_IC7R=0x1450,
    MAP_IC8R=0x1454,
    MAP_IC9R=0x1458,
    MAP_OCFAR=0x1460,
    MAP_U1RXR=0x1468,
    MAP_U1CTSR=0x146C,
    MAP_U2RXR=0x1470,
    MAP_U2CTSR=0x1474,
    MAP_U3RXR=0x1478,
    MAP_U3CTSR=0x147C,
    MAP_U4RXR=0x1480,
    MAP_U4CTSR=0x1484,
    MAP_U5RXR=0x1488,
    MAP_U5CTSR=0x148C,
    MAP_U6RXR=0x1490,
    MAP_U6CTSR=0x1494,
    MAP_SDI1R=0x149C,
    MAP_SS1R=0x14A0,
    MAP_SDI2R=0x14A8,
    MAP_SS2R=0x14AC,
    MAP_SDI3R=0x14B4,
    MAP_SS3R=0x14B8,
    MAP_SDI4R=0x14C0,
    MAP_SS4R=0x14C4,
    MAP_SDI5R=0x14CC,
    MAP_SS5R=0x14D0,
    MAP_SDI6R=0x14D8,
    MAP_SS6R=0x14DC,
    MAP_C1RXR=0x14E0,
    MAP_C2RXR=0x14E4,
    MAP_REFCLKI1R=0x14E8,
    MAP_REFCLKI3R=0x14F0,
    MAP_REFCLKI4R=0x14F4,
}GPIO_INPUT_MAPPING;

 /**
 * @brief Output map register definitions for PIC32MZ family. 
 * Each element contains the address of the corresponding output map register.
 * Refer to PIC32MZ datasheet.
 * 
 * This definition should only be included in PIC32MZ family configurations.
 * 
 */   
typedef enum{
    MAP_RPA14R=0x1538,
    MAP_RPA15R=0x153C,
    MAP_RPB0R=0x1540,
    MAP_RPB1R=0x1544,
    MAP_RPB2R=0x1548,
    MAP_RPB3R=0x154C,
    MAP_RPB5R=0x1554,
    MAP_RPB6R=0x1558,
    MAP_RPB7R=0x155C,
    MAP_RPB8=0x1560,
    MAP_RPB9R=0x1564,
    MAP_RPB10R=0x1568,
    MAP_RPB14R=0x1578,
    MAP_RPB15R=0x157C,
    MAP_RPC1R=0x1584,
    MAP_RPC2R=0x1588,
    MAP_RPC3R=0x158C,
    MAP_RPC4R=0x1590,
    MAP_RPC13R=0x15B4,
    MAP_RPC14R=0x15B8,
    MAP_RPD0R=0x15C0,
    MAP_RPD1R=0x15C4,
    MAP_RPD2R=0x15C8,
    MAP_RPD3R=0x15CC,
    MAP_RPD4R=0x15D0,
    MAP_RPD5R=0x15D4,
    MAP_RPD6R=0x15D8,
    MAP_RPD7R=0x15DC,
    MAP_RPD9R=0x15E4,
    MAP_RPD10R=0x15E8,
    MAP_RPD11R=0x15EC,
    MAP_RPD12R=0x15F0,
    MAP_RPD14R=0x15F8,
    MAP_RPD15R=0x15FC,
    MAP_RPE3R=0x160C,
    MAP_RPE5R=0x1614,
    MAP_RPE8R=0x1620,
    MAP_RPE9R=0x1624,
    MAP_RPF0R=0x1640,
    MAP_RPF1R=0x1644,
    MAP_RPF2R=0x1648,
    MAP_RPF3R=0x164C,
    MAP_RPF4R=0x1650,
    MAP_RPF5R=0x1654,
    MAP_RPF8R=0x1660,
    MAP_RPF12R=0x1670,
    MAP_RPF13R=0x1674,
    MAP_RPG0R=0x1680,
    MAP_RPG1R=0x1684,
    MAP_RPG6R=0x1698,
    MAP_RPG7R=0x169C,
    MAP_RPG8R=0x16A0,
    MAP_RPG9R=0x16A4,
}GPIO_OUTPUT_MAPPING;

/**
 * @brief General pin alternate function definitions.
 * 
 */
typedef enum{
    AF_0 = 0,
    AF_1,
    AF_2,
    AF_3,
    AF_4,
    AF_5,
    AF_6,
    AF_7,
    AF_8,
    AF_9,
    AF_10,
    AF_11,
    AF_12,
    AF_13,
    AF_14,
    AF_15,
    AF_NONE = -1,
}GPIO_ALTERNATE_FUNCTION;

/**
 * @brief Pin interrput callback function typedef.
 * 
 */
typedef void (*GPIO_CallbackFunction)(GPIO_PIN,uintptr_t);
/**
 * @brief Interrupt callback object definition.
 * 
 */
typedef struct{
    GPIO_PIN pin;///<Callback is executed with this pin's interrupt triggers.
    uintptr_t context;///<Generic data passed to the callback, user specified.
    GPIO_CallbackFunction callback;///<Callback function.
}GPIO_InterruptCallback;

/**
 * @brief Defines pin mode by specifying pin alternate function.
 * Implementation for PIC32MZ family.
 */
typedef struct{
    uint32_t reg;///<Register address of Input or Output mapping
    GPIO_ALTERNATE_FUNCTION function; ///<Alternate function for pin
}GPIO_MODE;

/**
 * @brief Basic configuration table for current pin.
 * 
 */
typedef struct{
    GPIO_PIN pin;///<Current pin being configured
    GPIO_DIRECTION direction;///<Direction of current pin
    GPIO_PULLUP pullup;
    GPIO_PULLDOWN pulldown;
    GPIO_SLEW_RATE slew;
    GPIO_OPEN_DRAIN od;
    GPIO_STATE state;///<Initial output state of current pin
    GPIO_INTERRUPT irq;
    GPIO_MODE mode;///<Alternate function of current pin
}GPIO_ConfigTable;
/**
 * @brief GPIO peripheral configuration struct.
 * This struct is passed to the @ref GPIO_Init function for pin initialization
 * and peripheral configuration.
 * 
 */
typedef struct{
    const GPIO_ConfigTable *const table;///<Pointer to the configuration table.
    const uint32_t tableSize;///<Configuration table size.
}GPIO_Config;

/**
 * @brief Function that gets the configuration struct.
 * 
 * @return const GPIO_Config* Configuration struct.
 */
const GPIO_Config* GPIO_GetConfig( void );

#ifdef __cplusplus
}
#endif

#endif