/**********************************************************************
* Includes
**********************************************************************/
#include "evic.h"
#include "pic32mx_registers.h"
#include <xc.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define IPC_BASE    (MemRegister)(&IPC0)
#define IEC_BASE    (MemRegister)(&IEC0)
#define IFS_BASE    (MemRegister)(&IFS0)
/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static const uint8_t vector_number[76] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,23,23,24,24,24,25,
    25,25,26,27,28,29,30,31,31,31,32,32,32, 33,
    33,33,34,35,36,37,38,39,40,41,42,43,44,45,
    46,47,48,5,9,13,17,21,28,49,49,49,50,50,
    50,51,51,51
};
/**********************************************************************
* Function Definitions
**********************************************************************/

int     EVIC_init(void *data)
{
    /*Multi-vectored interrupts*/
    INTCONSET = _INTCON_MVEC_MASK;
    return 0;
}
int     EVIC_channel_state_Set(
        EVIC_CHANNEL channel,
        EVIC_STATE state,
        EVIC_PRIORITY priority,
        EVIC_SUB_PRIORITY sub_priority
)
{
    return 0;
}
bool    EVIC_channel_pending_get(EVIC_CHANNEL channel)
{
    int offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    return (IFS_BASE+offset)->reg & bitOffset;
}
void    EVIC_channel_pending_clear(EVIC_CHANNEL channel)
{
    int offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    (IFS_BASE+offset)->clr = bitOffset;
}
void        EVIC_channel_priority(EVIC_CHANNEL channel, EVIC_PRIORITY priority, EVIC_SUB_PRIORITY subPriority)
{
    uint32_t offset;

    /*Dividir para cuatro el número del canal de interrupción para obtener
         la dirección del registro IPC correspondiente.*/
    channel = vector_number[channel];
    offset = channel >> 2;
    /*Se utiliza los dos primeros bits del número del canal para obtener el
     offset del byte correspondiente dentro del registro IPC*/
    uint32_t byteOffset = channel & 0b11;
    /*Apuntar hacia el registro IPC correspondiente*/
    /*Configurar prioridad y sub-prioridad del byte en el registro IPC*/
    (IPC_BASE + offset)->set = (subPriority << (8 * byteOffset)) |
                               (priority << (8*byteOffset+2));
}
void        EVIC_channel_set(EVIC_CHANNEL channel)
{
    uint32_t offset;
    offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    (IEC_BASE+offset)->set = bitOffset;
}
void        EVIC_channel_clr(EVIC_CHANNEL channel)
{
    uint32_t offset;
    offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    (IEC_BASE+offset)->clr = bitOffset;
}

bool        EVIC_channel_get(EVIC_CHANNEL channel)
{
    uint32_t offset;
    offset = channel >> 5;
    int bitOffset = 1<<(channel & 0x1f);
    return ((IEC_BASE+offset)->reg & bitOffset) == bitOffset;
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