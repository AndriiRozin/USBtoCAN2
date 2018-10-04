#ifndef HMI_INFO_H
#define HMI_INFO_H
#include "hmi.h"

class Hmi_info: public Hmi
{
public:
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;
};

#endif // HMI_INFO_H
