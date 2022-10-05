/**
 * @file evic.h
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EVIC_H
#define EVIC_H

/**********************************************************************
* Includes
**********************************************************************/
#include "evic_config.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Inicializa el controlador de interrupciones con las configuraciones 
 * proporcionadas.
 * 
 * @param config Configuraciones del controlador.
 */
void EVIC_Init(const EVIC_Config *config);
/**
 * @brief Activa o desactiva la interrupción deseada.
 * 
 * @param channel Interrupción que será modificada.
 */
void EVIC_ChannelStateSet(EVIC_IrqChannel channel, EVIC_IrqState state);
/**
 * @brief Devuelve el estado de la bandera de interrupción.
 * 
 * @param channel Interrupción de la cual se necesita el estado de su bandera.
 * @return true Si la interrupción ya ocurrió y no ha sido atendida.
 * @return false Falso si la interrupeción ya fue atendida o todavía no ocurre.
 */
bool EVIC_IrqPendingGet(EVIC_IrqChannel channel);
/**
 * @brief Limpia la bandera de interrupción después de que ha sido atendida.
 * 
 * @param channel Interrupción que será modificada;
 */
void EVIC_IrqPendingClear(EVIC_IrqChannel channel);
/**
 * @brief Activa las interrupciones globales.
 * 
 */
void EVIC_EnableInterrupts(void);
/**
 * @brief Desactiva las interrupciones globales.
 * 
 */
bool EVIC_DisableInterrupts(void);
/**
 * @brief Restaura el estado original de las interrupciones.
 * Se debe usar esta función cuando se deshabilitan las funciones usando
 * EVIC_DisableInterrupts().
 * @example Ejemplo:
 * @code
 * bool status = EVIC_EnableInterrupts();
 * ...
 * EVIC_RestoreInterrupts(status);
 * @endcode
 * @param status Estado original
 * 
 */
void EVIC_RestoreInterrupts(bool status);

#ifdef __cplusplus
}
#endif

#endif /*EVIC_H*/