
/**********************************************************************
* Includes
**********************************************************************/
#include "gpio.h"
#include "pic32mz_registers.h"
#include <xc.h>
#include <sys/attribs.h>

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/


/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/


/**********************************************************************
* Module Typedefs
**********************************************************************/

//
//#ifndef GPIO_Reg
//#define GPIO_Reg    volatile TYPE * const

/**********************************************************************
* Module Variable Definitions
**********************************************************************/

/**
 * @brief Arreglo de interrupciones, depende de la cantidad de interrupciones
 * definidos para la aplicación.
 * 
 */
static GPIO_InterruptCallback callbackArray[NUMBER_OF_INTERRUPTS];

/**
 * @brief Registros de configuración de dirección.
 * 
 */
static MemRegister tris[NUMBER_OF_PORTS]={
    (MemRegister)&TRISA,(MemRegister)&TRISB,(MemRegister)&TRISC,(MemRegister)&TRISD,
    (MemRegister)&TRISE,(MemRegister)&TRISF,(MemRegister)&TRISG
};
/**
 * @brief Registros de lectura de puertos.
 * 
 */
static MemRegister port[NUMBER_OF_PORTS]={
    (MemRegister)&PORTA,(MemRegister)&PORTB,(MemRegister)&PORTC,(MemRegister)&PORTD,
    (MemRegister)&PORTE,(MemRegister)&PORTF,(MemRegister)&PORTG
};
/**
 * @brief Registros de escritura de puertos.
 * 
 */
static MemRegister latch[NUMBER_OF_PORTS]={
    (MemRegister)&LATA,(MemRegister)&LATB,(MemRegister)&LATC,(MemRegister)&LATD,
    (MemRegister)&LATE,(MemRegister)&LATF,(MemRegister)&LATG
};
/**
 * @brief Registros de configuración de modo analógico.
 * 
 */
static MemRegister ansel[NUMBER_OF_PORTS]={
    (MemRegister)&ANSELA,(MemRegister)&ANSELB,(MemRegister)&ANSELC,(MemRegister)&ANSELD,
    (MemRegister)&ANSELE,(MemRegister)&ANSELF,(MemRegister)&ANSELG
};
/**
 * @brief Registros de configuración de pull-ups.
 * 
 */
static MemRegister cnpu[NUMBER_OF_PORTS]={
    (MemRegister)&CNPUA,(MemRegister)&CNPUB,(MemRegister)&CNPUC,(MemRegister)&CNPUD,
    (MemRegister)&CNPUE,(MemRegister)&CNPUF,(MemRegister)&CNPUG
};
/**
 * @brief Registros para la configuración de pull-downs.
 * 
 */
static MemRegister cnpd[NUMBER_OF_PORTS]={
    (MemRegister)&CNPDA,(MemRegister)&CNPDB,(MemRegister)&CNPDC,(MemRegister)&CNPDD,
    (MemRegister)&CNPDE,(MemRegister)&CNPDF,(MemRegister)&CNPDG
};
/**
 * @brief Registros para la configuración de open-drain.
 * 
 */
static MemRegister odc[NUMBER_OF_PORTS]={
    (MemRegister)&ODCA,(MemRegister)&ODCB,(MemRegister)&ODCC,(MemRegister)&ODCD,
    (MemRegister)&ODCE,(MemRegister)&ODCF,(MemRegister)&ODCG
};
/**
 * @brief Registros para la configuración de slew rate.
 * 
 */
static MemRegister srcon0[NUMBER_OF_PORTS]={
    (MemRegister)&SRCON0A,(MemRegister)&SRCON0B,(MemRegister)NULL,(MemRegister)NULL,
    (MemRegister)&SRCON0E,(MemRegister)&SRCON0F,(MemRegister)&SRCON0G
};
static MemRegister srcon1[NUMBER_OF_PORTS]={
    (MemRegister)&SRCON1A,(MemRegister)&SRCON1B,(MemRegister)NULL,(MemRegister)NULL,
    (MemRegister)&SRCON1E,(MemRegister)&SRCON1F,(MemRegister)&SRCON1G
};
/**
 * @brief Registros para el control de interrupciones por puerto.
 * 
 */
static MemRegister cncon[NUMBER_OF_PORTS]={
    (MemRegister)&CNCONA,(MemRegister)&CNCONB,(MemRegister)&CNCONC,(MemRegister)&CNCOND,
    (MemRegister)&CNCONE,(MemRegister)&CNCONF,(MemRegister)&CNCONG
};
/**
 * @brief Registros para la habilitación de interrupciones por pin.
 * 
 */
static MemRegister cnen[NUMBER_OF_PORTS]={
    (MemRegister)&CNENA,(MemRegister)&CNENB,(MemRegister)&CNENC,(MemRegister)&CNEND,
    (MemRegister)&CNENE,(MemRegister)&CNENF,(MemRegister)&CNENG
};
/**
 * Registros de banderas de interrupción por pin.
 */
static MemRegister cnstat[NUMBER_OF_PORTS]={
    (MemRegister)&CNSTATA,(MemRegister)&CNSTATB,(MemRegister)&CNSTATC,(MemRegister)&CNSTATD,
    (MemRegister)&CNSTATE,(MemRegister)&CNSTATF,(MemRegister)&CNSTATG,
};
//static int cn_interrupt_enable[NUMBER_OF_PORTS]={0,0,0,0,0,0,0};

/**********************************************************************
* Function Prototypes
**********************************************************************/

