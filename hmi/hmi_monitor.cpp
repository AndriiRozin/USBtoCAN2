#include "hmi_monitor.h"
#include <QDebug>

bool Hmi_monitor::draw(QString time)
{
    qDebug()<<"Hmi_monitor::draw:"<<time;
    return true;
}

bool Hmi_monitor::hmi_key()
{
    return true;
}
