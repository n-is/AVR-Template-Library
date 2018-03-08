#include <inttypes.h>

#include "ExtInt.h"

static void nothing(void) {

}

static volatile voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS] = {
        #if EXTERNAL_NUM_INTERRUPTS > 8
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 7
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 6
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 5
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 4
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 3
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 2
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 1
        nothing,
        #endif
        #if EXTERNAL_NUM_INTERRUPTS > 0
        nothing,
        #endif
};

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
        if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {

                intFunc[interruptNum] = userFunc;

                switch (interruptNum) {
                        case 2:
                        EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
                        EIMSK |= (1 << INT0);
                        break;
                        case 3:
                        EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
                        EIMSK |= (1 << INT1);
                        break;
                        case 4:
                        EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
                        EIMSK |= (1 << INT2);
                        break;
                        case 5:
                        EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
                        EIMSK |= (1 << INT3);
                        break;
                        case 0:
                        EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
                        EIMSK |= (1 << INT4);
                        break;
                        case 1:
                        EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
                        EIMSK |= (1 << INT5);
                        break;
                        case 6:
                        EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
                        EIMSK |= (1 << INT6);
                        break;
                        case 7:
                        EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
                        EIMSK |= (1 << INT7);
                        break;
                }
        }
}

void detachInterrupt(uint8_t interruptNum) {
        if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {

                switch(interruptNum)
                {
                        case 2:
                        EIMSK &= ~(1 << INT0);
                        break;
                        case 3:
                        EIMSK &= ~(1 << INT1);
                        break;
                        case 4:
                        EIMSK &= ~(1 << INT2);
                        break;
                        case 5:
                        EIMSK &= ~(1 << INT3);
                        break;
                        case 0:
                        EIMSK &= ~(1 << INT4);
                        break;
                        case 1:
                        EIMSK &= ~(1 << INT5);
                        break;
                        case 6:
                        EIMSK &= ~(1 << INT6);
                        break;
                        case 7:
                        EIMSK &= ~(1 << INT7);
                        break;
                }
                intFunc[interruptNum] = nothing;
        }
}

ISR(INT0_vect) {
        intFunc[EXTERNAL_INT_2]();
}

ISR(INT1_vect) {
        intFunc[EXTERNAL_INT_3]();
}

ISR(INT2_vect) {
        intFunc[EXTERNAL_INT_4]();
}

ISR(INT3_vect) {
        intFunc[EXTERNAL_INT_5]();
}

ISR(INT4_vect) {
        intFunc[EXTERNAL_INT_0]();
}

ISR(INT5_vect) {
        intFunc[EXTERNAL_INT_1]();
}

ISR(INT6_vect) {
        intFunc[EXTERNAL_INT_6]();
}

ISR(INT7_vect) {
        intFunc[EXTERNAL_INT_7]();
}

