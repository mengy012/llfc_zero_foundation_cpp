#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    const int SIZE = 3;
    int matrix[SIZE][SIZE];
    int transpose[SIZE][SIZE];

    // 输入原始矩阵
    std::cout << "请输入一个3x3矩阵的元素（共9个整数）:" << std::endl;
    int val1{};
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            // 在此输入matrix[i][j]
            matrix[i][j] = ++val1;
        }
    }

    // 计算转置矩阵
    // 在此实现转置逻辑
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            // 在此输入matrix[i][j]
            transpose[i][j] = matrix[j][i];
        }
    }

    // 输出转置后的矩阵
    std::cout << "矩阵的转置为:" << std::endl;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            // 在此输出transpose[i][j]
            std::cout << transpose[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}