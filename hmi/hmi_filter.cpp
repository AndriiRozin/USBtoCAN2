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
    int countRow = m_table_filter->rowCount();
    m_table_filter->insertRow(countRow);
    for(int i=0; i<=4; i++){
        m_table_filter->setItem(countRow,i,new QTableWidgetItem(str_list.at(i)));
        m_table_filter->item(countRow,i)->setTextAlignment(Qt::AlignCenter);
        if(str_list[5]=="true"){
            m_table_filter->item(countRow,0)->setCheckState(Qt::Checked);
        }
        else{
            m_table_filter->item(countRow,0)->setCheckState(Qt::Unchecked);
        }

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

    Hmi_filter::loadFilterFromFile();
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

    QString number;
    QString data1;
    QString data2;
    QString data3;
    QString data4;
    QString status;

    for (int i=0; i<=13; i++ )
    {
        settings.beginGroup("Filter"+QString::number(i));
        number=QString::number(i);
        data1 = settings.value("data1").toString();
        data2 = settings.value("data2").toString();
        data3 = settings.value("data3").toString();
        data4 = settings.value("data4").toString();
        status = settings.value("status").toString();
        settings.endGroup();


        QStringList currentRow;
        currentRow <<number<<data1<<data2<<data3<<data4<<status;
        Hmi_filter::draw(currentRow);


        qDebug()<<"Hmi_filter"<<currentRow;


    }
}
