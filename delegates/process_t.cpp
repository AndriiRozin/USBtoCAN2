#include "process_t.h"
#include "messageprocessor.h"
#include "QDebug"

Process_t::Process_t() {}

Process_t::~Process_t() {}

bool Process_t::processMesage(QString data)
{
    const QString txCondLow="<t";
    QString currentCondition=data.mid(0,2);

    if(currentCondition != txCondLow) {
        return false;
    }

    qDebug()<<"processMesage:t"<<data;
    return true;
}
