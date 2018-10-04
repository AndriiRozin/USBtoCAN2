#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H
#include "messageprocessor.h"
#include <QtWidgets/QTableWidget>

class Process_Info: public MessageProcessor
{
    virtual bool processMesage(QString data) override;

public:
    Process_Info(QTableWidget * table);
    virtual ~Process_Info() override;

private:
    QTableWidget * m_table;
};

#endif // PROCESS_INFO_H



