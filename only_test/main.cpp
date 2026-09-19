#include <iostream>
#include <string>
#include <vector>

#include "1.h"

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

    std::cout << -9 % 2 << std::endl;
    std::cout << -9 / 2 << std::endl;
    std::cout << -10 % 2 << std::endl;

    return 0;
}