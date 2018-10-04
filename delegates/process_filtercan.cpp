#include "process_filtercan.h"
#include <QDebug>
#include <QTime>

Process_FilterCAN::Process_FilterCAN(QTableWidget * table)
    : m_table(table)
{}

Process_FilterCAN::~Process_FilterCAN() {}



bool Process_FilterCAN::processMesage(QString messageData)
{
    const QString filterCondition="<F";
    const QString stopCondition=">";
    QString currentMessage=messageData;
    QString currentCondition=messageData.mid(0,2);

    if(currentCondition !=filterCondition) {        //Is current message Filter-type?
        return false;
    }

    QTime mtime=QTime::currentTime();               //get current time and date
    QString time=mtime.toString();
    QDate mdate=QDate::currentDate();
    QString date=mdate.toString("dd.MM.yyyy");

    QString outMessage;
    QString fNumber;
    QString fStatus;
    QString id1;
    QString id2;
    QString id3;
    QString id4;
    QString fMode;
    QString fScale;
    QString fFifo;
    QString fRate;

    currentMessage=currentMessage.remove(0,2);    //clear filterCondition

    fNumber = currentMessage.mid(0,1);      //read number of Filter
    currentMessage=currentMessage.remove(0,1);    //clear message

    fStatus=currentMessage.mid(0,1);
    currentMessage=currentMessage.remove(0,1);    //clear message



    id1=currentMessage.mid(0,3);            //read id from message
    id2=currentMessage.mid(3,3);
    id3=currentMessage.mid(6,3);
    id4=currentMessage.mid(10,3);
    currentMessage=currentMessage.remove(0,10);


    fMode=currentMessage.mid(16,1);         //read filter Mode from message
    if(fMode=="0"){
        fMode="ID list;";
    }
    else{
        fMode="ID mask;";
    }

    fScale=currentMessage.mid(17,1);        //read filter Scale from message
    if(fScale=="0"){
        fScale=" 16bit;";
    }
    else{
        fScale=" 32bit;";
    }

    fFifo=currentMessage.mid(18,1);       //read FIFO from message
    if(fFifo=="0"){
        fFifo=" FIFO0;";
    }
    else{
        fFifo=" FIFO1;";
    }

    fRate=currentMessage.mid(19,1);        //read CAN rate from message
    if(fRate=="0"){
        fRate=" 1000K;";
    }
    else if(fRate=="1"){
        fRate=" 500K;";
    }
    else{
        fRate=" 250k;";
    }


    if(fStatus=="0"){      //print filterStatus
        fStatus +="Off";
        outMessage = "F"+fNumber+"-"+fStatus;
    }
    else{
        fStatus +="On";
        outMessage = "F"+fNumber+"-"+fStatus+"; id: "+id1+", "+id2+", "+id3+", "+id4 +"; "+fMode+ fScale +fFifo +fRate;
    }


    //write data to info-table
    int countRow=m_table->rowCount();
    m_table->insertRow(countRow);
    m_table->setItem(countRow,0,new QTableWidgetItem(date));
    m_table->setItem(countRow,1,new QTableWidgetItem(time));
    m_table->setItem(countRow,2,new QTableWidgetItem("Config"));
    m_table->setItem(countRow,3,new QTableWidgetItem(outMessage));

    m_table->item(countRow,0)->setTextAlignment(Qt::AlignCenter);
    m_table->item(countRow,1)->setTextAlignment(Qt::AlignCenter);
    m_table->item(countRow,2)->setTextAlignment(Qt::AlignCenter);
    m_table->item(countRow,2)->setTextColor(Qt::blue);

    m_table->scrollToBottom();

    qDebug()<<"processMesage:filterCAN:"<<outMessage;
    return true;
}
