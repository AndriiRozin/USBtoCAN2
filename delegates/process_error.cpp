#include "process_error.h"
#include <QDebug>
#include <QTime>

Process_Error::Process_Error(QTableWidget * table)
    : m_table(table)
{}

Process_Error::~Process_Error()
{}

bool Process_Error::processMesage(QString messageData)
{
    const QString errCondition="<E";
    const QString stopCondition=">";
    QString currentMessage=messageData;

    QString currentCondition=currentMessage.mid(0,2);   //Is message Error-type
    if(currentCondition !=errCondition) {
        return false;
    }

    QTime mtime=QTime::currentTime();                   //get Date and Time
    QString time=mtime.toString();
    QDate mdate=QDate::currentDate();
    QString date=mdate.toString("dd.MM.yyyy");

    currentMessage=currentMessage.remove(errCondition);     //clear message
    currentMessage.remove(stopCondition);



    int countRow=m_table->rowCount();
    m_table->insertRow(countRow);
    m_table->setItem(countRow,0,new QTableWidgetItem(date));
    m_table->setItem(countRow,1,new QTableWidgetItem(time));
    m_table->setItem(countRow,2,new QTableWidgetItem("Error"));
    m_table->setItem(countRow,3,new QTableWidgetItem(currentMessage));

    m_table->item(countRow,0)->setTextAlignment(Qt::AlignCenter);
    m_table->item(countRow,1)->setTextAlignment(Qt::AlignCenter);
    m_table->item(countRow,2)->setTextAlignment(Qt::AlignCenter);
    m_table->item(countRow,2)->setTextColor(Qt::red);

    m_table->scrollToBottom();

    qDebug()<<"processMesage:error:"<<date<<time<<currentMessage;

    return true;
}



