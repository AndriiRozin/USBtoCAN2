#ifndef INP_FILE_H
#define INP_FILE_H
#include "inp_devices.h"
#include <QString>
#include <QFile>
#include <QStatusBar>

class Inp_File: public Inp_Devices
{
    virtual bool config() override;
    virtual bool start() override;
    virtual bool stop() override;
    virtual bool read_DATA(QQueue<QString> & queueData) override;
    virtual QString write_DATA(QString ) override;


void parsingMessage(QQueue<QString> & m_queue);
    QFile mFile;

    struct{
        QString readData;

    } mFileData;

public:
    Inp_File(QStatusBar * statusLable);
//    Inp_Serial(const ConfigSerialPort& _structSerial);
    virtual ~Inp_File() override;

private:
    QStatusBar * m_statusLable;
};




#endif // INP_FILE_H
