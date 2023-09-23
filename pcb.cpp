#include "pcb.h"

pcb::pcb(osp2023::id_type _id, osp2023::time_type _total_time)
    : id(_id), total_time(_total_time),
      time_used(0), total_wait_time(0), last_cpu_time(0)
{
}

osp2023::id_type pcb::getID()
{
    return id;
}

osp2023::time_type pcb::getTotalTime()
{
    return total_time;
}

osp2023::time_type pcb::getTimeUsed() const
{
    return time_used;
}

osp2023::time_type pcb::getTotalWaitTime() const
{
    return total_wait_time;
}

osp2023::time_type pcb::getLastCPUTime()
{
    return last_cpu_time;
}

// Update methods
void pcb::updateTimeUsed(osp2023::time_type time)
{
    time_used += time;
}

void pcb::updateTotalWaitTime(osp2023::time_type time)
{
    total_wait_time += time;
}

void pcb::updatedLastCPUTime(osp2023::time_type time)
{
    last_cpu_time = time;
}
