#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H
#include "process_message.h"

class Process_Monitor: public Process_message
{
public:
    Process_Monitor();
    virtual bool processMesage(QString data) override;
       virtual ~Process_Monitor() override;
};

#endif // PROCESS_MONITOR_H
