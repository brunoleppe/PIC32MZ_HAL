//
// Created by bruno on 25/01/23.
//

#ifndef SYSTEM_H
#define SYSTEM_H
/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define SYS_UNLOCK_IO                       0x0001


#define SYS_PERIPHERAL_CLOCK_1              (0)
#define SYS_PERIPHERAL_CLOCK_2              (1)
#define SYS_PERIPHERAL_CLOCK_3              (2)
#define SYS_PERIPHERAL_CLOCK_4              (3)
#define SYS_PERIPHERAL_CLOCK_5              (4)
#define SYS_PERIPHERAL_CLOCK_6              (5)
#define SYS_PERIPHERAL_CLOCK_7              (6)
#define SYS_PERIPHERAL_CLOCK_8              (7)


/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)


/**********************************************************************
* Function Prototypes
**********************************************************************/


#ifdef __cplusplus
extern "C"{
#endif
void        SYS_initialize();
void        SYS_Unlock(uint32_t flags);
void        SYS_Lock();
void        SYS_peripheral_clock_config(uint32_t clockChannel, uint32_t flags);
uint32_t    SYS_peripheral_clock_frequency_get(uint32_t clockChannel);
void        SYS_soft_reset(uint32_t rconVal);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

#define SYS_PBCLK_ENABLED                   (0)
#define SYS_PBCLK_DISABLED                  (0x0100)
#define SYS_PBCLK_DIVISOR_1				(1)
#define SYS_PBCLK_DIVISOR_2				(2)
#define SYS_PBCLK_DIVISOR_3				(3)
#define SYS_PBCLK_DIVISOR_4				(4)
#define SYS_PBCLK_DIVISOR_5				(5)
#define SYS_PBCLK_DIVISOR_6				(6)
#define SYS_PBCLK_DIVISOR_7				(7)
#define SYS_PBCLK_DIVISOR_8				(8)
#define SYS_PBCLK_DIVISOR_9				(9)
#define SYS_PBCLK_DIVISOR_10				(10)
#define SYS_PBCLK_DIVISOR_11				(11)
#define SYS_PBCLK_DIVISOR_12				(12)
#define SYS_PBCLK_DIVISOR_13				(13)
#define SYS_PBCLK_DIVISOR_14				(14)
#define SYS_PBCLK_DIVISOR_15				(15)
#define SYS_PBCLK_DIVISOR_16				(16)
#define SYS_PBCLK_DIVISOR_17				(17)
#define SYS_PBCLK_DIVISOR_18				(18)
#define SYS_PBCLK_DIVISOR_19				(19)
#define SYS_PBCLK_DIVISOR_20				(20)
#define SYS_PBCLK_DIVISOR_21				(21)
#define SYS_PBCLK_DIVISOR_22				(22)
#define SYS_PBCLK_DIVISOR_23				(23)
#define SYS_PBCLK_DIVISOR_24				(24)
#define SYS_PBCLK_DIVISOR_25				(25)
#define SYS_PBCLK_DIVISOR_26				(26)
#define SYS_PBCLK_DIVISOR_27				(27)
#define SYS_PBCLK_DIVISOR_28				(28)
#define SYS_PBCLK_DIVISOR_29				(29)
#define SYS_PBCLK_DIVISOR_30				(30)
#define SYS_PBCLK_DIVISOR_31				(31)
#define SYS_PBCLK_DIVISOR_32				(32)
#define SYS_PBCLK_DIVISOR_33				(33)
#define SYS_PBCLK_DIVISOR_34				(34)
#define SYS_PBCLK_DIVISOR_35				(35)
#define SYS_PBCLK_DIVISOR_36				(36)
#define SYS_PBCLK_DIVISOR_37				(37)
#define SYS_PBCLK_DIVISOR_38				(38)
#define SYS_PBCLK_DIVISOR_39				(39)
#define SYS_PBCLK_DIVISOR_40				(40)
#define SYS_PBCLK_DIVISOR_41				(41)
#define SYS_PBCLK_DIVISOR_42				(42)
#define SYS_PBCLK_DIVISOR_43				(43)
#define SYS_PBCLK_DIVISOR_44				(44)
#define SYS_PBCLK_DIVISOR_45				(45)
#define SYS_PBCLK_DIVISOR_46				(46)
#define SYS_PBCLK_DIVISOR_47				(47)
#define SYS_PBCLK_DIVISOR_48				(48)
#define SYS_PBCLK_DIVISOR_49				(49)
#define SYS_PBCLK_DIVISOR_50				(50)
#define SYS_PBCLK_DIVISOR_51				(51)
#define SYS_PBCLK_DIVISOR_52				(52)
#define SYS_PBCLK_DIVISOR_53				(53)
#define SYS_PBCLK_DIVISOR_54				(54)
#define SYS_PBCLK_DIVISOR_55				(55)
#define SYS_PBCLK_DIVISOR_56				(56)
#define SYS_PBCLK_DIVISOR_57				(57)
#define SYS_PBCLK_DIVISOR_58				(58)
#define SYS_PBCLK_DIVISOR_59				(59)
#define SYS_PBCLK_DIVISOR_60				(60)
#define SYS_PBCLK_DIVISOR_61				(61)
#define SYS_PBCLK_DIVISOR_62				(62)
#define SYS_PBCLK_DIVISOR_63				(63)
#define SYS_PBCLK_DIVISOR_64				(64)
#define SYS_PBCLK_DIVISOR_65				(65)
#define SYS_PBCLK_DIVISOR_66				(66)
#define SYS_PBCLK_DIVISOR_67				(67)
#define SYS_PBCLK_DIVISOR_68				(68)
#define SYS_PBCLK_DIVISOR_69				(69)
#define SYS_PBCLK_DIVISOR_70				(70)
#define SYS_PBCLK_DIVISOR_71				(71)
#define SYS_PBCLK_DIVISOR_72				(72)
#define SYS_PBCLK_DIVISOR_73				(73)
#define SYS_PBCLK_DIVISOR_74				(74)
#define SYS_PBCLK_DIVISOR_75				(75)
#define SYS_PBCLK_DIVISOR_76				(76)
#define SYS_PBCLK_DIVISOR_77				(77)
#define SYS_PBCLK_DIVISOR_78				(78)
#define SYS_PBCLK_DIVISOR_79				(79)
#define SYS_PBCLK_DIVISOR_80				(80)
#define SYS_PBCLK_DIVISOR_81				(81)
#define SYS_PBCLK_DIVISOR_82				(82)
#define SYS_PBCLK_DIVISOR_83				(83)
#define SYS_PBCLK_DIVISOR_84				(84)
#define SYS_PBCLK_DIVISOR_85				(85)
#define SYS_PBCLK_DIVISOR_86				(86)
#define SYS_PBCLK_DIVISOR_87				(87)
#define SYS_PBCLK_DIVISOR_88				(88)
#define SYS_PBCLK_DIVISOR_89				(89)
#define SYS_PBCLK_DIVISOR_90				(90)
#define SYS_PBCLK_DIVISOR_91				(91)
#define SYS_PBCLK_DIVISOR_92				(92)
#define SYS_PBCLK_DIVISOR_93				(93)
#define SYS_PBCLK_DIVISOR_94				(94)
#define SYS_PBCLK_DIVISOR_95				(95)
#define SYS_PBCLK_DIVISOR_96				(96)
#define SYS_PBCLK_DIVISOR_97				(97)
#define SYS_PBCLK_DIVISOR_98				(98)
#define SYS_PBCLK_DIVISOR_99				(99)
#define SYS_PBCLK_DIVISOR_100				(100)
#define SYS_PBCLK_DIVISOR_101				(101)
#define SYS_PBCLK_DIVISOR_102				(102)
#define SYS_PBCLK_DIVISOR_103				(103)
#define SYS_PBCLK_DIVISOR_104				(104)
#define SYS_PBCLK_DIVISOR_105				(105)
#define SYS_PBCLK_DIVISOR_106				(106)
#define SYS_PBCLK_DIVISOR_107				(107)
#define SYS_PBCLK_DIVISOR_108				(108)
#define SYS_PBCLK_DIVISOR_109				(109)
#define SYS_PBCLK_DIVISOR_110				(110)
#define SYS_PBCLK_DIVISOR_111				(111)
#define SYS_PBCLK_DIVISOR_112				(112)
#define SYS_PBCLK_DIVISOR_113				(113)
#define SYS_PBCLK_DIVISOR_114				(114)
#define SYS_PBCLK_DIVISOR_115				(115)
#define SYS_PBCLK_DIVISOR_116				(116)
#define SYS_PBCLK_DIVISOR_117				(117)
#define SYS_PBCLK_DIVISOR_118				(118)
#define SYS_PBCLK_DIVISOR_119				(119)
#define SYS_PBCLK_DIVISOR_120				(120)
#define SYS_PBCLK_DIVISOR_121				(121)
#define SYS_PBCLK_DIVISOR_122				(122)
#define SYS_PBCLK_DIVISOR_123				(123)
#define SYS_PBCLK_DIVISOR_124				(124)
#define SYS_PBCLK_DIVISOR_125				(125)
#define SYS_PBCLK_DIVISOR_126				(126)
#define SYS_PBCLK_DIVISOR_127				(127)
#define SYS_PBCLK_DIVISOR_128				(128)






#endif //SYSTEM_H
