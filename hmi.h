#ifndef HMI_H
#define HMI_H
#include <QString>
#include <QTabWidget>


class Hmi
{
public:
    virtual bool hmi_init()=0;
    virtual bool draw(QString time)=0;
    virtual bool hmi_key()=0;

    virtual ~Hmi(){};

};

#endif // HMI_H
