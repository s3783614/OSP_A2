#include "scheduler.h"
#include <iostream>

Scheduler::Scheduler(const std::vector<pcb> &process)
    : readyQueue(process)
{
    // TODO: Constructor
}

void Scheduler::runFIFO()
{
    // TODO: IMPLEMENT FIFO scheduling
    // TODO update PCB attributes as the processes run
}

void Scheduler::runSJF()
{
    // TODO: IMPLEMENT SJF scheduling
    // TODO update PCB attributes as the processes run
}

void Scheduler::runRR(osp2023::time_type quantam)
{
    // TODO: IMPLEMENT RR scheduling
    // TODO update PCB attributes as the processes run
}

double Scheduler::getAverageResponseTime() const
{
    return NULL;
}

double Scheduler::getAverageTurnAroundTime() const
{
    return NULL;
}

double Scheduler::getAverageWaitingTime() const
{
    return NULL;
}
