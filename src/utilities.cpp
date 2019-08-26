#include "utilities.h"

void perr()
{
    std::cerr << "ERROR" << std::strerror(errno) << std::endl;
};

void psuccess(std::string msg)
{
    std::cout << msg << std::endl;
};