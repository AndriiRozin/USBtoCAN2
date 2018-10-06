#ifndef HMI_MONITOR_H
#define HMI_MONITOR_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>
#include <QHeaderView>

class Hmi_monitor: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QStringList str_list) override;
    virtual bool hmi_key() override;

    Hmi_monitor(QTableWidget * table_monitor);
    virtual ~Hmi_monitor() override;

private:
    QTableWidget * m_table_monitor;


};

#endif // HMI_MONITOR_H
