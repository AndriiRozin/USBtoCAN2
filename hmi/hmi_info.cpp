#include "hmi_info.h"
#include <QDebug>

bool Hmi_info::draw(QString time)
{
    qDebug()<<"Hmi_info::draw:"<<time;
    return true;
}

bool Hmi_info::hmi_key()
{
    return true;
}
