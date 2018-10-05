#include "hmi_info.h"
#include <QDebug>


Hmi_info::Hmi_info(QTableWidget * table_info)
    : m_table_info(table_info)
{}

Hmi_info::~Hmi_info()
{}

bool Hmi_info::draw(QString time)
{
    m_table_info->setItem(1,0,new QTableWidgetItem(time));
    m_table_info->setItem(1,1,new QTableWidgetItem("time"));
    m_table_info->setItem(1,2,new QTableWidgetItem("Error"));
    qDebug()<<"Hmi_info::draw:"<<time;
    return true;
}

bool Hmi_info::hmi_key()
{
    return true;
}

bool Hmi_info::hmi_init()
{
    return true;
}
