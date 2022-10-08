/**
 * @file evic.c
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
#include <xc.h>
#include "evic.h"
#include "pic32mz_registers.h"

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
/**
 * Define la posición inicial de los registros de prioridad y subprioridad de
 * interrupciones del pic32MZ.
 */
static MemRegister ipcBase = (MemRegister)(&IPC0);
/**
 * Define la posición inicial de los registros de habilitación de interrupciones
 * del pic32MZ.
 */
static MemRegister iecBase = (MemRegister)(&IEC0);
/**
 * Define la posición inicial de los registros de banderas de interrupción
 * del pic32MZ.
 */
static MemRegister ifsBase = (MemRegister)(&IFS0);

/**********************************************************************
* Function Definitions
**********************************************************************/
void EVIC_Init(const EVIC_Config *config)
{
    /*Multi-vectored interrupts*/
    INTCONSET = _INTCON_MVEC_MASK;
    
    /*Configuración de registros IPC de prioridad y subprioridad.
     Nota: La prioridad debe ser mayor a 0. Si la prioridad es 0 la interrupción
     no será atendida por el procesasdor.
     */
    int i;
    for(i=0;i<config->tableSize;i++){
        /*Dividir para cuatro el número del canal de interrupción para obtener
         la dirección del registro IPC correspondiente.*/
        int offset = config->table[i].channel >> 2;
        /*Se utiliza los dos primeros bits del número del canal para obtener el
         offset del byte correspondiente dentro del registro IPC*/
        int byteOffset = config->table[i].channel & 0b11;
        /*Apuntar hacia el registro IPC correspondiente*/
        MemRegister reg = ipcBase+offset;
        /*Configurar prioridad y subprioridad del byte en el registro IPC*/
        reg->set = (config->table[i].subPriority << (8*byteOffset)) | 
                (config->table[i].priority << (8*byteOffset+2));
    }
    
     PRISS = 0x76543210;
}

void EVIC_ChannelStateSet(EVIC_IrqChannel channel, EVIC_IrqState state)
{
    int offset = channel >> 5; 
    int bitOffset = 1<<(channel & 0x1f);
    MemRegister reg = iecBase+offset;
    if(state == IRQ_ENABLED)
        reg->set = bitOffset;
    else
        reg->clr = bitOffset;
}

bool EVIC_IrqPendingGet(EVIC_IrqChannel channel)
{
    int offset = channel >> 5; 
    int bitOffset = 1<<(channel & 0x1f);
    MemRegister reg = ifsBase+offset;
    return reg->reg & bitOffset;
}

void EVIC_IrqPendingClear(EVIC_IrqChannel channel)
{
    int offset = channel >> 5; 
    int bitOffset = 1<<(channel & 0x1f);
    MemRegister reg = ifsBase+offset;
    reg->clr = bitOffset;
}

void EVIC_EnableInterrupts(void)
{
    __builtin_enable_interrupts();
}

bool EVIC_DisableInterrupts(void)
{
    return __builtin_disable_interrupts() & 0x1;
}

void EVIC_RestoreInterrupts(bool status)
{
    if(status)
        __builtin_enable_interrupts();
}
