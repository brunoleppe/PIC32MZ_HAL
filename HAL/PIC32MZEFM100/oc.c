/**********************************************************************
* Includes
**********************************************************************/
#include "oc.h"
#include "pic32mz_registers.h"
#include "evic.h"
#include <xc.h>
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define OC_BASE                             _OCMP1_BASE_ADDRESS
#define OC_NUMBER_OF_CHANNELS               (9)
#define OC_MODE_MASK                        (7)
/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define OC_DESCRIPTOR(channel)              ((OC_Descriptor)(((uint8_t*)(OC_BASE)) + 0x200*(channel)))
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
void        OC_initialize   (uint32_t ocChannel, uint32_t flags, uint32_t compareValue)
{
    OC_DESCRIPTOR(ocChannel)->ocxcon.reg = 0;
    OC_DESCRIPTOR(ocChannel)->ocxcon.set = (flags & OC_MODE_MASK) << _OC1CON_OCM0_POSITION;
    if(flags & OC_MODE_32)
        OC_DESCRIPTOR(ocChannel)->ocxcon.set = _OC1CON_OC32_MASK;
    if(flags & OC_MODE_USE_TMR3)
        OC_DESCRIPTOR(ocChannel)->ocxcon.set = _OC1CON_OCTSEL_MASK;

    OC_DESCRIPTOR(ocChannel)->ocxr.reg  = compareValue;
    OC_DESCRIPTOR(ocChannel)->ocxrs.reg = compareValue;

}
void        OC_enable       (uint32_t ocChannel)
{
    OC_DESCRIPTOR(ocChannel)->ocxcon.set = _OC1CON_ON_MASK;
}
void        OC_disable      (uint32_t ocChannel)
{
    OC_DESCRIPTOR(ocChannel)->ocxcon.clr = _OC1CON_ON_MASK;
}
void        OC_compare_set  (uint32_t ocChannel, uint32_t compareValue)
{
    OC_DESCRIPTOR(ocChannel)->ocxrs.reg = compareValue;
}
uint32_t    OC_compare_get  (uint32_t ocChannel)
{
    return OC_DESCRIPTOR(ocChannel)->ocxrs.reg;
}
