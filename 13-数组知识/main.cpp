#include <iostream>

// 自定义的字符串连接函数
char* my_strcat(char* dest, const char* src)
{
    // 在此实现函数逻辑
    auto re = dest;

    // dest移动到尾部
    while (*(dest++) != '\0')
    {
    }
    dest--;
    // 开始合并
    while (*src != '\0')
    {
        *(dest++) = *(src++);
    }
    *dest = '\0';
    return re;
}

int main()
{
    char destination[100] = "Hello, "; // 初始内容
    const char* source = "World!";

    my_strcat(destination, source);

    std::cout << "After concatenation: " << destination << std::endl;

    return 0;
}