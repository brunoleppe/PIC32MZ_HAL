#ifndef PPS_H
#define PPS_H
/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define PPS_INPUT_REG_INT3              (volatile uint32_t*)(&INT3R)
#define PPS_INPUT_REG_T2CK              (volatile uint32_t*)(&T2CKR)
#define PPS_INPUT_REG_T6CK              (volatile uint32_t*)(&T6CKR)
#define PPS_INPUT_REG_IC3               (volatile uint32_t*)(&IC3R)
#define PPS_INPUT_REG_IC7               (volatile uint32_t*)(&IC7R)
#define PPS_INPUT_REG_U1RX              (volatile uint32_t*)(&U1RXR)
#define PPS_INPUT_REG_U2CTS             (volatile uint32_t*)(&U2CTSR)
#define PPS_INPUT_REG_U5RX              (volatile uint32_t*)(&U5RXR)
#define PPS_INPUT_REG_U6CTS             (volatile uint32_t*)(&U6CTSR)
#define PPS_INPUT_REG_SDI1              (volatile uint32_t*)(&SDI1R)
#define PPS_INPUT_REG_SDI3              (volatile uint32_t*)(&SDI3R)
#define PPS_INPUT_REG_SDI5              (volatile uint32_t*)(&SDI5R)
#define PPS_INPUT_REG_SS6               (volatile uint32_t*)(&SS6R)
#define PPS_INPUT_REG_REFCLKI1          (volatile uint32_t*)(&REFCLKI1R)
#define PPS_INPUT_REG_INT4              (volatile uint32_t*)(&INT4R)
#define PPS_INPUT_REG_T5CK              (volatile uint32_t*)(&T5CKR)
#define PPS_INPUT_REG_T7CK              (volatile uint32_t*)(&T7CKR)
#define PPS_INPUT_REG_IC4               (volatile uint32_t*)(&IC4R)
#define PPS_INPUT_REG_IC8               (volatile uint32_t*)(&IC8R)
#define PPS_INPUT_REG_U3RX              (volatile uint32_t*)(&U3RXR)
#define PPS_INPUT_REG_U4CTS             (volatile uint32_t*)(&U4CTSR)
#define PPS_INPUT_REG_SDI2              (volatile uint32_t*)(&SDI2R)
#define PPS_INPUT_REG_SDI4              (volatile uint32_t*)(&SDI4R)
#define PPS_INPUT_REG_C1RX              (volatile uint32_t*)(&C1RXR)
#define PPS_INPUT_REG_REFCLKI4          (volatile uint32_t*)(&REFCLKI4R)
#define PPS_INPUT_REG_INT2              (volatile uint32_t*)(&INT2R)
#define PPS_INPUT_REG_T3CK              (volatile uint32_t*)(&T3CKR)
#define PPS_INPUT_REG_T8CK              (volatile uint32_t*)(&T8CKR)
#define PPS_INPUT_REG_IC2               (volatile uint32_t*)(&IC2R)
#define PPS_INPUT_REG_IC5               (volatile uint32_t*)(&IC5R)
#define PPS_INPUT_REG_IC9               (volatile uint32_t*)(&IC9R)
#define PPS_INPUT_REG_U1CTS             (volatile uint32_t*)(&U1CTSR)
#define PPS_INPUT_REG_U2RX              (volatile uint32_t*)(&U2RXR)
#define PPS_INPUT_REG_U5CTS             (volatile uint32_t*)(&U5CTSR)
#define PPS_INPUT_REG_SS1               (volatile uint32_t*)(&SS1R)
#define PPS_INPUT_REG_SS3               (volatile uint32_t*)(&SS3R)
#define PPS_INPUT_REG_SS4               (volatile uint32_t*)(&SS4R)
#define PPS_INPUT_REG_SS5               (volatile uint32_t*)(&SS5R)
#define PPS_INPUT_REG_C2RX              (volatile uint32_t*)(&C2RXR)
#define PPS_INPUT_REG_INT1              (volatile uint32_t*)(&INT1R)
#define PPS_INPUT_REG_T4CK              (volatile uint32_t*)(&T4CKR)
#define PPS_INPUT_REG_T9CK              (volatile uint32_t*)(&T9CKR)
#define PPS_INPUT_REG_IC1               (volatile uint32_t*)(&IC1R)
#define PPS_INPUT_REG_IC6               (volatile uint32_t*)(&IC6R)
#define PPS_INPUT_REG_U3CTS             (volatile uint32_t*)(&U3CTSR)
#define PPS_INPUT_REG_U4RX              (volatile uint32_t*)(&U4R)
#define PPS_INPUT_REG_U6RX              (volatile uint32_t*)(&U6R)
#define PPS_INPUT_REG_SS2               (volatile uint32_t*)(&SS2R)
#define PPS_INPUT_REG_SDI6              (volatile uint32_t*)(&SDI6R)
#define PPS_INPUT_REG_OCFA              (volatile uint32_t*)(&OCFAR)
#define PPS_INPUT_REG_REFCLKI3          (volatile uint32_t*)(&REFCLKI3R)

#define PPS_OUTPUT_REG_RPD2             (volatile uint32_t*)(&RPD2R)
#define PPS_OUTPUT_REG_RPG8             (volatile uint32_t*)(&RPG8R)
#define PPS_OUTPUT_REG_RPF4             (volatile uint32_t*)(&RPF4R)
#define PPS_OUTPUT_REG_RPD10            (volatile uint32_t*)(&RPD10R)
#define PPS_OUTPUT_REG_RPF1             (volatile uint32_t*)(&RPF1R)
#define PPS_OUTPUT_REG_RPB9             (volatile uint32_t*)(&RPB9R)
#define PPS_OUTPUT_REG_RPB10            (volatile uint32_t*)(&RPB10R)
#define PPS_OUTPUT_REG_RPC14            (volatile uint32_t*)(&RPC14R)
#define PPS_OUTPUT_REG_RPB5             (volatile uint32_t*)(&RPB5R)
#define PPS_OUTPUT_REG_RPC1             (volatile uint32_t*)(&RPC1R)
#define PPS_OUTPUT_REG_RPD14            (volatile uint32_t*)(&RPD14R)
#define PPS_OUTPUT_REG_RPG1             (volatile uint32_t*)(&RPG1R)
#define PPS_OUTPUT_REG_RPA14            (volatile uint32_t*)(&RPA14R)
#define PPS_OUTPUT_REG_RPD6             (volatile uint32_t*)(&RPD6R)
#define PPS_OUTPUT_REG_RPD3             (volatile uint32_t*)(&RPD3R)
#define PPS_OUTPUT_REG_RPG7             (volatile uint32_t*)(&RPG7R)
#define PPS_OUTPUT_REG_RPF5             (volatile uint32_t*)(&RPF5R)
#define PPS_OUTPUT_REG_RPD11            (volatile uint32_t*)(&RPD11R)
#define PPS_OUTPUT_REG_RPF0             (volatile uint32_t*)(&RPF0R)
#define PPS_OUTPUT_REG_RPB1             (volatile uint32_t*)(&RPB1R)
#define PPS_OUTPUT_REG_RPE5             (volatile uint32_t*)(&RPE5R)
#define PPS_OUTPUT_REG_RPC13            (volatile uint32_t*)(&RPC13R)
#define PPS_OUTPUT_REG_RPB3             (volatile uint32_t*)(&RPB3R)
#define PPS_OUTPUT_REG_RPC4             (volatile uint32_t*)(&RPC4R)
#define PPS_OUTPUT_REG_RPD15            (volatile uint32_t*)(&RPD15R)
#define PPS_OUTPUT_REG_RPG0             (volatile uint32_t*)(&RPG0R)
#define PPS_OUTPUT_REG_RPA15            (volatile uint32_t*)(&RPA15R)
#define PPS_OUTPUT_REG_RPD7             (volatile uint32_t*)(&RPD7R)
#define PPS_OUTPUT_REG_RPD9             (volatile uint32_t*)(&RPD9R)
#define PPS_OUTPUT_REG_RPG6             (volatile uint32_t*)(&RPG6R)
#define PPS_OUTPUT_REG_RPB8             (volatile uint32_t*)(&RPB8R)
#define PPS_OUTPUT_REG_RPb15            (volatile uint32_t*)(&RPb15R)
#define PPS_OUTPUT_REG_RPD4             (volatile uint32_t*)(&RPD4R)
#define PPS_OUTPUT_REG_RPB0             (volatile uint32_t*)(&RPB0R)
#define PPS_OUTPUT_REG_RPE3             (volatile uint32_t*)(&RPE3R)
#define PPS_OUTPUT_REG_RPB7             (volatile uint32_t*)(&RPB7R)
#define PPS_OUTPUT_REG_RPF12            (volatile uint32_t*)(&RPF12R)
#define PPS_OUTPUT_REG_RPD12            (volatile uint32_t*)(&RPD12R)
#define PPS_OUTPUT_REG_RPF8             (volatile uint32_t*)(&RPF8R)
#define PPS_OUTPUT_REG_RPC3             (volatile uint32_t*)(&RPC3R)
#define PPS_OUTPUT_REG_RPE9             (volatile uint32_t*)(&RPE9R)
#define PPS_OUTPUT_REG_RPD1             (volatile uint32_t*)(&RPD1R)
#define PPS_OUTPUT_REG_RPG9             (volatile uint32_t*)(&RPG9R)
#define PPS_OUTPUT_REG_RPB14            (volatile uint32_t*)(&RPB14R)
#define PPS_OUTPUT_REG_RPD0             (volatile uint32_t*)(&RPD0R)
#define PPS_OUTPUT_REG_RPB6             (volatile uint32_t*)(&RPB6R)
#define PPS_OUTPUT_REG_RPD5             (volatile uint32_t*)(&RPD5R)
#define PPS_OUTPUT_REG_RPB2             (volatile uint32_t*)(&RPB2R)
#define PPS_OUTPUT_REG_RPF3             (volatile uint32_t*)(&RPF3R)
#define PPS_OUTPUT_REG_RPF13            (volatile uint32_t*)(&RPF13R)
#define PPS_OUTPUT_REG_RPC2             (volatile uint32_t*)(&RPC2R)
#define PPS_OUTPUT_REG_RPE8             (volatile uint32_t*)(&RPE8R)
#define PPS_OUTPUT_REG_RPF2             (volatile uint32_t*)(&RPF2R)

