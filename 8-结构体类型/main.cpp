#include <iostream>
#include <windows.h>

struct Student
{
    int id;
    std::string name;
    float grade;
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    // 创建包含3个学生信息的数组
    Student students[3] = {1001, "Alice", 89.5f, 1002, "Bob", 92.0f, 1003, "Charlie", 85.0f};

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "学生ID: " << students[i].id << ", 姓名: " << students[i].name << ", 成绩: " << students[i].grade << std::endl;
    }
}