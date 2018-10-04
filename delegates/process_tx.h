#ifndef PROCESS_TX_H
#define PROCESS_TX_H
#include "messageprocessor.h"
#include <QtWidgets/QTableWidget>

class Process_Tx: public MessageProcessor
{
    virtual bool processMesage(QString data) override;

public:
    Process_Tx(QTableWidget * table);
    virtual ~Process_Tx() override;

private:
    QTableWidget * m_table;
};

#endif // PROCESS_TX_H
