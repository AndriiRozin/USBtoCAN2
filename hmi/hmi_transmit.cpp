#include "hmi_transmit.h"
#include <QDebug>

bool Hmi_transmit::draw(QString time)
{
    qDebug()<<"Hmi_transmit::draw:"<<time;
    return true;
}

bool Hmi_transmit::hmi_key()
{
return true;
}
