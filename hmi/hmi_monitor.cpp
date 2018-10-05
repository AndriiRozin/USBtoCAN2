#include "hmi_monitor.h"
#include <QDebug>

Hmi_monitor::Hmi_monitor(QTableWidget * table_monitor)
    : m_table_monitor(table_monitor)
{}

Hmi_monitor::~Hmi_monitor()
{}

bool Hmi_monitor::draw(QString time)
{
    m_table_monitor->setItem(1,0,new QTableWidgetItem(time));
    m_table_monitor->setItem(1,1,new QTableWidgetItem("time"));
    m_table_monitor->setItem(1,2,new QTableWidgetItem("Error"));
    qDebug()<<"Hmi_monitor::draw:"<<time;
    return true;
}

bool Hmi_monitor::hmi_key()
{
    return true;
}

bool Hmi_monitor::hmi_init()
{
    return true;
}
