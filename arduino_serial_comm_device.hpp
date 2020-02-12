#pragma once

#include "comm_device.hpp"
#include "TimedBlock.hpp"

// #ifndef __cplusplus
// #define __cplusplus
// #endif

// #ifndef CDC_ENABLED
// #define CDC_ENABLED
// #endif

// #ifndef USBCON
// #define USBCON
// #endif

//#define DEBUG_COMM

#include "Arduino.h"
#undef max
#undef min

class ArduinoSerialCommDevice : public CommDevice, public TimedBlock
{
    public:

        static ArduinoSerialCommDevice* A;

        ArduinoSerialCommDevice(block_frequency);
        //serialUSB is SAMD21
        //TODO: refactor, to add different communication other than serialUSB
        bool attach_hardware_sender(void* sender_obj) override;
        void send_data_to_hardware(DataMessage* ) override;
        void attach_hardware_callback(void* call_back_obj){};
        void reset_hardware(void* sender_obj);
        void receive_msg_data(DataMessage*);
        static void receiveDataFromHardware();
        void loopInternal();

    private:
    
        //TODO: is this ok const?
        static const int max_msg_size = 1024;
        int m_baud_rate;
        //static Serial_* m_ard_hardware;
        static SerialDataMsg serial_data;
};