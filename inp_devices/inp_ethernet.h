#ifndef INP_ETHERNET_H
#define INP_ETHERNET_H
#include "inp_devices.h"
#include <QString>


class Inp_Ethernet: public Inp_Devices
{
    virtual bool config() override;
    virtual bool start() override;
    virtual bool stop() override;
    virtual bool read_DATA(QQueue<QString> & queueData) override;
    virtual QString write_DATA(QString) override;


};




#endif // INP_ETHERNET_H
