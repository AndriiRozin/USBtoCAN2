#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H
#include <QString>

class MessageProcessor
{
public:
    virtual bool processMesage(QString data)=0;
//    virtual bool start()=0;
//    virtual bool stop()=0;
//    virtual bool read_DATA(QQueue<QString> & queueData)=0;
//    virtual QString write_DATA(QString data)=0;


    virtual ~MessageProcessor(){};

};

#endif // MESSAGEPROCESSOR_H
