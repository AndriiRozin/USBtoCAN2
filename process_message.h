#ifndef PROCESS_MESSAGE_H
#define PROCESS_MESSAGE_H
#include <QString>

class Process_message
{
public:
    virtual bool processMesage(QString data)=0;
    virtual ~Process_message() {};
};

#endif // PROCESS_MESSAGE_H
