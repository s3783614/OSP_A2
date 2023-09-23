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
    queueSize = readyQueue.size();
    std::cout << "queue size: " << queueSize << std::endl;
    osp2023::time_type currentTime = 0;

    totalTurnaroundTime = 0;
    totalWaitTime = 0;
    totalResponseTime = 0;

    while (!readyQueue.empty() || !myQueue.empty())
    {
        // Check if there is anything and then add it to queue
        while (!readyQueue.empty() && readyQueue.front().getLastCPUTime() <= currentTime)
        {
            // POP
            myQueue.push(readyQueue.front());
            readyQueue.erase(readyQueue.begin());
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

            // Calculating the times
            osp2023::time_type turnaroundTime = currentTime;
            osp2023::time_type waitingTime = currentTime - curProcess.getTotalTime();
            osp2023::time_type responseTime = currentTime - curProcess.getTotalTime();

            totalTurnaroundTime += turnaroundTime;
            totalWaitTime += waitingTime;
            // totalResponseTime += responseTime;

            // Print process details
            std::cout
                << "Proccess ID: " << curProcess.getID()
                << ", Burst Time: " << executeTime
                << ", Turnaround Time: " << turnaroundTime
                << ", Waiting Time: " << waitingTime
                << ", Response Time: " << responseTime
                << std::endl;
        }
        else
        {
            // no proccess in the fifo queue
            currentTime++;
        }
    }
}

void Scheduler::runSJF()
{
    std::queue<pcb> myQueue;
    osp2023::time_type currentTime = 0;

    totalTurnaroundTime = 0;
    totalWaitTime = 0;
    totalResponseTime = 0;

    while (!readyQueue.empty() || !myQueue.empty())
    {
        // std::sort(readyQueue.begin(), readyQueue.end(), [](pcb a, pcb b));
    }
}

void Scheduler::runRR(osp2023::time_type quantam)
{
    // TODO: IMPLEMENT RR scheduling
    // TODO update PCB attributes as the processes run
}

double Scheduler::getAverageResponseTime() const
{
    // if (readyQueue.empty())
    // {
    //     return 0.0;
    // }

    // double totalResponseTime = 0;
    // for (const pcb &process : readyQueue)
    // {
    //     totalResponseTime += process.getTotalWaitTime();
    // }
    // return totalResponseTime / readyQueue.size();
    return totalResponseTime / queueSize;
}

double Scheduler::getAverageTurnAroundTime() const
{
    // if (readyQueue.empty())
    // {
    //     return 0.0;
    // }

    // double totalResponseTime = 0;
    // for (const pcb &process : readyQueue)
    // {
    //     totalResponseTime += process.getTimeUsed();
    // }
    // return totalResponseTime / readyQueue.size();
    return totalTurnaroundTime / queueSize;
}

double Scheduler::getAverageWaitingTime() const
{
    // if (readyQueue.empty())
    // {
    //     return 0.0;
    // }

    // double totalWaitTime = 0;
    // for (const pcb &process : readyQueue)
    // {
    //     totalWaitTime += process.getTotalWaitTime();
    // }
    // return totalWaitTime / readyQueue.size();
    return totalWaitTime / queueSize;
}
