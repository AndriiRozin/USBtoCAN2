#include "hmi_filter.h"
#include <QDebug>

Hmi_filter::Hmi_filter(QTableWidget * table_filter)
    : m_table_filter(table_filter)
{}

Hmi_filter::~Hmi_filter()
{}

bool Hmi_filter::draw(QString time)
{
    m_table_filter->setItem(1,1,new QTableWidgetItem(time));
    m_table_filter->setItem(1,2,new QTableWidgetItem("time"));
    m_table_filter->setItem(1,3,new QTableWidgetItem("Error"));
    qDebug()<<"Hmi_info::draw:"<<time;
    return true;
}

bool Hmi_filter::hmi_key()
{
    return true;
}

bool Hmi_filter::hmi_init()
{
    QStringList tableFilter;
    tableFilter <<"No"<<"ID1"<<"ID2"<<"ID3"<<"ID4";

    m_table_filter->setColumnCount(6);
    m_table_filter->setHorizontalHeaderLabels(tableFilter);
    m_table_filter->horizontalHeader()->resizeSection(0,60);
    m_table_filter->horizontalHeader()->resizeSection(1,60);
    m_table_filter->horizontalHeader()->resizeSection(2,60);
    m_table_filter->horizontalHeader()->resizeSection(3,60);
    m_table_filter->horizontalHeader()->resizeSection(4,60);
    m_table_filter->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Stretch);

    m_table_filter->horizontalHeader()->setStyleSheet("color: blue");
    m_table_filter->horizontalHeader()->setVisible(true);

    qDebug()<<"HMI_filter: table was created";
    return true;
}
