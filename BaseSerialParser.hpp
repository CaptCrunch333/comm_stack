#pragma once

#include "MsgReceiver.hpp"
#include "MsgEmitter.hpp"
#include <string.h>
#include "CRC.hpp"
#include "ThreeAxisSensorMsg.hpp"
#include "SerialDataMsg.hpp"
#include "ControllerOutputMsg.hpp"
#include "HeartbeatMsg.hpp"
#include "SerialDataMsg.hpp"
#include "MsgHandler.hpp"
//#define DEBUG_COMM
#ifdef DEBUG_COMM
#include "arduino_serial_comm_device.hpp" //TODO: delete
#endif

class BaseSerialParser : public msg_receiver, public msg_emitter
{
	public:
		
		//void update_readings(uint8_t*,size_t); 
		void configure(tPacketProp);
		void receive_msg_data(DataMessage*) override;

	private:

		int payload_len;
		int padding_len;
		int header_len;
		int crc_len;
		int frame_len;
		int byte_index = 0;
		uint8_t padding;
		uint8_t data_stream[300];
		uint8_t* payload_data;
		enum pointer_pose { Padd_search, header_read, EOH_check, msg_read, EOP_check, crc_read, done_reading };
		pointer_pose state = Padd_search;
		tPacketProp packet_config;
		msg_type _msg_type;
		struct tCounters
		{
			int padding_counter;
			int msg_counter;
			int header_counter;
			int crc_counter;
		}byte_counter;
		uint8_t state_machine(uint8_t input_byte);
		MsgHandler m_msg_handler;
};