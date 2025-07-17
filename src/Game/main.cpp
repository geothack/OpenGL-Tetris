#include "Utility/PreLibrary.h"
#include "Application.h"

#ifdef _DEBUG

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

#endif

#ifdef NDEBUG

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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
    return 0;
}

#endif