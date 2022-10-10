/**********************************************************************
* Includes
**********************************************************************/

#include <xc.h>
#include "hal.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

struct _MemRegister{
    uint32_t reg; ///<Base address the register
    uint32_t clr; ///<Maps the CLR register
    uint32_t set; ///<Maps the SET register
    uint32_t inv; ///<Maps the INV register
};

/*********************************************************************
* Module Variable Definitions
**********************************************************************/