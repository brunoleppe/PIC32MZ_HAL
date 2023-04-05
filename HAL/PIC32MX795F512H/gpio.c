
/**********************************************************************
* Includes
**********************************************************************/
#include <xc.h>
#include "gpio.h"
#include "pic32mx_registers.h"
#include "evic.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

#define GPIO_BASE_PORT                  (GPIO_Descriptor)&TRISA
#define GPIO_PORT(port)                 ((GPIO_Descriptor)(((uint8_t*)&TRISB)+0x40*((port)-1)))
#define GPIO_PORT_IRQ_CHANNEL(port)     (EVIC_CHANNEL_CHANGE_NOTICE)
#define GPIO_PIN(val)                   (val & GPIO_PIN_MASK)
#define GPIO_MAX_PINS                   (112)
#define GPIO_CN_DESCRIPTOR(port)        ((GPIO_ChangeNoticeDescriptor)&CNCON)
#define GPIO_MAX_CN_PINS                (19)
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/


/**********************************************************************
* Module Typedefs
**********************************************************************/

/**********************************************************************
* Module Variable Definitions
**********************************************************************/
static const uint32_t cnen_map[GPIO_MAX_CN_PINS] = {
GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_14), GPIO_PIN_MAP(GPIO_PORT_C, GPIO_PIN_13),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_0),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_1),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_2),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_3),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_4),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_5),
GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_6),
GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_7),
GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_8),
GPIO_PIN_MAP(GPIO_PORT_G, GPIO_PIN_9),
GPIO_PIN_MAP(GPIO_PORT_B, GPIO_PIN_15),
GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_4),
GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_5),
GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_6),
GPIO_PIN_MAP(GPIO_PORT_D, GPIO_PIN_7),
GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_4),
GPIO_PIN_MAP(GPIO_PORT_F, GPIO_PIN_5),
};
/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
void    GPIO_pin_initialize             (GPIO_PinMap pin, int flags)
{
    if(flags & GPIO_OUTPUT){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.clr = GPIO_PIN(pin);
        if(flags & GPIO_OPENDRAIN)
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.set = GPIO_PIN(pin);
        return;
    }

    if(flags & GPIO_PULLUP) {
        for (int i=0;i<GPIO_MAX_CN_PINS;i++){
            if(cnen_map[i] == pin){
                GPIO_CN_DESCRIPTOR(0)->cnpue.set = 1<<i;
                break;
            }
        }
    }
    if(flags & GPIO_IRQ) {
        for (int i=0;i<GPIO_MAX_CN_PINS;i++){
            if(cnen_map[i] == pin){
                GPIO_CN_DESCRIPTOR(0)->cnen.set = 1<<i;
                break;
            }
        }
        GPIO_CN_DESCRIPTOR(0)->cncon.set = _CNCON_ON_MASK;
    }
}
void    GPIO_pin_deinitialize           (GPIO_PinMap pin)
{

    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.set = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.clr = GPIO_PIN(pin);
    for (int i=0;i<GPIO_MAX_CN_PINS;i++){
        if(cnen_map[i] == pin){
            GPIO_CN_DESCRIPTOR(0)->cnpue.clr = 1<<i;
            break;
        }
    }
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.clr = GPIO_PIN(pin);
    for (int i=0;i<GPIO_MAX_CN_PINS;i++){
        if(cnen_map[i] == pin){
            GPIO_CN_DESCRIPTOR(0)->cnen.clr = 1<<i;
            break;
        }
    }
    if((GPIO_CN_DESCRIPTOR(0)->cnen.reg ) == 0)
        GPIO_CN_DESCRIPTOR(0)->cncon.clr = _CNCON_ON_MASK;
}
bool    GPIO_pin_read              (GPIO_PinMap pin)
{

    return (GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.reg & GPIO_PIN(pin)) == GPIO_PIN(pin);
}
void    GPIO_pin_write             (GPIO_PinMap pin, bool value)
{

    if(value){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.set = GPIO_PIN(pin);
    }
    else{
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = GPIO_PIN(pin);
    }
}
void    GPIO_pin_toggle            (GPIO_PinMap pin)
{
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.inv = GPIO_PIN(pin);
}

void GPIO_port_write(GPIO_Port port, uint32_t value, uint32_t mask)
{
    GPIO_PORT(port)->lat.reg = value & mask;
}
uint32_t    GPIO_port_read                  (GPIO_Port port, uint32_t mask)
{
    return GPIO_PORT(port)->port.reg & mask;
}
void    GPIO_port_toggle                (GPIO_Port port, uint32_t mask)
{
    GPIO_PORT(port)->lat.inv = mask;
}

void    GPIO_pin_interrupt_set     (GPIO_PinMap pin, bool state)
{
    for (int i=0;i<GPIO_MAX_CN_PINS;i++){
        if(cnen_map[i] == pin){
            if(state)
                GPIO_CN_DESCRIPTOR(0)->cnpue.set = 1<<i;
            else
                GPIO_CN_DESCRIPTOR(0)->cnpue.clr = 1<<i;
            break;
        }
    }
}

HAL_WEAK_FUNCTION void    GPIO_pin_interrupt_callback     (GPIO_PinMap pin)
{
    (void)pin;
}

void GPIO_interrupt_handler(GPIO_Port port)
{
    EVIC_channel_pending_clear(GPIO_PORT_IRQ_CHANNEL(port));
    GPIO_pin_interrupt_callback( 0 );
}
