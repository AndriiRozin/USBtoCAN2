#ifndef HMI_TRANSMIT_H
#define HMI_TRANSMIT_H
#include "hmi.h"

class Hmi_transmit: public Hmi
{
public:
    virtual bool draw(QString time) override;
    virtual bool hmi_key() override;
};

#endif // HMI_TRANSMIT_H
