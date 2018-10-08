#ifndef INP_SERIAL_H
#define INP_SERIAL_H

#include "inp_devices.h"
#include "configure_input.h"
#include <QSerialPort>
#include <QString>
#include <QStatusBar>

struct ConfigSerialPort
{
    QString portName;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBit;
    QSerialPort::FlowControl flowControl;
};

class Inp_Serial : public Configure_Input<ConfigSerialPort>, public Inp_Devices
{
    typedef Configure_Input<ConfigSerialPort> Parent;
    virtual bool config() override;
    virtual bool start() override;
    virtual bool stop() override;
    virtual bool read_DATA(QQueue<QString> & queueData) override;
    virtual QString write_DATA(QString data) override;


    QSerialPort mQSerialPort;
    struct{
        QByteArray readData;
    } serialPort;

    void parsingMessage(QQueue<QString> & m_queue);

public:
    Inp_Serial(QStatusBar * statusLable);
    Inp_Serial(const ConfigSerialPort& _structSerial);
    virtual ~Inp_Serial() override;

private:
private:
    QStatusBar * m_statusLable;
};

#endif // INP_SERIAL_H
