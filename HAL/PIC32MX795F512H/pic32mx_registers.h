//
// Created by bleppe on 27/03/23.
//

#ifndef PIC32MX_REGISTERS_H
#define PIC32MX_REGISTERS_H

#include <stdint.h>

typedef struct MemRegister{
    uint32_t reg; ///<Base address of a register
    uint32_t clr; ///<Maps the CLR register
    uint32_t set; ///<Maps the SET register
    uint32_t inv; ///<Maps the INV register
}volatile * const MemRegister;

typedef struct{
    struct MemRegister spicon1;
    struct MemRegister spistat;
    struct MemRegister spibuf;
    struct MemRegister spibrg;
}volatile * const SPI_Descriptor;

typedef struct{
    struct MemRegister tris;
    struct MemRegister port;
    struct MemRegister lat;
    struct MemRegister odc;
}volatile * const GPIO_Descriptor;

typedef struct{
    struct MemRegister cncon;
    struct MemRegister cnen;
    struct MemRegister cnpue;
}volatile * const GPIO_ChangeNoticeDescriptor;

typedef struct{
    struct MemRegister dchcon;
    struct MemRegister dchecon;
    struct MemRegister dchint;
    struct MemRegister dchssa;
    struct MemRegister dchdsa;
    struct MemRegister dchssiz;
    struct MemRegister dchdsiz;
    struct MemRegister dchsptr;
    struct MemRegister dchdptr;
    struct MemRegister dchcsiz;
    struct MemRegister dchcptr;
    struct MemRegister dchdat;
}volatile * const DMA_Descriptor;

typedef struct{
    struct MemRegister txcon;
    struct MemRegister tmrx;
    struct MemRegister prx;
}volatile * const TMR_Descriptor;

typedef struct{
    struct MemRegister ocxcon;
    struct MemRegister ocxr;
    struct MemRegister ocxrs;
}volatile * const OC_Descriptor;

typedef struct{
    struct MemRegister umode;
    struct MemRegister usta;
    struct MemRegister utxreg;
    struct MemRegister urxreg;
    struct MemRegister ubrg;
}volatile * const UART_Descriptor;

#endif //PIC32MX_REGISTERS_H
