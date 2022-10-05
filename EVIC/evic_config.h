/**
 * @file evic_config.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EVIC_CONFIG_H
#define EVIC_CONFIG_H

/**********************************************************************
* Includes
**********************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <xc.h>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/
/**
 * @brief Define el canal de la interrupción.
 *  
 */
typedef uint32_t EVIC_IrqChannel;
/**
 * @brief Define las posibles prioridades de la interrupción.
 * 
 */
typedef enum{
    IRQ_PRIO_0 = 0,
    IRQ_PRIO_1,
    IRQ_PRIO_2,
    IRQ_PRIO_3,
    IRQ_PRIO_4,
    IRQ_PRIO_5,
    IRQ_PRIO_6,
    IRQ_PRIO_7,
}EVIC_IrqPriority;
/**
 * @brief Define las posibles subprioridades de la interrupción.
 * 
 */
typedef enum{
    IRQ_SUB_0 = 0,
    IRQ_SUB_1,
    IRQ_SUB_2,
    IRQ_SUB_3,
}EVIC_IrqSubPriority;
/**
 * @brief Define el estado de la interrupción.
 * 
 */
typedef enum{
    IRQ_ENABLED,
    IRQ_DISABLED,
}EVIC_IrqState;
/**
 * @brief Define la estructura de la tabla de interrupciones.
 * 
 */
typedef struct{
    EVIC_IrqChannel channel;
    EVIC_IrqPriority priority;
    EVIC_IrqSubPriority subPriority;
}EVIC_Table;
/**
 * @brief Define la estructura de configuraciones de interrupciones del sistem.
 * 
 */
typedef struct{
    const EVIC_Table * const table;
    const int tableSize;
}EVIC_Config;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Devuelve un puntero a las configuraciones de interrupciones del sistema.
 * 
 * @return const EVIC_Config* Configuraciones del sistema.
 */
const EVIC_Config* EVIC_GetConfig( void );

#ifdef __cplusplus
}
#endif


#endif /*EVIC_CONFIG_H*/