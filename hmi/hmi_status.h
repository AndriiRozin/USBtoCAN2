#ifndef HMI_STATUS_H
#define HMI_STATUS_H
#include "hmi.h"


class Hmi_status: public Hmi
{
public:
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;
};

#endif // HMI_STATUS_H
