#ifndef PROCESS_TX_H
#define PROCESS_TX_H
#include "process_message.h"
#include "hmi/hmi_monitor.h"

class Process_Tx: public Process_message
{
public:
    Process_Tx(Hmi_monitor * monitor_viewer);
    virtual bool processMesage(QString data) override;
       virtual ~Process_Tx() override;
private:
    Hmi_monitor * m_monitor_viewer;
};

#endif // PROCESS_TX_H
