/*
* undefs.h
*
* Created: 1/20/2018 2:33:14 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/


#ifndef BASICS_UNDEFS_H_
#define BASICS_UNDEFS_H_

#include <avr/io.h>

/***** PORTA *****/
#ifdef PA0
        #undef  PA0
        #define PA0	0
#endif // PA0

#ifdef PA1
        #undef  PA1
        #define PA1	1
#endif // PA1

#ifdef PA2
        #undef  PA2
        #define PA2	2
#endif // PA2

#ifdef PA3
        #undef  PA3
        #define PA3	3
#endif // PA3

#ifdef PA4
        #undef  PA4
        #define PA4	4
#endif // PA4

#ifdef PA5
        #undef  PA5
        #define PA5	5
#endif // PA5

#ifdef PA6
        #undef  PA6
        #define PA6	6
#endif // PA6

#ifdef PA7
        #undef  PA7
        #define PA7	7
#endif // PA7


/***** PORTB *****/
#ifdef PB0
        #undef  PB0
        #define PB0	8
#endif // PB0

#ifdef PB1
        #undef  PB1
        #define PB1	9
#endif // PB1

#ifdef PB2
        #undef  PB2
        #define PB2	10
#endif // PB2

#ifdef PB3
        #undef  PB3
        #define PB3	11
#endif // PB3

#ifdef PB4
        #undef  PB4
        #define PB4	12
#endif // PB4

#ifdef PB5
        #undef  PB5
        #define PB5	13
#endif // PB5

#ifdef PB6
        #undef  PB6
        #define PB6	14
#endif // PB6

#ifdef PB7
        #undef  PB7
        #define PB7	15
#endif // PB7


/***** PORTC *****/
#ifdef PC0
        #undef  PC0
        #define PC0	16
#endif // PC0

#ifdef PC1
        #undef  PC1
        #define PC1	17
#endif // PC1

#ifdef PC2
        #undef  PC2
        #define PC2	18
#endif // PC2

#ifdef PC3
        #undef  PC3
        #define PC3	19
#endif // PC3

#ifdef PC4
        #undef  PC4
        #define PC4	20
#endif // PC4

#ifdef PC5
        #undef  PC5
        #define PC5	21
#endif // PC5

#ifdef PC6
        #undef  PC6
        #define PC6	22
#endif // PC6

#ifdef PC7
        #undef  PC7
        #define PC7	23
#endif // PC7


/***** PORTD *****/
#ifdef PD0
        #undef  PD0
        #define PD0	24
#endif // PD0

#ifdef PD1
        #undef  PD1
        #define PD1	25
#endif // PD1

#ifdef PD2
        #undef  PD2
        #define PD2	26
#endif // PD2

#ifdef PD3
        #undef  PD3
        #define PD3	27
#endif // PD3

#ifdef PD4
        #undef  PD4
        #define PD4	28
#endif // PD4

#ifdef PD5
        #undef  PD5
        #define PD5	29
#endif // PD5

#ifdef PD6
        #undef  PD6
        #define PD6	30
#endif // PD6

#ifdef PD7
        #undef  PD7
        #define PD7	31
#endif // PD7


/***** PORTE *****/
#ifdef PE0
        #undef  PE0
        #define PE0	32
#endif // PE0

#ifdef PE1
        #undef  PE1
        #define PE1	33
#endif // PE1

#ifdef PE2
        #undef  PE2
        #define PE2	34
#endif // PE2

#ifdef PE3
        #undef  PE3
        #define PE3	35
#endif // PE3

#ifdef PE4
        #undef  PE4
        #define PE4	36
#endif // PE4

#ifdef PE5
        #undef  PE5
        #define PE5	37
#endif // PE5

#ifdef PE6
        #undef  PE6
        #define PE6	38
#endif // PE6

#ifdef PE7
        #undef  PE7
        #define PE7	39
#endif // PE7


/***** PORTF *****/
#ifdef PF0
        #undef  PF0
        #define PF0	40
#endif // PF0

#ifdef PF1
        #undef  PF1
        #define PF1	41
#endif // PF1

#ifdef PF2
        #undef  PF2
        #define PF2	42
#endif // PF2

#ifdef PF3
        #undef  PF3
        #define PF3	43
#endif // PF3

#ifdef PF4
        #undef  PF4
        #define PF4	44
#endif // PF4

#ifdef PF5
        #undef  PF5
        #define PF5	45
#endif // PF5

#ifdef PF6
        #undef  PF6
        #define PF6	46
#endif // PF6

#ifdef PF7
        #undef  PF7
        #define PF7	47
