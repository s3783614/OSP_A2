#include "scheduler.h"
#include <iostream>
#include <queue>

Scheduler::Scheduler(const std::vector<pcb> &process)
    : readyQueue(process)
{
    // TODO: Constructor
}

void Scheduler::runFIFO()
{
    std::queue<pcb> myQueue;
    osp2023::time_type currentTime = 0;
    double totalTurnaroundTime = 0;
    // double totalWaitTime = 0;
    double totalResponseTime = 0;

    while (readyQueue.empty() || myQueue.empty())
    {
        // Check if there is anything and then add it to queue
        while (!readyQueue.empty() && readyQueue.front().getLastCPUTime() <= currentTime)
        {
            myQueue.push(readyQueue.front());
            readyQueue.erase(readyQueue.begin());
        }
    }

    if (!myQueue.empty())
    {
        pcb curProcess = myQueue.front();
        myQueue.pop();

        // Updated Response for the current Process
        totalResponseTime += currentTime - curProcess.getLastCPUTime();

        // Execute the process
        osp2023::time_type executeTime = std::min(curProcess.getTotalTime() - curProcess.getTimeUsed(), curProcess.getTotalTime());
        currentTime += executeTime;

        curProcess.updateTimeUsed(executeTime);
        curProcess.updateTotalWaitTime(currentTime - curProcess.getLastCPUTime() - executeTime);
        curProcess.updatedLastCPUTime(currentTime);

        // Update turnaround time for the current process.
        totalTurnaroundTime += currentTime - curProcess.getLastCPUTime();

        // Print process details
        std::cout << "Proccess ID: " << curProcess.getID()
                  << ", Burst Time: " << executeTime
                  << ", Turnaround Time: " << currentTime - curProcess.getLastCPUTime()
                  << ", Waiting Time: " << currentTime - curProcess.getLastCPUTime() - executeTime
                  << ", Response Time: " << currentTime - curProcess.getLastCPUTime()
                  << std::endl;
    }
    else
    {
        // no proccess in the fifo queue
        currentTime++;
    }
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
    return 0.0;
}

double Scheduler::getAverageTurnAroundTime() const
{
    return 0.0;
}

double Scheduler::getAverageWaitingTime() const
{
    return 0.0;
}
