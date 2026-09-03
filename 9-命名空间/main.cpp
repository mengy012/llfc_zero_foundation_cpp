#include <iostream>
using namespace std;

int a = 10;

int main()
{
    cout << "Hello World!" << endl;
    int a = 20;
    std::cout << ::a << a << std::endl;
    return 0;
}