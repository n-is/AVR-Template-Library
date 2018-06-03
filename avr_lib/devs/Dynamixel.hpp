/*
 * Dynamixel.hpp
 *
 * Created: 3/10/2018 4:11:35 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */

/* Important Sites
 * http://support.robotis.com/en/product/actuator/dynamixel/communication/dxl_packet.htm
 * http://support.robotis.com/en/product/actuator/dynamixel/communication/dxl_instruction.htm
 * https://www.pishrobot.com/files/products/datasheets/dynamixel_ax-12a.pdf
 * https://www.pishrobot.com/files/products/datasheets/dynamixel_mx-12w.pdf
 * https://github.com/vanadiumlabs/arbotix/tree/master/libraries/Bioloid
 *
 */

#pragma once

#include "basics/AVR.hpp"

/** \class MX12
 ** \brief A class that describe the MX-12W dynamixel. The addresses are
 **		   according to the datasheet at :
 ** https://www.pishrobot.com/files/products/datasheets/dynamixel_mx-12w.pdf
 **/
class MX12 {
public:
        static const u8 model_num_l = 0x00;
        static const u8 model_num_h = 1;
        static const u8 firmware_ver = 2;
        static const u8 id = 3;
        static const u8 baud = 4;
        static const u8 return_delay = 5;
        static const u8 cw_angle_l = 6;
        static const u8 cw_angle_h = 7;
        static const u8 ccw_angle_l = 8;
        static const u8 ccw_angle_h = 9;
        static const u8 highest_temp = 11;
        static const u8 lowest_volt = 12;
        static const u8 highest_volt = 13;
        static const u8 max_torque_l = 14;
        static const u8 max_torque_h = 15;
        static const u8 status_return = 16;
        static const u8 alarm_led = 17;
        static const u8 alarm_shutdown = 18;
        static const u8 multi_turn_offset_l = 20;
        static const u8 multi_turn_offset_h = 21;
        static const u8 resolution_divider = 22;
        static const u8 torque_enable = 24;
        static const u8 led = 25;
        static const u8 d_gain = 26;
        static const u8 i_gain = 27;
        static const u8 p_gain = 28;
        static const u8 goal_pos_l = 30;
        static const u8 goal_pos_h = 31;
        static const u8 moving_speed_l = 32;
        static const u8 moving_speed_h = 33;
        static const u8 torque_limit_l = 34;
        static const u8 torque_limit_h = 35;
        static const u8 present_pos_l = 36;
        static const u8 present_pos_h = 37;
        static const u8 present_speed_l = 38;
        static const u8 present_speed_h = 39;
        static const u8 present_load_l = 40;
        static const u8 present_load_h = 41;
        static const u8 present_voltage = 42;
        static const u8 present_temp = 43;
        static const u8 registered = 44;
        static const u8 moving = 46;
        static const u8 lock = 47;
        static const u8 punch_l = 48;
        static const u8 punch_h = 49;
        static const u8 goal_accel = 73;


	template <u8 addr>
	static bool is_Available() {
		return (addr == model_num_l ||
			addr == model_num_h ||
			addr == firmware_ver ||
			addr == id ||
			addr == baud ||
			addr == cw_angle_l ||
			addr == cw_angle_h ||
			addr == ccw_angle_l ||
			addr == ccw_angle_h ||
			addr == highest_temp ||
			addr == lowest_volt ||
			addr == highest_volt ||
			addr == max_torque_l ||
			addr == max_torque_h ||
			addr == status_return ||
			addr == alarm_led ||
			addr == alarm_shutdown ||
			addr == multi_turn_offset_l ||
			addr == multi_turn_offset_h ||
			addr == resolution_divider ||
			addr == torque_enable ||
			addr == led ||
			addr == d_gain ||
			addr == i_gain ||
			addr == p_gain ||
			addr == goal_pos_l ||
			addr == goal_pos_h ||
			addr == moving_speed_l ||
			addr == moving_speed_h ||
			addr == torque_limit_l ||
			addr == torque_limit_h ||
			addr == present_pos_l ||
			addr == present_pos_h ||
			addr == present_speed_l ||
			addr == present_speed_h ||
			addr == present_load_l ||
			addr == present_load_h ||
			addr == present_voltage ||
			addr == present_temp ||
			addr == registered ||
			addr == moving ||
			addr == lock ||
			addr == punch_l ||
			addr == punch_h ||
			addr == goal_accel);
	}
};


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

