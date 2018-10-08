#include "hmi_filter.h"
#include <QDebug>

Hmi_filter::Hmi_filter(QTableWidget * table_filter)
    : m_table_filter(table_filter)
{}

Hmi_filter::~Hmi_filter()
{}

bool Hmi_filter::draw(QStringList str_list)
{
    for(int i=0; i<4; i++){
        m_table_filter->setItem(0,i+1,new QTableWidgetItem(str_list.at(i)));
        m_table_filter->item(0,i+1)->setTextAlignment(Qt::AlignCenter);
    }

    qDebug()<<"Hmi_info::draw: ok";
    return true;
}

bool Hmi_filter::hmi_key()
{
    return true;
}

bool Hmi_filter::hmi_init()
{
    QStringList tableFilter;
    tableFilter <<"Filter"<<"ID1H"<<"ID1L"<<"ID2H"<<"ID2L"<<"Result";
            //<<"No"<<"ID1"<<"ID2"<<"ID3"<<"ID4";

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
