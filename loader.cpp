#include "loader.h"
#include <fstream>
#include <iostream>

Loader::Loader(const std::string &file)
{
    // TODO: Constructor
    if (!loadData(file))
    {
        std::cerr << "Error loading the data file: " << file << std::endl;
        // TODO: Error handling
    }
}

const std::vector<pcb> &Loader::getReadyQueue() const
{
    return readyQueue;
}

bool Loader::loadData(const std::string &dataFile)
{
    std::ifstream file(dataFile);
    if (!file)
    {
        // Unable to open the file
        return false;
    }

    file.close();
}