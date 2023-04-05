/**********************************************************************
* Includes
**********************************************************************/
#include "evic.h"
#include "pic32mz_registers.h"
#include <xc.h>
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

static MemRegister ipc_base = (MemRegister)(&IPC0);

static MemRegister iec_base = (MemRegister)(&IEC0);

static MemRegister ifs_base = (MemRegister)(&IFS0);

/**********************************************************************
* Function Definitions
**********************************************************************/

int     EVIC_init(void *data)
{
    /*Multi-vectored interrupts*/
    INTCONSET = _INTCON_MVEC_MASK;
    PRISS = 0x76543210;
    return 0;
}
int     EVIC_channel_state_Set(
        EVIC_CHANNEL channel,
        EVIC_STATE state,
        EVIC_PRIORITY priority,
        EVIC_SUB_PRIORITY sub_priority
)
{
    uint32_t offset;

    /*Dividir para cuatro el número del canal de interrupción para obtener
         la dirección del registro IPC correspondiente.*/
    offset = channel >> 2;
    /*Se utiliza los dos primeros bits del número del canal para obtener el
     offset del byte correspondiente dentro del registro IPC*/
    uint32_t byteOffset = channel & 0b11;
    /*Apuntar hacia el registro IPC correspondiente*/
    /*Configurar prioridad y sub-prioridad del byte en el registro IPC*/
    (ipc_base + offset)->set = (sub_priority << (8*byteOffset)) |
               (priority << (8*byteOffset+2));


    offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    if(state == EVIC_STATE_ENABLED)
        (iec_base+offset)->set = bitOffset;
    else
        (iec_base+offset)->clr = bitOffset;

    return 0;
}
bool    EVIC_channel_pending_get(EVIC_CHANNEL channel)
{
    int offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    return (ifs_base+offset)->reg & bitOffset;
}
void    EVIC_channel_pending_clear(EVIC_CHANNEL channel)
{
    int offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    (ifs_base+offset)->clr = bitOffset;
}
void        EVIC_channel_priority(EVIC_CHANNEL channel, EVIC_PRIORITY priority, EVIC_SUB_PRIORITY subPriority)
{
    uint32_t offset;

    /*Dividir para cuatro el número del canal de interrupción para obtener
         la dirección del registro IPC correspondiente.*/
    offset = channel >> 2;
    /*Se utiliza los dos primeros bits del número del canal para obtener el
     offset del byte correspondiente dentro del registro IPC*/
    uint32_t byteOffset = channel & 0b11;
    /*Apuntar hacia el registro IPC correspondiente*/
    /*Configurar prioridad y sub-prioridad del byte en el registro IPC*/
    (ipc_base + offset)->set = (subPriority << (8 * byteOffset)) |
                               (priority << (8*byteOffset+2));
}
void        EVIC_channel_set(EVIC_CHANNEL channel)
{
    uint32_t offset;
    offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
        (iec_base+offset)->set = bitOffset;
}
void        EVIC_channel_clr(EVIC_CHANNEL channel)
{
    uint32_t offset;
    offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    (iec_base+offset)->clr = bitOffset;
}
uint32_t    EVIC_enable_interrupts( void )
{
    return __builtin_enable_interrupts();
}
uint32_t    EVIC_disable_interrupts( void )
{
    return __builtin_disable_interrupts();
}
void    EVIC_restore_interrupts( uint32_t status )
{
    if(status)
        __builtin_enable_interrupts();
}