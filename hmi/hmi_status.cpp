#include "hmi_status.h"
#include <QDebug>

bool Hmi_status::draw(QString time)
{
    qDebug()<<"Hmi_status::draw:"<<time;
//    ui->statusBar->showMessage("Data Port: not connect");
    return true;
}

bool Hmi_status::hmi_key()
{
    return true;
}