/*** 
 ** \class Dynamixel
 **
 ** \brief A class that models a dynamixel module.
 ** 
 ** This class can be used for both AX12 and MX12 dynamixels. Others are not
 ** yet tested or checked(this is not yet tested for AX12 and will do so soon).
 **
 ** \param H    : A template parameter to denote the hardware to use for the
 **               dynamixel. Since dynamixel uses UART for data and instruction
 **               transmssion, a valid Hardware name as specified in enum class
 **               Hardware is expected.
 **
 ** \param UART_Mode : A template parameter to denote the mode the UART used
 **                    by the dynamixel for transmission. Both Polling mode
 **                    and the Interrupt mode can be used for this purpose.
 **
 ** \param D    : A template parameter to denote the actual dynamixel hardware.
 **               This class is actually just a collection of the memory
 **               addresses of the EEPROM and the RAM within the dynamixel.
 **               An example to describe the hardware is given for the MX-12W
 **               dynamixel int the class MX12, which can be used as an example
 **               to describe the dynamixel. If additional parts(i.e. additional
 **               memory address is present), the class itself needs to be
 **               modified.
 **/
template <Hardware H, class UART_Mode, class D>
class Dynamixel
{
// Data Members
private:
        HardwareUART<UART_Mode> uart_;
        u8 parameters_[Dyna::max_params];

// Member Functions
public:
        Dynamixel():
        uart_(HardwareUART<UART_Mode>::template get_Instance<H>()) { }

	~Dynamixel() { terminate(); }

        /***
	 ** A function to initialize the dynamixel.
         ** \param baud The speed of communication with dynamixel, a template
         **             parameter.
         ** \return 0 if initialized properly else 1.
         **/
        template <u32 baud>
        inline u8 initialize() const {
                u8 err = uart_.template initialize<baud> ();
                uart_.rx_Off();
                return err;
        }

        inline void terminate() { uart_.template terminate<H>(); }

	/***
	 ** A function that transmits the data in the parameters_[] array of
         ** the class by framing it properly.
         **
         ** \param id The id of the dynamixel.
         ** \param instruction The instruction given to the dynamixel to execute.
         ** \param params_no The number of data filled in parameters_[] that is
         **                     to be transmitted.
         ** \return void
         **/
        void transmit_Packet(u8 id, u8 instruction, u8 params_no) const;

	/***
	 ** A function template that receives 'data_len' bytes from the
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
        u8 receive_Packet(u8 (&arr)[N]);

	/***
	 ** This function is a clone of the receive_Packet function template
         ** above.
         ** @pros The parameters can be dynamic.
         ** @cons It is costlier than the function template above, that does the
         **       same task.
         **/
        template <size_t N>
        u8 receive_Packet(u8 id, u8 start_addr, u8 data_len, u8 (&arr)[N]);

        /** This function is just here to call transmit interrupt request.*/
        inline void transmit_Irq() const { uart_.transmit_Irq (); }
        /** This function is just here to call receive interrupt request.*/
        inline void receive_Irq() const { uart_.receive_Irq (); }

        inline void set_Position(u8 id, u16 pos) {
                parameters_[0] = D::goal_pos_l;
                parameters_[1] = (u8)pos;
                parameters_[2] = (u8)(pos >> 8);
                transmit_Packet (id, Dyna::write_inst, 3);
        }

        inline void set_Id(u8 id) {
                parameters_[0] = D::id;
                parameters_[1] = id;
                transmit_Packet (Dyna::broadcast_id, Dyna::write_inst, 2);
        }

        inline void led(u8 id, u8 state) {
                parameters_[0] = D::led;
                parameters_[1] = state;
                transmit_Packet (id, Dyna::write_inst, 2);
        }

        inline void joint_Mode(u8 id, u16 cw_limit, u16 ccw_limit) {
                parameters_[0] = D::cw_angle_l;
                parameters_[1] = (u8)cw_limit;
                parameters_[2] = (u8)(cw_limit >> 8);
                parameters_[3] = (u8)ccw_limit;
                parameters_[4] = (u8)(ccw_limit >> 8);
                transmit_Packet (id, Dyna::write_inst, 5);
        }

