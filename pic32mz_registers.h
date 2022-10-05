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

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * PIC32MZ Register definition.
 * Struct used for mapping the base address of a register to obtain the following SET, CLR and INV registers.
 * Refer to PIC32MZ family datasheet.
 */
typedef struct{
    uint32_t reg; ///<Base address of a register
    uint32_t clr; ///<Maps the CLR register
    uint32_t set; ///<Maps the SET register
    uint32_t inv; ///<Maps the INV register
}volatile * const MemRegister;



#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MZ_REGISTERS_H */

