#pragma once

#include "MsgEmitter.hpp"
#include "comm_device.hpp"
#include "Timer.hpp"
#include "logger.hpp"
#include "TimedBlock.hpp"
#include "HeartbeatMsg.hpp"
#include <unistd.h>
#include "WDTZero.h"

// #include "Arduino.h"
// #undef max
// #undef min


class CommChecker : public msg_emitter, public msg_receiver, public TimedBlock
{

public:

    CommChecker(CommDevice*, void*, block_frequency);
    ~CommChecker();

    void sendRequest(DataMessage*);
    void receive_msg_data(DataMessage*);
    void loopInternal();

private:

    Timer m_timer;
    CommDevice* m_dev;
    WDTZero m_wdt;
    const int m_timeout = 5000000;
    void* m_comm_port;
};