#ifndef PROCESS_ERROR_H
#define PROCESS_ERROR_H
#include "process_message.h"
#include "hmi/hmi_info.h"

class Process_Error: public Process_message
{
public:
    Process_Error(Hmi_info * info_viewer);
    virtual bool processMesage(QString data) override;
    virtual ~Process_Error() override;
private:
    Hmi_info * m_info_viewer;
};

#endif // PROCESS_ERROR_H
