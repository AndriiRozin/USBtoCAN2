#ifndef INP_DEVICES_H
#define INP_DEVICES_H
#include <QString>
#include <qqueue.h>


class Inp_Devices
{
public:
    virtual bool config()=0;
    virtual bool start()=0;
    virtual bool stop()=0;
    virtual bool read_DATA(QQueue<QString> & queueData)=0;
    virtual QString write_DATA(QString data)=0;


    virtual ~Inp_Devices(){};


};

#endif // INP_DEVICES_H
