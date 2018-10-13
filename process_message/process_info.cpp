#include "process_info.h"
#include <QDebug>
#include <QTime>

Process_Info::Process_Info(Hmi_info * info_viewer)
    : m_info_viewer(info_viewer)
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

    QStringList infoList={date, time, "Info", currentMessage};
    m_info_viewer->draw(infoList);

    qDebug()<<"processMesage:info:"<<date<<time<<"Info"<<currentMessage;
    return true;
}
