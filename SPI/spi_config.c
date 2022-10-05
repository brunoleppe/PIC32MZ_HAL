/**
 * @file spi_config.c
 * @author Bruno Leppe (bleppe@solintece.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**********************************************************************
* Includes
**********************************************************************/
#include "spi_config.h" 

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
/*
typedef struct{
    SPI_CHANNEL channel;
    SPI_MODE mode;
    SPI_MASTER_MODE mode;
    uint32_t baudrate;
}SPI_Table;
 */
static const SPI_Table table[]={
    /*LCD*/
    {SPI_CHANNEL_2, SPI_MODE_3, SPI_MASTER, 20000000, SPI_SAMPLE_MID},
    /*QTOUCH*/
    {SPI_CHANNEL_3, SPI_MODE_3, SPI_MASTER, 1000000 , SPI_SAMPLE_MID},
    /*Ext Flash*/
    {SPI_CHANNEL_4, SPI_MODE_0, SPI_MASTER, 40000000, SPI_SAMPLE_END},
};

static const SPI_Config config = {
    .table = (const SPI_Table*)&table,
    .tableSize = sizeof(table)/sizeof(SPI_Table)
};

/**********************************************************************
* Function Definitions
**********************************************************************/
const SPI_Config* SPI_GetConfig( void ){
    return (const SPI_Config*)&config;
}