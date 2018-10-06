#include "hmi_filters.h"
#include <QDebug>

Hmi_filters::Hmi_filters(QTableWidget * table_filter)
    : m_table_filters(table_filter)
{}

Hmi_filters::~Hmi_filters()
{}

bool Hmi_filters::draw(QString time)
{
//    m_table_filters->setItem(1,0,new QTableWidgetItem(time));
//    m_table_filters->setItem(1,1,new QTableWidgetItem("time"));
//    m_table_filters->setItem(1,2,new QTableWidgetItem("Error"));
    qDebug()<<"Hmi_filters::draw:"<<time;
    return true;
}

bool Hmi_filters::hmi_key()
{
    return true;
}

bool Hmi_filters::hmi_init()
{
//    QStringList table_filters;
//    table_filters <<"Date"<<"Time"<<"State"<<"Comment";

//    m_table_filters->setColumnCount(4);
 //   m_table_filters->setHorizontalHeaderLabels("tableInfo");
    m_table_filters->horizontalHeader()->resizeSection(0,100);
    m_table_filters->horizontalHeader()->resizeSection(1,100);
    m_table_filters->horizontalHeader()->resizeSection(2,60);
    m_table_filters->horizontalHeader()->resizeSection(3,60);
    m_table_filters->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);

    m_table_filters->horizontalHeader()->setStyleSheet("color: blue");
    m_table_filters->horizontalHeader()->setVisible(true);

    qDebug()<<"HMI_info: table was created";
    return true;
}
