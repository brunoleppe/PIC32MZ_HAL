/**********************************************************************
* Includes
**********************************************************************/
#include "system.h"
#include <xc.h>
#include "pic32mx_registers.h"
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define SYS_PBCLK_BASE                          ((uint8_t*)&PB1DIV)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
void SYS_initialize()
{
    while(!OSCCONbits.SLOCK);

    __builtin_mtc0(16, 0,(__builtin_mfc0(16, 0) | 0x3));

    /* Configure Flash Wait States and Prefetch */
    CHECONbits.PFMWS = 2;
    CHECONbits.PREFEN = 3;

    BMXCONbits.BMXWSDRM = 0;

    DDPCONbits.JTAGEN = 0;
}

void SYS_Unlock(uint32_t flags)
{
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

//    if(flags & SYS_UNLOCK_IO)
//        CFGCONbits.IOLOCK = 0;

}
void SYS_Lock()
{
//    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;
}

void SYS_peripheral_clock_config(uint32_t clockChannel, uint32_t flags)
{
//    if(clockChannel > SYS_PERIPHERAL_CLOCK_8)
//        return;
//    if((flags & SYS_PBCLK_DISABLED) && clockChannel > 1)
//        SYS_PBCLK(clockChannel)->pbxdiv.clr = _PB2DIV_ON_MASK;
//
//    while(!(SYS_PBCLK(clockChannel)->pbxdiv.reg & _PB1DIV_PBDIVRDY_POSITION));
//
//    if((HAL_SYSTEM_CLOCK > 100000000UL) &&
//       ((clockChannel != SYS_PERIPHERAL_CLOCK_4) && (clockChannel != SYS_PERIPHERAL_CLOCK_7)) &&
//       ((flags & 127) & SYS_PBCLK_DIVISOR_1))
//        return;
//
//    SYS_PBCLK(clockChannel)->pbxdiv.set = (flags & 127) - 1;

}

uint32_t    SYS_peripheral_clock_frequency_get(uint32_t clockChannel)
{
    return HAL_SYSTEM_CLOCK / (1 << ((OSCCON & _OSCCON_PBDIV_MASK) >> _OSCCON_PBDIV_POSITION));
}

void SYS_soft_reset(uint32_t val)
{
    SYSKEY = 0x00000000; //write invalid key to force lock
    SYSKEY = 0xAA996655; //write key1 to SYSKEY
    SYSKEY = 0x556699AA; //write key2 to SYSKEY

    RCON = val;
// OSCCON is now unlocked
/* set SWRST bit to arm reset */
    RSWRSTSET = 1;
/* read RSWRST register to trigger reset */
    unsigned int dummy;
    dummy = RSWRST;
    (void)dummy;
/* prevent any unwanted code execution until reset occurs*/
    while(1);
}