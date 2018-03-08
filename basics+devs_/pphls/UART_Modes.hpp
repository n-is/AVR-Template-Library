/*
 * UART_Modes.hpp
 *
 * Created: 3/6/2018 7:24:31 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef PPHLS_UART_MODES_HPP_
#define PPHLS_UART_MODES_HPP_

#include "UART_Params.hpp"
#include "dtypes/Queue.hpp"

class UART_Modes
{
public:
        ~UART_Modes() { }
        virtual u8 initialize(const UART_Params & u) const = 0;
        virtual u8 receive(const UART_Params & u) = 0;
        virtual u8 transmitt(const UART_Params & u, const u8 c) = 0;
};

namespace UART {

        class Polling_Mode : public UART_Modes
        {
        protected:
                Polling_Mode() { }

                inline u8 initialize(const UART_Params & u) const override {
                        *(u.ucsrb_) |= (1 << UART::rx_en)
                                    |  (1 << UART::tx_en);
                        return 0;
                }

                inline u8 receive(const UART_Params & u) override {
                        while( !(*(u.ucsra_) & _BV(UART::rxc)) );
                        return *(u.udr_);
                }

                inline u8 transmitt(const UART_Params & u, const u8 c)override{
                        while( !(*(u.ucsra_) & _BV(UART::udre)) );
                        *(u.udr_) = c;
                        return 0;
                }

        private:
                Polling_Mode( const Polling_Mode & ) = delete;
                Polling_Mode& operator=( const Polling_Mode & ) = delete;
        };

        class Interrupt_Mode : public UART_Modes
        {
        // Variables
        private:
                volatile u8 tx_elements_;
                Queue<u8, UART::tx_buf_size> tx_queue_;

                volatile u8 rx_elements_;
                Queue<u8, UART::rx_buf_size> rx_queue_;
        // Member Functions
        protected:
                Interrupt_Mode():
                tx_elements_(0), tx_queue_(), rx_elements_(0), rx_queue_() { }

                inline u8 initialize(const UART_Params & u) const override {
                        *(u.ucsrb_) |= _BV(UART::rxcie)
                                    |  _BV(UART::rx_en)
                                    |  _BV(UART::tx_en);

                        return 0;
                }

                inline u8 receive(const UART_Params & u) override {
                        return rx_queue_.lookup ();
                }

                inline void receive_irq(const UART_Params & u) {
                        rx_queue_.insert (*(u.udr_));
                }

                inline u8 transmitt(const UART_Params & u, const u8 c)override{

                        tx_queue_.insert (c);

                        *(u.ucsrb_) |= _BV(UART::udrie);

                        return 0;
                }

                inline u8 transmitt_irq(const UART_Params & u) {

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


#endif /* PPHLS_UART_MODES_HPP_ */