#include "loader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Loader::Loader(const std::string &file)
{
    // TODO: Constructor
    if (!loadData(file))
    {
        throw std::runtime_error("Error loading the data file: " + file);
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
        std::cerr << "Error loading the data file: " << dataFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        osp2023::id_type id;
        osp2023::time_type total_time;

        if (iss >> id >> total_time)
        {
            std::cerr << "Error: Invalid data format in file: " << dataFile << std::endl;
            return false;
        }

        pcb process(id, total_time);
        readyQueue.push_back(process);
    }

    file.close();
    return true;
}