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

void Scheduler::runRR(osp2023::time_type quantam)
{
    std::vector<pcb> myQueue(readyQueue);
    osp2023::time_type currentTime = 0;
    queueSize = readyQueue.size();

    totalResponseTime = 0;
    totalTurnaroundTime = 0;
    totalWaitTime = 0;

    int total = 0;
    int i = 0;

    // for (int i = 0; i < readyQueue.size(); i++)
    // {
    //     std::cout << "i: " << i << std::endl;
    //     std::cout << "readyQueue[i]: " << readyQueue[i].getID() << std::endl;
    // }

    // while (!readyQueue.empty() || !myQueue.empty())
    // {

    // while (!readyQueue.empty() && readyQueue.front().getLastCPUTime() <= currentTime)
    // {
    //     myQueue.push_back(readyQueue.front());

    //     readyQueue.erase(readyQueue.begin());
    //     std::cout << readyQueue.front().getID() << std::endl;
    // }
    // std::cout << "i: " << i << std::endl;
    // std::cout << "myQueue[i]: " << myQueue[i].getID() << std::endl;
    // std::cout << "readyQueue[i]: " << readyQueue[i].getID() << std::endl;

    // for (int i = 0; i < myQueue.size(); i++)
    // {
    //     std::cout << "i: " << i << std::endl;
    //     std::cout << "myQueue[i]: " << myQueue[i].getID() << std::endl;
    // }

    while (!myQueue.empty())
    {
        pcb curProcess = myQueue.front();

        if (curProcess.getTotalTime() - curProcess.getTimeUsed() <= quantam)
        {
            osp2023::time_type executeTime = curProcess.getTotalTime() - curProcess.getTimeUsed();
            currentTime += executeTime;
            total += executeTime;

            osp2023::time_type turnaroundTime = total;
            osp2023::time_type waitTime = total - curProcess.getTotalTime();
            osp2023::time_type responseTime = total - curProcess.getTotalTime();

            totalTurnaroundTime += turnaroundTime;
            totalWaitTime += waitTime;
            totalResponseTime += responseTime;

            // Print process details
            std::cout
                << "Proccess ID: " << myQueue[i].getID()
                << ", Burst Time: " << myQueue[i].getTotalTime()
                << ", Turnaround Time: " << turnaroundTime
                << ", Waiting Time: " << waitTime
                << ", Response Time: " << responseTime
                << std::endl;
            myQueue.erase(myQueue.begin());
            // std::cout << "POST COMPLETE ERASE: " << myQueue[i].getID() << std::endl;
        }
        else
        {
            currentTime += quantam;
            total += quantam;

            curProcess.updateTimeUsed(quantam);

            myQueue.push_back(curProcess);

            myQueue.erase(myQueue.begin());

            // Move to the back of the queue
            // readyQueue.push_back(myQueue[i]);
            // std::cout << "pre erase: " << readyQueue.back().getID() << std::endl;
            // myQueue.erase(myQueue.begin());

            // std::cout << "post erase: " << myQueue[i].getID() << std::endl;
        }

        // if (i < myQueue.size() - 1)
        // {
        //     i++;
        // }
        // else
        // {
        //     i = 0;
        // }
    }
    // else
    // {
    //     // In case there isn't a process
    //     currentTime++;
    // }
    // }
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
