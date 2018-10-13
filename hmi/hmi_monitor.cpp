#include "hmi_monitor.h"
#include <QDebug>

Hmi_monitor::Hmi_monitor(QTableWidget * table_monitor)
    : m_table_monitor(table_monitor)
{}

Hmi_monitor::~Hmi_monitor()
{}

bool Hmi_monitor::draw(QStringList str_list)
{
    int countRow = m_table_monitor->rowCount();
    m_table_monitor->insertRow(countRow);
    for (int i=0; i<7; i++){
        m_table_monitor->setItem(countRow,i,new QTableWidgetItem(str_list.at(i)));
        m_table_monitor->item(countRow,i)->setTextAlignment(Qt::AlignCenter);
    }

    m_table_monitor->scrollToBottom();

    qDebug()<<"Hmi_monitor::draw:ok";
    return true;
}

bool Hmi_monitor::hmi_key()
{
    return true;
}

bool Hmi_monitor::hmi_init()
{
    QStringList table_Monitor;
    table_Monitor <<"No"<<"Time (ms)"<<"State"<<"ID (hex)"<<"DLC"<<"Data (hex)"<<"ASCII";

    m_table_monitor->setColumnCount(7);
    m_table_monitor->setHorizontalHeaderLabels(table_Monitor);

    m_table_monitor->horizontalHeader()->resizeSection(0,60);
    m_table_monitor->horizontalHeader()->resizeSection(1,60);
    m_table_monitor->horizontalHeader()->resizeSection(2,60);
    m_table_monitor->horizontalHeader()->resizeSection(3,60);
    m_table_monitor->horizontalHeader()->resizeSection(4,60);
    m_table_monitor->horizontalHeader()->resizeSection(5,150);
    m_table_monitor->horizontalHeader()->setSectionResizeMode(6,QHeaderView::Stretch);

    m_table_monitor->horizontalHeader()->setStyleSheet("color: blue");
    m_table_monitor->horizontalHeader()->setVisible(true);
    m_table_monitor->verticalHeader()->setVisible(false);

    qDebug()<<"HMI_monitor: table was created";
    return true;
}
