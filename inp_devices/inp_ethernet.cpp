#include "inp_ethernet.h"
#include "QDebug"





bool Inp_Ethernet::config()
    {
        qDebug()<<"Inp_Ethernet: config";
        return true;
    }
bool Inp_Ethernet::read_DATA(QQueue<QString> & queueData)
    {
        qDebug()<<"Inp_Ethernet: read_DATA";
        return true;
    }
QString Inp_Ethernet::write_DATA(QString data)
    {
        qDebug()<<"Inp_Ethernet: write_Data";
        return "ok";
    }
bool Inp_Ethernet::start()
    {
        qDebug()<<"Inp_Ethernet: start";
        return "ok";
    }
bool Inp_Ethernet::stop()
    {
        qDebug()<<"Inp_Ethernet: stop";
        return "ok";
    }