        inline void speed(u8 id, u16 speed_of_motor) {
                parameters_[0] = D::moving_speed_l;
                parameters_[1] = (u8)speed_of_motor;
                parameters_[2] = (u8)(speed_of_motor >> 8);
                transmit_Packet (id, Dyna::write_inst, 3);
        }

        inline void torque(u8 id, bool on_off) {
                parameters_[0] = D::torque_enable;
                parameters_[1] = on_off;
                transmit_Packet (id, Dyna::write_inst, 3);
        }

	inline bool is_Null() const {
		return uart_.is_Null();
	}

private:
	Dynamixel(const Dynamixel &c) = delete;
	Dynamixel& operator=(const Dynamixel &c) = delete;

        inline void set_Tx_Only() const {
                uart_.rx_Off();
                uart_.tx_On();
        }

        inline void set_Rx_Only() const {
                uart_.tx_Off();
                uart_.rx_On();
        }

        /** Any dynamixel packet starts with 0xFF 0xFF */
        inline void begin_Packet() const {
                uart_.transmit (0xFF);
                uart_.transmit (0xFF);
        }
};


// Any Instruction and parameters packets should be sent in following format :
// 0xFF 0xFF ID LENGTH INSTRUCTION PARAMETER_1...PARAMETER_N CHECK_SUM
template <Hardware H, class UART_Mode, class D>
void Dynamixel<H, UART_Mode, D>::transmit_Packet
(u8 id, u8 instruction, u8 params_no) const
{
        u8 len = params_no + 2;
        u16 checksum = (id + instruction + len);
        set_Tx_Only ();
        begin_Packet ();
        uart_.transmit (id);
        uart_.transmit (len);
        uart_.transmit (instruction);

        for( u8 i = 0; i < params_no; ++i ) {
                uart_.transmit(parameters_[i]);
                checksum += parameters_[i];
        }

        uart_.transmit (~((u8)checksum));
}

// The packets are received in the following format :
// 0xFF 0xFF ID LENGTH ERROR PARAMETER_1...PARAMETER_N CHECK_SUM
template <Hardware H, class UART_Mode, class D>
template <u8 id, u8 start_addr, u8 data_len, size_t N>
u8 Dynamixel<H, UART_Mode, D>::receive_Packet(u8 (&arr)[N])
{
        static_assert (start_addr <= Dyna::max_addrs,
                "Out of Bounds Memory requested.");

        static_assert (D::template is_Available<start_addr> (),
                "Out of Bounds Memory requested.");
        static_assert (data_len <= N,
                "Data requested more than the array can hold.");

        parameters_[0] = start_addr;
        parameters_[1] = data_len;
        transmit_Packet (id, Dyna::Inst::read_data, 2);

        set_Rx_Only ();
        u8 raw[data_len + 6];  // There are 6 extra bytes in the packet
        uart_.flush();
        for(u8 i = 0; i < array_Size (raw); ++i) {
                raw[i] = uart_.receive();
        }
        for(u8 i = 0; i < data_len; ++i) {
                arr[i] = raw[i + 5];
        }

        return raw[4];  // 5th byte is the error byte
}

// The packets are received in the following format :
// 0xFF 0xFF ID LENGTH ERROR PARAMETER_1...PARAMETER_N CHECK_SUM
template <Hardware H, class UART_Mode, class D>
template <size_t N>
u8 Dynamixel<H, UART_Mode, D>::receive_Packet
(u8 id, u8 start_addr, u8 data_len, u8 (&arr)[N])
{
        parameters_[0] = start_addr;
        parameters_[1] = data_len;
        transmit_Packet (id, Dyna::Inst::read_data, 2);

        set_Rx_Only ();
        u8 raw[N + 6];  // There are 6 extra bytes in the packet
        uart_.flush();
        for(u8 i = 0; i < (data_len + 6); ++i) {
                raw[i] = uart_.receive();
        }
        for(u8 i = 0; i < data_len; ++i) {
                arr[i] = raw[i + 5];
        }

        return raw[4];  // 5th byte is the error byte
}
