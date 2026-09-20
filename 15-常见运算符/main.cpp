#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <utility>
#include <functional>
#include <thread>

int foo()
{
    return 42;
}

class Complex
{
  public:
    int real, imag;

    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend std::ostream& operator<<(std::ostream& os, const Complex& c1);
};

Complex operator+(const Complex& c1, const Complex& c2)
{
    Complex temp;
    temp.real = c1.real + c2.real;
    temp.imag = c1.imag + c2.imag;
    return temp;
}
std::ostream& operator<<(std::ostream& os, const Complex& c1)
{
    os << c1.real << ' ' << c1.imag;
    return os;
}

template <typename T>
concept integral = std::integral<T>;

auto main() -> int
{
    // // std::cout << "hello" << std::endl;

    // std::vector<int> arr;
    // for (int i = 0; i < 10; ++i)
    // {
    //     arr.push_back(i);
    // }

    // std::for_each_n(arr.begin(), 2, [](int& v) { ++v; });
    // // std::invoke(std::for_each(arr.begin(), arr.end(), [](auto&& v) { std::cout << v << std::endl; }), 99999);
    // // std::ranges::for_each(arr, [](auto&& v) { std::cout << v << std::endl; });

    // std::jthread([&arr]() { std::ranges::for_each(arr, [](auto&& v) { std::cout << v << std::endl; }); });

    // {
    //     int a = 10, b = 3;
    //     int sum = a + b;  // 13
    //     int diff = a - b; // 7
    //     int prod = a * b; // 30
    //     int div = a / b;  // 3
    //     int mod = a % b;  // 1
    //     a++;              // a = 11
    //     --b;              // b = 2
    // }
    // {
    //     int a = 5, b = 10;
    //     bool result1 = (a == b); // false
    //     bool result2 = (a < b);  // true
    //     bool result3 = (a >= b); // false
    // }
    // {
    //     int a = 3;
    //     int b = 4;
    //     std::cout << (a ^ b ^ b ^ b ^ b) << std::endl;
    //     std::cout << (a ^ b ^ b ^ b) << std::endl;
    //     std::cout << (a ^ b ^ b) << std::endl;
    //     std::cout << (a ^ b) << std::endl;
    // }

    // {
    //     bool a = true, b = false;
    //     bool result1 = a && b; // false
    //     bool result2 = a || b; // true
    //     bool result3 = !a;     // false
    // }

    // {
    //     int a = 5;               // 二进制：0101
    //     int b = 3;               // 二进制：0011
    //     int andResult = a & b;   // 1 (0001)
    //     int orResult = a | b;    // 7 (0111)
    //     int xorResult = a ^ b;   // 6 (0110)
    //     int notResult = ~a;      // -6 (补码)
    //     int leftShift = a << 1;  // 10 (1010)
    //     int rightShift = a >> 1; // 2 (0010)
    // }

    // {
    //     int a = 5;
    //     int b = 3;
    //     a += b; // a = 8
    //     a *= 2; // a = 16
    //     a &= b; // a = 16 & 3 = 0
    // }
    // {
    //     int a = 10, b = 20, c;
    //     c = (a > b) ? a : b; // c = 20
    // }
    // {
    //     int a = 5;
    //     int b = ++a; // a = 6, b = 6
    //     int c = a--; // a = 5, c = 6
    //     std::cout << c << std::endl;
    // }
    // {
    //     int a = 10;
    //     int* ptr = &a;
    //     int value = *ptr; // value = 10
    // }
    // {
    //     struct Point
    //     {
    //         int x;
    //         int y;
    //         int get_x() noexcept
    //         {
    //             return x;
    //         }
    //     };

    //     Point p = {10, 20};
    //     // Point* ptr = &p;
    //     // int a = p.x;    // 使用 . 运算符
    //     // int b = ptr->y; // 使用 -> 运算符
    //     // using p_x = int Point::*;
    //     // p_x px = &Point::x;
    //     // std::cout << p.*px << std::endl;
    //     // p_x py = &Point::y;
    //     // std::cout << p.*py << std::endl;
    //     using m_fp = int (Point::*)();
    //     m_fp fp = &Point::get_x;
    //     std::cout << (p.*fp)() << std::endl;

    //     using funcp = int (*)();
    //     funcp foo_funcp = foo;

    //     std::cout << (uint64_t)foo_funcp << std::endl;
    //     std::cout << (uint64_t)foo << std::endl;
    //     std::cout << typeid(funcp).name() << std::endl;
    // }

    // {
    //     int a = 5;
    //     int size = sizeof(a); // size = 4 (通常)
    //     int b, c;
    //     b = (a++, a + 2); // a = 6, b = 8
    // }

    // {
    //     Complex c1{10, 20};
    //     Complex c2{100, 200};

    //     std::cout << (c1 + c2) << std::endl;
    // }

    // {
    //     // 交换两个数字

    //     int a = 3;
    //     int b = 5;

    //     a = a ^ b;
    //     b = a ^ b;
    //     a = a ^ b;

    //     std::cout << a << ' ' << b << std::endl;
    // }
    {
        //  编写一个函数，接受一个整数指针，使用解引用运算符修改其值为原值的平方。
        auto fun = [](int* p)
        {
            *p = (*p) * (*p);
        };
        int a = 3;
        fun(&a);
        std::cout << a << std::endl;
    }

    {
        auto fun = [](auto begin, auto end)
        {
            using sum_type = std::iterator_traits<decltype(begin)>::value_type;

            sum_type sum{};
            std::for_each(begin, end, [&sum](const std::integral auto& v) { sum += v; });
            return sum;
        };

        // std::vector<int> numbers{1, 2, 3};
        std::vector<int> numbers = {2, 4, 6, 8, 10};
        std::vector<long long> ll_numbers{1, 2, 3};
        std::vector<float> floats{.1, .2, .5};

        std::cout << fun(numbers.begin(), numbers.end()) << std::endl;
        std::cout << fun(ll_numbers.begin(), ll_numbers.end()) << std::endl;
        // std::cout << fun(floats.begin(), floats.end()) << std::endl;
    }
}