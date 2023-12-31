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
        // std::cout << "file: " << file << std::endl;
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

    if (!file.is_open())
    {

        std::cerr << "Error loading the data file: " << dataFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string id_str, total_time_str;

        if (!(std::getline(iss, id_str, ',') && std::getline(iss, total_time_str, ',')))
        {
            std::cerr << "Error: Invalid data format in provided data file: " << dataFile << std::endl;
            return false;
        }

        try
        {
            osp2023::id_type id = std::stoi(id_str);
            osp2023::time_type total_time = std::stoi(total_time_str);

            pcb process(id, total_time);
            readyQueue.push_back(process);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing data from file: " << dataFile << std::endl;
            return false;
        }
    }

    file.close();
    return true;
}