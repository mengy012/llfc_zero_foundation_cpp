#include <iostream>

int main()
{
    {
        double dval = 3.14;
        const int& ri = dval;
        std::cout << ri << std::endl;
    }
}