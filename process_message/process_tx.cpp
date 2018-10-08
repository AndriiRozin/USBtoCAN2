#include "process_tx.h"
#include <QDebug>

Process_Tx::Process_Tx() {}

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



    qDebug()<<"processMesage:TX"<<"N="<<currentNumber<<"T="<<currentTime<<"ID="<<currentID<<"DLC="<<currentDLC<<"Data="<<currentData;

//    int countRow = m_table->rowCount();       //create new row
//    m_table->insertRow(countRow);
//    m_table->setItem(countRow,0,new QTableWidgetItem(currentNumber));
//    m_table->setItem(countRow,1,new QTableWidgetItem(currentTime));
//    m_table->setItem(countRow,2,new QTableWidgetItem("Tx"));
//    m_table->setItem(countRow,3,new QTableWidgetItem(currentID));
//    m_table->setItem(countRow,4,new QTableWidgetItem(currentDLC));
//    m_table->setItem(countRow,5,new QTableWidgetItem(currentData));
//    m_table->setItem(countRow,6,new QTableWidgetItem(currentISCII));

//    m_table->item(countRow,0)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,1)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,2)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,3)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,4)->setTextAlignment(Qt::AlignCenter);

//    if(currentNumber=="Err"){
//        m_table->item(countRow,0)->setTextColor(Qt::red);
//    }
//    if(currentTime=="Err"){
//        m_table->item(countRow,1)->setTextColor(Qt::red);
//    }
//    if(currentDLC=="Err"){
//        m_table->item(countRow,4)->setTextColor(Qt::red);
//    }

//    m_table->scrollToBottom();

    return true;
}
