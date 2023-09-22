#include "loader.h"
#include "scheduler.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // std::cout << "argv[0]: " << argv[0] << std::endl;
        // std::cout << "argv[0]: " << argv[1] << std::endl;

        std::cerr << "Usage :: " << argv[0] << " <algorithm> <datafile>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string algorithm = argv[0];
    std::string datafile = argv[1];
    // std::cout << "algorithm: " << argv[0] << std::endl;
    // std::cout << "datafile: " << argv[1] << std::endl;
    // std::cout << "datafile: " << argv[2] << std::endl;

    // if (argc == 2)
    // {
    //     datafile = argv[1];
    // }
    // else if (argc == 3)
    // {
    //     datafile = argv[2];
    // }
    // else
    // {
    //     std::cerr << "Usage :: " << argv[0] << " <algorithm> <datafile>" << std::endl;
    //     return EXIT_FAILURE;
    // }

    // TODO:: REMOVE LATER FOR TESTING PURPOSES
    // std::cout << "datafile: " << datafile << std::endl;
    // return EXIT_SUCCESS;

    // CREATING SCHEDULER AND LOADER
    Loader loader(datafile);
    std::cout << "Testing if we get here" << std::endl;
    Scheduler scheduler(loader.getReadyQueue());

    if (algorithm == "./fifo")
    {
        // TODO:: REMOVE LATER FOR TESTING PURPOSES
        // std::cout << "We got in" << std::endl;
        // std::cout << "argv[0]: " << argv[0] << std::endl;
        // std::cout << "argv[0]: " << argv[1] << std::endl;
        scheduler.runFIFO();
    }
    else if (algorithm == "./sjf")
    {
        scheduler.runSJF();
    }
    else if (algorithm == "./rr" && argc == 4)
    {
        osp2023::time_type quantam = std::stoll(argv[3]);
        scheduler.runRR(quantam);
    }
    else
    {
        std::cerr << "Invalid algorithm / arguments." << std::endl;
        return EXIT_FAILURE;
    }

    // Displaying Times
    std::cout << "Average Turnaround Time: " << std::endl;
    std::cout << "Average Waiting Time: " << std::endl;
    std::cout << "Average Response Time: " << std::endl;

    return EXIT_SUCCESS;
}
