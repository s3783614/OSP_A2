#include "scheduler.h"
#include <iostream>
#include <queue>
#include <algorithm>

Scheduler::Scheduler(const std::vector<pcb> &process)
    : readyQueue(process)
{
    // TODO: Constructor
}

void Scheduler::runFIFO()
{
    std::queue<pcb> myQueue;
    queueSize = readyQueue.size();
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
    queueSize = readyQueue.size();

    totalTurnaroundTime = 0;
    totalWaitTime = 0;
    totalResponseTime = 0;

    while (!readyQueue.empty() || !myQueue.empty())
    {
        std::sort(readyQueue.begin(), readyQueue.end(), [](const pcb a, const pcb b)
                  { return a.getTotalTime() - a.getTimeUsed() < b.getTotalTime() - b.getTimeUsed(); });

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

void Scheduler::runRR(osp2023::time_type quantam)
{
    std::vector<pcb> myQueue(readyQueue);
    osp2023::time_type currentTime = 0;
    queueSize = readyQueue.size();

    totalResponseTime = 0;
    totalTurnaroundTime = 0;
    totalWaitTime = 0;

    int total = 0;

    // vector to store
    std::vector<osp2023::time_type> bleh(readyQueue.size() + 1, -1);

    while (!myQueue.empty())
    {
        pcb curProcess = myQueue.front();

        if (bleh[curProcess.getID()] == -1)
        {
            bleh[curProcess.getID()] = currentTime;
        }

        if (curProcess.getTotalTime() - curProcess.getTimeUsed() <= quantam)
        {
            osp2023::time_type executeTime = curProcess.getTotalTime() - curProcess.getTimeUsed();
            currentTime += executeTime;
            total += executeTime;

            osp2023::time_type turnaroundTime = total;
            osp2023::time_type waitTime = total - curProcess.getTotalTime();
            osp2023::time_type responseTime = bleh[curProcess.getID()];

            totalTurnaroundTime += turnaroundTime;
            totalWaitTime += waitTime;
            totalResponseTime += responseTime;

            // Print process details
            std::cout
                << "Proccess ID: " << curProcess.getID()
                << ", Burst Time: " << executeTime
                << ", Turnaround Time: " << turnaroundTime
                << ", Waiting Time: " << waitTime
                << ", Response Time: " << responseTime
                << std::endl;
            myQueue.erase(myQueue.begin());
        }
        else
        {
            currentTime += quantam;
            total += quantam;

            curProcess.updateTimeUsed(quantam);

            myQueue.push_back(curProcess);

            myQueue.erase(myQueue.begin());
        }
    }
}

double Scheduler::getAverageResponseTime() const
{
    return totalResponseTime / queueSize;
}

double Scheduler::getAverageTurnAroundTime() const
{
    return totalTurnaroundTime / queueSize;
}

double Scheduler::getAverageWaitingTime() const
{
    return totalWaitTime / queueSize;
}
