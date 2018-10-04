#ifndef PROCESS_RX_H
#define PROCESS_RX_H
#include "messageprocessor.h"
#include <QtWidgets/QTableWidget>

class Process_Rx: public MessageProcessor
{
    virtual bool processMesage(QString data) override;

public:
    Process_Rx(QTableWidget * table);
    virtual ~Process_Rx() override;

private:
    QTableWidget * m_table;
};


#endif // PROCESS_RX_H
