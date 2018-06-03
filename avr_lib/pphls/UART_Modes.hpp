/*
 * UART_Modes.hpp
 *
 * Created: 3/6/2018 7:24:31 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */

#pragma once

#include "UART_Params.hpp"
#include "dtypes/Queue.hpp"

namespace UART {

        class Polling_Mode
        {
        protected:
                Polling_Mode() { }

                inline u8 initialize(const UART_Params & u) const {
                        *(u.ucsrb_) |= (1 << UART::rx_en)
                                    |  (1 << UART::tx_en);
                        return 0;
                }

                inline u8 receive(const UART_Params & u) {
                        while( !(*(u.ucsra_) & _BV(UART::rxc)) );
                        return *(u.udr_);
                }

                inline u8 transmit(const UART_Params & u, const char c) {
                        while( !(*(u.ucsra_) & _BV(UART::udre)) );
                        *(u.udr_) = c;
                        return 0;
                }

        private:
                Polling_Mode( const Polling_Mode & ) = delete;
                Polling_Mode& operator=( const Polling_Mode & ) = delete;
        };


        class Interrupt_Mode
        {
        // Variables
        private:
                Queue<u8, UART::buf_size_t, UART::tx_buf_size> tx_queue_;

                Queue<u8, UART::buf_size_t, UART::rx_buf_size> rx_queue_;
        // Member Functions
        protected:
                Interrupt_Mode():
                tx_queue_(), rx_queue_() { }

                inline u8 initialize(const UART_Params & u) const {
                        *(u.ucsrb_) |= _BV(UART::rxcie)
                                    |  _BV(UART::rx_en)
                                    |  _BV(UART::tx_en);

                        return 0;
                }

                inline u8 receive(const UART_Params & u) {
                        return rx_queue_.lookup ();
                }

                inline void receive_Irq(const UART_Params & u) {
                        rx_queue_.insert (*(u.udr_));
                }

                inline u8 transmit(const UART_Params & u, const char c) {

                        tx_queue_.insert (c);

                        *(u.ucsrb_) |= _BV(UART::udrie);

                        return 0;
                }

                inline u8 transmit_Irq(const UART_Params & u) {

                        if( tx_queue_.length () )
                                *(u.udr_) = tx_queue_.lookup ();
                        else
                                *(u.ucsrb_) &= ~_BV(UART::udrie);

                        return 0;
                }

        private:
                Interrupt_Mode( const Interrupt_Mode & ) = delete;
                Interrupt_Mode& operator=( const Interrupt_Mode & ) = delete;
        };

}
