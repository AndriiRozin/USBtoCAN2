#ifndef HMI_TRANSMIT_H
#define HMI_TRANSMIT_H
#include "hmi.h"
#include <QtWidgets/QTableWidget>

class Hmi_transmit: public Hmi
{
public:
    virtual bool hmi_init() override;
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;

    Hmi_transmit(QTableWidget * table_tx);
    virtual ~Hmi_transmit() override;

private:
    QTableWidget * m_table_tx;


};

#endif // HMI_TRANSMIT_H
