#include "hmi_status.h"
#include <QDebug>
#include "mainwindow.h"

Hmi_status::Hmi_status(QStatusBar * status_bar)
    : m_statusBar(status_bar)
{}

Hmi_status::~Hmi_status()
{}

bool Hmi_status::draw(QString time)
{
    qDebug()<<"Hmi_status::draw:"<<time;
    m_statusBar->showMessage(time);
    return true;
}

bool Hmi_status::hmi_key()
{
    return true;
}

bool Hmi_status::hmi_init()
{
    return true;
}
