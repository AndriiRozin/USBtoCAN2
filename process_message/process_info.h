#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H
#include "process_message.h"
#include "hmi/hmi_info.h"

class Process_Info: public Process_message
{
public:
    Process_Info(Hmi_info * info_viewer);
    virtual bool processMesage(QString data) override;
    virtual ~Process_Info() override;
private:
    Hmi_info * m_info_viewer;
};

#endif // PROCESS_INFO_H
