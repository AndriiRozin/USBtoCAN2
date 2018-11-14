#include "inp_serial.h"

#include <QDebug>
#include <QtGlobal>
#include "mainwindow.h"
#include <qsettings.h>
#include "mainwindow.h"

Inp_Serial::Inp_Serial(QStatusBar * statusLable)
    : m_statusLable(statusLable)
{
}

Inp_Serial::Inp_Serial(const ConfigSerialPort& _structSerial)
: Parent(_structSerial)
{
};

Inp_Serial::~Inp_Serial()
{
    if (mSerialPort.isOpen()) {
        mSerialPort.close();
    }
}

bool Inp_Serial::config()
{
    mConfigureData.dataBits=QSerialPort::Data8;
    mConfigureData.parity=QSerialPort::NoParity;
    mConfigureData.stopBit=QSerialPort::OneStop;
    mConfigureData.flowControl=QSerialPort::NoFlowControl;

    QSettings  settings("USBtoCAN.ini", QSettings::IniFormat) ;
    settings.beginGroup("SerialPort");
    mConfigureData.portName = settings.value("portName").toString();
    mConfigureData.baudRate = settings.value("baudRate").toInt();
    settings.endGroup();


    mSerialPort.setPortName(mConfigureData.portName);
    mSerialPort.setBaudRate(mConfigureData.baudRate);
    mSerialPort.setDataBits(mConfigureData.dataBits);
    mSerialPort.setParity(mConfigureData.parity);
    mSerialPort.setStopBits(mConfigureData.stopBit);
    mSerialPort.setFlowControl(mConfigureData.flowControl);


    qDebug()<<"inp_serial::SerialPort.name:"<<mConfigureData.portName;
    qDebug()<<"inp_serial::SerialPort.baudRate:"<<mConfigureData.baudRate;
    qDebug()<<"inp_serial::SerialPort.dataBits:"<<mConfigureData.dataBits;
    qDebug()<<"inp_serial::SerialPort.parity:"<<mConfigureData.parity;
    qDebug()<<"inp_serial::SerialPort.stopBit:"<<mConfigureData.stopBit;
    qDebug()<<"inp_serial::SerialPort.flowControl:"<<mConfigureData.flowControl;

    return true;
}

bool Inp_Serial::start()
{
    if(mSerialPort.open(QIODevice::ReadWrite)) {
        qDebug()<<"Serial Port.open:ok";
        m_statusLable->showMessage("Serial Port: open");
        return true;
    }
    else {
        qDebug()<<"Serial Port.open:err";
        m_statusLable->showMessage("Serial Port: opening error");
        return false;
    }
}



QString Inp_Serial::write_DATA(QString data)
{
    if(mSerialPort.isOpen()) {
        QByteArray data_latin = data.toLatin1();
        mSerialPort.write(data_latin);
        qDebug()<<"Serial Port.write: "<<data_latin;
        return data_latin;
    }
    else {
        return "err";
    }
}


bool Inp_Serial::stop()
{
    if (mSerialPort.isOpen()) {
        mSerialPort.close();
        qDebug()<<"Serial Port.close:ok";
        m_statusLable->showMessage("Serial Port: close");

        return true;
    }
    else {
        m_statusLable->showMessage("Serial Port: closing error");
        qDebug()<<"Serial Port.close:err";
        return false;
    }
}


bool Inp_Serial::read_DATA(QQueue<QString> & queueData)
{
    if(mSerialPort.isOpen()){
        //mSerialPort.readData += mQSerialPort.readAll();
        serialPort.readData += mSerialPort.readAll();
        if(serialPort.readData.length()!=0){
            qDebug()<<"Serial Port.read:str "<<serialPort.readData<<serialPort.readData.length();
            Inp_Serial::parsingMessage(queueData);
        }
        return true;
    }
    else return false;
}

void Inp_Serial::parsingMessage(QQueue<QString> & queueData)
{
    /*get message,
     *add message to buffer
     *extract all ready message
     *transmit message to function for analyse
     * startCondition="<"
     * endCondition=">"
    */

     const QChar startCondition='<';
     const QChar endCondition='>';
     int startConditionPosition;
     int endConditionPosition;

     do
     {
         startConditionPosition =serialPort.readData.indexOf(startCondition,0);
         switch (startConditionPosition){
         case -1:                       //"startCondition" not present in message
             serialPort.readData="";
             break;
         case 0:                        //"startCondition" in 0-position
             break;
         default:                       //"startCondition" present in message
             serialPort.readData.remove(0,startConditionPosition);           //remove startCondition
             break;
         }

         endConditionPosition= serialPort.readData.indexOf(endCondition,1);
         if(endConditionPosition !=-1){
             QString newMessage= serialPort.readData.left(endConditionPosition+1);
             serialPort.readData.remove(0,endConditionPosition+1);

             if(newMessage!=""){
                 qDebug()<<"inp_serial:enqueue"<<newMessage;
                 queueData.enqueue(newMessage);
             }
         }
     }
     while (endConditionPosition !=-1);
}
