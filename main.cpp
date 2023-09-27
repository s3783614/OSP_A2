#include "loader.h"
#include "scheduler.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage :: " << argv[0] << " <algorithm> <datafile>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string algorithm = argv[0];
    std::string datafile;

    if (argc == 2)
    {
        datafile = argv[1];
    }
    else if (argc == 3)
    {
        datafile = argv[2];
        try
        {
            osp2023::time_type quantum = std::stoll(argv[1]);
            if (quantum <= 0)
            {
                std::cerr << "Invalid Quantum Value, Provide a positive value" << std::endl;
                return EXIT_FAILURE;
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid Quantum Value, Provide a positive value" << std::endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        std::cerr << "Usage :: " << argv[0] << " <algorithm> <datafile>" << std::endl;
        return EXIT_FAILURE;
    }
    // CREATING SCHEDULER AND LOADER
    Loader loader(datafile);
    Scheduler scheduler(loader.getReadyQueue());

    if (algorithm == "./fifo")
    {
        scheduler.runFIFO();
    }
    else if (algorithm == "./sjf")
    {
        scheduler.runSJF();
    }
    else if (algorithm == "./rr" && argc == 3)
    {
        osp2023::time_type quantam = std::stoll(argv[1]);
        scheduler.runRR(quantam);
    }
    else
    {
        std::cerr << "Invalid algorithm / arguments." << std::endl;
        return EXIT_FAILURE;
    }

    // Displaying Times
    std::cout << "Average Turnaround Time: " << scheduler.getAverageTurnAroundTime() << std::endl;
    std::cout << "Average Waiting Time: " << scheduler.getAverageWaitingTime() << std::endl;
    std::cout << "Average Response Time: " << scheduler.getAverageResponseTime() << std::endl;
    return EXIT_SUCCESS;
}
