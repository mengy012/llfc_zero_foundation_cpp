#include <iostream>
#include <Windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    std::cout << "Hello, World!" << std::endl;
    std::cout << "cpp大王" << std::endl; 
    return 0;
}