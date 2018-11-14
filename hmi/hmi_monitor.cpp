#include "hmi_monitor.h"
#include <QDebug>

Hmi_monitor::Hmi_monitor(QTableWidget * table_monitor)
    : m_table_monitor(table_monitor)
{}

Hmi_monitor::~Hmi_monitor()
{}

bool Hmi_monitor::edit(QStringList strlist)
{
    qDebug()<<"Hmi_monitor::edit"<<strlist;
    return true;
}

bool Hmi_monitor::draw(QStringList str_list)
{
    int countRow = m_table_monitor->rowCount();
    m_table_monitor->insertRow(countRow);

    m_table_monitor->setItem(countRow,0,new QTableWidgetItem(str_list.at(0)));
    m_table_monitor->item(countRow,0)->setTextAlignment(Qt::AlignCenter);

    m_table_monitor->setItem(countRow,1,new QTableWidgetItem(str_list.at(1)));
    m_table_monitor->item(countRow,1)->setTextAlignment(Qt::AlignCenter);

    m_table_monitor->setItem(countRow,2,new QTableWidgetItem(str_list.at(2)));
    m_table_monitor->item(countRow,2)->setTextAlignment(Qt::AlignCenter);

    m_table_monitor->setItem(countRow,3,new QTableWidgetItem(str_list.at(3)));
    m_table_monitor->item(countRow,3)->setTextAlignment(Qt::AlignCenter);

    m_table_monitor->setItem(countRow,4,new QTableWidgetItem(str_list.at(4)));
    m_table_monitor->item(countRow,4)->setTextAlignment(Qt::AlignCenter);

    m_table_monitor->setItem(countRow,5,new QTableWidgetItem(str_list.at(5)));

    m_table_monitor->setItem(countRow,6,new QTableWidgetItem(str_list.at(6)));

    if (monitor_down_flag){
        m_table_monitor->scrollToBottom();
    }
    qDebug()<<"Hmi_monitor::draw:ok";
    return true;
}

bool Hmi_monitor::hmi_key(QStringList strlist)
{
    QString down_table_status=strlist.at(0);
    if(down_table_status=="Down_true"){
        monitor_down_flag = true;
    }
    else{
        monitor_down_flag = false;
    }
    qDebug()<<"Hmi_monitor::hmi_key"<<down_table_status<<monitor_down_flag;
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
