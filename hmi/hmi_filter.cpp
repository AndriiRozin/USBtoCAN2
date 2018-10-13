#include "hmi_filter.h"
#include <QDebug>
#include <QSettings>

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
    int column_count=tableFilter.size();

    m_table_filter->setColumnCount(column_count);
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

void Hmi_filter::loadFilterFromFile()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;

    settings.beginGroup("FilterCAN");
    filterCAN.mode=settings.value("filterMode").toInt();
    filterCAN.scale=settings.value("filterScale").toInt();
    filterCAN.fifo=settings.value("fifoBuffer").toInt();
    settings.endGroup();

    settings.beginGroup("CANbus");
    filterCAN.baudRate=settings.value("baudRate").toInt();
    settings.endGroup();


    for (int i=0; i<=13; i++ )
    {
        settings.beginGroup("Filter"+QString::number(i));
        filterCAN.filter[i].data1 = settings.value("data1").toString();
        filterCAN.filter[i].data2 = settings.value("data2").toString();
        filterCAN.filter[i].data3 = settings.value("data3").toString();
        filterCAN.filter[i].data4 = settings.value("data4").toString();
        filterCAN.filter[i].status = settings.value("status").toBool();
        settings.endGroup();

        qDebug()<<"load filter"+QString::number(i)<<filterCAN.filter[i].data1
                                    <<filterCAN.filter[i].data2
                                    <<filterCAN.filter[i].data3
                                    <<filterCAN.filter[i].data4
                                    <<filterCAN.filter[i].status;

    }
}
