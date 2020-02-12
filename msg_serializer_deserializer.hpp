#pragma once

#include <list>
#include "SerialDataMsg.hpp"

class MsgSerializerDeserializer {

public:
    
    SerialDataMsg* serialize(DataMessage*);
    DataMessage* deserialize(std::list<uint8_t>*);

private:
    DataMessage* ret;
    SerialDataMsg m_serial_msg;
};