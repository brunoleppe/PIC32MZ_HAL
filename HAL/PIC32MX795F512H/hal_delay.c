//
// Created by bruno on 28/01/23.
//

#include <xc.h>
#include "hal_delay.h"

static const uint32_t uSeconds = (HAL_SYSTEM_CLOCK / MICRO_SECONDS) >> 1;
static const uint32_t mSeconds = (HAL_SYSTEM_CLOCK / MILLI_SECONDS) >> 1;

void HAL_delay_ms(uint32_t ms)
{
    uint32_t t_wait = mSeconds * ms;
    uint32_t t_start = _CP0_GET_COUNT();
    t_start=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-t_start)<t_wait);
}
void HAL_delay_us(uint32_t us)
{
    uint32_t t_wait = uSeconds * us;
    uint32_t t_start = _CP0_GET_COUNT();
    t_start=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-t_start)<t_wait);
}
void HAL_delay_cy(uint32_t cy)
{
    uint32_t tStart;
    tStart=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-tStart)<cy);
}