#include <iostream>
#include <my_math.h>
#include <iomanip>

int main()
{
    std::cout << "hello world" << std::endl;
    std::cout << add_int(1, 2) << std::endl;
    std::cout << add_float(.1, .2) << std::endl;
    add_int(1, 2);
    add_float(.1, .2);
}