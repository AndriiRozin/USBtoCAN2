#include "hmi_transmit.h"
#include <QDebug>

Hmi_transmit::Hmi_transmit(QTableWidget * table_tx)
    : m_table_tx(table_tx)
{}

Hmi_transmit::~Hmi_transmit()
{}

bool Hmi_transmit::draw(QString time)
{
    m_table_tx->setItem(1,0,new QTableWidgetItem(time));
    m_table_tx->setItem(1,1,new QTableWidgetItem("time"));
    m_table_tx->setItem(1,2,new QTableWidgetItem("Error"));
    qDebug()<<"Hmi_transmit::draw:"<<time;
    return true;
}

bool Hmi_transmit::hmi_key()
{
return true;
}

bool Hmi_transmit::hmi_init()
{
    return true;
}
