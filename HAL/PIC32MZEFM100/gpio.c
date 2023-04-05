
/**********************************************************************
* Includes
**********************************************************************/
#include <xc.h>
#include "gpio.h"
#include "pic32mz_registers.h"
#include "evic.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define GPIO_BASE_PORT                  (GPIO_Descriptor)&ANSELA
#define GPIO_PORT(port)                 ((GPIO_Descriptor)(((uint8_t*)&ANSELA)+0x100*(port)))
#define GPIO_PORT_IRQ_CHANNEL(port)     (EVIC_CHANNEL_CHANGE_NOTICE_A+(port))
#define GPIO_PIN(val)                   (val & GPIO_PIN_MASK)
#define GPIO_MAX_PINS                   (112)
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/


/**********************************************************************
* Module Typedefs
**********************************************************************/

/**********************************************************************
* Module Variable Definitions
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
void    GPIO_pin_initialize             (GPIO_PinMap pin, int flags)
{

    if(flags & GPIO_ANALOG) {
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.set = GPIO_PIN(pin);
        return;
    }

    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.clr = GPIO_PIN(pin);
    if(flags & GPIO_OUTPUT){
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.clr = GPIO_PIN(pin);
        if(flags & GPIO_OPENDRAIN)
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.set = GPIO_PIN(pin);
        if(flags & GPIO_SLOWEST) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.set = GPIO_PIN(pin);
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.set = GPIO_PIN(pin);
        }
        else if(flags & GPIO_SLOW) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.clr = GPIO_PIN(pin);
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.set = GPIO_PIN(pin);
        }
        else if(flags & GPIO_FAST) {
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.set = GPIO_PIN(pin);
            GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.clr = GPIO_PIN(pin);
        }
        return;
    }

    if(flags & GPIO_PULLUP)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpu.set = GPIO_PIN(pin);
    else if(flags & GPIO_PULLDOWN)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpd.set = GPIO_PIN(pin);

    if(flags & GPIO_IRQ) {
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.set = GPIO_PIN(pin);
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cncon.set = _CNCONA_ON_MASK;
    }
}
void    GPIO_pin_deinitialize           (GPIO_PinMap pin)
{

    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->ansel.set = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->tris.set = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->lat.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->port.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon1.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->srcon0.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpd.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnpu.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->odc.clr = GPIO_PIN(pin);
    GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.clr = GPIO_PIN(pin);
    if((GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.reg & GPIO_PIN(pin)) == 0)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cncon.clr = _CNCONA_ON_MASK;
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
    if(state)
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.set = GPIO_PIN(pin);
    else
        GPIO_PORT(pin>>GPIO_PORT_SHIFT)->cnen.clr = GPIO_PIN(pin);
}

HAL_WEAK_FUNCTION void    GPIO_pin_interrupt_callback     (GPIO_PinMap pin)
{
    (void)pin;
}

void GPIO_interrupt_handler(GPIO_Port port)
{
    uint32_t status;

    status  = GPIO_PORT(port)->cnstat.reg;
    status &= GPIO_PORT(port)->cnen.reg;

    GPIO_PORT(port)->port.reg;

    EVIC_channel_pending_clear(GPIO_PORT_IRQ_CHANNEL(port));
    GPIO_pin_interrupt_callback(status | (port << GPIO_PORT_SHIFT));
}
