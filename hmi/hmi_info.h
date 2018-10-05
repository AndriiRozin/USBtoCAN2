#ifndef HMI_INFO_H
#define HMI_INFO_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>

class Hmi_info: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;


    Hmi_info(QTableWidget * m_table_info);
    virtual ~Hmi_info() override;

private:
    QTableWidget * m_table_info;
};

#endif // HMI_INFO_H
