#ifndef HMI_TRANSMIT_H
#define HMI_TRANSMIT_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>
#include <QHeaderView>

class Hmi_transmit: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QStringList str_list) override;
    virtual bool hmi_key() override;

    Hmi_transmit(QTableWidget * table_tx);
    virtual ~Hmi_transmit() override;

private:
    QTableWidget * m_table_tx;

    struct SRow{
         QString description;
         QString idHex;
         QString rtr;
         QString d0;
         QString d1;
         QString d2;
         QString d3;
         QString d4;
         QString d5;
         QString d6;
         QString d7;
     };

     struct STableTX{
         SRow tx_row[5];
     } mTableTx;

     bool readTXdataFromINI();
     bool writeAllDatatoTXtable();

};

#endif // HMI_TRANSMIT_H
