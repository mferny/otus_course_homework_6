#include "include/CommandProcessor.h"
#include "include/Logger.h"

int main(int argc, char** argv)
{
    if (argc != 2 or std::atoll(argv[1]) <= 0)
    {
        std::cerr << "Usage: ./bulk N, where N is a positive "
                     "number which defines size of a block" << std::endl;
        return 1;
    }

    CommandProcessor processor(std::atoll(argv[1]));

    std::string input;
    while (std::getline(std::cin, input))
    {
        processor.onEvent(input);
    }

    processor.onExit();

    return 0;
}