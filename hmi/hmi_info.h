#ifndef HMI_INFO_H
#define HMI_INFO_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>
#include <QHeaderView>

class Hmi_info: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QStringList str_list) override;
    virtual bool hmi_key(QStringList strlist) override;
    virtual bool edit(QStringList strlist) override;

    Hmi_info(QTableWidget * m_table_info);
    virtual ~Hmi_info() override;

private:
    QTableWidget * m_table_info;
};

#endif // HMI_INFO_H
