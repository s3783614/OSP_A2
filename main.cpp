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

    if (argc == 2)
    {
        std::string datafile = argv[1];
    }
    else if (argc == 3)
    {
        std::string datafile = argv[2];
    }
    else
    {
        std::cerr << "Too many arguments" << std::endl;
        return EXIT_FAILURE;
    }
    // TODO :: CREATE SCHEDULER AND LOADER

    if (algorithm == "./fifo")
    {
        std::cout << "We got in" << std::endl;
        std::cout << "argv[0]: " << argv[0] << std::endl;
        std::cout << "argv[0]: " << argv[1] << std::endl;
    }
    else if (algorithm == "./sjf")
    {
        /* code */
    }
    else if (algorithm == "./rr")
    {
        /* code */
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
