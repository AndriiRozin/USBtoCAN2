#ifndef PROCESS_ERROR_H
#define PROCESS_ERROR_H
#include "process_message.h"

class Process_Error: public Process_message
{
public:
    Process_Error();
    virtual bool processMesage(QString data) override;
    virtual ~Process_Error() override;
};

#endif // PROCESS_ERROR_H
