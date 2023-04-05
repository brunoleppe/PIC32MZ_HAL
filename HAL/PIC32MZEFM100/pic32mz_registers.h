/**
 * @file pic32mz_registers.h
 * @author Bruno Leppe
 * @brief Struct definition for PIC32MZ family registers. Every register is associated with three registers: SET, CLR, INV.
 * Setting any bit of these registers set, clear or inverse the selected bit of the parent register. Lets take PORTA = 0b00001111.
 * Writing 0x0F to PORTACLR register gives PORTA = 0b00000000. Writing 0x10 to PORTASET gives PORTA = 0b00010000. Writing 0x11 to
 * PORTAINV gives PORTA = 0b00000001.
 * @date 30 de septiembre de 2022, 16:30
 */

#ifndef PIC32MZ_REGISTERS_H
#define	PIC32MZ_REGISTERS_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * PIC32MZ Register definition.
 * Struct used for mapping the base address of a register to obtain the following SET, CLR and INV registers.
 * Refer to PIC32MZ family datasheet.
 */
typedef struct MemRegister{
    uint32_t reg; ///<Base address of a register
    uint32_t clr; ///<Maps the CLR register
    uint32_t set; ///<Maps the SET register
    uint32_t inv; ///<Maps the INV register
}volatile * const MemRegister;

typedef struct{
    struct MemRegister ansel;
    struct MemRegister tris;
    struct MemRegister port;
    struct MemRegister lat;
    struct MemRegister odc;
    struct MemRegister cnpu;
    struct MemRegister cnpd;
    struct MemRegister cncon;
    struct MemRegister cnen;
    struct MemRegister cnstat;
    struct MemRegister cnne;
    struct MemRegister cnf;
    struct MemRegister srcon0;
    struct MemRegister srcon1;
}volatile * const GPIO_Descriptor;

typedef struct{
    struct MemRegister spicon1;
    struct MemRegister spistat;
    struct MemRegister spibuf;
    struct MemRegister spibrg;
    struct MemRegister spicon2;
}volatile * const SPI_Descriptor;

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
    struct MemRegister pbxdiv;
}volatile * const PBCLK_Descriptor;

typedef struct{
    struct MemRegister umode;
    struct MemRegister usta;
    struct MemRegister utxreg;
    struct MemRegister urxreg;
    struct MemRegister ubrg;
}volatile * const UART_Descriptor;
#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MZ_REGISTERS_H */
