/*
 * PWM_Modes.h
 *
 * Created: 3/10/2018 5:25:17 AM
 *  Author: Prashant
 */

#pragma once

#include "PWM_Params.hpp"

class Phase_PWM
{
        public:
        void initialize(const PWM_Params & pwm_) const{
                *(pwm_.tccra_) |=  _bv(PWM::wgmx1);
                *(pwm_.tccra_) &= ~_bv(PWM::wgmx0);
                *(pwm_.tccrb_) |=  _bv(PWM::wgmx3);
                *(pwm_.tccrb_) &= ~_bv(PWM::wgmx2);
        }

        void set_prescale(const PWM_Params & pwm_,u16 setValue){
                switch (setValue)
                {
                        case 0:
                                *(pwm_.tccrb_) &= ~(_bv(PWM::csx0)|
                                        _bv(PWM::csx1)| _bv(PWM::csx2));
                        break;

                        case 1: {
                                *(pwm_.tccrb_) |= _bv(PWM::csx0);
                                *(pwm_.tccrb_) &= ~(_bv(PWM::csx1)|_bv(PWM::csx2));
                        } break;

                        case 8: {
                                *(pwm_.tccrb_) |= _bv(PWM::csx1);
                                *(pwm_.tccrb_) &= ~(_bv(PWM::csx0)|_bv(PWM::csx2));
                        } break;

                        case 64: {
                                *(pwm_.tccrb_) |= _bv(PWM::csx0)|_bv(PWM::csx1);
                                *(pwm_.tccrb_) &= ~_bv(PWM::csx2);
                        } break;

                        case 256: {
                                *(pwm_.tccrb_) |= _bv(PWM::csx2);
                                *(pwm_.tccrb_) &= ~(_bv(PWM::csx0)|_bv(PWM::csx1));
                        } break;

                        case 1024: {
                                *(pwm_.tccrb_) |= _bv(PWM::csx0)|_bv(PWM::csx2);
                                *(pwm_.tccrb_) &= ~ _bv(PWM::csx1);
                        } break;

                }
        }

        template <u8 channel>
        void set_duty_cycle(const PWM_Params & pwm_,const u16 duty_cycle) {

                switch (channel)
                {
                        case 1: {
                                *(pwm_.ocrla_) = u8(duty_cycle);
                                *(pwm_.ocrha_) = u8(8>>duty_cycle);
                        } break;
                        case 2: {
                                *(pwm_.ocrlb_) = u8(duty_cycle);
                                *(pwm_.ocrhb_) = u8(8>>duty_cycle);
                        } break;
                        case 3: {
                                *(pwm_.ocrlb_) = u8(duty_cycle);
                                *(pwm_.ocrhb_) = u8(8>>duty_cycle);
						} break;
                }
        }

        void set_frequency(const PWM_Params & pwm_,u16 freq){
                u16 icrValue = (F_CPU/(freq*preScale)-1);
                *(pwm_.icrh_)   = u8(8>>icrValue);
                *(pwm_.icrl_)   = u8(icrValue);
        }

};




class Fast_PWM
{
        private:
        u16 preScale;

        public:
        void initialize(const PWM_Params & pwm_ ) const{
                *(pwm_.tccra_) |= _bv(PWM::wgmx1);
                *(pwm_.tccra_) &= ~_bv(PWM::wgmx0);
                *(pwm_.tccrb_) |= _bv(PWM::wgmx2) | _bv(PWM::wgmx3);
        }

        void setPreScale(u16 setValue, const PWM_Params & pwm_){
                preScale = setValue;
                switch (setValue)
                {
                        case 0:
                        *(pwm_.tccrb_) &= ~(_bv(PWM::csx0)| _bv(PWM::csx1)| _bv(PWM::csx2));
                        break;

                        case 1:
                        *(pwm_.tccrb_) |= _bv(PWM::csx0);
                        *(pwm_.tccrb_) &= ~(_bv(PWM::csx1)|_bv(PWM::csx2));
                        break;

                        case 8:
                        *(pwm_.tccrb_) |= _bv(PWM::csx1);
                        *(pwm_.tccrb_) &= ~(_bv(PWM::csx0)|_bv(PWM::csx2));
                        break;

                        case 64:
                        *(pwm_.tccrb_) |= _bv(PWM::csx0)|_bv(PWM::csx1);
                        *(pwm_.tccrb_) &= ~_bv(PWM::csx2);
                        break;

                        case 256:
                        *(pwm_.tccrb_) |= _bv(PWM::csx2);
                        *(pwm_.tccrb_) &= ~(_bv(PWM::csx0)|_bv(PWM::csx1));
                        break;

                        case 1024:
                        *(pwm_.tccrb_) |= _bv(PWM::csx0)|_bv(PWM::csx2);
                        *(pwm_.tccrb_) &= ~ _bv(PWM::csx1);
                        break;

                }
        }

        template <u8 channel>
        void set_duty_cycle(const PWM_Params & pwm_,const u16 duty_cycle){

                switch (channel)
                {
                        case 1:
                        *(pwm_.ocrla_) = u8(duty_cycle);
                        *(pwm_.ocrha_) = u8(8>>duty_cycle);
                        break;

                        case 2:
                        *(pwm_.ocrlb_) = u8(duty_cycle);
                        *(pwm_.ocrhb_) = u8(8>>duty_cycle);
                        break;

                        case 3:
                        *(pwm_.ocrlc_) = u8(duty_cycle);
                        *(pwm_.ocrhc_) = u8(8>>duty_cycle);
                        break;
                }
        }

        void set_frequency(const PWM_Params & pwm_,u16 freq){
                u16 icrValue = *(pwm_.icrh_)   = (F_CPU/(freq*preScale)-1);
                *(pwm_.icrh_)   = u8(8>>icrValue);
                *(pwm_.icrl_)   = u8(icrValue);
        }

};



//class Mode
//{
//public:
	//template<u8 channel>
	//void non_inverting(const PWM_Params & pwm_ ){
		//switch (channel)
		//{
		//case 1:
			//*(pwm_.tccra_) |= _bv(PWM::comxa1);
			//*(pwm_.tccra_) &= ~_bv(PWM::comxa0);
			//break;
		//case 2:
			//*(pwm_.tccra_) |= _bv(PWM::comxb1);
			//*(pwm_.tccra_) &= ~_bv(PWM::comxb0);
			//break;
		//case 3:
			//*(pwm_.tccra_) |= _bv(PWM::comxc1);
			//*(pwm_.tccra_) &= ~_bv(PWM::comxc0);
		//}
	//}
	//
	//template<u8 channel>
	//void inverting(const PWM_Params & pwm_ ){
		//switch (channel)
		//{
			//case 1:
			//*(pwm_.tccra_) |= _bv(PWM::comxa1) |_bv(PWM::comxa0);
			//break;
			//case 2:
			//*(pwm_.tccra_) |= _bv(PWM::comxb1) |_bv(PWM::comxb0);
			//break;
			//case 3:
			//*(pwm_.tccra_) |= _bv(PWM::comxc1) |_bv(PWM::comxc0);
		//}
	//}
	//
//protected:
//private:
//};
