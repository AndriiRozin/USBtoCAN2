#include "hmi_info.h"
#include <QDebug>

Hmi_info::Hmi_info(QTableWidget * table_info)
    : m_table_info(table_info)
{}

Hmi_info::~Hmi_info()
{

}

bool Hmi_info::draw(QStringList str_list)
{
    int countRow = m_table_info->rowCount();
    m_table_info->insertRow(countRow);

        m_table_info->setItem(countRow,0,new QTableWidgetItem(str_list.at(0)));
        m_table_info->item(countRow,0)->setTextAlignment(Qt::AlignCenter);

        m_table_info->setItem(countRow,1,new QTableWidgetItem(str_list.at(1)));
        m_table_info->item(countRow,1)->setTextAlignment(Qt::AlignCenter);

        m_table_info->setItem(countRow,2,new QTableWidgetItem(str_list.at(2)));
        m_table_info->item(countRow,2)->setTextAlignment(Qt::AlignCenter);

        m_table_info->setItem(countRow,3,new QTableWidgetItem(str_list.at(3)));



    m_table_info->scrollToBottom();
    qDebug()<<"Hmi_info::draw:ok";
    return true;
}

bool Hmi_info::hmi_key(QStringList strlist)
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
