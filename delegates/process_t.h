#ifndef PROCESS_T_H
#define PROCESS_T_H
#include "messageprocessor.h"

class Process_t: public MessageProcessor
{
    virtual bool processMesage(QString data) override;

public:
    Process_t();
    virtual ~Process_t() override;
};

#endif // PROCESS_T_H