/**********************************************************************
* Typedefs
**********************************************************************/
typedef volatile uint32_t * PPS_Register;
typedef uint32_t PPS_AlternateFunction;
/*INPUT*/
enum PPS_INT3{
    PPS_INT3_RPD2 	 = 0,
    PPS_INT3_RPG8 	 = 1,
    PPS_INT3_RPF4 	 = 2,
    PPS_INT3_RPD10 	 = 3,
    PPS_INT3_RPF1 	 = 4,
    PPS_INT3_RPB9 	 = 5,
    PPS_INT3_RPB10 	 = 6,
    PPS_INT3_RPC14 	 = 7,
    PPS_INT3_RPB5 	 = 8,
    PPS_INT3_RPC1 	 = 10,
    PPS_INT3_RPD14 	 = 11,
    PPS_INT3_RPG1 	 = 12,
    PPS_INT3_RPA14 	 = 13,
    PPS_INT3_RPD6 	 = 14,
};
enum PPS_T2CK{
    PPS_T2CK_RPD2 	 = 0,
    PPS_T2CK_RPG8 	 = 1,
    PPS_T2CK_RPF4 	 = 2,
    PPS_T2CK_RPD10 	 = 3,
    PPS_T2CK_RPF1 	 = 4,
    PPS_T2CK_RPB9 	 = 5,
    PPS_T2CK_RPB10 	 = 6,
    PPS_T2CK_RPC14 	 = 7,
    PPS_T2CK_RPB5 	 = 8,
    PPS_T2CK_RPC1 	 = 10,
    PPS_T2CK_RPD14 	 = 11,
    PPS_T2CK_RPG1 	 = 12,
    PPS_T2CK_RPA14 	 = 13,
    PPS_T2CK_RPD6 	 = 14,
};
enum PPS_T6CK{
    PPS_T6CK_RPD2 	 = 0,
    PPS_T6CK_RPG8 	 = 1,
    PPS_T6CK_RPF4 	 = 2,
    PPS_T6CK_RPD10 	 = 3,
    PPS_T6CK_RPF1 	 = 4,
    PPS_T6CK_RPB9 	 = 5,
    PPS_T6CK_RPB10 	 = 6,
    PPS_T6CK_RPC14 	 = 7,
    PPS_T6CK_RPB5 	 = 8,
    PPS_T6CK_RPC1 	 = 10,
    PPS_T6CK_RPD14 	 = 11,
    PPS_T6CK_RPG1 	 = 12,
    PPS_T6CK_RPA14 	 = 13,
    PPS_T6CK_RPD6 	 = 14,
};
enum PPS_IC3{
    PPS_IC3_RPD2 	 = 0,
    PPS_IC3_RPG8 	 = 1,
    PPS_IC3_RPF4 	 = 2,
    PPS_IC3_RPD10 	 = 3,
    PPS_IC3_RPF1 	 = 4,
    PPS_IC3_RPB9 	 = 5,
    PPS_IC3_RPB10 	 = 6,
    PPS_IC3_RPC14 	 = 7,
    PPS_IC3_RPB5 	 = 8,
    PPS_IC3_RPC1 	 = 10,
    PPS_IC3_RPD14 	 = 11,
    PPS_IC3_RPG1 	 = 12,
    PPS_IC3_RPA14 	 = 13,
    PPS_IC3_RPD6 	 = 14,
};
enum PPS_IC7{
    PPS_IC7_RPD2 	 = 0,
    PPS_IC7_RPG8 	 = 1,
    PPS_IC7_RPF4 	 = 2,
    PPS_IC7_RPD10 	 = 3,
    PPS_IC7_RPF1 	 = 4,
    PPS_IC7_RPB9 	 = 5,
    PPS_IC7_RPB10 	 = 6,
    PPS_IC7_RPC14 	 = 7,
    PPS_IC7_RPB5 	 = 8,
    PPS_IC7_RPC1 	 = 10,
    PPS_IC7_RPD14 	 = 11,
    PPS_IC7_RPG1 	 = 12,
    PPS_IC7_RPA14 	 = 13,
    PPS_IC7_RPD6 	 = 14,
};
enum PPS_U1RX{
    PPS_U1RX_RPD2 	 = 0,
    PPS_U1RX_RPG8 	 = 1,
    PPS_U1RX_RPF4 	 = 2,
    PPS_U1RX_RPD10 	 = 3,
    PPS_U1RX_RPF1 	 = 4,
    PPS_U1RX_RPB9 	 = 5,
    PPS_U1RX_RPB10 	 = 6,
    PPS_U1RX_RPC14 	 = 7,
    PPS_U1RX_RPB5 	 = 8,
    PPS_U1RX_RPC1 	 = 10,
    PPS_U1RX_RPD14 	 = 11,
    PPS_U1RX_RPG1 	 = 12,
    PPS_U1RX_RPA14 	 = 13,
    PPS_U1RX_RPD6 	 = 14,
};
enum PPS_U2CTS{
    PPS_U2CTS_RPD2 	 = 0,
    PPS_U2CTS_RPG8 	 = 1,
    PPS_U2CTS_RPF4 	 = 2,
    PPS_U2CTS_RPD10  = 3,
    PPS_U2CTS_RPF1 	 = 4,
    PPS_U2CTS_RPB9 	 = 5,
    PPS_U2CTS_RPB10  = 6,
    PPS_U2CTS_RPC14  = 7,
    PPS_U2CTS_RPB5 	 = 8,
    PPS_U2CTS_RPC1 	 = 10,
    PPS_U2CTS_RPD14  = 11,
    PPS_U2CTS_RPG1 	 = 12,
    PPS_U2CTS_RPA14  = 13,
    PPS_U2CTS_RPD6 	 = 14,
};
enum PPS_U5RX{
    PPS_U5RX_RPD2 	 = 0,
    PPS_U5RX_RPG8 	 = 1,
    PPS_U5RX_RPF4 	 = 2,
    PPS_U5RX_RPD10 	 = 3,
    PPS_U5RX_RPF1 	 = 4,
    PPS_U5RX_RPB9 	 = 5,
    PPS_U5RX_RPB10 	 = 6,
    PPS_U5RX_RPC14 	 = 7,
    PPS_U5RX_RPB5 	 = 8,
    PPS_U5RX_RPC1 	 = 10,
    PPS_U5RX_RPD14 	 = 11,
    PPS_U5RX_RPG1 	 = 12,
    PPS_U5RX_RPA14 	 = 13,
    PPS_U5RX_RPD6 	 = 14,
};
enum PPS_U6CTS{
    PPS_U6CTS_RPD2 	 = 0,
    PPS_U6CTS_RPG8 	 = 1,
    PPS_U6CTS_RPF4 	 = 2,
    PPS_U6CTS_RPD10  = 3,
    PPS_U6CTS_RPF1 	 = 4,
    PPS_U6CTS_RPB9 	 = 5,
    PPS_U6CTS_RPB10  = 6,
    PPS_U6CTS_RPC14  = 7,
    PPS_U6CTS_RPB5 	 = 8,
    PPS_U6CTS_RPC1 	 = 10,
    PPS_U6CTS_RPD14  = 11,
    PPS_U6CTS_RPG1 	 = 12,
    PPS_U6CTS_RPA14  = 13,
    PPS_U6CTS_RPD6 	 = 14,
};
enum PPS_SDI1{
    PPS_SDI1_RPD2 	 = 0,
    PPS_SDI1_RPG8 	 = 1,
    PPS_SDI1_RPF4 	 = 2,
    PPS_SDI1_RPD10 	 = 3,
    PPS_SDI1_RPF1 	 = 4,
    PPS_SDI1_RPB9 	 = 5,
    PPS_SDI1_RPB10 	 = 6,
    PPS_SDI1_RPC14 	 = 7,
    PPS_SDI1_RPB5 	 = 8,
    PPS_SDI1_RPC1 	 = 10,
    PPS_SDI1_RPD14 	 = 11,
    PPS_SDI1_RPG1 	 = 12,
    PPS_SDI1_RPA14 	 = 13,
    PPS_SDI1_RPD6 	 = 14,
};
enum PPS_SDI3{
    PPS_SDI3_RPD2 	 = 0,
    PPS_SDI3_RPG8 	 = 1,
    PPS_SDI3_RPF4 	 = 2,
    PPS_SDI3_RPD10 	 = 3,
    PPS_SDI3_RPF1 	 = 4,
    PPS_SDI3_RPB9 	 = 5,
    PPS_SDI3_RPB10 	 = 6,
    PPS_SDI3_RPC14 	 = 7,
    PPS_SDI3_RPB5 	 = 8,
    PPS_SDI3_RPC1 	 = 10,
    PPS_SDI3_RPD14 	 = 11,
    PPS_SDI3_RPG1 	 = 12,
    PPS_SDI3_RPA14 	 = 13,
    PPS_SDI3_RPD6 	 = 14,
};
enum PPS_SDI5{
    PPS_SDI5_RPD2 	 = 0,
    PPS_SDI5_RPG8 	 = 1,
    PPS_SDI5_RPF4 	 = 2,
    PPS_SDI5_RPD10 	 = 3,
    PPS_SDI5_RPF1 	 = 4,
    PPS_SDI5_RPB9 	 = 5,
    PPS_SDI5_RPB10 	 = 6,
    PPS_SDI5_RPC14 	 = 7,
    PPS_SDI5_RPB5 	 = 8,
    PPS_SDI5_RPC1 	 = 10,
    PPS_SDI5_RPD14 	 = 11,
    PPS_SDI5_RPG1 	 = 12,
    PPS_SDI5_RPA14 	 = 13,
    PPS_SDI5_RPD6 	 = 14,
};
enum PPS_SS6{
    PPS_SS6_RPD2 	 = 0,
    PPS_SS6_RPG8 	 = 1,
    PPS_SS6_RPF4 	 = 2,
    PPS_SS6_RPD10 	 = 3,
    PPS_SS6_RPF1 	 = 4,
    PPS_SS6_RPB9 	 = 5,
    PPS_SS6_RPB10 	 = 6,
    PPS_SS6_RPC14 	 = 7,
    PPS_SS6_RPB5 	 = 8,
    PPS_SS6_RPC1 	 = 10,
    PPS_SS6_RPD14 	 = 11,
    PPS_SS6_RPG1 	 = 12,
    PPS_SS6_RPA14 	 = 13,
    PPS_SS6_RPD6 	 = 14,
};
enum PPS_REFCLKI1{
    PPS_REFCLKI1_RPD2 	 = 0,
    PPS_REFCLKI1_RPG8 	 = 1,
    PPS_REFCLKI1_RPF4 	 = 2,
    PPS_REFCLKI1_RPD10 	 = 3,
    PPS_REFCLKI1_RPF1 	 = 4,
    PPS_REFCLKI1_RPB9 	 = 5,
    PPS_REFCLKI1_RPB10 	 = 6,
    PPS_REFCLKI1_RPC14 	 = 7,
    PPS_REFCLKI1_RPB5 	 = 8,
    PPS_REFCLKI1_RPC1 	 = 10,
    PPS_REFCLKI1_RPD14 	 = 11,
    PPS_REFCLKI1_RPG1 	 = 12,
    PPS_REFCLKI1_RPA14 	 = 13,
    PPS_REFCLKI1_RPD6 	 = 14,
};
enum PPS_INT4{
    PPS_INT4_RPD3 	 = 0,
    PPS_INT4_RPG7 	 = 1,
    PPS_INT4_RPF5 	 = 2,
    PPS_INT4_RPD11 	 = 3,
    PPS_INT4_RPF0 	 = 4,
    PPS_INT4_RPB1 	 = 5,
    PPS_INT4_RPE5 	 = 6,
    PPS_INT4_RPC13 	 = 7,
    PPS_INT4_RPB3 	 = 8,
    PPS_INT4_RPC4 	 = 10,
    PPS_INT4_RPD15 	 = 11,
    PPS_INT4_RPG0 	 = 12,
    PPS_INT4_RPA15 	 = 13,
    PPS_INT4_RPD7 	 = 14,
};
enum PPS_T5CK{
    PPS_T5CK_RPD3 	 = 0,
    PPS_T5CK_RPG7 	 = 1,
    PPS_T5CK_RPF5 	 = 2,
    PPS_T5CK_RPD11 	 = 3,
    PPS_T5CK_RPF0 	 = 4,
    PPS_T5CK_RPB1 	 = 5,
    PPS_T5CK_RPE5 	 = 6,
    PPS_T5CK_RPC13 	 = 7,
    PPS_T5CK_RPB3 	 = 8,
    PPS_T5CK_RPC4 	 = 10,
    PPS_T5CK_RPD15 	 = 11,
    PPS_T5CK_RPG0 	 = 12,
    PPS_T5CK_RPA15 	 = 13,
    PPS_T5CK_RPD7 	 = 14,
};
enum PPS_T7CK{
    PPS_T7CK_RPD3 	 = 0,
    PPS_T7CK_RPG7 	 = 1,
    PPS_T7CK_RPF5 	 = 2,
    PPS_T7CK_RPD11 	 = 3,
    PPS_T7CK_RPF0 	 = 4,
    PPS_T7CK_RPB1 	 = 5,
    PPS_T7CK_RPE5 	 = 6,
    PPS_T7CK_RPC13 	 = 7,
    PPS_T7CK_RPB3 	 = 8,
    PPS_T7CK_RPC4 	 = 10,
    PPS_T7CK_RPD15 	 = 11,
    PPS_T7CK_RPG0 	 = 12,
    PPS_T7CK_RPA15 	 = 13,
    PPS_T7CK_RPD7 	 = 14,
};
enum PPS_IC4{
    PPS_IC4_RPD3 	 = 0,
    PPS_IC4_RPG7 	 = 1,
    PPS_IC4_RPF5 	 = 2,
    PPS_IC4_RPD11 	 = 3,
    PPS_IC4_RPF0 	 = 4,
    PPS_IC4_RPB1 	 = 5,
    PPS_IC4_RPE5 	 = 6,
    PPS_IC4_RPC13 	 = 7,
    PPS_IC4_RPB3 	 = 8,
    PPS_IC4_RPC4 	 = 10,
    PPS_IC4_RPD15 	 = 11,
    PPS_IC4_RPG0 	 = 12,
    PPS_IC4_RPA15 	 = 13,
    PPS_IC4_RPD7 	 = 14,
};
enum PPS_IC8{
    PPS_IC8_RPD3 	 = 0,
    PPS_IC8_RPG7 	 = 1,
    PPS_IC8_RPF5 	 = 2,
    PPS_IC8_RPD11 	 = 3,
    PPS_IC8_RPF0 	 = 4,
    PPS_IC8_RPB1 	 = 5,
    PPS_IC8_RPE5 	 = 6,
    PPS_IC8_RPC13 	 = 7,
    PPS_IC8_RPB3 	 = 8,
    PPS_IC8_RPC4 	 = 10,
    PPS_IC8_RPD15 	 = 11,
    PPS_IC8_RPG0 	 = 12,
    PPS_IC8_RPA15 	 = 13,
    PPS_IC8_RPD7 	 = 14,
};
enum PPS_U3RX{
    PPS_U3RX_RPD3 	 = 0,
    PPS_U3RX_RPG7 	 = 1,
    PPS_U3RX_RPF5 	 = 2,
    PPS_U3RX_RPD11 	 = 3,
    PPS_U3RX_RPF0 	 = 4,
    PPS_U3RX_RPB1 	 = 5,
    PPS_U3RX_RPE5 	 = 6,
    PPS_U3RX_RPC13 	 = 7,
    PPS_U3RX_RPB3 	 = 8,
    PPS_U3RX_RPC4 	 = 10,
    PPS_U3RX_RPD15 	 = 11,
    PPS_U3RX_RPG0 	 = 12,
    PPS_U3RX_RPA15 	 = 13,
    PPS_U3RX_RPD7 	 = 14,
};
enum PPS_U4CTS{
    PPS_U4CTS_RPD3 	 = 0,
    PPS_U4CTS_RPG7 	 = 1,
    PPS_U4CTS_RPF5 	 = 2,
    PPS_U4CTS_RPD11 	 = 3,
    PPS_U4CTS_RPF0 	 = 4,
    PPS_U4CTS_RPB1 	 = 5,
    PPS_U4CTS_RPE5 	 = 6,
    PPS_U4CTS_RPC13 	 = 7,
    PPS_U4CTS_RPB3 	 = 8,
    PPS_U4CTS_RPC4 	 = 10,
    PPS_U4CTS_RPD15 	 = 11,
    PPS_U4CTS_RPG0 	 = 12,
    PPS_U4CTS_RPA15 	 = 13,
    PPS_U4CTS_RPD7 	 = 14,
};
enum PPS_SDI2{
    PPS_SDI2_RPD3 	 = 0,
    PPS_SDI2_RPG7 	 = 1,
    PPS_SDI2_RPF5 	 = 2,
    PPS_SDI2_RPD11 	 = 3,
    PPS_SDI2_RPF0 	 = 4,
    PPS_SDI2_RPB1 	 = 5,
    PPS_SDI2_RPE5 	 = 6,
    PPS_SDI2_RPC13 	 = 7,
    PPS_SDI2_RPB3 	 = 8,
    PPS_SDI2_RPC4 	 = 10,
    PPS_SDI2_RPD15 	 = 11,
    PPS_SDI2_RPG0 	 = 12,
    PPS_SDI2_RPA15 	 = 13,
    PPS_SDI2_RPD7 	 = 14,
};
enum PPS_SDI4{
    PPS_SDI4_RPD3 	 = 0,
    PPS_SDI4_RPG7 	 = 1,
    PPS_SDI4_RPF5 	 = 2,
    PPS_SDI4_RPD11 	 = 3,
    PPS_SDI4_RPF0 	 = 4,
    PPS_SDI4_RPB1 	 = 5,
    PPS_SDI4_RPE5 	 = 6,
    PPS_SDI4_RPC13 	 = 7,
    PPS_SDI4_RPB3 	 = 8,
    PPS_SDI4_RPC4 	 = 10,
    PPS_SDI4_RPD15 	 = 11,
    PPS_SDI4_RPG0 	 = 12,
    PPS_SDI4_RPA15 	 = 13,
    PPS_SDI4_RPD7 	 = 14,
};
enum PPS_C1RX{
    PPS_C1RX_RPD3 	 = 0,
    PPS_C1RX_RPG7 	 = 1,
    PPS_C1RX_RPF5 	 = 2,
    PPS_C1RX_RPD11 	 = 3,
    PPS_C1RX_RPF0 	 = 4,
    PPS_C1RX_RPB1 	 = 5,
    PPS_C1RX_RPE5 	 = 6,
    PPS_C1RX_RPC13 	 = 7,
    PPS_C1RX_RPB3 	 = 8,
    PPS_C1RX_RPC4 	 = 10,
    PPS_C1RX_RPD15 	 = 11,
    PPS_C1RX_RPG0 	 = 12,
    PPS_C1RX_RPA15 	 = 13,
    PPS_C1RX_RPD7 	 = 14,
};
enum PPS_REFCLKI4{
    PPS_REFCLKI4_RPD3 	 = 0,
    PPS_REFCLKI4_RPG7 	 = 1,
    PPS_REFCLKI4_RPF5 	 = 2,
    PPS_REFCLKI4_RPD11 	 = 3,
    PPS_REFCLKI4_RPF0 	 = 4,
    PPS_REFCLKI4_RPB1 	 = 5,
    PPS_REFCLKI4_RPE5 	 = 6,
    PPS_REFCLKI4_RPC13 	 = 7,
    PPS_REFCLKI4_RPB3 	 = 8,
    PPS_REFCLKI4_RPC4 	 = 10,
    PPS_REFCLKI4_RPD15 	 = 11,
    PPS_REFCLKI4_RPG0 	 = 12,
    PPS_REFCLKI4_RPA15 	 = 13,
    PPS_REFCLKI4_RPD7 	 = 14,
};
enum PPS_INT2{
    PPS_INT2_RPD9 	 = 0,
    PPS_INT2_RPG6 	 = 1,
    PPS_INT2_RPB8 	 = 2,
    PPS_INT2_RPB15 	 = 3,
    PPS_INT2_RPD4 	 = 4,
    PPS_INT2_RPB0 	 = 5,
    PPS_INT2_RPE3 	 = 6,
    PPS_INT2_RPB7 	 = 7,
    PPS_INT2_RPF12 	 = 9,
    PPS_INT2_RPD12 	 = 10,
    PPS_INT2_RPF8 	 = 11,
    PPS_INT2_RPC3 	 = 12,
    PPS_INT2_RPE9 	 = 13,
};
enum PPS_T3CK{
    PPS_T3CK_RPD9 	 = 0,
    PPS_T3CK_RPG6 	 = 1,
    PPS_T3CK_RPB8 	 = 2,
    PPS_T3CK_RPB15 	 = 3,
    PPS_T3CK_RPD4 	 = 4,
    PPS_T3CK_RPB0 	 = 5,
    PPS_T3CK_RPE3 	 = 6,
    PPS_T3CK_RPB7 	 = 7,
    PPS_T3CK_RPF12 	 = 9,
    PPS_T3CK_RPD12 	 = 10,
    PPS_T3CK_RPF8 	 = 11,
    PPS_T3CK_RPC3 	 = 12,
    PPS_T3CK_RPE9 	 = 13,
};
enum PPS_T8CK{
    PPS_T8CK_RPD9 	 = 0,
    PPS_T8CK_RPG6 	 = 1,
    PPS_T8CK_RPB8 	 = 2,
    PPS_T8CK_RPB15 	 = 3,
    PPS_T8CK_RPD4 	 = 4,
    PPS_T8CK_RPB0 	 = 5,
    PPS_T8CK_RPE3 	 = 6,
    PPS_T8CK_RPB7 	 = 7,
    PPS_T8CK_RPF12 	 = 9,
    PPS_T8CK_RPD12 	 = 10,
    PPS_T8CK_RPF8 	 = 11,
    PPS_T8CK_RPC3 	 = 12,
    PPS_T8CK_RPE9 	 = 13,
};
enum PPS_IC2{
    PPS_IC2_RPD9 	 = 0,
    PPS_IC2_RPG6 	 = 1,
    PPS_IC2_RPB8 	 = 2,
    PPS_IC2_RPB15 	 = 3,
    PPS_IC2_RPD4 	 = 4,
    PPS_IC2_RPB0 	 = 5,
    PPS_IC2_RPE3 	 = 6,
    PPS_IC2_RPB7 	 = 7,
    PPS_IC2_RPF12 	 = 9,
    PPS_IC2_RPD12 	 = 10,
    PPS_IC2_RPF8 	 = 11,
    PPS_IC2_RPC3 	 = 12,
    PPS_IC2_RPE9 	 = 13,
};
enum PPS_IC5{
    PPS_IC5_RPD9 	 = 0,
    PPS_IC5_RPG6 	 = 1,
    PPS_IC5_RPB8 	 = 2,
    PPS_IC5_RPB15 	 = 3,
    PPS_IC5_RPD4 	 = 4,
    PPS_IC5_RPB0 	 = 5,
    PPS_IC5_RPE3 	 = 6,
    PPS_IC5_RPB7 	 = 7,
    PPS_IC5_RPF12 	 = 9,
    PPS_IC5_RPD12 	 = 10,
    PPS_IC5_RPF8 	 = 11,
    PPS_IC5_RPC3 	 = 12,
    PPS_IC5_RPE9 	 = 13,
};
enum PPS_IC9{
    PPS_IC9_RPD9 	 = 0,
    PPS_IC9_RPG6 	 = 1,
    PPS_IC9_RPB8 	 = 2,
    PPS_IC9_RPB15 	 = 3,
    PPS_IC9_RPD4 	 = 4,
    PPS_IC9_RPB0 	 = 5,
    PPS_IC9_RPE3 	 = 6,
    PPS_IC9_RPB7 	 = 7,
    PPS_IC9_RPF12 	 = 9,
    PPS_IC9_RPD12 	 = 10,
    PPS_IC9_RPF8 	 = 11,
    PPS_IC9_RPC3 	 = 12,
    PPS_IC9_RPE9 	 = 13,
};
enum PPS_U1CTS{
    PPS_U1CTS_RPD9 	 = 0,
    PPS_U1CTS_RPG6 	 = 1,
    PPS_U1CTS_RPB8 	 = 2,
    PPS_U1CTS_RPB15 	 = 3,
    PPS_U1CTS_RPD4 	 = 4,
    PPS_U1CTS_RPB0 	 = 5,
    PPS_U1CTS_RPE3 	 = 6,
    PPS_U1CTS_RPB7 	 = 7,
    PPS_U1CTS_RPF12 	 = 9,
    PPS_U1CTS_RPD12 	 = 10,
    PPS_U1CTS_RPF8 	 = 11,
    PPS_U1CTS_RPC3 	 = 12,
    PPS_U1CTS_RPE9 	 = 13,
};
enum PPS_U2RX{
    PPS_U2RX_RPD9 	 = 0,
    PPS_U2RX_RPG6 	 = 1,
    PPS_U2RX_RPB8 	 = 2,
    PPS_U2RX_RPB15 	 = 3,
    PPS_U2RX_RPD4 	 = 4,
    PPS_U2RX_RPB0 	 = 5,
    PPS_U2RX_RPE3 	 = 6,
    PPS_U2RX_RPB7 	 = 7,
    PPS_U2RX_RPF12 	 = 9,
    PPS_U2RX_RPD12 	 = 10,
    PPS_U2RX_RPF8 	 = 11,
    PPS_U2RX_RPC3 	 = 12,
    PPS_U2RX_RPE9 	 = 13,
};
enum PPS_U5CTS{
    PPS_U5CTS_RPD9 	 = 0,
    PPS_U5CTS_RPG6 	 = 1,
    PPS_U5CTS_RPB8 	 = 2,
    PPS_U5CTS_RPB15 	 = 3,
    PPS_U5CTS_RPD4 	 = 4,
    PPS_U5CTS_RPB0 	 = 5,
    PPS_U5CTS_RPE3 	 = 6,
    PPS_U5CTS_RPB7 	 = 7,
    PPS_U5CTS_RPF12 	 = 9,
    PPS_U5CTS_RPD12 	 = 10,
    PPS_U5CTS_RPF8 	 = 11,
    PPS_U5CTS_RPC3 	 = 12,
    PPS_U5CTS_RPE9 	 = 13,
};
enum PPS_SS1{
    PPS_SS1_RPD9 	 = 0,
    PPS_SS1_RPG6 	 = 1,
    PPS_SS1_RPB8 	 = 2,
    PPS_SS1_RPB15 	 = 3,
    PPS_SS1_RPD4 	 = 4,
    PPS_SS1_RPB0 	 = 5,
    PPS_SS1_RPE3 	 = 6,
    PPS_SS1_RPB7 	 = 7,
    PPS_SS1_RPF12 	 = 9,
    PPS_SS1_RPD12 	 = 10,
    PPS_SS1_RPF8 	 = 11,
    PPS_SS1_RPC3 	 = 12,
    PPS_SS1_RPE9 	 = 13,
};
enum PPS_SS3{
    PPS_SS3_RPD9 	 = 0,
    PPS_SS3_RPG6 	 = 1,
    PPS_SS3_RPB8 	 = 2,
    PPS_SS3_RPB15 	 = 3,
    PPS_SS3_RPD4 	 = 4,
    PPS_SS3_RPB0 	 = 5,
    PPS_SS3_RPE3 	 = 6,
    PPS_SS3_RPB7 	 = 7,
    PPS_SS3_RPF12 	 = 9,
    PPS_SS3_RPD12 	 = 10,
    PPS_SS3_RPF8 	 = 11,
    PPS_SS3_RPC3 	 = 12,
    PPS_SS3_RPE9 	 = 13,
};
enum PPS_SS4{
    PPS_SS4_RPD9 	 = 0,
    PPS_SS4_RPG6 	 = 1,
    PPS_SS4_RPB8 	 = 2,
    PPS_SS4_RPB15 	 = 3,
    PPS_SS4_RPD4 	 = 4,
    PPS_SS4_RPB0 	 = 5,
    PPS_SS4_RPE3 	 = 6,
    PPS_SS4_RPB7 	 = 7,
    PPS_SS4_RPF12 	 = 9,
    PPS_SS4_RPD12 	 = 10,
    PPS_SS4_RPF8 	 = 11,
    PPS_SS4_RPC3 	 = 12,
    PPS_SS4_RPE9 	 = 13,
};
enum PPS_SS5{
    PPS_SS5_RPD9 	 = 0,
    PPS_SS5_RPG6 	 = 1,
    PPS_SS5_RPB8 	 = 2,
    PPS_SS5_RPB15 	 = 3,
    PPS_SS5_RPD4 	 = 4,
    PPS_SS5_RPB0 	 = 5,
    PPS_SS5_RPE3 	 = 6,
    PPS_SS5_RPB7 	 = 7,
    PPS_SS5_RPF12 	 = 9,
    PPS_SS5_RPD12 	 = 10,
    PPS_SS5_RPF8 	 = 11,
    PPS_SS5_RPC3 	 = 12,
    PPS_SS5_RPE9 	 = 13,
};
enum PPS_INT1{
    PPS_INT1_RPD1 	 = 0,
    PPS_INT1_RPG9 	 = 1,
    PPS_INT1_RPB14 	 = 2,
    PPS_INT1_RPD0 	 = 3,
    PPS_INT1_RPB6 	 = 5,
    PPS_INT1_RPD5 	 = 6,
    PPS_INT1_RPB2 	 = 7,
    PPS_INT1_RPF3 	 = 8,
    PPS_INT1_RPF13 	 = 9,
    PPS_INT1_NoConnect 	 = 10,
    PPS_INT1_RPF2 	 = 11,
    PPS_INT1_RPC2 	 = 12,
    PPS_INT1_RPE8 	 = 13,
};
enum PPS_T4CK{
    PPS_T4CK_RPD1 	 = 0,
    PPS_T4CK_RPG9 	 = 1,
    PPS_T4CK_RPB14 	 = 2,
    PPS_T4CK_RPD0 	 = 3,
    PPS_T4CK_RPB6 	 = 5,
    PPS_T4CK_RPD5 	 = 6,
    PPS_T4CK_RPB2 	 = 7,
    PPS_T4CK_RPF3 	 = 8,
    PPS_T4CK_RPF13 	 = 9,
    PPS_T4CK_NoConnect 	 = 10,
    PPS_T4CK_RPF2 	 = 11,
    PPS_T4CK_RPC2 	 = 12,
    PPS_T4CK_RPE8 	 = 13,
};
enum PPS_T9CK{
    PPS_T9CK_RPD1 	 = 0,
    PPS_T9CK_RPG9 	 = 1,
    PPS_T9CK_RPB14 	 = 2,
    PPS_T9CK_RPD0 	 = 3,
    PPS_T9CK_RPB6 	 = 5,
    PPS_T9CK_RPD5 	 = 6,
    PPS_T9CK_RPB2 	 = 7,
    PPS_T9CK_RPF3 	 = 8,
    PPS_T9CK_RPF13 	 = 9,
    PPS_T9CK_NoConnect 	 = 10,
    PPS_T9CK_RPF2 	 = 11,
    PPS_T9CK_RPC2 	 = 12,
    PPS_T9CK_RPE8 	 = 13,
};
enum PPS_IC1{
    PPS_IC1_RPD1 	 = 0,
    PPS_IC1_RPG9 	 = 1,
    PPS_IC1_RPB14 	 = 2,
    PPS_IC1_RPD0 	 = 3,
    PPS_IC1_RPB6 	 = 5,
    PPS_IC1_RPD5 	 = 6,
    PPS_IC1_RPB2 	 = 7,
    PPS_IC1_RPF3 	 = 8,
    PPS_IC1_RPF13 	 = 9,
    PPS_IC1_NoConnect 	 = 10,
    PPS_IC1_RPF2 	 = 11,
    PPS_IC1_RPC2 	 = 12,
    PPS_IC1_RPE8 	 = 13,
};
enum PPS_IC6{
    PPS_IC6_RPD1 	 = 0,
    PPS_IC6_RPG9 	 = 1,
    PPS_IC6_RPB14 	 = 2,
    PPS_IC6_RPD0 	 = 3,
    PPS_IC6_RPB6 	 = 5,
    PPS_IC6_RPD5 	 = 6,
    PPS_IC6_RPB2 	 = 7,
    PPS_IC6_RPF3 	 = 8,
    PPS_IC6_RPF13 	 = 9,
    PPS_IC6_NoConnect 	 = 10,
    PPS_IC6_RPF2 	 = 11,
    PPS_IC6_RPC2 	 = 12,
    PPS_IC6_RPE8 	 = 13,
};
enum PPS_U3CTS{
    PPS_U3CTS_RPD1 	 = 0,
    PPS_U3CTS_RPG9 	 = 1,
    PPS_U3CTS_RPB14 	 = 2,
    PPS_U3CTS_RPD0 	 = 3,
    PPS_U3CTS_RPB6 	 = 5,
    PPS_U3CTS_RPD5 	 = 6,
    PPS_U3CTS_RPB2 	 = 7,
    PPS_U3CTS_RPF3 	 = 8,
    PPS_U3CTS_RPF13 	 = 9,
    PPS_U3CTS_NoConnect 	 = 10,
    PPS_U3CTS_RPF2 	 = 11,
    PPS_U3CTS_RPC2 	 = 12,
    PPS_U3CTS_RPE8 	 = 13,
};
enum PPS_U4RX{
    PPS_U4RX_RPD1 	 = 0,
    PPS_U4RX_RPG9 	 = 1,
    PPS_U4RX_RPB14 	 = 2,
    PPS_U4RX_RPD0 	 = 3,
    PPS_U4RX_RPB6 	 = 5,
    PPS_U4RX_RPD5 	 = 6,
    PPS_U4RX_RPB2 	 = 7,
    PPS_U4RX_RPF3 	 = 8,
    PPS_U4RX_RPF13 	 = 9,
    PPS_U4RX_NoConnect 	 = 10,
    PPS_U4RX_RPF2 	 = 11,
    PPS_U4RX_RPC2 	 = 12,
    PPS_U4RX_RPE8 	 = 13,
};
enum PPS_U6RX{
    PPS_U6RX_RPD1 	 = 0,
    PPS_U6RX_RPG9 	 = 1,
    PPS_U6RX_RPB14 	 = 2,
    PPS_U6RX_RPD0 	 = 3,
    PPS_U6RX_RPB6 	 = 5,
    PPS_U6RX_RPD5 	 = 6,
    PPS_U6RX_RPB2 	 = 7,
    PPS_U6RX_RPF3 	 = 8,
    PPS_U6RX_RPF13 	 = 9,
    PPS_U6RX_NoConnect 	 = 10,
    PPS_U6RX_RPF2 	 = 11,
    PPS_U6RX_RPC2 	 = 12,
    PPS_U6RX_RPE8 	 = 13,
};
enum PPS_SS2{
    PPS_SS2_RPD1 	 = 0,
    PPS_SS2_RPG9 	 = 1,
    PPS_SS2_RPB14 	 = 2,
    PPS_SS2_RPD0 	 = 3,
    PPS_SS2_RPB6 	 = 5,
    PPS_SS2_RPD5 	 = 6,
    PPS_SS2_RPB2 	 = 7,
    PPS_SS2_RPF3 	 = 8,
    PPS_SS2_RPF13 	 = 9,
    PPS_SS2_NoConnect 	 = 10,
    PPS_SS2_RPF2 	 = 11,
    PPS_SS2_RPC2 	 = 12,
    PPS_SS2_RPE8 	 = 13,
};
enum PPS_SDI6{
    PPS_SDI6_RPD1 	 = 0,
    PPS_SDI6_RPG9 	 = 1,
    PPS_SDI6_RPB14 	 = 2,
    PPS_SDI6_RPD0 	 = 3,
    PPS_SDI6_RPB6 	 = 5,
    PPS_SDI6_RPD5 	 = 6,
    PPS_SDI6_RPB2 	 = 7,
    PPS_SDI6_RPF3 	 = 8,
    PPS_SDI6_RPF13 	 = 9,
    PPS_SDI6_NoConnect 	 = 10,
    PPS_SDI6_RPF2 	 = 11,
    PPS_SDI6_RPC2 	 = 12,
    PPS_SDI6_RPE8 	 = 13,
};
enum PPS_OCFA{
    PPS_OCFA_RPD1 	 = 0,
    PPS_OCFA_RPG9 	 = 1,
    PPS_OCFA_RPB14 	 = 2,
    PPS_OCFA_RPD0 	 = 3,
    PPS_OCFA_RPB6 	 = 5,
    PPS_OCFA_RPD5 	 = 6,
    PPS_OCFA_RPB2 	 = 7,
    PPS_OCFA_RPF3 	 = 8,
    PPS_OCFA_RPF13 	 = 9,
    PPS_OCFA_NoConnect 	 = 10,
    PPS_OCFA_RPF2 	 = 11,
    PPS_OCFA_RPC2 	 = 12,
    PPS_OCFA_RPE8 	 = 13,
};
enum PPS_REFCLKI3{
    PPS_REFCLKI3_RPD1 	 = 0,
    PPS_REFCLKI3_RPG9 	 = 1,
    PPS_REFCLKI3_RPB14 	 = 2,
    PPS_REFCLKI3_RPD0 	 = 3,
    PPS_REFCLKI3_RPB6 	 = 5,
    PPS_REFCLKI3_RPD5 	 = 6,
    PPS_REFCLKI3_RPB2 	 = 7,
    PPS_REFCLKI3_RPF3 	 = 8,
    PPS_REFCLKI3_RPF13 	 = 9,
    PPS_REFCLKI3_NoConnect 	 = 10,
    PPS_REFCLKI3_RPF2 	 = 11,
    PPS_REFCLKI3_RPC2 	 = 12,
    PPS_REFCLKI3_RPE8 	 = 13,
};
/*OUTPUT*/
enum PPS_RPD2{
    PPS_RPD2_NoConnect 	 = 0,
    PPS_RPD2_U3TX 	 = 1,
    PPS_RPD2_U4RTS 	 = 2,
    PPS_RPD2_SDO1 	 = 5,
    PPS_RPD2_SDO2 	 = 6,
    PPS_RPD2_SDO3 	 = 7,
    PPS_RPD2_SDO5 	 = 9,
    PPS_RPD2_SS6 	 = 10,
    PPS_RPD2_OC3 	 = 11,
    PPS_RPD2_OC6 	 = 12,
    PPS_RPD2_REFCLKO4 	 = 13,
    PPS_RPD2_C2OUT 	 = 14,
    PPS_RPD2_C1TX 	 = 15,
};
enum PPS_RPG8{
    PPS_RPG8_NoConnect 	 = 0,
    PPS_RPG8_U3TX 	 = 1,
    PPS_RPG8_U4RTS 	 = 2,
    PPS_RPG8_SDO1 	 = 5,
    PPS_RPG8_SDO2 	 = 6,
    PPS_RPG8_SDO3 	 = 7,
    PPS_RPG8_SDO5 	 = 9,
    PPS_RPG8_SS6 	 = 10,
    PPS_RPG8_OC3 	 = 11,
    PPS_RPG8_OC6 	 = 12,
    PPS_RPG8_REFCLKO4 	 = 13,
    PPS_RPG8_C2OUT 	 = 14,
    PPS_RPG8_C1TX 	 = 15,
};
enum PPS_RPF4{
    PPS_RPF4_NoConnect 	 = 0,
    PPS_RPF4_U3TX 	 = 1,
    PPS_RPF4_U4RTS 	 = 2,
    PPS_RPF4_SDO1 	 = 5,
    PPS_RPF4_SDO2 	 = 6,
    PPS_RPF4_SDO3 	 = 7,
    PPS_RPF4_SDO5 	 = 9,
    PPS_RPF4_SS6 	 = 10,
    PPS_RPF4_OC3 	 = 11,
    PPS_RPF4_OC6 	 = 12,
    PPS_RPF4_REFCLKO4 	 = 13,
    PPS_RPF4_C2OUT 	 = 14,
    PPS_RPF4_C1TX 	 = 15,
};
enum PPS_RPD10{
    PPS_RPD10_NoConnect 	 = 0,
    PPS_RPD10_U3TX 	 = 1,
    PPS_RPD10_U4RTS 	 = 2,
    PPS_RPD10_SDO1 	 = 5,
    PPS_RPD10_SDO2 	 = 6,
    PPS_RPD10_SDO3 	 = 7,
    PPS_RPD10_SDO5 	 = 9,
    PPS_RPD10_SS6 	 = 10,
    PPS_RPD10_OC3 	 = 11,
    PPS_RPD10_OC6 	 = 12,
    PPS_RPD10_REFCLKO4 	 = 13,
    PPS_RPD10_C2OUT 	 = 14,
    PPS_RPD10_C1TX 	 = 15,
};
enum PPS_RPF1{
    PPS_RPF1_NoConnect 	 = 0,
    PPS_RPF1_U3TX 	 = 1,
    PPS_RPF1_U4RTS 	 = 2,
    PPS_RPF1_SDO1 	 = 5,
    PPS_RPF1_SDO2 	 = 6,
    PPS_RPF1_SDO3 	 = 7,
    PPS_RPF1_SDO5 	 = 9,
    PPS_RPF1_SS6 	 = 10,
    PPS_RPF1_OC3 	 = 11,
    PPS_RPF1_OC6 	 = 12,
    PPS_RPF1_REFCLKO4 	 = 13,
    PPS_RPF1_C2OUT 	 = 14,
    PPS_RPF1_C1TX 	 = 15,
};
enum PPS_RPB9{
    PPS_RPB9_NoConnect 	 = 0,
    PPS_RPB9_U3TX 	 = 1,
    PPS_RPB9_U4RTS 	 = 2,
    PPS_RPB9_SDO1 	 = 5,
    PPS_RPB9_SDO2 	 = 6,
    PPS_RPB9_SDO3 	 = 7,
    PPS_RPB9_SDO5 	 = 9,
    PPS_RPB9_SS6 	 = 10,
    PPS_RPB9_OC3 	 = 11,
    PPS_RPB9_OC6 	 = 12,
    PPS_RPB9_REFCLKO4 	 = 13,
    PPS_RPB9_C2OUT 	 = 14,
    PPS_RPB9_C1TX 	 = 15,
};
enum PPS_RPB10{
    PPS_RPB10_NoConnect 	 = 0,
    PPS_RPB10_U3TX 	 = 1,
    PPS_RPB10_U4RTS 	 = 2,
    PPS_RPB10_SDO1 	 = 5,
    PPS_RPB10_SDO2 	 = 6,
    PPS_RPB10_SDO3 	 = 7,
    PPS_RPB10_SDO5 	 = 9,
    PPS_RPB10_SS6 	 = 10,
    PPS_RPB10_OC3 	 = 11,
    PPS_RPB10_OC6 	 = 12,
    PPS_RPB10_REFCLKO4 	 = 13,
    PPS_RPB10_C2OUT 	 = 14,
    PPS_RPB10_C1TX 	 = 15,
};
enum PPS_RPC14{
    PPS_RPC14_NoConnect 	 = 0,
    PPS_RPC14_U3TX 	 = 1,
    PPS_RPC14_U4RTS 	 = 2,
    PPS_RPC14_SDO1 	 = 5,
    PPS_RPC14_SDO2 	 = 6,
    PPS_RPC14_SDO3 	 = 7,
    PPS_RPC14_SDO5 	 = 9,
    PPS_RPC14_SS6 	 = 10,
    PPS_RPC14_OC3 	 = 11,
    PPS_RPC14_OC6 	 = 12,
    PPS_RPC14_REFCLKO4 	 = 13,
    PPS_RPC14_C2OUT 	 = 14,
    PPS_RPC14_C1TX 	 = 15,
};
enum PPS_RPB5{
    PPS_RPB5_NoConnect 	 = 0,
    PPS_RPB5_U3TX 	 = 1,
    PPS_RPB5_U4RTS 	 = 2,
    PPS_RPB5_SDO1 	 = 5,
    PPS_RPB5_SDO2 	 = 6,
    PPS_RPB5_SDO3 	 = 7,
    PPS_RPB5_SDO5 	 = 9,
    PPS_RPB5_SS6 	 = 10,
    PPS_RPB5_OC3 	 = 11,
    PPS_RPB5_OC6 	 = 12,
    PPS_RPB5_REFCLKO4 	 = 13,
    PPS_RPB5_C2OUT 	 = 14,
    PPS_RPB5_C1TX 	 = 15,
};
enum PPS_RPC1{
    PPS_RPC1_NoConnect 	 = 0,
    PPS_RPC1_U3TX 	 = 1,
    PPS_RPC1_U4RTS 	 = 2,
    PPS_RPC1_SDO1 	 = 5,
    PPS_RPC1_SDO2 	 = 6,
    PPS_RPC1_SDO3 	 = 7,
    PPS_RPC1_SDO5 	 = 9,
    PPS_RPC1_SS6 	 = 10,
    PPS_RPC1_OC3 	 = 11,
    PPS_RPC1_OC6 	 = 12,
    PPS_RPC1_REFCLKO4 	 = 13,
    PPS_RPC1_C2OUT 	 = 14,
    PPS_RPC1_C1TX 	 = 15,
};
enum PPS_RPD14{
    PPS_RPD14_NoConnect 	 = 0,
    PPS_RPD14_U3TX 	 = 1,
    PPS_RPD14_U4RTS 	 = 2,
    PPS_RPD14_SDO1 	 = 5,
    PPS_RPD14_SDO2 	 = 6,
    PPS_RPD14_SDO3 	 = 7,
    PPS_RPD14_SDO5 	 = 9,
    PPS_RPD14_SS6 	 = 10,
    PPS_RPD14_OC3 	 = 11,
    PPS_RPD14_OC6 	 = 12,
    PPS_RPD14_REFCLKO4 	 = 13,
    PPS_RPD14_C2OUT 	 = 14,
    PPS_RPD14_C1TX 	 = 15,
};
enum PPS_RPG1{
    PPS_RPG1_NoConnect 	 = 0,
    PPS_RPG1_U3TX 	 = 1,
    PPS_RPG1_U4RTS 	 = 2,
    PPS_RPG1_SDO1 	 = 5,
    PPS_RPG1_SDO2 	 = 6,
    PPS_RPG1_SDO3 	 = 7,
    PPS_RPG1_SDO5 	 = 9,
    PPS_RPG1_SS6 	 = 10,
    PPS_RPG1_OC3 	 = 11,
    PPS_RPG1_OC6 	 = 12,
    PPS_RPG1_REFCLKO4 	 = 13,
    PPS_RPG1_C2OUT 	 = 14,
    PPS_RPG1_C1TX 	 = 15,
};
enum PPS_RPA14{
    PPS_RPA14_NoConnect 	 = 0,
    PPS_RPA14_U3TX 	 = 1,
    PPS_RPA14_U4RTS 	 = 2,
    PPS_RPA14_SDO1 	 = 5,
    PPS_RPA14_SDO2 	 = 6,
    PPS_RPA14_SDO3 	 = 7,
    PPS_RPA14_SDO5 	 = 9,
    PPS_RPA14_SS6 	 = 10,
    PPS_RPA14_OC3 	 = 11,
    PPS_RPA14_OC6 	 = 12,
    PPS_RPA14_REFCLKO4 	 = 13,
    PPS_RPA14_C2OUT 	 = 14,
    PPS_RPA14_C1TX 	 = 15,
};
enum PPS_RPD6{
    PPS_RPD6_NoConnect 	 = 0,
    PPS_RPD6_U3TX 	 = 1,
    PPS_RPD6_U4RTS 	 = 2,
    PPS_RPD6_SDO1 	 = 5,
    PPS_RPD6_SDO2 	 = 6,
    PPS_RPD6_SDO3 	 = 7,
    PPS_RPD6_SDO5 	 = 9,
    PPS_RPD6_SS6 	 = 10,
    PPS_RPD6_OC3 	 = 11,
    PPS_RPD6_OC6 	 = 12,
    PPS_RPD6_REFCLKO4 	 = 13,
    PPS_RPD6_C2OUT 	 = 14,
    PPS_RPD6_C1TX 	 = 15,
};
enum PPS_RPD3{
    PPS_RPD3_NoConnect 	 = 0,
    PPS_RPD3_U1TX 	 = 1,
    PPS_RPD3_U2RTS 	 = 2,
    PPS_RPD3_U5TX 	 = 3,
    PPS_RPD3_U6RTS 	 = 4,
    PPS_RPD3_SDO1 	 = 5,
    PPS_RPD3_SDO2 	 = 6,
    PPS_RPD3_SDO3 	 = 7,
    PPS_RPD3_SDO4 	 = 8,
    PPS_RPD3_SDO5 	 = 9,
    PPS_RPD3_OC4 	 = 11,
    PPS_RPD3_OC7 	 = 12,
    PPS_RPD3_REFCLKO1 	 = 15,
};
enum PPS_RPG7{
    PPS_RPG7_NoConnect 	 = 0,
    PPS_RPG7_U1TX 	 = 1,
    PPS_RPG7_U2RTS 	 = 2,
    PPS_RPG7_U5TX 	 = 3,
    PPS_RPG7_U6RTS 	 = 4,
    PPS_RPG7_SDO1 	 = 5,
    PPS_RPG7_SDO2 	 = 6,
    PPS_RPG7_SDO3 	 = 7,
    PPS_RPG7_SDO4 	 = 8,
    PPS_RPG7_SDO5 	 = 9,
    PPS_RPG7_OC4 	 = 11,
    PPS_RPG7_OC7 	 = 12,
    PPS_RPG7_REFCLKO1 	 = 15,
};
enum PPS_RPF5{
    PPS_RPF5_NoConnect 	 = 0,
    PPS_RPF5_U1TX 	 = 1,
    PPS_RPF5_U2RTS 	 = 2,
    PPS_RPF5_U5TX 	 = 3,
    PPS_RPF5_U6RTS 	 = 4,
    PPS_RPF5_SDO1 	 = 5,
    PPS_RPF5_SDO2 	 = 6,
    PPS_RPF5_SDO3 	 = 7,
    PPS_RPF5_SDO4 	 = 8,
    PPS_RPF5_SDO5 	 = 9,
    PPS_RPF5_OC4 	 = 11,
    PPS_RPF5_OC7 	 = 12,
    PPS_RPF5_REFCLKO1 	 = 15,
};
enum PPS_RPD11{
    PPS_RPD11_NoConnect 	 = 0,
    PPS_RPD11_U1TX 	 = 1,
    PPS_RPD11_U2RTS 	 = 2,
    PPS_RPD11_U5TX 	 = 3,
    PPS_RPD11_U6RTS 	 = 4,
    PPS_RPD11_SDO1 	 = 5,
    PPS_RPD11_SDO2 	 = 6,
    PPS_RPD11_SDO3 	 = 7,
    PPS_RPD11_SDO4 	 = 8,
    PPS_RPD11_SDO5 	 = 9,
    PPS_RPD11_OC4 	 = 11,
    PPS_RPD11_OC7 	 = 12,
    PPS_RPD11_REFCLKO1 	 = 15,
};
enum PPS_RPF0{
    PPS_RPF0_NoConnect 	 = 0,
    PPS_RPF0_U1TX 	 = 1,
    PPS_RPF0_U2RTS 	 = 2,
    PPS_RPF0_U5TX 	 = 3,
    PPS_RPF0_U6RTS 	 = 4,
    PPS_RPF0_SDO1 	 = 5,
    PPS_RPF0_SDO2 	 = 6,
    PPS_RPF0_SDO3 	 = 7,
    PPS_RPF0_SDO4 	 = 8,
    PPS_RPF0_SDO5 	 = 9,
    PPS_RPF0_OC4 	 = 11,
    PPS_RPF0_OC7 	 = 12,
    PPS_RPF0_REFCLKO1 	 = 15,
};
enum PPS_RPB1{
    PPS_RPB1_NoConnect 	 = 0,
    PPS_RPB1_U1TX 	 = 1,
    PPS_RPB1_U2RTS 	 = 2,
    PPS_RPB1_U5TX 	 = 3,
    PPS_RPB1_U6RTS 	 = 4,
    PPS_RPB1_SDO1 	 = 5,
    PPS_RPB1_SDO2 	 = 6,
    PPS_RPB1_SDO3 	 = 7,
    PPS_RPB1_SDO4 	 = 8,
    PPS_RPB1_SDO5 	 = 9,
    PPS_RPB1_OC4 	 = 11,
    PPS_RPB1_OC7 	 = 12,
    PPS_RPB1_REFCLKO1 	 = 15,
};
enum PPS_RPE5{
    PPS_RPE5_NoConnect 	 = 0,
    PPS_RPE5_U1TX 	 = 1,
    PPS_RPE5_U2RTS 	 = 2,
    PPS_RPE5_U5TX 	 = 3,
    PPS_RPE5_U6RTS 	 = 4,
    PPS_RPE5_SDO1 	 = 5,
    PPS_RPE5_SDO2 	 = 6,
    PPS_RPE5_SDO3 	 = 7,
    PPS_RPE5_SDO4 	 = 8,
    PPS_RPE5_SDO5 	 = 9,
    PPS_RPE5_OC4 	 = 11,
    PPS_RPE5_OC7 	 = 12,
    PPS_RPE5_REFCLKO1 	 = 15,
};
enum PPS_RPC13{
    PPS_RPC13_NoConnect 	 = 0,
    PPS_RPC13_U1TX 	 = 1,
    PPS_RPC13_U2RTS 	 = 2,
    PPS_RPC13_U5TX 	 = 3,
    PPS_RPC13_U6RTS 	 = 4,
    PPS_RPC13_SDO1 	 = 5,
    PPS_RPC13_SDO2 	 = 6,
    PPS_RPC13_SDO3 	 = 7,
    PPS_RPC13_SDO4 	 = 8,
    PPS_RPC13_SDO5 	 = 9,
    PPS_RPC13_OC4 	 = 11,
    PPS_RPC13_OC7 	 = 12,
    PPS_RPC13_REFCLKO1 	 = 15,
};
enum PPS_RPB3{
    PPS_RPB3_NoConnect 	 = 0,
    PPS_RPB3_U1TX 	 = 1,
    PPS_RPB3_U2RTS 	 = 2,
    PPS_RPB3_U5TX 	 = 3,
    PPS_RPB3_U6RTS 	 = 4,
    PPS_RPB3_SDO1 	 = 5,
    PPS_RPB3_SDO2 	 = 6,
    PPS_RPB3_SDO3 	 = 7,
    PPS_RPB3_SDO4 	 = 8,
    PPS_RPB3_SDO5 	 = 9,
    PPS_RPB3_OC4 	 = 11,
    PPS_RPB3_OC7 	 = 12,
    PPS_RPB3_REFCLKO1 	 = 15,
};
enum PPS_RPC4{
    PPS_RPC4_NoConnect 	 = 0,
    PPS_RPC4_U1TX 	 = 1,
    PPS_RPC4_U2RTS 	 = 2,
    PPS_RPC4_U5TX 	 = 3,
    PPS_RPC4_U6RTS 	 = 4,
    PPS_RPC4_SDO1 	 = 5,
    PPS_RPC4_SDO2 	 = 6,
    PPS_RPC4_SDO3 	 = 7,
    PPS_RPC4_SDO4 	 = 8,
    PPS_RPC4_SDO5 	 = 9,
    PPS_RPC4_OC4 	 = 11,
    PPS_RPC4_OC7 	 = 12,
    PPS_RPC4_REFCLKO1 	 = 15,
};
enum PPS_RPD15{
    PPS_RPD15_NoConnect 	 = 0,
    PPS_RPD15_U1TX 	 = 1,
    PPS_RPD15_U2RTS 	 = 2,
    PPS_RPD15_U5TX 	 = 3,
    PPS_RPD15_U6RTS 	 = 4,
    PPS_RPD15_SDO1 	 = 5,
    PPS_RPD15_SDO2 	 = 6,
    PPS_RPD15_SDO3 	 = 7,
    PPS_RPD15_SDO4 	 = 8,
    PPS_RPD15_SDO5 	 = 9,
    PPS_RPD15_OC4 	 = 11,
    PPS_RPD15_OC7 	 = 12,
    PPS_RPD15_REFCLKO1 	 = 15,
};
enum PPS_RPG0{
    PPS_RPG0_NoConnect 	 = 0,
    PPS_RPG0_U1TX 	 = 1,
    PPS_RPG0_U2RTS 	 = 2,
    PPS_RPG0_U5TX 	 = 3,
    PPS_RPG0_U6RTS 	 = 4,
    PPS_RPG0_SDO1 	 = 5,
    PPS_RPG0_SDO2 	 = 6,
    PPS_RPG0_SDO3 	 = 7,
    PPS_RPG0_SDO4 	 = 8,
    PPS_RPG0_SDO5 	 = 9,
    PPS_RPG0_OC4 	 = 11,
    PPS_RPG0_OC7 	 = 12,
    PPS_RPG0_REFCLKO1 	 = 15,
};
enum PPS_RPA15{
    PPS_RPA15_NoConnect 	 = 0,
    PPS_RPA15_U1TX 	 = 1,
    PPS_RPA15_U2RTS 	 = 2,
    PPS_RPA15_U5TX 	 = 3,
    PPS_RPA15_U6RTS 	 = 4,
    PPS_RPA15_SDO1 	 = 5,
    PPS_RPA15_SDO2 	 = 6,
    PPS_RPA15_SDO3 	 = 7,
    PPS_RPA15_SDO4 	 = 8,
    PPS_RPA15_SDO5 	 = 9,
    PPS_RPA15_OC4 	 = 11,
    PPS_RPA15_OC7 	 = 12,
    PPS_RPA15_REFCLKO1 	 = 15,
};
enum PPS_RPD7{
    PPS_RPD7_NoConnect 	 = 0,
    PPS_RPD7_U1TX 	 = 1,
    PPS_RPD7_U2RTS 	 = 2,
    PPS_RPD7_U5TX 	 = 3,
    PPS_RPD7_U6RTS 	 = 4,
    PPS_RPD7_SDO1 	 = 5,
    PPS_RPD7_SDO2 	 = 6,
    PPS_RPD7_SDO3 	 = 7,
    PPS_RPD7_SDO4 	 = 8,
    PPS_RPD7_SDO5 	 = 9,
    PPS_RPD7_OC4 	 = 11,
    PPS_RPD7_OC7 	 = 12,
    PPS_RPD7_REFCLKO1 	 = 15,
};
enum PPS_RPD9{
    PPS_RPD9_NoConnect 	 = 0,
    PPS_RPD9_U3RTS 	 = 1,
    PPS_RPD9_U4TX 	 = 2,
    PPS_RPD9_U6TX 	 = 4,
    PPS_RPD9_SS1 	 = 5,
    PPS_RPD9_SS3 	 = 7,
    PPS_RPD9_SS4 	 = 8,
    PPS_RPD9_SS5 	 = 9,
    PPS_RPD9_SDO6 	 = 10,
    PPS_RPD9_OC5 	 = 11,
    PPS_RPD9_OC8 	 = 12,
    PPS_RPD9_C1OUT 	 = 14,
    PPS_RPD9_REFCLKO3 	 = 15,
};
enum PPS_RPG6{
    PPS_RPG6_NoConnect 	 = 0,
    PPS_RPG6_U3RTS 	 = 1,
    PPS_RPG6_U4TX 	 = 2,
    PPS_RPG6_U6TX 	 = 4,
    PPS_RPG6_SS1 	 = 5,
    PPS_RPG6_SS3 	 = 7,
    PPS_RPG6_SS4 	 = 8,
    PPS_RPG6_SS5 	 = 9,
    PPS_RPG6_SDO6 	 = 10,
    PPS_RPG6_OC5 	 = 11,
    PPS_RPG6_OC8 	 = 12,
    PPS_RPG6_C1OUT 	 = 14,
    PPS_RPG6_REFCLKO3 	 = 15,
};
enum PPS_RPB8{
    PPS_RPB8_NoConnect 	 = 0,
    PPS_RPB8_U3RTS 	 = 1,
    PPS_RPB8_U4TX 	 = 2,
    PPS_RPB8_U6TX 	 = 4,
    PPS_RPB8_SS1 	 = 5,
    PPS_RPB8_SS3 	 = 7,
    PPS_RPB8_SS4 	 = 8,
    PPS_RPB8_SS5 	 = 9,
    PPS_RPB8_SDO6 	 = 10,
    PPS_RPB8_OC5 	 = 11,
    PPS_RPB8_OC8 	 = 12,
    PPS_RPB8_C1OUT 	 = 14,
    PPS_RPB8_REFCLKO3 	 = 15,
};
enum PPS_RPB15{
    PPS_RPB15_NoConnect 	 = 0,
    PPS_RPB15_U3RTS 	 = 1,
    PPS_RPB15_U4TX 	 = 2,
    PPS_RPB15_U6TX 	 = 4,
    PPS_RPB15_SS1 	 = 5,
    PPS_RPB15_SS3 	 = 7,
    PPS_RPB15_SS4 	 = 8,
    PPS_RPB15_SS5 	 = 9,
    PPS_RPB15_SDO6 	 = 10,
    PPS_RPB15_OC5 	 = 11,
    PPS_RPB15_OC8 	 = 12,
    PPS_RPB15_C1OUT 	 = 14,
    PPS_RPB15_REFCLKO3 	 = 15,
};
enum PPS_RPD4{
    PPS_RPD4_NoConnect 	 = 0,
    PPS_RPD4_U3RTS 	 = 1,
    PPS_RPD4_U4TX 	 = 2,
    PPS_RPD4_U6TX 	 = 4,
    PPS_RPD4_SS1 	 = 5,
    PPS_RPD4_SS3 	 = 7,
    PPS_RPD4_SS4 	 = 8,
    PPS_RPD4_SS5 	 = 9,
    PPS_RPD4_SDO6 	 = 10,
    PPS_RPD4_OC5 	 = 11,
    PPS_RPD4_OC8 	 = 12,
    PPS_RPD4_C1OUT 	 = 14,
    PPS_RPD4_REFCLKO3 	 = 15,
};
enum PPS_RPB0{
    PPS_RPB0_NoConnect 	 = 0,
    PPS_RPB0_U3RTS 	 = 1,
    PPS_RPB0_U4TX 	 = 2,
    PPS_RPB0_U6TX 	 = 4,
    PPS_RPB0_SS1 	 = 5,
    PPS_RPB0_SS3 	 = 7,
    PPS_RPB0_SS4 	 = 8,
    PPS_RPB0_SS5 	 = 9,
    PPS_RPB0_SDO6 	 = 10,
    PPS_RPB0_OC5 	 = 11,
    PPS_RPB0_OC8 	 = 12,
    PPS_RPB0_C1OUT 	 = 14,
    PPS_RPB0_REFCLKO3 	 = 15,
};
enum PPS_RPE3{
    PPS_RPE3_NoConnect 	 = 0,
    PPS_RPE3_U3RTS 	 = 1,
    PPS_RPE3_U4TX 	 = 2,
    PPS_RPE3_U6TX 	 = 4,
    PPS_RPE3_SS1 	 = 5,
    PPS_RPE3_SS3 	 = 7,
    PPS_RPE3_SS4 	 = 8,
    PPS_RPE3_SS5 	 = 9,
    PPS_RPE3_SDO6 	 = 10,
    PPS_RPE3_OC5 	 = 11,
    PPS_RPE3_OC8 	 = 12,
    PPS_RPE3_C1OUT 	 = 14,
    PPS_RPE3_REFCLKO3 	 = 15,
};
enum PPS_RPB7{
    PPS_RPB7_NoConnect 	 = 0,
    PPS_RPB7_U3RTS 	 = 1,
    PPS_RPB7_U4TX 	 = 2,
    PPS_RPB7_U6TX 	 = 4,
    PPS_RPB7_SS1 	 = 5,
    PPS_RPB7_SS3 	 = 7,
    PPS_RPB7_SS4 	 = 8,
    PPS_RPB7_SS5 	 = 9,
    PPS_RPB7_SDO6 	 = 10,
    PPS_RPB7_OC5 	 = 11,
    PPS_RPB7_OC8 	 = 12,
    PPS_RPB7_C1OUT 	 = 14,
    PPS_RPB7_REFCLKO3 	 = 15,
};
enum PPS_RPF12{
    PPS_RPF12_NoConnect 	 = 0,
    PPS_RPF12_U3RTS 	 = 1,
    PPS_RPF12_U4TX 	 = 2,
    PPS_RPF12_U6TX 	 = 4,
    PPS_RPF12_SS1 	 = 5,
    PPS_RPF12_SS3 	 = 7,
    PPS_RPF12_SS4 	 = 8,
    PPS_RPF12_SS5 	 = 9,
    PPS_RPF12_SDO6 	 = 10,
    PPS_RPF12_OC5 	 = 11,
    PPS_RPF12_OC8 	 = 12,
    PPS_RPF12_C1OUT 	 = 14,
    PPS_RPF12_REFCLKO3 	 = 15,
};
enum PPS_RPD12{
    PPS_RPD12_NoConnect 	 = 0,
    PPS_RPD12_U3RTS 	 = 1,
    PPS_RPD12_U4TX 	 = 2,
    PPS_RPD12_U6TX 	 = 4,
    PPS_RPD12_SS1 	 = 5,
    PPS_RPD12_SS3 	 = 7,
    PPS_RPD12_SS4 	 = 8,
    PPS_RPD12_SS5 	 = 9,
    PPS_RPD12_SDO6 	 = 10,
    PPS_RPD12_OC5 	 = 11,
    PPS_RPD12_OC8 	 = 12,
    PPS_RPD12_C1OUT 	 = 14,
    PPS_RPD12_REFCLKO3 	 = 15,
};
enum PPS_RPF8{
    PPS_RPF8_NoConnect 	 = 0,
    PPS_RPF8_U3RTS 	 = 1,
    PPS_RPF8_U4TX 	 = 2,
    PPS_RPF8_U6TX 	 = 4,
    PPS_RPF8_SS1 	 = 5,
    PPS_RPF8_SS3 	 = 7,
    PPS_RPF8_SS4 	 = 8,
    PPS_RPF8_SS5 	 = 9,
    PPS_RPF8_SDO6 	 = 10,
    PPS_RPF8_OC5 	 = 11,
    PPS_RPF8_OC8 	 = 12,
    PPS_RPF8_C1OUT 	 = 14,
    PPS_RPF8_REFCLKO3 	 = 15,
};
enum PPS_RPC3{
    PPS_RPC3_NoConnect 	 = 0,
    PPS_RPC3_U3RTS 	 = 1,
    PPS_RPC3_U4TX 	 = 2,
    PPS_RPC3_U6TX 	 = 4,
    PPS_RPC3_SS1 	 = 5,
    PPS_RPC3_SS3 	 = 7,
    PPS_RPC3_SS4 	 = 8,
    PPS_RPC3_SS5 	 = 9,
    PPS_RPC3_SDO6 	 = 10,
    PPS_RPC3_OC5 	 = 11,
    PPS_RPC3_OC8 	 = 12,
    PPS_RPC3_C1OUT 	 = 14,
    PPS_RPC3_REFCLKO3 	 = 15,
};
enum PPS_RPE9{
    PPS_RPE9_NoConnect 	 = 0,
    PPS_RPE9_U3RTS 	 = 1,
    PPS_RPE9_U4TX 	 = 2,
    PPS_RPE9_U6TX 	 = 4,
    PPS_RPE9_SS1 	 = 5,
    PPS_RPE9_SS3 	 = 7,
    PPS_RPE9_SS4 	 = 8,
    PPS_RPE9_SS5 	 = 9,
    PPS_RPE9_SDO6 	 = 10,
    PPS_RPE9_OC5 	 = 11,
    PPS_RPE9_OC8 	 = 12,
    PPS_RPE9_C1OUT 	 = 14,
    PPS_RPE9_REFCLKO3 	 = 15,
};
enum PPS_RPD1{
    PPS_RPD1_NoConnect 	 = 0,
    PPS_RPD1_U1RTS 	 = 1,
    PPS_RPD1_U2TX 	 = 2,
    PPS_RPD1_U5RTS 	 = 3,
    PPS_RPD1_U6TX 	 = 4,
    PPS_RPD1_SS2 	 = 6,
    PPS_RPD1_SDO4 	 = 8,
    PPS_RPD1_SDO6 	 = 10,
    PPS_RPD1_OC2 	 = 11,
    PPS_RPD1_OC1 	 = 12,
    PPS_RPD1_OC9 	 = 13,
    PPS_RPD1_C2TX 	 = 15,
};
enum PPS_RPG9{
    PPS_RPG9_NoConnect 	 = 0,
    PPS_RPG9_U1RTS 	 = 1,
    PPS_RPG9_U2TX 	 = 2,
    PPS_RPG9_U5RTS 	 = 3,
    PPS_RPG9_U6TX 	 = 4,
    PPS_RPG9_SS2 	 = 6,
    PPS_RPG9_SDO4 	 = 8,
    PPS_RPG9_SDO6 	 = 10,
    PPS_RPG9_OC2 	 = 11,
    PPS_RPG9_OC1 	 = 12,
    PPS_RPG9_OC9 	 = 13,
    PPS_RPG9_C2TX 	 = 15,
};
enum PPS_RPB14{
    PPS_RPB14_NoConnect 	 = 0,
    PPS_RPB14_U1RTS 	 = 1,
    PPS_RPB14_U2TX 	 = 2,
    PPS_RPB14_U5RTS 	 = 3,
    PPS_RPB14_U6TX 	 = 4,
    PPS_RPB14_SS2 	 = 6,
    PPS_RPB14_SDO4 	 = 8,
    PPS_RPB14_SDO6 	 = 10,
    PPS_RPB14_OC2 	 = 11,
    PPS_RPB14_OC1 	 = 12,
    PPS_RPB14_OC9 	 = 13,
    PPS_RPB14_C2TX 	 = 15,
};
enum PPS_RPD0{
    PPS_RPD0_NoConnect 	 = 0,
    PPS_RPD0_U1RTS 	 = 1,
    PPS_RPD0_U2TX 	 = 2,
    PPS_RPD0_U5RTS 	 = 3,
    PPS_RPD0_U6TX 	 = 4,
    PPS_RPD0_SS2 	 = 6,
    PPS_RPD0_SDO4 	 = 8,
    PPS_RPD0_SDO6 	 = 10,
    PPS_RPD0_OC2 	 = 11,
    PPS_RPD0_OC1 	 = 12,
    PPS_RPD0_OC9 	 = 13,
    PPS_RPD0_C2TX 	 = 15,
};
enum PPS_RPB6{
    PPS_RPB6_NoConnect 	 = 0,
    PPS_RPB6_U1RTS 	 = 1,
    PPS_RPB6_U2TX 	 = 2,
    PPS_RPB6_U5RTS 	 = 3,
    PPS_RPB6_U6TX 	 = 4,
    PPS_RPB6_SS2 	 = 6,
    PPS_RPB6_SDO4 	 = 8,
    PPS_RPB6_SDO6 	 = 10,
    PPS_RPB6_OC2 	 = 11,
    PPS_RPB6_OC1 	 = 12,
    PPS_RPB6_OC9 	 = 13,
    PPS_RPB6_C2TX 	 = 15,
};
enum PPS_RPD5{
    PPS_RPD5_NoConnect 	 = 0,
    PPS_RPD5_U1RTS 	 = 1,
    PPS_RPD5_U2TX 	 = 2,
    PPS_RPD5_U5RTS 	 = 3,
    PPS_RPD5_U6TX 	 = 4,
    PPS_RPD5_SS2 	 = 6,
    PPS_RPD5_SDO4 	 = 8,
    PPS_RPD5_SDO6 	 = 10,
    PPS_RPD5_OC2 	 = 11,
    PPS_RPD5_OC1 	 = 12,
    PPS_RPD5_OC9 	 = 13,
    PPS_RPD5_C2TX 	 = 15,
};
enum PPS_RPB2{
    PPS_RPB2_NoConnect 	 = 0,
    PPS_RPB2_U1RTS 	 = 1,
    PPS_RPB2_U2TX 	 = 2,
    PPS_RPB2_U5RTS 	 = 3,
    PPS_RPB2_U6TX 	 = 4,
    PPS_RPB2_SS2 	 = 6,
    PPS_RPB2_SDO4 	 = 8,
    PPS_RPB2_SDO6 	 = 10,
    PPS_RPB2_OC2 	 = 11,
    PPS_RPB2_OC1 	 = 12,
    PPS_RPB2_OC9 	 = 13,
    PPS_RPB2_C2TX 	 = 15,
};
enum PPS_RPF3{
    PPS_RPF3_NoConnect 	 = 0,
    PPS_RPF3_U1RTS 	 = 1,
    PPS_RPF3_U2TX 	 = 2,
    PPS_RPF3_U5RTS 	 = 3,
    PPS_RPF3_U6TX 	 = 4,
    PPS_RPF3_SS2 	 = 6,
    PPS_RPF3_SDO4 	 = 8,
    PPS_RPF3_SDO6 	 = 10,
    PPS_RPF3_OC2 	 = 11,
    PPS_RPF3_OC1 	 = 12,
    PPS_RPF3_OC9 	 = 13,
    PPS_RPF3_C2TX 	 = 15,
};
enum PPS_RPF13{
    PPS_RPF13_NoConnect 	 = 0,
    PPS_RPF13_U1RTS 	 = 1,
    PPS_RPF13_U2TX 	 = 2,
    PPS_RPF13_U5RTS 	 = 3,
    PPS_RPF13_U6TX 	 = 4,
    PPS_RPF13_SS2 	 = 6,
    PPS_RPF13_SDO4 	 = 8,
    PPS_RPF13_SDO6 	 = 10,
    PPS_RPF13_OC2 	 = 11,
    PPS_RPF13_OC1 	 = 12,
    PPS_RPF13_OC9 	 = 13,
    PPS_RPF13_C2TX 	 = 15,
};
enum PPS_RPC2{
    PPS_RPC2_NoConnect 	 = 0,
    PPS_RPC2_U1RTS 	 = 1,
    PPS_RPC2_U2TX 	 = 2,
    PPS_RPC2_U5RTS 	 = 3,
    PPS_RPC2_U6TX 	 = 4,
    PPS_RPC2_SS2 	 = 6,
    PPS_RPC2_SDO4 	 = 8,
    PPS_RPC2_SDO6 	 = 10,
    PPS_RPC2_OC2 	 = 11,
    PPS_RPC2_OC1 	 = 12,
    PPS_RPC2_OC9 	 = 13,
    PPS_RPC2_C2TX 	 = 15,
};
enum PPS_RPE8{
    PPS_RPE8_NoConnect 	 = 0,
    PPS_RPE8_U1RTS 	 = 1,
    PPS_RPE8_U2TX 	 = 2,
    PPS_RPE8_U5RTS 	 = 3,
    PPS_RPE8_U6TX 	 = 4,
    PPS_RPE8_SS2 	 = 6,
    PPS_RPE8_SDO4 	 = 8,
    PPS_RPE8_SDO6 	 = 10,
    PPS_RPE8_OC2 	 = 11,
    PPS_RPE8_OC1 	 = 12,
    PPS_RPE8_OC9 	 = 13,
    PPS_RPE8_C2TX 	 = 15,
};
enum PPS_RPF2{
    PPS_RPF2_NoConnect 	 = 0,
    PPS_RPF2_U1RTS 	 = 1,
    PPS_RPF2_U2TX 	 = 2,
    PPS_RPF2_U5RTS 	 = 3,
    PPS_RPF2_U6TX 	 = 4,
    PPS_RPF2_SS2 	 = 6,
    PPS_RPF2_SDO4 	 = 8,
    PPS_RPF2_SDO6 	 = 10,
    PPS_RPF2_OC2 	 = 11,
    PPS_RPF2_OC1 	 = 12,
    PPS_RPF2_OC9 	 = 13,
    PPS_RPF2_C2TX 	 = 15,
};


/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void PPS_pin_mapping(PPS_Register reg, PPS_AlternateFunction af);

#ifdef __cplusplus
}
#endif
#endif //PPS_H
