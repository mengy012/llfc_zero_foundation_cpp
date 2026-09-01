#include "Student.h"

#include <iostream>
#include <charconv>
#include <windows.h>
#include <limits>
#include <string>
#include <sstream>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Student_management_system sys;
    // sys.add_student(1, 1.f, "alice");
    // sys.add_student(2, 2.f, "bob");
    // sys.add_student(3, 3.f, "cily");

    // sys.print_all_student();

    // sys.find_student(1);
    // sys.find_student(3);

    bool is_running = true;
    while (is_running)
    {
        std::cout << "===== 学生信息管理系统 =====\n"
                     "1. 添加学生\n"
                     "2. 显示所有学生\n"
                     "3. 根据ID查找学生\n"
                     "4. 退出\n";

        std::cout << "请选择(1-4): ";
        int input{};
        std::cin >> input;

        switch (input)
        {
        case 1:
        { // 1. 添加学生
            std::cout << "id score name\n";
            int id{};
            float score{};
            std::string name;

            std::string line;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, line);
            std::stringstream ss(line);
            ss >> id >> score >> name;

            if (id == 0 && score == 0.f && name.empty())
            {
                std::cout << "添加失败!" << std::endl;
                break;
            }
            sys.add_student(id, score, name);
            break;
        }
        case 2:
        { // 显示所有学生
            sys.print_all_student();
        }
        break;
        case 3:
        { // 根据ID查找学生
            std::cout << "请输入要查找的学生ID: ";
            int id{};
            std::cin >> id;
            sys.find_student(id);
        }
        break;
        case 4:
        { // 退出
            std::cout << "谢谢使用!" << std::endl;
            is_running = false;
        }
        break;

        default:
            std::cout << "没有这个功能!" << std::endl;
            break;
        }
    }
}