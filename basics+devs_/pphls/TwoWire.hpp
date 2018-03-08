/*
 * Two_Wire.hpp
 *
 * Created: 3/8/2018 12:11:54 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef PPHLS_TWO_WIRE_HPP_
#define PPHLS_TWO_WIRE_HPP_

#include "TwoWire_Params.hpp"
#include "TwoWire_Modes.hpp"

template <class Mode>
class TwoWire : public Mode
{
// Data Members
private:
        TwoWire_Params tw_;

//Member Functions
public:
        template <size_t N>
        TwoWire( u8 (&arr)[N] = TWI::_0 ) :
        tw_(arr) { }

        TwoWire( const TwoWire && tmp ):
        tw_(tmp.tw_) { }

        /// The transmission frequency(scl_freq) should be greater than 30kHz.
        ///
        /// The pre-scaler is set to be 1 since we don't need to communicate at
        /// frequency lower than 30kHz. If needed this member function will be
        /// modified.
        inline u8 initialize(const u32 scl_freq) const;

        /// Any value returned beside 0 is the error.
        inline u8 start(const u8 address) const {

                *(tw_.twcr_) = _BV(TWI::twen)   // Activate the TWI
                             | _BV(TWI::twint)  // Clear the interrupt flag
                             | _BV(TWI::twsta); // Generate START condition

                // Waiting for the end of transmission
                wait_for_twint_to_clear ();

                // Checking 'Start Condition' transmission (Reset: 0xF8)
                if( mask(tw_.twsr_, 0xFC & 0xF8) != TWI::started)
                        return error();

                u8 status = write(address);
                if( (status != TWI::slave_addr) &&
                        (status != TWI::slave_addw) )
                                return error();

                return 0;
        }

        inline void stop() const {

                *(tw_.twcr_) = _BV(TWI::twen)
                             | _BV(TWI::twint)
                             | _BV(TWI::twsto);
                while( *(tw_.twcr_) & _BV(TWI::twsto) );
        }

        inline u8 transmitt(const u8 value) const {

                u8 status = write(value);
                if( status != TWI::data )
                        return error();

                return 0;
        }

        inline u8 receive(const u8 ack_nack) const {
                *(tw_.twcr_) = _BV(TWI::twen)
                             | _BV(TWI::twint)
                             | (ack_nack << TWI::twea);

                wait_for_twint_to_clear ();
                return *(tw_.twdr_);
        }

        template <Hardware H>
        inline static TwoWire<Mode> getInstance() {

                Manager::record<H> ();

                static_assert(H == Hardware::TWI_0,
                                "Non-existing TWI requested.");

                if( H == Hardware::TWI_0 )
                        return TwoWire<Mode>(TWI::_0);

                return TwoWire<Mode>(TWI::_NULL);
        }

private:
        inline u8 error() { return 1; }
        inline u8 mask(volatile u8 * reg, const u8 mask) const {
                return *(reg) & mask;
        }

        inline void wait_for_twint_to_clear() const {
                while( *(tw_.twcr_) & _BV(TWI::twint) );
        }

        inline u8 write(const u8 value) const {
                *(tw_.twdr_) = value;
                *(tw_.twcr_) = _BV(TWI::twint)
                             | _BV(TWI::twen);

                // Waiting for the end of transmission
                wait_for_twint_to_clear ();

                return mask(tw_.twsr_, 0xFC & 0xF8);
        }
};

constexpr u8 twbr_val(const u32 scl_freq)
{
        return (((F_CPU / scl_freq) - 16) / 2);
}

template <class Mode>
u8 TwoWire<Mode>::initialize(const u32 scl_freq) const
{
        *(tw_.twbr_) = twbr_val (scl_freq);
        *(tw_.twsr_) = 0;       // Pre-scaler = 1 (hard-coded)
        *(tw_.twcr_) = _BV(TWI::twen);

        return 0;
}


#endif /* PPHLS_TWO_WIRE_HPP_ */