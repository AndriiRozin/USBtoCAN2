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
    QStringList tableInfo;
    tableInfo <<"Date"<<"Time"<<"State"<<"Comment";

    m_table_info->setColumnCount(4);
    m_table_info->setHorizontalHeaderLabels(tableInfo);
    m_table_info->horizontalHeader()->resizeSection(0,100);
    m_table_info->horizontalHeader()->resizeSection(1,100);
    m_table_info->horizontalHeader()->resizeSection(2,60);
    m_table_info->horizontalHeader()->resizeSection(3,60);
    m_table_info->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);

    m_table_info->horizontalHeader()->setStyleSheet("color: blue");
    m_table_info->horizontalHeader()->setVisible(true);
    m_table_info->verticalHeader()->setVisible(false);

    qDebug()<<"HMI_info: table was created";
    return true;
}
