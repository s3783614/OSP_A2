#pragma once
#include <vector>
#include "pcb.h"

class Scheduler
{
private:
    std::vector<pcb> readyQueue;

public:
    Scheduler(const std::vector<pcb> &process);

    // Functions for running the different simulations
    void runFIFO();
    void runSJF();
    void runRR(osp2023::time_type quantum);

    // Function to calculate and retrive stats
    double getAverageTurnAroundTime() const;
    double getAverageWaitingTime() const;
    double getAverageResponseTime() const;
};