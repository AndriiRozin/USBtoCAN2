#ifndef HMI_FILTER_H
#define HMI_FILTER_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>
#include <QHeaderView>

class Hmi_filter: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;

    Hmi_filter(QTableWidget * m_table_filter);
    virtual ~Hmi_filter() override;

private:
    QTableWidget * m_table_filter;
};

#endif // HMI_FILTER_H
