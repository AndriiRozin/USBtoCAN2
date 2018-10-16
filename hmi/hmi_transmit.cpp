#include "hmi_transmit.h"
#include <QDebug>
#include <QSettings>

Hmi_transmit::Hmi_transmit(QTableWidget * table_tx)
    : m_table_tx(table_tx)
{}

Hmi_transmit::~Hmi_transmit()
{}

bool Hmi_transmit::draw(QStringList str_list)
{
    int countRow = m_table_tx->rowCount();       //create new row
    int countColumn= m_table_tx->columnCount();
    m_table_tx->insertRow(countRow);
    for(int i=0; i<countColumn; i++){
        m_table_tx->setItem(countRow,i,new QTableWidgetItem(str_list.at(i)));
        m_table_tx->item(countRow,i)->setTextAlignment(Qt::AlignCenter);
   }
    qDebug()<<"Hmi_transmit::draw:ok";
    return true;
}

bool Hmi_transmit::hmi_key()
{
return true;
}

bool Hmi_transmit::hmi_init()
{
    QStringList lable_table_tx;
    lable_table_tx <<"TX"<<"ID (hex)"<<"RTR"<<"D0"<<"D1"<<"D2"<<"D3"<<"D4"<<"D5"<<"D6"<<"D7"<<"Description";
    int row_count=lable_table_tx.size();

    m_table_tx->setColumnCount(row_count);
    m_table_tx->setHorizontalHeaderLabels(lable_table_tx);

    m_table_tx->horizontalHeader()->setStyleSheet("color: blue");
    m_table_tx->horizontalHeader()->setVisible(true);
    m_table_tx->verticalHeader()->setVisible(false);

    m_table_tx->horizontalHeader()->resizeSection(0,50);
    m_table_tx->horizontalHeader()->resizeSection(1,60);
    m_table_tx->horizontalHeader()->resizeSection(2,40);
    m_table_tx->horizontalHeader()->resizeSection(3,40);

    for(int i=4; i<row_count; i++ )
    {
         m_table_tx->horizontalHeader()->resizeSection(i,40);
    }

    m_table_tx->horizontalHeader()->setSectionResizeMode(row_count-1,QHeaderView::Stretch);


   for(int i=0; i<5; i++)
    {
        for(int j=0; j<row_count; j++)
        {
             m_table_tx->setItem(i,j,new QTableWidgetItem(""));
        }
    }

    Hmi_transmit::readTXdataFromINI();
    Hmi_transmit::writeAllDatatoTXtable();
    return true;
}

bool Hmi_transmit::readTXdataFromINI()
{
    QSettings  settings("USBtoCAN.ini",QSettings::IniFormat) ;

    for (int i=0; i<5; i++ )
    {
        settings.beginGroup("TXrow"+QString::number(i));
        mTableTx.tx_row[i].description=settings.value("description").toString();
        mTableTx.tx_row[i].idHex = settings.value("idHex").toString();
        mTableTx.tx_row[i].rtr = settings.value("rtr").toString();
        mTableTx.tx_row[i].d0 = settings.value("d0").toString();
        mTableTx.tx_row[i].d1 = settings.value("d1").toString();
        mTableTx.tx_row[i].d2 = settings.value("d2").toString();
        mTableTx.tx_row[i].d3 = settings.value("d3").toString();
        mTableTx.tx_row[i].d4 = settings.value("d4").toString();
        mTableTx.tx_row[i].d5 = settings.value("d5").toString();
        mTableTx.tx_row[i].d6 = settings.value("d6").toString();
        mTableTx.tx_row[i].d7 = settings.value("d7").toString();
        settings.endGroup();

        qDebug()<<"Hmi_transmit::readTXdataFromINI():"<<mTableTx.tx_row[i].description
                                                        <<mTableTx.tx_row[i].idHex
                                                        <<mTableTx.tx_row[i].rtr
                                                        <<mTableTx.tx_row[i].d0
                                                        <<mTableTx.tx_row[i].d1
                                                        <<mTableTx.tx_row[i].d2
                                                        <<mTableTx.tx_row[i].d3
                                                        <<mTableTx.tx_row[i].d4
                                                        <<mTableTx.tx_row[i].d5
                                                        <<mTableTx.tx_row[i].d6
                                                        <<mTableTx.tx_row[i].d7;
    }
    return true;
}

bool Hmi_transmit::writeAllDatatoTXtable()
{
    for (int i=0; i<=4; i++)
    {
  //      m_table_tx->item(i,0)->setText(QString::number(i));
  //      m_table_tx->item(i,0)->setIcon()


        m_table_tx->item(i,1)->setText(mTableTx.tx_row[i].idHex);
        m_table_tx->item(i,1)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,2)->setText(mTableTx.tx_row[i].rtr);
        m_table_tx->item(i,2)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,3)->setText(mTableTx.tx_row[i].d0);
        m_table_tx->item(i,3)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,4)->setText(mTableTx.tx_row[i].d1);
        m_table_tx->item(i,4)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,5)->setText(mTableTx.tx_row[i].d2);
        m_table_tx->item(i,5)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,6)->setText(mTableTx.tx_row[i].d3);
        m_table_tx->item(i,6)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,7)->setText(mTableTx.tx_row[i].d4);
        m_table_tx->item(i,7)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,8)->setText(mTableTx.tx_row[i].d5);
        m_table_tx->item(i,8)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,9)->setText(mTableTx.tx_row[i].d6);
        m_table_tx->item(i,9)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,10)->setText(mTableTx.tx_row[i].d7);
        m_table_tx->item(i,10)->setTextAlignment(Qt::AlignCenter);

        m_table_tx->item(i,11)->setText(mTableTx.tx_row[i].description);
        m_table_tx->item(i,11)->setTextAlignment(Qt::AlignCenter);
    }
    return true;
}
