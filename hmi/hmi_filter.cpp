#include "hmi_filter.h"
#include <QDebug>
#include <QSettings>
#include <QListWidget>

Hmi_filter::Hmi_filter(QTableWidget * table_filter)
    : m_table_filter(table_filter)
{}

Hmi_filter::~Hmi_filter()
{}



bool Hmi_filter::draw(QStringList str_list)
{
    QString setRow_str=str_list.at(0);
    QString data1=str_list.at(1);
    QString data2=str_list.at(2);
    QString data3=str_list.at(3);
    QString data4=str_list.at(4);
    QString status=str_list.at(5);
    QString comment=str_list.at(6);

    bool convertOK;
    int setRow = setRow_str.toInt(&convertOK,10);
    if(!convertOK) setRow=-1;

    int newRow = m_table_filter->rowCount();   //counter of new row
    int row =newRow;

    Hmi_filter::createNewRow(data1, data2, data3, data4,comment);
//    switch (setRow) {
//    case -1:

//        break;

//    default:
// //       Hmi_filter::editCurrentRow(row, data1, data2, data3, data4);
//        break;

//    }




    if(status=="true"){
        m_table_filter->item(row,0)->setCheckState(Qt::Checked);
        m_table_filter->item(row,1)->setTextColor(Qt::black);
        m_table_filter->item(row,2)->setTextColor(Qt::black);
        m_table_filter->item(row,3)->setTextColor(Qt::black);
        m_table_filter->item(row,4)->setTextColor(Qt::black);
        }
    else{
        m_table_filter->item(row,0)->setCheckState(Qt::Unchecked);
        m_table_filter->item(row,1)->setTextColor(Qt::gray);
        m_table_filter->item(row,2)->setTextColor(Qt::gray);
        m_table_filter->item(row,3)->setTextColor(Qt::gray);
        m_table_filter->item(row,4)->setTextColor(Qt::gray);
    }
    qDebug()<<"Hmi_info::draw: ok";
    return true;
}

void Hmi_filter::createNewRow(QString data1,QString data2,QString data3,QString data4,QString comment)
{
    int row = m_table_filter->rowCount();   //counter of new row
    m_table_filter->insertRow(row);
    m_table_filter->setItem(row,0,new QTableWidgetItem(QString::number(row)));
    m_table_filter->setItem(row,1,new QTableWidgetItem(data1));
    m_table_filter->setItem(row,2,new QTableWidgetItem(data2));
    m_table_filter->setItem(row,3,new QTableWidgetItem(data3));
    m_table_filter->setItem(row,4,new QTableWidgetItem(data4));
    m_table_filter->setItem(row,5,new QTableWidgetItem(comment));

    m_table_filter->item(row,0)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,1)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,2)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,3)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,4)->setTextAlignment(Qt::AlignCenter);
}

void Hmi_filter::editCurrentRow(int row,QString data1,QString data2,QString data3,QString data4)
{
    m_table_filter->item(row,1)->setText(data1);
    m_table_filter->item(row,2)->setText(data2);
    m_table_filter->item(row,3)->setText(data3);
    m_table_filter->item(row,4)->setText(data4);
}

bool Hmi_filter::hmi_key(QStringList strlist)
{
    return true;
}

bool Hmi_filter::hmi_init()
{
    QStringList tableFilter;
    tableFilter <<"Filter"<<"ID1H"<<"ID1L"<<"ID2H"<<"ID2L"<<"Comment";
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

void Hmi_filter::loadFilterFromFile()  //to table
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

    QString status_str;

    for (int i=0; i<=13; i++ )
    {
        settings.beginGroup("Filter"+QString::number(i));  //read data to structure from file
        filterCAN.filter[i].data1 = settings.value("data1").toString();
        filterCAN.filter[i].data2 = settings.value("data2").toString();
        filterCAN.filter[i].data3 = settings.value("data3").toString();
        filterCAN.filter[i].data4 = settings.value("data4").toString();
        filterCAN.filter[i].comment = settings.value("comment").toString();
        filterCAN.filter[i].status = settings.value("status").toBool();
        settings.endGroup();

        if(filterCAN.filter[i].status){
            status_str="true";
        }
        else {
            status_str="false";
        }

        QStringList currentRow;         //write data to table
        currentRow <<"+"
                   <<filterCAN.filter[i].data1
                   <<filterCAN.filter[i].data2
                   <<filterCAN.filter[i].data3
                   <<filterCAN.filter[i].data4
                   <<status_str
                   <<filterCAN.filter[i].comment ;
        Hmi_filter::draw(currentRow);
        qDebug()<<"Hmi_filter::draw"<<currentRow;
    }
}



bool Hmi_filter::edit(QStringList str_list)
    //write edit_data to structure and to file
{
    int row = str_list.at(0).toInt();
    int column = str_list.at(1).toInt();
    QString iniFileGroup = "Filter"+QString::number(row);

    filterCAN.filter[row].status=m_table_filter->item(row,0)->checkState();

    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;
    settings.beginGroup(iniFileGroup);

    switch (column)
    {
     case 0:
        settings.setValue("status",filterCAN.filter[row].status);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"status="<<filterCAN.filter[row].status;
        break;
    case 1:
        filterCAN.filter[row].data1 = m_table_filter->item(row,column)->text();
        settings.setValue("data1",filterCAN.filter[row].data1);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data1="<<filterCAN.filter[row].data1;
        break;
    case 2:
        filterCAN.filter[row].data2 = m_table_filter->item(row,column)->text();
        settings.setValue("data2",filterCAN.filter[row].data2);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data2="<<filterCAN.filter[row].data2;
        break;
    case 3:
        filterCAN.filter[row].data3 = m_table_filter->item(row,column)->text();
        settings.setValue("data3",filterCAN.filter[row].data3);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data3="<<filterCAN.filter[row].data3;
        break;
    case 4:
        filterCAN.filter[row].data4 = m_table_filter->item(row,column)->text();
        settings.setValue("data4",filterCAN.filter[row].data4);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data4="<<filterCAN.filter[row].data4;
        break;
    case 5:
        filterCAN.filter[row].comment = m_table_filter->item(row,column)->text();
        settings.setValue("comment",filterCAN.filter[row].comment);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data4="<<filterCAN.filter[row].comment;
        break;

    default:
        break;
    }
    settings.endGroup();
    return true;
}