#endif // PF7


/***** PORTG *****/
#ifdef PG0
        #undef  PG0
        #define PG0	48
#endif // PG0

#ifdef PG1
        #undef  PG1
        #define PG1	49
#endif // PG1

#ifdef PG2
        #undef  PG2
        #define PG2	50
#endif // PG2

#ifdef PG3
        #undef  PG3
        #define PG3	51
#endif // PG3

#ifdef PG4
        #undef  PG4
        #define PG4	52
#endif // PG4

#ifdef PG5
        #undef  PG5
        #define PG5	53
#endif // PG5

#ifdef PG6
        #undef  PG6
        #define PG6	54
#endif // PG6

#ifdef PG7
        #undef  PG7
        #define PG7	55
#endif // PG7


/***** PORTH *****/
#ifdef PH0
        #undef  PH0
        #define PH0	56
#endif // PH0

#ifdef PH1
        #undef  PH1
        #define PH1	57
#endif // PH1

#ifdef PH2
        #undef  PH2
        #define PH2	58
#endif // PH2

#ifdef PH3
        #undef  PH3
        #define PH3	59
#endif // PH3

#ifdef PH4
        #undef  PH4
        #define PH4	60
#endif // PH4

#ifdef PH5
        #undef  PH5
        #define PH5	61
#endif // PH5

#ifdef PH6
        #undef  PH6
        #define PH6	62
#endif // PH6

#ifdef PH7
        #undef  PH7
        #define PH7	63
#endif // PH7


/***** PORTI *****/
#ifdef PI0
        #undef  PI0
        #define PI0	64
#endif // PI0

#ifdef PI1
        #undef  PI1
        #define PI1	65
#endif // PI1

#ifdef PI2
        #undef  PI2
        #define PI2	66
#endif // PI2

#ifdef PI3
        #undef  PI3
        #define PI3	67
#endif // PI3

#ifdef PI4
        #undef  PI4
        #define PI4	68
#endif // PI4

#ifdef PI5
        #undef  PI5
        #define PI5	69
#endif // PI5

#ifdef PI6
        #undef  PI6
        #define PI6	71
#endif // PI6

#ifdef PI7
        #undef  PI7
        #define PI7	71
#endif // PI7


/***** PORTJ *****/
#ifdef PJ0
        #undef  PJ0
        #define PJ0	72
#endif // PJ0

#ifdef PJ1
        #undef  PJ1
        #define PJ1	73
#endif // PJ1

#ifdef PJ2
        #undef  PJ2
        #define PJ2	74
#endif // PJ2

#ifdef PJ3
        #undef  PJ3
        #define PJ3	75
#endif // PJ3

#ifdef PJ4
        #undef  PJ4
        #define PJ4	76
#endif // PJ4

#ifdef PJ5
        #undef  PJ5
        #define PJ5	77
#endif // PJ5

#ifdef PJ6
        #undef  PJ6
        #define PJ6	78
#endif // PJ6

#ifdef PJ7
        #undef  PJ7
        #define PJ7	79
#endif // PJ7


/***** PORTK *****/
#ifdef PK0
        #undef  PK0
        #define PK0	80
#endif // PK0

#ifdef PK1
        #undef  PK1
        #define PK1	81
#endif // PK1

#ifdef PK2
        #undef  PK2
        #define PK2	82
#endif // PK2

#ifdef PK3
        #undef  PK3
        #define PK3	83
#endif // PK3

#ifdef PK4
        #undef  PK4
        #define PK4	84
#endif // PK4

#ifdef PK5
        #undef  PK5
        #define PK5	85
#endif // PK5

#ifdef PK6
        #undef  PK6
        #define PK6	86
#endif // PK6

#ifdef PK7
        #undef  PK7
        #define PK7	87
#endif // PK7


/***** PORTL *****/
#ifdef PL0
        #undef  PL0
        #define PL0	88
#endif // PL0

#ifdef PL1
        #undef  PL1
        #define PL1	89
#endif // PL1

#ifdef PL2
        #undef  PL2
        #define PL2	90
#endif // PL2

#ifdef PL3
        #undef  PL3
        #define PL3	91
#endif // PL3

#ifdef PL4
        #undef  PL4
        #define PL4	92
#endif // PL4

#ifdef PL5
        #undef  PL5
        #define PL5	93
#endif // PL5

#ifdef PL6
        #undef  PL6
        #define PL6	94
#endif // PL6

#ifdef PL7
        #undef  PL7
        #define PL7	95
#endif // PL7


#endif /* BASICS_UNDEFS_H_ */
