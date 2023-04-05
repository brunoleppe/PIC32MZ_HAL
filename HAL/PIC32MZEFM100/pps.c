//
// Created by bruno on 02/02/23.
//

#include "pps.h"

void PPS_pin_mapping(PPS_Register reg , PPS_AlternateFunction af)
{
    *reg = af;
}