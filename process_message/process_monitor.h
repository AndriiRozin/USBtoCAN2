#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H
#include "process_message.h"
#include "hmi/hmi_monitor.h"

class Process_Monitor: public Process_message
{
public:
    Process_Monitor(Hmi_monitor * monitor_viewer);
    virtual bool processMesage(QString data) override;
       virtual ~Process_Monitor() override;
private:
    Hmi_monitor * m_monitor_viewer;
};

#endif // PROCESS_MONITOR_H
