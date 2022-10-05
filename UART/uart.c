/**
 * @file uart.c
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**********************************************************************
* Includes
**********************************************************************/

#include <xc.h>
#include "uart.h"
#include "pic32mz_registers.h"
#include "definitions.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
MemRegister ucon[NUMBER_OF_UART_CHANNELS]={
    (MemRegister)&U1MODE,(MemRegister)&U2MODE,(MemRegister)&U3MODE,
    (MemRegister)&U4MODE,(MemRegister)&U5MODE,(MemRegister)&U6MODE,
};
MemRegister ustat[NUMBER_OF_UART_CHANNELS]={
    (MemRegister)&U1STA,(MemRegister)&U2STA,(MemRegister)&U3STA,
    (MemRegister)&U4STA,(MemRegister)&U5STA,(MemRegister)&U6STA,
};
MemRegister utxreg[NUMBER_OF_UART_CHANNELS]={
    (MemRegister)&U1TXREG,(MemRegister)&U2TXREG,(MemRegister)&U3TXREG,
    (MemRegister)&U4TXREG,(MemRegister)&U5TXREG,(MemRegister)&U6TXREG,
};
MemRegister urxreg[NUMBER_OF_UART_CHANNELS]={
    (MemRegister)&U1RXREG,(MemRegister)&U2RXREG,(MemRegister)&U3RXREG,
    (MemRegister)&U4RXREG,(MemRegister)&U5RXREG,(MemRegister)&U6RXREG,
};
MemRegister ubrg[NUMBER_OF_UART_CHANNELS]={
    (MemRegister)&U1BRG,(MemRegister)&U2BRG,(MemRegister)&U3BRG,
    (MemRegister)&U4BRG,(MemRegister)&U1BRG,(MemRegister)&U6BRG,
};
/**********************************************************************
* Function Definitions
**********************************************************************/
static uint32_t _brg16_get(uint32_t baudrate){
    uint32_t clock;
    uint32_t brg;
    
    clock = CPU_CLOCK_FREQUENCY/((PB1DIV&_PB1DIV_PBDIV_MASK)+1);
    brg = clock/(16*baudrate) - 1; 
    return brg;
}

int UART_Init(const UART_Config *config)
{
    int i;
    for(i=0;i<config->tableSize;i++){
        int channel = config->table[i].channel;
        if(channel >= UART_CHANNEL_MAX)
            return -UART_BAD_CHANNEL;
        
        /*Limpiar el registro de control*/
        ucon[channel]->reg = 0;
        
        /*Habilitar RX y TX*/
        ustat[channel]->set = _U1STA_UTXEN_MASK | _U1STA_URXEN_MASK;
        
        /*Data bits & Parity*/
        if(config->table[i].databits >= DATA_BITS_MAX)
            return -UART_BAD_DATABITS;
        
        uint32_t databits = 0;
        if(config->table[i].databits == DATA_BITS_9){
            databits = 0b11;
        }
        else{
            switch(config->table[i].parity){
                case PARITY_NONE: databits = 0;break;
                case PARITY_EVEN: databits = 1;break;
                case PARITY_ODD : databits = 2;break;
                default: return -UART_BAD_PARITY;
            }
        }
        ucon[channel]->set = databits << _U1MODE_PDSEL0_POSITION;
       
        /*Stop bits*/
        if(config->table[i].stopbits >= STOP_BITS_MAX)
            return -UART_BAD_STOPBITS;
        
        if(config->table[i].stopbits == STOP_BITS_2){
            ucon[channel]->set = 1;
        }
        
        /*Baudrate*/
        uint32_t brg;
        /*NO usar BRGH = 1 porque no funciona en pic32mz*/
        /*Forzar BRGH = 0, brg = (Fpb)/(16*baudrate) - 1*/
        brg = _brg16_get(config->table[i].baudrate);
        if(brg > 0xFFFF)
            return -UART_BAD_BAUDRATE;
        ubrg[channel]->reg = brg;
        
        /*Encender UART*/
        ucon[channel]->set = _U1MODE_ON_MASK;
          
    }
    return 0;
}

int UART_WriteByte(UART_CHANNEL channel, uint8_t data)
{
    if(channel >= UART_CHANNEL_MAX)
        return -UART_BAD_CHANNEL;
    utxreg[channel]->reg = data;
    return 0;
}

int UART_Write(UART_CHANNEL channel, void *data, size_t size)
{
    if(channel >= UART_CHANNEL_MAX)
        return -UART_BAD_CHANNEL;
    
    uint8_t *txBuffer = (uint8_t*)data;
    
    while((!(U3STA & _U3STA_UTXBF_MASK) && size--)){
        utxreg[channel]->reg = *txBuffer++;
    }
    return 0;
}