#ifndef PROCESS_RX_H
#define PROCESS_RX_H
#include "process_message.h"
#include "hmi/hmi_monitor.h"

class Process_rx: public Process_message
{
public:
    Process_rx(Hmi_monitor * monitor_viewer);
    virtual bool processMesage(QString data) override;
       virtual ~Process_rx() override;
private:
    Hmi_monitor * m_monitor_viewer;
};

#endif // PROCESS_RX_H
