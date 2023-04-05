
/**********************************************************************
* Includes
**********************************************************************/
#include "timer.h"
#include "pic32mz_registers.h"
#include "evic.h"
#include <xc.h>
#include "system.h"
/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define TMR_BASE                            _TMR2_BASE_ADDRESS
#define TMR_NUMBER_OF_CHANNELS              (8)

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/
#define TMR_DESCRIPTOR(channel)             ((TMR_Descriptor)(((uint8_t*)(TMR_BASE)) + 0x200*(channel)))
/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static const uint32_t prescalerTable[] = {
    1,2,4,8,16,32,64,256
};
static const EVIC_CHANNEL timerEvicChannels[]={
        EVIC_CHANNEL_TIMER_2,
        EVIC_CHANNEL_TIMER_3,
        EVIC_CHANNEL_TIMER_4,
        EVIC_CHANNEL_TIMER_5,
        EVIC_CHANNEL_TIMER_6,
        EVIC_CHANNEL_TIMER_7,
        EVIC_CHANNEL_TIMER_8,
        EVIC_CHANNEL_TIMER_9,
};
/**********************************************************************
* Function Prototypes
**********************************************************************/
static uint16_t TMR_period_value_get(uint32_t frequency, uint32_t prescaler);
/**********************************************************************
* Function Definitions
**********************************************************************/
void        TMR_initialize(uint32_t channel, uint32_t flags, uint32_t period)
{
    TMR_DESCRIPTOR(channel)->txcon.reg = 0;
    TMR_DESCRIPTOR(channel)->txcon.set = (TMR_TCKPS_MASK & flags) << _T1CON_TCKPS0_POSITION;
    if(flags & TMR_GATED)
        TMR_DESCRIPTOR(channel)->txcon.set = _T2CON_TGATE_MASK;
    if(flags & TMR_MODE_32)
        TMR_DESCRIPTOR(channel)->txcon.set = _T2CON_T32_MASK;

    TMR_DESCRIPTOR(channel)->tmrx.reg = 0;
    TMR_DESCRIPTOR(channel)->prx.reg = period;
    //    TMR_DESCRIPTOR(channel)->prx.reg = TMR_period_value_get(frequency, prescalerTable[TMR_TCKPS_MASK & flags]);
}
void        TMR_start(uint32_t channel)
{
    TMR_DESCRIPTOR(channel)->tmrx.reg = 0;
    TMR_DESCRIPTOR(channel)->txcon.set = _T2CON_ON_MASK;
}
void        TMR_stop(uint32_t channel)
{
    TMR_DESCRIPTOR(channel)->txcon.clr = _T2CON_ON_MASK;
}
uint32_t    TMR_count_get(uint32_t channel)
{
    return TMR_DESCRIPTOR(channel)->tmrx.reg;
}
uint32_t    TMR_frequency_get(uint32_t channel)
{
    uint32_t pre = prescalerTable[(TMR_DESCRIPTOR(channel)->txcon.reg & _T2CON_TCKPS_MASK) >> _T2CON_TCKPS0_POSITION];
    return (SYS_peripheral_clock_frequency_get(SYS_PERIPHERAL_CLOCK_3))/((TMR_DESCRIPTOR(channel)->prx.reg + 1)*pre);
}

void        TMR_interrupt_handler(uint32_t channel)
{
    EVIC_channel_pending_clear(timerEvicChannels[channel]);
    TMR_channel_interrupt_callback(channel);
}
HAL_WEAK_FUNCTION void TMR_channel_interrupt_callback     (uint32_t channel)
{
    (void)channel;
}
void        TMR_period_set(uint32_t channel, uint16_t period)
{
    TMR_DESCRIPTOR(channel)->prx.reg = period;
}
void        TMR_prescaler_set(uint32_t channel, uint16_t prescaler)
{
    TMR_DESCRIPTOR(channel)->txcon.set = prescaler << _T2CON_TCKPS0_POSITION;
}
void    TMR_frequency_set(uint32_t channel, uint32_t frequency)
{
    TMR_DESCRIPTOR(channel)->prx.reg = TMR_period_value_get(
            frequency,
            prescalerTable[
                    (TMR_DESCRIPTOR(channel)->txcon.reg & _T2CON_TCKPS_MASK) >> _T2CON_TCKPS0_POSITION]);
}

static uint16_t TMR_period_value_get(uint32_t frequency, uint32_t prescaler)
{
    uint16_t period = (SYS_peripheral_clock_frequency_get(SYS_PERIPHERAL_CLOCK_3))/(prescaler * frequency) - 1;
    return period;
}

