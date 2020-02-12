#include "arduino_serial_comm_device.hpp"

ArduinoSerialCommDevice* ArduinoSerialCommDevice::A;
const int ArduinoSerialCommDevice::max_msg_size;
//Serial_* ArduinoSerialCommDevice::m_ard_hardware;
SerialDataMsg ArduinoSerialCommDevice::serial_data;

ArduinoSerialCommDevice::ArduinoSerialCommDevice(block_frequency t_bf) : TimedBlock(t_bf)
{

}

void ArduinoSerialCommDevice::send_data_to_hardware(DataMessage* t_msg)
{
    SerialDataMsg* t_serial_msg = (SerialDataMsg*) t_msg;
    #ifdef DEBUG_COMM
    SerialUSB.println("Sending Data! ");
    #endif
    for(int i = 0; i < t_serial_msg->len; i++)
    {
        #ifdef DEBUG_COMM
        //SerialUSB.println(String(t_serial_msg->data[i]));
        #else
        SerialUSB.write(t_serial_msg->data[i]);
        #endif
    }
}

bool ArduinoSerialCommDevice::attach_hardware_sender(void* sender_obj)
{
    //TODO: change to adjust dependong on arg
    //m_ard_hardware = (Serial_*) sender_obj;
    m_baud_rate = 230400;
    SerialUSB.begin(m_baud_rate);
    A = this;
    if(SerialUSB)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ArduinoSerialCommDevice::reset_hardware(void* sender_obj)
{
    //TODO: change to adjust dependong on arg
    //m_ard_hardware = (Serial_*) sender_obj;
    SerialUSB.end();
    //SerialUSB.begin(m_baud_rate);
}

void ArduinoSerialCommDevice::receiveDataFromHardware()
{
    int data_in_buffer = SerialUSB.available();
    if(data_in_buffer > 0)
    {
        #ifdef DEBUG_COMM
        //SerialUSB.println("Data Received! " + String(data_in_buffer));
        SerialUSB.println("Data Received! ");
        #endif
        //while(m_ard_hardware->available())
        for(int i = 0; i<data_in_buffer; i++)
        {
            //serial_data.data[i] = m_ard_hardware->read();
            serial_data.data[i] = (uint8_t) SerialUSB.read();
        }
        #ifdef DEBUG_COMM
        //SerialUSB.println("Data read ! " + String(data_in_buffer));
        #endif
        serial_data.len = data_in_buffer;
        A->emit_message((DataMessage*) &serial_data);
    }
}

void ArduinoSerialCommDevice::receive_msg_data(DataMessage* t_msg)
{
    CommDevice::receive_msg_data(t_msg);
}

void ArduinoSerialCommDevice::loopInternal()
{
    A->receiveDataFromHardware();
}