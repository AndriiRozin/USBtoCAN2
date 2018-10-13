#include "process_error.h"
#include <QDebug>
#include <QTime>

Process_Error::Process_Error(Hmi_info * info_viewer)
    : m_info_viewer(info_viewer)
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

    QStringList infoList={date, time, "Err", currentMessage};
    m_info_viewer->draw(infoList);
    qDebug()<<"processMesage:error:"<<date<<time<<currentMessage;

    return true;
}
