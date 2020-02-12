#include "CommChecker.hpp"

CommChecker::CommChecker(CommDevice* t_dev, void* t_sender, block_frequency t_bf) : TimedBlock(t_bf)
{
    m_timer.tick();
    m_dev = t_dev;
    m_comm_port = t_sender;
    m_wdt.setup(WDT_HARDCYCLE4S);
    m_wdt.clear();
    if(m_dev->attach_hardware_sender(m_comm_port))
    {
        //Logger::getAssignedLogger()->log("Connection Established", LoggerLevel::Info);
    }
    else
    {
        //Logger::getAssignedLogger()->log("Failed To Establish Connection, Retrying...", LoggerLevel::Info);
    }
}

CommChecker::~CommChecker() 
{

}

void CommChecker::loopInternal()
{
    HeartbeatMsg t_msg;
    emit_message((DataMessage*) &t_msg);
}

void CommChecker::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::HEARTBEAT)
    {
        m_wdt.clear();
    }
}