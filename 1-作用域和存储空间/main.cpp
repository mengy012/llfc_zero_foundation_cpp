#include <iostream>

void calculate()
{
    // 整形变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`,`%`等
    int a = 10;
    int b = 20;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;
    std::cout << "a % b = " << a % b << std::endl;
    // 浮点型变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`等
    float c = 10.5;
    float d = 20.3;
    std::cout << "c + d = " << c + d << std::endl;
    std::cout << "c - d = " << c - d << std::endl;
    std::cout << "c * d = " << c * d << std::endl;
    std::cout << "c / d = " << c / d << std::endl;
    // 浮点型变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`等
    double e = 10.5;
    double f = 20.3;
    std::cout << "e + f = " << e + f << std::endl;
    std::cout << "e - f = " << e - f << std::endl;
    std::cout << "e * f = " << e * f << std::endl;
    std::cout << "e / f = " << e / f << std::endl;
}

int main()
{
    calculate();
}