#ifndef PROCESS_FILTERCAN_H
#define PROCESS_FILTERCAN_H
#include "messageprocessor.h"
#include <QtWidgets/QTableWidget>

class Process_FilterCAN: public MessageProcessor
{
    virtual bool processMesage(QString data) override;

public:
    Process_FilterCAN(QTableWidget * table);
    virtual ~Process_FilterCAN() override;

private:
    QTableWidget * m_table;
};

#endif // PROCESS_FILTERCAN_H
