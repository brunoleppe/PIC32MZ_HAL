/**
 * @file evic_config.c
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
#include "evic_config.h" 


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
/*typedef struct{
    EVIC_IrqChannel channel;
    EVIC_IrqPriority priority;
    EVIC_IrqSubPriority subPriority;
}EVIC_Table;*/
/**
 * @brief Tabla de configuración de interrupciones.
 */
static const EVIC_Table table[]={
    {_CORE_TIMER_VECTOR     ,IRQ_PRIO_1,IRQ_SUB_0},
    {_TIMER_2_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_TIMER_3_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_TIMER_4_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_CHANGE_NOTICE_E_VECTOR,IRQ_PRIO_1,IRQ_SUB_0},
    {_USB_VECTOR            ,IRQ_PRIO_1,IRQ_SUB_0},
    {_USB_DMA_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_SPI2_RX_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_SPI2_TX_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_UART2_FAULT_VECTOR    ,IRQ_PRIO_1,IRQ_SUB_0},
    {_UART2_RX_VECTOR       ,IRQ_PRIO_1,IRQ_SUB_0},
    {_UART2_TX_VECTOR       ,IRQ_PRIO_1,IRQ_SUB_0},
    {_ETHERNET_VECTOR       ,IRQ_PRIO_1,IRQ_SUB_0},
    {_SPI3_RX_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_SPI3_TX_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_UART3_FAULT_VECTOR    ,IRQ_PRIO_1,IRQ_SUB_0},
    {_UART3_RX_VECTOR       ,IRQ_PRIO_1,IRQ_SUB_0},
    {_UART3_TX_VECTOR       ,IRQ_PRIO_1,IRQ_SUB_0},
    {_SPI4_RX_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_SPI4_TX_VECTOR        ,IRQ_PRIO_1,IRQ_SUB_0},
    {_FLASH_CONTROL_VECTOR  ,IRQ_PRIO_1,IRQ_SUB_0}
};
/**
 * @brief Objeto que contiene la tabla de interrupciones y su tamaño.
 * 
 */
static const EVIC_Config config = {
    .table = (const EVIC_Table*)&table,
    .tableSize = sizeof(table)/sizeof(EVIC_Table)
};

/**********************************************************************
* Function Definitions
**********************************************************************/
const EVIC_Config* EVIC_GetConfig( void ){
    return (const EVIC_Config*)&config;
}