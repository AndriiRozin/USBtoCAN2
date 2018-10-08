#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H
#include "process_message.h"

class Process_Info: public Process_message
{
public:
    Process_Info();
    virtual bool processMesage(QString data) override;
    virtual ~Process_Info() override;
};

#endif // PROCESS_INFO_H
