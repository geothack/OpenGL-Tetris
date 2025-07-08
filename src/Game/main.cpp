#include "Application.h"

int main()
{
    try
    {
        Application app;
    }
    catch (std::exception exception)
    {
        std::println("{}", exception.what());
        return -1;
    }
}