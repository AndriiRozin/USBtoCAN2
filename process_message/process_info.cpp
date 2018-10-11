#include "process_info.h"
#include <QDebug>
#include <QTime>

#include "hmi/hmi_info.h"


Process_Info::Process_Info(QTableWidget * table_info)
    : m_tableInfo(table_info)
{

}

Process_Info::~Process_Info(){}

bool Process_Info::processMesage(QString messageData)
{
    const QString infoCondition="<I";
    const QString stopCondition=">";
    QString currentMessage=messageData;

    QString currentCondition=currentMessage.mid(0,2);  //Is current message INFO-type?
    if(currentCondition !=infoCondition) {
        return false;
    }

    QTime mtime=QTime::currentTime();                   //Get current TIME and DATE
    QString time=mtime.toString();
    QDate mdate=QDate::currentDate();
    QString date=mdate.toString("dd.MM.yyyy");

    currentMessage=currentMessage.remove(infoCondition);    //clear message
    currentMessage.remove(stopCondition);

    Hmi_info infoMessage(m_tableInfo);
    infoMessage.hmi_init();
    QStringList infoList={"06.10.2018", "13:08", "Info", "The first comment"};
    infoMessage.draw(infoList);
    infoMessage.draw(infoList);


//    int countRow=m_table->rowCount();
//    m_table->insertRow(countRow);
//    m_table->setItem(countRow,0,new QTableWidgetItem(date));
//    m_table->setItem(countRow,1,new QTableWidgetItem(time));
//    m_table->setItem(countRow,2,new QTableWidgetItem("Info"));
//    m_table->setItem(countRow,3,new QTableWidgetItem(currentMessage));

//    m_table->item(countRow,0)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,1)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,2)->setTextAlignment(Qt::AlignCenter);
//    m_table->item(countRow,2)->setTextColor(Qt::green);

//    m_table->scrollToBottom();

    qDebug()<<"processMesage:info:"<<date<<time<<"Info"<<currentMessage;
    return true;
}
