/*
 * UART_ISRs.hpp
 *
 * Created: 3/8/2018 9:16:36 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */

/** This file should be included at the end of the file containing main routine.
 **
 ** This file contains interrupt routine for the UART communication interface.
 ** So, if the UART is to be used in the interrupt mode, this file should be
 ** absolutely included.
 **/

#ifndef PPHLS_UART_ISRS_HPP_
#define PPHLS_UART_ISRS_HPP_

#include <avr/interrupt.h>

#ifdef UART0_INTERRUPT
ISR(USART0_UDRE_vect)
{
        UART0_INTERRUPT.transmitt_irq ();
}
ISR(USART0_RX_vect)
{
        UART0_INTERRUPT.receive_irq ();
}
#endif // UART0_INTERRUPT

#ifdef UART1_INTERRUPT
ISR(USART1_UDRE_vect)
{
        UART1_INTERRUPT.transmitt_irq ();
}

ISR(USART1_RX_vect)
{
        UART1_INTERRUPT.receive_irq ();
}
#endif // UART1_INTERRUPT

#ifdef UART2_INTERRUPT
ISR(USART2_UDRE_vect)
{
        UART2_INTERRUPT.transmitt_irq ();
}

ISR(USART2_RX_vect)
{
        UART2_INTERRUPT.receive_irq ();
}
#endif // UART2_INTERRUPT

#ifdef UART3_INTERRUPT
ISR(USART3_UDRE_vect)
{
        UART3_INTERRUPT.transmitt_irq ();
}

ISR(USART3_RX_vect)
{
        UART3_INTERRUPT.receive_irq ();
}
#endif // UART3_INTERRUPT


#endif // PPHLS_UART_ISRS_HPP_
