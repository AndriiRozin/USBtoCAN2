#ifndef PROCESS_ERROR_H
#define PROCESS_ERROR_H
#include "messageprocessor.h"
#include <QtWidgets/QTableWidget>

class Process_Error: public MessageProcessor
{
    virtual bool processMesage(QString data) override;

public:
    Process_Error(QTableWidget * table);
    virtual ~Process_Error() override;

private:
    QTableWidget * m_table;
};

#endif // PROCESS_ERROR_H
