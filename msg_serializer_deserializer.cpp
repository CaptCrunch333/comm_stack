#include "msg_serializer_deserializer.hpp"

SerialDataMsg* MsgSerializerDeserializer::serialize(DataMessage* t_msg)
{
    uint8_t* t_buffer = (uint8_t*)t_msg;
    //m_serial_msg.len  = t_msg->getSize();
    m_serial_msg.len  = 8;
    for(int i = 0; i< m_serial_msg.len; i++)
    {
        m_serial_msg.data[i] = *(t_buffer+i);
    }
    return &m_serial_msg;
}

DataMessage* MsgSerializerDeserializer::deserialize(std::list<uint8_t>* t_serial_msg)
{
    std::list<uint8_t>::iterator it;
    m_serial_msg.len  = 0;
    for(it = t_serial_msg->begin(); it != t_serial_msg->end(); ++it)
    {
        m_serial_msg.data[m_serial_msg.len] = (*it);
        m_serial_msg.len++;
    }
    ret = (DataMessage*)m_serial_msg.data;
    return ret;
}