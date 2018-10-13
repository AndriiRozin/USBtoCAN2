#include "process_filter.h"

Process_filter::Process_filter(Hmi_info * info_viewer)
    : m_info_viewer(info_viewer)
{}

Process_filter::~Process_filter()
{}

bool Process_filter::processMesage(QString messageData)
{
    return true;
}
