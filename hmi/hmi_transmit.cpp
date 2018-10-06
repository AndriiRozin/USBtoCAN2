#include "hmi_transmit.h"
#include <QDebug>

Hmi_transmit::Hmi_transmit(QTableWidget * table_tx)
    : m_table_tx(table_tx)
{}

Hmi_transmit::~Hmi_transmit()
{}

bool Hmi_transmit::draw(QStringList str_list)
{
    int countRow = m_table_tx->rowCount();       //create new row
    m_table_tx->insertRow(countRow);
    for(int i=0; i<=12; i++){
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
    lable_table_tx <<"TX"<<"ID (hex)"<<"RTR"<<"DLC"<<"D0"<<"D1"<<"D2"<<"D3"<<"D4"<<"D5"<<"D6"<<"D7"<<"Description";

    m_table_tx->setColumnCount(13);
    m_table_tx->setHorizontalHeaderLabels(lable_table_tx);

    m_table_tx->horizontalHeader()->setStyleSheet("color: blue");
    m_table_tx->horizontalHeader()->setVisible(true);
    m_table_tx->verticalHeader()->setVisible(false);

    m_table_tx->horizontalHeader()->resizeSection(0,50);
    m_table_tx->horizontalHeader()->resizeSection(1,60);
    m_table_tx->horizontalHeader()->resizeSection(2,60);
    m_table_tx->horizontalHeader()->resizeSection(3,60);
    for(int i=4; i<12; i++ )
    {
         m_table_tx->horizontalHeader()->resizeSection(i,40);
    }
    m_table_tx->horizontalHeader()->setSectionResizeMode(12,QHeaderView::Stretch);


    for(int i=0; i<5; i++)
    {
        for(int j=0; j<13; j++)
         {
             m_table_tx->setItem(i,j,new QTableWidgetItem(""));
         }
    }

//     for (int i=0; i<5; i++)
//     {
//         m_table_tx->item(i,2)->setText(mTableTx.tx_row[i].description);
//         m_table_tx->item(i,1)->setText(mTableTx.tx_row[i].idHex);
//         m_table_tx->item(i,3)->setText(mTableTx.tx_row[i].rtr);
//         m_table_tx->item(i,4)->setText(mTableTx.tx_row[i].d0);
//         m_table_tx->item(i,5)->setText(mTableTx.tx_row[i].d1);
//         m_table_tx->item(i,6)->setText(mTableTx.tx_row[i].d2);
//         m_table_tx->item(i,7)->setText(mTableTx.tx_row[i].d3);
//         m_table_tx->item(i,8)->setText(mTableTx.tx_row[i].d4);
//         m_table_tx->item(i,9)->setText(mTableTx.tx_row[i].d5);
//         m_table_tx->item(i,10)->setText(mTableTx.tx_row[i].d6);
//         m_table_tx->item(i,11)->setText(mTableTx.tx_row[i].d7);
//     }


    return true;
}
