/*
 * Dynamixel.hpp
 *
 * Created: 3/10/2018 4:11:35 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef DYNAMIXEL_DYNAMIXEL_HPP_
#define DYNAMIXEL_DYNAMIXEL_HPP_

#include "basics/AVR.hpp"

namespace MX12 {

        const u8 model_num_l = 0x00;
        const u8 model_num_h = 1;
        const u8 firmware_ver = 2;
        const u8 id = 3;
        const u8 baud = 4;
        const u8 return_delay = 5;
        const u8 cw_angle_l = 6;
        const u8 cw_angle_h = 7;
        const u8 ccw_angle_l = 8;
        const u8 ccw_angle_h = 9;
        const u8 highest_temp = 11;
        const u8 lowest_volt = 12;
        const u8 highest_volt = 13;
        const u8 max_torque_l = 14;
        const u8 max_torque_h = 15;
        const u8 status_return = 16;
        const u8 alarm_led = 17;
        const u8 alarm_shutdown = 18;
        const u8 multi_turn_offset_l = 20;
        const u8 multi_turn_offset_h = 21;
        const u8 resolution_divider = 22;
        const u8 torque_enable = 24;
        const u8 led = 25;
        const u8 d_gain = 26;
        const u8 i_gain = 27;
        const u8 p_gain = 28;
        const u8 goal_pos_l = 30;
        const u8 goal_pos_h = 31;
        const u8 moving_speed_l = 32;
        const u8 moving_speed_h = 33;
        const u8 torque_limit_l = 34;
        const u8 torque_limit_h = 35;
        const u8 present_pos_l = 36;
        const u8 present_pos_h = 37;
        const u8 present_speed_l = 38;
        const u8 present_speed_h = 39;
        const u8 present_load_l = 40;
        const u8 present_load_h = 41;
        const u8 present_voltage = 42;
        const u8 present_temp = 43;
        const u8 registered = 44;
        const u8 moving = 46;
        const u8 lock = 47;
        const u8 punch_l = 48;
        const u8 punch_h = 49;
        const u8 goal_accel = 73;

}

namespace Dyna {

        const u8 max_addrs = 73;
        const u8 max_params = 10;

        const u8 broadcast_id = 0xfe;

        const u8 write_inst = 0x03;

        namespace Inst {
                const u8 write_data = 2;
                const u8 read_data = 3;

                const u8 reg_write = 1;
                const u8 action = 5;
                const u8 ping = 1;
                const u8 reset = 6;
        }
}

template <Hardware H, class UART_Mode>
class Dynamixel
{
// Data Members
protected:
        HardwareUART<UART_Mode> uart_;
        u8 parameters_[Dyna::max_params];

// Member Functions
public:
        Dynamixel():
        uart_(HardwareUART<UART_Mode>::template getInstance<H>()) { }

        ~Dynamixel() { }

        /** A function to initialize the dynamixel.
         ** \param baud The speed of communication with dynamixel, a template
         **             parameter.
         ** \return 0 if initialized properly else 1.
         **/
        template <u32 baud>
        inline u8 initialize() const {
                u8 err = uart_.initialize<baud> ();
                uart_.rx_off();
                return err;
        }

        /** A function that transmitts the data in the parameters_[] array of
         ** the class by framing it properly.
         **
         ** \param id The id of the dynamixel.
         ** \param instruction The instruction given to the dynamixel to execute.
         ** \param params_no The number of data filled in parameters_[] that is
         **                     to be transmitted.
         ** \return void
         **/
        void transmitt_packet(u8 id, u8 instruction, u8 params_no) const;

        /** A function template that receives 'data_len' bytes from the
         ** dynamixel starting from 'start_addr' address. Both ROM and RAM can
         ** be accessed through this function.
         **
         ** \param id The id of the dynamixel.
         ** \param start_addr The address to start reading from.
         ** \param data_len The length of bytes to read.
         ** \param arr The array to hold the data.
         ** \return The error byte. Error byte can be masked to check if
         **             specific error has occured.
         **/
        template <u8 id, u8 start_addr, u8 data_len, size_t N>
        u8 receive_packet(u8 (&arr)[N]);

        /** This function is a clone of the receive_packet function template
         ** above.
         ** @pros The parameters can be dynamic.
         ** @cons It is costlier than the function template above, that does the
         **             same task.
         **/
        template <size_t N>
        u8 receive_packet(u8 id, u8 start_addr, u8 data_len, u8 (&arr)[N]);

        /** This function is just here to call transmitt interrupt request.*/
        inline void transmitt_irq() { uart_.transmitt_irq (); }
        /** This function is just here to call receive interrupt request.*/
        inline void receive_irq() { uart_.receive_irq (); }

        inline void set_position(u8 id, u16 pos) {
                parameters_[0] = MX12::goal_pos_l;
                parameters_[1] = (u8)pos;
                parameters_[2] = (u8)(pos >> 8);
                transmitt_packet (id, Dyna::write_inst, 3);
        }

        inline void set_id(u8 id) {
                parameters_[0] = MX12::id;
                parameters_[1] = id;
                transmitt_packet (Dyna::broadcast_id, Dyna::write_inst, 2);
        }

        inline void led(u8 id, u8 state) {
                parameters_[0] = MX12::led;
                parameters_[1] = state;
                transmitt_packet (id, Dyna::write_inst, 2);
        }

        inline void joint_mode(u8 id, u16 cw_limit, u16 ccw_limit) {
                parameters_[0] = MX12::cw_angle_l;
                parameters_[1] = (u8)cw_limit;
                parameters_[2] = (u8)(cw_limit >> 8);
                parameters_[3] = (u8)ccw_limit;
                parameters_[4] = (u8)(ccw_limit >> 8);
                transmitt_packet (id, Dyna::write_inst, 5);
        }

        inline void speed(u8 id, u16 speed_of_motor) {
                parameters_[0] = MX12::moving_speed_l;
                parameters_[1] = (u8)speed_of_motor;
                parameters_[2] = (u8)(speed_of_motor >> 8);
                transmitt_packet (id, Dyna::write_inst, 3);
        }

        inline void torque(u8 id, bool on_off) {
                parameters_[0] = MX12::torque_enable;
                parameters_[1] = on_off;
                transmitt_packet (id, Dyna::write_inst, 3);
        }

