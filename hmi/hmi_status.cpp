#include "hmi_status.h"
#include <QDebug>
#include "mainwindow.h"

Hmi_status::Hmi_status(QStatusBar * status_bar)
    : m_statusBar(status_bar)
{}

Hmi_status::~Hmi_status()
{}

bool Hmi_status::draw(QStringList str_list)
{
    qDebug()<<"Hmi_status::draw:";
    m_statusBar->showMessage(str_list.at(0));
    return true;
}

bool Hmi_status::hmi_key(QStringList strlist)
{
    return true;
}

bool Hmi_status::hmi_init()
{
    return true;
}
