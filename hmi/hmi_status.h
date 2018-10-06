#ifndef HMI_STATUS_H
#define HMI_STATUS_H
#include "hmi.h"
#include <QStatusBar>


class Hmi_status: public Hmi
{
 public:
    virtual bool hmi_init() override;
    virtual bool draw(QStringList str_list) override;
    virtual bool hmi_key() override;

    Hmi_status(QStatusBar * status_bar);
    virtual ~Hmi_status() override;

private:
    QStatusBar * m_statusBar;
};

#endif // HMI_STATUS_H