private:
        inline void set_tx_only(u8 id) const {
                uart_.rx_off();
                uart_.tx_on();
        }

        inline void set_rx_only(u8 id) const {
                uart_.tx_off();
                uart_.rx_on();
        }

        /** Any dynamixel packet starts with 0xFF 0xFF */
        inline void begin_packet() const {
                uart_.transmitt (0xFF);
                uart_.transmitt (0xFF);
        }
};


// Any Instruction and parameters packets should be sent in following format :
// 0xFF 0xFF ID LENGTH INSTRUCTION PARAMETER_1...PARAMETER_N CHECK_SUM
template <Hardware H, class UART_Mode>
void Dynamixel<H, UART_Mode>::transmitt_packet
(u8 id, u8 instruction, u8 params_no) const
{
        u8 len = params_no + 2;
        u16 checksum = (id + instruction + len);
        set_tx_only (id);
        begin_packet ();
        uart_.transmitt (id);
        uart_.transmitt (len);
        uart_.transmitt (instruction);

        for( u8 i = 0; i < params_no; ++i ) {
                uart_.transmitt(parameters_[i]);
                checksum += parameters_[i];
        }

        uart_.transmitt (~((u8)checksum));
}

// The packets are received in the following format :
// 0xFF 0xFF ID LENGTH ERROR PARAMETER_1...PARAMETER_N CHECK_SUM
template <Hardware H, class UART_Mode>
template <u8 id, u8 start_addr, u8 data_len, size_t N>
u8 Dynamixel<H, UART_Mode>::receive_packet(u8 (&arr)[N])
{
        static_assert (start_addr <= Dyna::max_addrs,
                "Out of Bounds Memory requested.");
        static_assert (data_len <= N,
                "Data requested more than the array can hold.");

        parameters_[0] = start_addr;
        parameters_[1] = data_len;
        transmitt_packet (id, Dyna::Inst::read_data, 2);

        u8 raw[data_len + 6];  // There are 6 extra bytes in the packet
        uart_.flush();
        for(u8 i = 0; i < arraySize (raw); ++i) {
                raw[i] = uart_.receive();
        }
        for(u8 i = 0; i < data_len; ++i) {
                arr[i] = raw[i + 5];
        }

        return raw[5];  // 5th byte is the error byte
}

// The packets are received in the following format :
// 0xFF 0xFF ID LENGTH ERROR PARAMETER_1...PARAMETER_N CHECK_SUM
template <Hardware H, class UART_Mode>
template <size_t N>
u8 Dynamixel<H, UART_Mode>::receive_packet
(u8 id, u8 start_addr, u8 data_len, u8 (&arr)[N])
{
        parameters_[0] = start_addr;
        parameters_[1] = data_len;
        transmitt_packet (id, Dyna::Inst::read_data, 2);

        u8 raw[N + 6];  // There are 6 extra bytes in the packet
        uart_.flush();
        for(u8 i = 0; i < (data_len + 6); ++i) {
                raw[i] = uart_.receive();
        }
        for(u8 i = 0; i < data_len; ++i) {
                arr[i] = raw[i + 5];
        }

        return raw[5];  // 5th byte is the error byte
}


#endif /* DYNAMIXEL_DYNAMIXEL_HPP_ */