#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <bit>
#include <cstdint>

#include "1.h"

#define crBegin static int state = 0; switch(state) { case 0:
#define crYield(x) do { state = __LINE__; return x; case __LINE__:; } while(0)
#define crFinish }

union int_data
{
    /* data */

    int a;
    unsigned char arr[4];
};

int next_value()
{
    static int state = 0;
    switch (state)
    {
    case 0:;
        while (1)
        {
            /* code */
            do
            {
                state = 18;
                return 10;
            case 18:;
            } while (0);
            do
            {
                state = 19;
                return 20;
            case 19:;
            } while (0);
            do
            {
                state = 20;
                return 30;
            case 20:;
            } while (0);
        }
    };
}

int main()
{
    // std::cin.tie(nullptr);
    // std::ios::sync_with_stdio(false);
    // {
    //     auto foo = []()
    //     {
    //         int arr[4]{};
    //         int i{};
    //         std::cout << "&i: " << &i << std::endl;
    //         for (; i <= 4; ++i)
    //         {
    //             arr[-1] -= 4;
    //             if (i % 1000000000 == 0)
    //             {
    //                 std::cout << "i: " << i << std::endl;
    //                 std::cout << "&arr[i]: " << &arr[i] << ' ' << "offset of i: " << (size_t)&arr[i] - (size_t)&i << std::endl;
    //             }
    //         }
    //     };

    //     foo();
    // }

    // std::cout << -9 % 2 << std::endl;
    // std::cout << -9 / 2 << std::endl;
    // std::cout << -10 % 2 << std::endl;

    int a = next_value();
    int b = next_value();
    int c = next_value();
    int d = next_value();

    std::cout << std::format("{} -> {} -> {}\n", a, b, c);

    const int val = a;

    unsigned char character[3] = {0xc2, 0xa7, 0};

    std::cout << character << std::endl;

    int_data v{.arr = {0xff, 0xff, 0xff, 0x00}};

    // 按原始位模式生成一个独立的整数，不读取 union 的非活跃成员 a。
    const auto number = std::bit_cast<std::uint32_t>(v.arr);
    std::cout << std::format("{:#010x}\n", number);

    std::cout << v.a << std::endl;

    std::cout << std::format("{:f}", 3.1415926) << std::endl;    // "3.141593"
    std::cout << std::format("{:.2f}", 3.1415926) << std::endl;  // "3.14"
    std::cout << std::format("{:8.2f}", 3.1415926) << std::endl; // "    3.14"
    std::cout << std::format("{:.3e}", 12345.0) << std::endl;    // "1.234e+04"
    std::cout << std::format("{:.4g}", 123.456) << std::endl;    // "123.5"

    return 0;
}
