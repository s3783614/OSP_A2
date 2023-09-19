#include "./fifo/fifo.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage :: " << argv[0] << " <algorithm> <datafile>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string algorithm = argv[1];
    std::string datafile = argv[2];

    if (algorithm == "FIFO")
    {
        /* code */
    }
    else if (algorithm == "SJF")
    {
        /* code */
    }
    else if (algorithm == "RR")
    {
        /* code */
    }
    else
    {
        std::cerr << "Invalid algorithm / arguments." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
