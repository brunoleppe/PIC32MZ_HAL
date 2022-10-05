/** 
 * @file pic32mz_registers.h
 * @author Bruno Leppe
 * @brief
 * @date 30 de septiembre de 2022, 16:30
 */

#ifndef PIC32MZ_REGISTERS_H
#define	PIC32MZ_REGISTERS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
    uint32_t reg;
    uint32_t clr;
    uint32_t set;
    uint32_t inv;
}volatile * const MemRegister;



#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MZ_REGISTERS_H */

