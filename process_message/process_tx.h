#ifndef PROCESS_TX_H
#define PROCESS_TX_H
#include "process_message.h"

class Process_Tx: public Process_message
{
public:
    Process_Tx();
    virtual bool processMesage(QString data) override;
       virtual ~Process_Tx() override;
};

#endif // PROCESS_TX_H