static void _register_config(MemRegister reg, uint32_t val, uint32_t compare, uint32_t bitNum);
static void _interrupt_handler(int portNumber);

/**********************************************************************
* Function Definitions
**********************************************************************/

void GPIO_Init(const GPIO_Config* config)
{
    int i;
    /* Unlock system for PPS configuration */
    
    for(i=0;i<config->tableSize;i++){
        /*Obtener el puerto desde el valor del pin*/
        int portNumber = config->table[i].pin >> 4;
        int bitNum = 1<<(config->table[i].pin&0xf);
        
        /*Configuración de modo analógico-digital*/
        _register_config(ansel[portNumber],config->table[i].direction,A_INPUT,bitNum);
        
        /*Configuración de dirección del pin*/
        _register_config(tris[portNumber],config->table[i].direction,D_INPUT,bitNum);
        
        /*Valor inicial del pin*/
        _register_config(latch[portNumber],config->table[i].state,HIGH,bitNum);
        
    }
    
    /*Remapeo de pines*/
    
    /*Desbloquear sistema para remapeo*/
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;
    
    /*Configurar registros*/
    for(i=0;i<config->tableSize;i++){
        if(config->table[i].mode.function != AF_NONE)
            *(volatile uint32_t*)(0xBF800000+(config->table[i].mode.reg&0xFFFF)) = 
                    config->table[i].mode.function;
    }
    
    /*Bloquear sistema*/
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;
}

void GPIO_PinPullupSet(GPIO_PIN pin, GPIO_PULLUP state)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    _register_config(cnpu[portNumber],state,PULLUP_ENABLE,bitNum);
}

void GPIO_PinPulldownSet(GPIO_PIN pin, GPIO_PULLDOWN state)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    _register_config(cnpd[portNumber],state,PULLDOWN_ENABLE,bitNum);
}

void GPIO_PinIrqSet(GPIO_PIN pin, GPIO_INTERRUPT state)
{
    int portNumber = pin >> 4;
    int bitnum = 1 << ( pin & 0xf );
    _register_config(cnen[portNumber],state,GPIO_IRQ_ENABLE,bitnum);
    
    cncon[portNumber]->set = _CNCONA_ON_MASK;
    /*Leer el puerto, según recomendaciones de microchip*/
    port[portNumber]->reg;
    
//    if(!(cncon[portNumber]->reg & bitnum))
//        cncon[portNumber]->set = bitnum;
}

GPIO_STATE GPIO_PinRead(GPIO_PIN pin)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    TYPE status = port[portNumber]->reg;
    if(status & bitNum)
        return HIGH;
    else
        return LOW;
}

void GPIO_PinWrite(GPIO_PIN pin, GPIO_STATE state){
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    if(state == HIGH)
        latch[portNumber]->set = bitNum;
    else
        latch[portNumber]->clr = bitNum;
}

void GPIO_PinToggle(GPIO_PIN pin)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    latch[portNumber]->inv = bitNum;
}

void GPIO_PinDirectionSet(GPIO_PIN pin, GPIO_DIRECTION direction)
{
    int portNumber = pin >> 4;
    int bitNum = 1 << ( pin & 0xf );
    if(direction == D_INPUT)
        tris[portNumber]->set = bitNum;
    else
        tris[portNumber]->clr = bitNum;
}

void GPIO_RegisterWrite(uintptr_t address, TYPE val)
{
    volatile TYPE *reg = (volatile TYPE*)address;
    *reg = val;
}

TYPE GPIO_RegisterRead(uintptr_t address)
{
    volatile TYPE *reg = (volatile TYPE*)address;
    return *reg;
}

void GPIO_CallbackRegister(
        GPIO_PIN pin, 
        GPIO_CallbackFunction callback, 
        uintptr_t context
)
{
    static int counter = 0;
    if(counter >= NUMBER_OF_INTERRUPTS)
        return;
    
    callbackArray[counter].callback = callback;
    callbackArray[counter].context = context;
    callbackArray[counter].pin = pin;
    
    counter++;   
}


void _register_config(MemRegister reg, uint32_t val, uint32_t compare, uint32_t bitNum){
    if(reg == NULL)
        return;
    if(val == compare)
        reg->set = bitNum;
    else
        reg->clr = bitNum;
}

void _interrupt_handler(int portNumber)
{
    TYPE status = cnstat[portNumber]->reg;
    status &= cnen[portNumber]->reg;
    port[portNumber]->reg;
    
    int i;
    for(i=0;i<NUMBER_OF_INTERRUPTS;i++){
        int portNum = callbackArray[i].pin >> 4;
        int bitNum = 1 << (callbackArray[i].pin & 0xf);
        if(portNum != portNumber)
            continue;
        if((status & bitNum) && (callbackArray[i].callback != NULL)){
            callbackArray[i].callback(callbackArray[i].pin,callbackArray[i].context);
        }
    }
}

/**********************************************************************
* Interrupt Handlers
**********************************************************************/
void CHANGE_NOTICE_E_InterruptHandler(void);

void __ISR(_CHANGE_NOTICE_E_VECTOR, ipl1SRS) CHANGE_NOTICE_E_Handler (void)
{
    CHANGE_NOTICE_E_InterruptHandler();
}

void CHANGE_NOTICE_E_InterruptHandler(void)
{
    _interrupt_handler(GPIO_PORTE);
    IFS3CLR = _IFS3_CNEIF_MASK;
}