/**
 * @file uart_config.c
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**********************************************************************
* Includes
**********************************************************************/
#include "uart_config.h" 

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/

static const UART_Table table[]={
//   UART_CHANNEL  | UART_PARITY |UART_STOP_BITS|UART_DATA_BITS| baudrate 
    {UART_CHANNEL_2, PARITY_NONE , STOP_BITS_2 , DATA_BITS_8   , 57600   },
    {UART_CHANNEL_3, PARITY_NONE , STOP_BITS_1 , DATA_BITS_8   , 9600    }
};

static const UART_Config config = {
    .table = (const UART_Table*)&table,
    .tableSize = sizeof(table)/sizeof(UART_Table)
};

/**********************************************************************
* Function Definitions
**********************************************************************/
const UART_Config* UART_GetConfig( void ){
    return (const UART_Config*)&config;
}