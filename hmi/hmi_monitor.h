#ifndef HMI_MONITOR_H
#define HMI_MONITOR_H
#include "hmi.h"


class Hmi_monitor: public Hmi
{
public:
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;
};

#endif // HMI_MONITOR_H
