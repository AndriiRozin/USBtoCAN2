#include "process_tx.h"
#include <QDebug>

Process_Tx::Process_Tx(Hmi_monitor * monitor_viewer)
    : m_monitor_viewer(monitor_viewer)
{}

Process_Tx::~Process_Tx() {}

bool Process_Tx::processMesage(QString messageData)
{
    const QString txCondition="<T";
    const QString stopCondition=">";
    QString currentMessage=messageData;

    QString currentCondition=currentMessage.mid(0,2);   //Is current message TX-type?
    if(currentCondition != txCondition) {
        return false;
    }


    bool ok;
    int temp;
    QString currentData="";
    QString currentISCII="";

    currentMessage.remove(txCondition);         //clear message
    currentMessage.remove(stopCondition);

    QString currentNumber=currentMessage.mid(0,4);
    currentMessage.remove(0,4);                    //remove currentNumber
    temp = currentNumber.toInt(&ok,16);     //number: hex(16)->to int(10)
    if(ok==false){
       currentNumber="Err";
    }
    else {
       currentNumber = QString("%L2").arg(temp);
    }

    QString currentTime=currentMessage.mid(0,4);
    currentMessage.remove(0,4);                    //remove currentTime
    temp = currentTime.toInt(&ok,16);
    if(ok==false){
        currentTime="Err";
    }
    else {
        currentTime=QString("%L2").arg(temp);
    }

    QString currentID=currentMessage.mid(0,3);
    currentMessage.remove(0,3);                    //remove currentID

    QString currentDLC=currentMessage.mid(0,1);
    currentMessage.remove(0,1);                    //remove currentDLC
    temp = currentDLC.toInt(&ok,16);     //number: hex(16)->to int(10)
        if(ok==false){
            currentDLC="Err";
        }
        else {
          for (int i=0; i<=temp; i++)
          {
              if(i==0) {
                   currentData ="";
              }
              else if(i==9){
                  currentData="Remote Frame (DLC=0)";
                  currentDLC="0";
                  currentISCII="";
              }
              else {
                   currentData = currentData+currentMessage.mid(0,2)+" ";
                   currentMessage.remove(0,2);                    //remove currentDLC
                   currentISCII=QString::fromLocal8Bit(QByteArray::fromHex(currentData.toLatin1()));
              }
          }
       }


    QStringList monitorList = {currentNumber,currentTime,"TX",currentID,currentDLC,currentData, "ascii"};
    m_monitor_viewer->draw(monitorList);
    qDebug()<<"processMesage:TX"<<"N="<<currentNumber<<"T="<<currentTime<<"ID="<<currentID<<"DLC="<<currentDLC<<"Data="<<currentData;

    return true;
}
