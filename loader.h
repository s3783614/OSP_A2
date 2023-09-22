#pragma once
#include <vector>
#include "pcb.h"
#include "types.h"

class Loader
{
private:
    std::vector<pcb> readyQueue;

public:
    Loader(const std::string &datafile);
    const std::vector<pcb> &getReadyQueue() const;

    // Implementing a function to load data from the input file
    bool loadData(const std::string &);
};