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

void sizeofnum()
{
    std::cout << "Size of char: " << sizeof(char) << " bytes\n";
    std::cout << "Size of int: " << sizeof(int) << " bytes\n";
    std::cout << "Size of float: " << sizeof(float) << " bytes\n";
    std::cout << "Size of double: " << sizeof(double) << " bytes\n";
    std::cout << "Size of long long: " << sizeof(long long) << " bytes\n";
}

int main()
{
    // calculate();

    // {
    //     // 字符变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`等
    //     char g = 'a';
    //     char h = 'b';
    //     std::cout << "g + h = " << (int)(g + h) << std::endl;
    //     std::cout << "g - h = " << (int)(g - h) << std::endl;
    //     std::cout << "g * h = " << (int)(g * h) << std::endl;
    //     std::cout << "g / h = " << (int)(g / h) << std::endl;

    // }

    {
        sizeofnum();
    }

    {
        int a = -1;
        unsigned int b = a;
        std::cout << a << '\n' << b << std::endl;
    }
}