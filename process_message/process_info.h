#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H
#include "process_message.h"
#include <QTableWidget>

class Process_Info: public Process_message
{
public:
    Process_Info(QTableWidget * table_info);
    virtual bool processMesage(QString data) override;
    virtual ~Process_Info() override;
private:
    QTableWidget * m_tableInfo;
};

#endif // PROCESS_INFO_H
