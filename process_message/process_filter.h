#ifndef PROCESS_FILTER_H
#define PROCESS_FILTER_H
#include "process_message.h"
#include "hmi/hmi_info.h"

class Process_filter: public Process_message
{
public:
    Process_filter(Hmi_info * info_viewer);
    virtual bool processMesage(QString data) override;
    virtual ~Process_filter() override;
private:
    Hmi_info * m_info_viewer;
};

#endif // PROCESS_FILTER_H
