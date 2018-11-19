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

    bool convertOK;
    int setRow = setRow_str.toInt(&convertOK,10);
    if(!convertOK) setRow=-1;

    int newRow = m_table_filter->rowCount();   //counter of new row
    int row =newRow;

    if(setRow==-1 || setRow>=newRow){
            row =newRow;
        qDebug()<<"Hmi_filter::draw:new"<<"setRow="<<setRow<<"newRow="<<newRow;
        Hmi_filter::createNewRow();
    }
    else{
            row =setRow;
        qDebug()<<"Hmi_filter::draw:edit"<<"setRow="<<setRow<<"newRow="<<newRow;
        Hmi_filter::editCurrentRow(row);
    }

    qDebug()<<"Hmi_info::draw: ok";
    return true;
}

void Hmi_filter::createNewRow()
{
    int row = m_table_filter->rowCount();   //counter of new row
    m_table_filter->insertRow(row);

    m_table_filter->setItem(row,0,new QTableWidgetItem(QString::number(row)));
    if(filterCAN.filter[row].status){
        m_table_filter->item(row,0)->setCheckState(Qt::Checked);
    }
    else{
        m_table_filter->item(row,0)->setCheckState(Qt::Unchecked);
    }


    m_table_filter->setItem(row,1,new QTableWidgetItem(filterCAN.filter[row].data1));
    m_table_filter->setItem(row,2,new QTableWidgetItem(filterCAN.filter[row].data2));
    m_table_filter->setItem(row,3,new QTableWidgetItem(filterCAN.filter[row].data3));
    m_table_filter->setItem(row,4,new QTableWidgetItem(filterCAN.filter[row].data4));
    m_table_filter->setItem(row,5,new QTableWidgetItem(filterCAN.filter[row].comment));

    m_table_filter->item(row,0)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,1)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,2)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,3)->setTextAlignment(Qt::AlignCenter);
    m_table_filter->item(row,4)->setTextAlignment(Qt::AlignCenter);

    Hmi_filter::colorRow(row);
}

void Hmi_filter::colorRow(int row)
{
    if(filterCAN.filter[row].status){
        m_table_filter->item(row,1)->setTextColor(Qt::black);
        m_table_filter->item(row,2)->setTextColor(Qt::black);
        m_table_filter->item(row,3)->setTextColor(Qt::black);
        m_table_filter->item(row,4)->setTextColor(Qt::black);
        m_table_filter->item(row,5)->setTextColor(Qt::black);
    }
    else {
        m_table_filter->item(row,1)->setTextColor(Qt::gray);
        m_table_filter->item(row,2)->setTextColor(Qt::gray);
        m_table_filter->item(row,3)->setTextColor(Qt::gray);
        m_table_filter->item(row,4)->setTextColor(Qt::gray);
        m_table_filter->item(row,5)->setTextColor(Qt::gray);
    }
}


void Hmi_filter::editCurrentRow(int row)
{
    qDebug()<<"Hmi_filter::editCurrentRow"<<row;
    m_table_filter->item(row,1)->setText(filterCAN.filter[row].data1);
    m_table_filter->item(row,2)->setText(filterCAN.filter[row].data2);
    m_table_filter->item(row,3)->setText(filterCAN.filter[row].data3);
    m_table_filter->item(row,4)->setText(filterCAN.filter[row].data4);
    m_table_filter->item(row,5)->setText(filterCAN.filter[row].comment);

    Hmi_filter::colorRow(row);
    return;
}

bool Hmi_filter::hmi_key(QStringList command)
{
    qDebug()<<"Hmi_filter::hmi_key"<<command;

    if(command.at(0)=="save")
    {
        QSettings  settings("USBtoCAN.ini",QSettings::IniFormat);
        QString group;

        for (int row=0; row<13; row++){
            group = "Filter"+QString::number(row);
            settings.beginGroup(group);
            settings.setValue("status",filterCAN.filter[row].status);
            settings.setValue("data1", filterCAN.filter[row].data1);
            settings.setValue("data2", filterCAN.filter[row].data2);
            settings.setValue("data3", filterCAN.filter[row].data3);
            settings.setValue("data4", filterCAN.filter[row].data4);
            settings.setValue("comment", filterCAN.filter[row].comment);
            settings.endGroup();
        }
        qDebug()<<"Hmi_filter::hmi_key:all table was saved";
    }
    return true;
}

bool Hmi_filter::hmi_init()
{
    initFlag=true;
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
    initFlag=false;
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

        qDebug()<<"Hmi_filter::loadFilterFromFile"  <<"Filter"+QString::number(i)
                                                    <<filterCAN.filter[i].status
                                                    <<filterCAN.filter[i].data1
                                                    <<filterCAN.filter[i].data2
                                                    <<filterCAN.filter[i].data3
                                                    <<filterCAN.filter[i].data4
                                                    <<filterCAN.filter[i].comment;

        QStringList currentRow;         //write data to table
        currentRow <<QString::number(i);
        Hmi_filter::draw(currentRow);
    }
}



bool Hmi_filter::edit(QStringList str_list)
    //write edit_data to structure after INITmode(initFlag)
{
   if(!initFlag) {
    int row = str_list.at(0).toInt();
    int column = str_list.at(1).toInt();
    QString iniFileGroup = "Filter"+QString::number(row);

    switch (column)
    {
    case 0:
        filterCAN.filter[row].status=m_table_filter->item(row,0)->checkState();
        Hmi_filter::colorRow(row);
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"status="<<filterCAN.filter[row].status;
        break;
    case 1:
        filterCAN.filter[row].data1 = m_table_filter->item(row,column)->text();
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data1="<<filterCAN.filter[row].data1;
        break;
    case 2:
        filterCAN.filter[row].data2 = m_table_filter->item(row,column)->text();
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data2="<<filterCAN.filter[row].data2;
        break;
    case 3:
        filterCAN.filter[row].data3 = m_table_filter->item(row,column)->text();
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data3="<<filterCAN.filter[row].data3;
        break;
    case 4:
        filterCAN.filter[row].data4 = m_table_filter->item(row,column)->text();
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"data4="<<filterCAN.filter[row].data4;
        break;
    case 5:
        filterCAN.filter[row].comment = m_table_filter->item(row,column)->text();
        qDebug()<<"Hmi_filter::edit"<<iniFileGroup<<"comment="<<filterCAN.filter[row].comment;
        break;
    default:
        break;
    }
}
   return true;
}
