/**
 * @file gpio_config.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
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
 * @brief Define el número de pines en cada puerto del procesador.
 * 
 */
#define NUMBER_OF_CHANNELS_PER_PORT (16U)
/**
 * @brief Define el número de puertos del procesador.
 * 
 */
#define NUMBER_OF_PORTS             (7)
/**
 * @brief Define el número de interrupciones de la aplicación.
 */
#define NUMBER_OF_INTERRUPTS        (1)
/**
 * @brief Define el ancho de la palabra de un registro del procesador.
 * 
 */
#define TYPE                        uint32_t

#ifdef __cplusplus
extern "C"{
#endif
/**
 * @brief Define los posibles estados para un pin de salida digital.
 * 
 */
typedef enum{
    LOW=0,///<Salida en bajo
    HIGH,///<Salida en alto
}GPIO_STATE;

/**
 * @brief Define el tipo de pin.
 * 
 */
typedef enum{
    D_INPUT,///<Pin de entrada digital
    D_OUTPUT,///<Pin de salida digital
    A_INPUT,///<Pin de entrada analógica
}GPIO_DIRECTION;

/**
 * @brief Define el estado de las resistencias de Pull-Up.
 * 
 */
typedef enum{
    PULLUP_ENABLE,///<Habilitar Pull-up interna
    PULLUP_DISABLE,///<Deshabilitar Pull-up interna
}GPIO_PULLUP;

/**
 * @brief Define el estado de las resistencias de Pull-Down.
 * 
 */
typedef enum{
    PULLDOWN_ENABLE,///<Habilitar Pull-down interna
    PULLDOWN_DISABLE,///<Deshabilitar Pull-down interna
}GPIO_PULLDOWN;

/**
 * @brief Define el slew rate para el pin
 * 
 */
typedef enum{
    SR_SLOWEST,///<Control de slew rate más lento
    SR_SLOW,///<Control de slew rate lento
    SR_FAST,///<Contol de slew rate normal 
    SR_FASTEST,///<Control de slew rate más rápido
}GPIO_SLEW_RATE;

/**
 * @brief Define los estados posibles para open drain.
 * 
 */
typedef enum{
    OD_ENABLE,///<Habilitar open drain
    OD_DISABLE,///<Deshabilitar open drain
}GPIO_OPEN_DRAIN;

/**
 * @brief Define los estados de la interrupción del pin por notificación de cambio
 * 
 */
typedef enum{
    GPIO_IRQ_ENABLE,///<Habilitar interrupción por cambio de estado
    GPIO_IRQ_DISABLE,///<Deshabilitar interrupción por cambio de estado
}GPIO_INTERRUPT;

/**
 * @brief Define los puertos del MCU
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
 * @brief Define los pines disponibles del MCU
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

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    PORT_NONE = -1

}GPIO_PIN;


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
 * @brief Define la función de callback para GPIO.
 * 
 */
typedef void (*GPIO_CallbackFunction)(GPIO_PIN,uintptr_t);
/**
 * @brief Define la estructura para el registro de callbacks.
 * 
 */
typedef struct{
    GPIO_PIN pin;
    uintptr_t context;
    GPIO_CallbackFunction callback;
}GPIO_InterruptCallback;

/**
 * @brief Define el modo de funcionamineto del PIN aplicado a PIC32MZ.
 * 
 */
typedef struct{
    uint32_t reg;
    GPIO_ALTERNATE_FUNCTION function;
}GPIO_MODE;

/**
 * @brief Define la configuración de un puerto.
 * 
 */
typedef struct{
    GPIO_PIN pin;
    GPIO_DIRECTION direction;
//    GPIO_PULLUP pullup;
//    GPIO_PULLDOWN pulldown;
//    GPIO_SLEW_RATE slew;
//    GPIO_OPEN_DRAIN od;
    GPIO_STATE state;
    GPIO_MODE mode;
//    GPIO_INTERRUPT interruptState;
}GPIO_ConfigTable;

typedef struct{
    const GPIO_ConfigTable *const table;
    uint32_t tableSize;
}GPIO_Config;

const GPIO_Config* GPIO_GetConfig( void );

#ifdef __cplusplus
}
#endif

#endif