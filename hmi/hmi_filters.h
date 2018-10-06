#ifndef HMI_FILTERS_H
#define HMI_FILTERS_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>
#include <QHeaderView>

class Hmi_filters: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;

    Hmi_filters(QTableWidget * m_table_filters);
    virtual ~Hmi_filters() override;

private:
    QTableWidget * m_table_filters;
};

#endif // HMI_FILTERS_H
