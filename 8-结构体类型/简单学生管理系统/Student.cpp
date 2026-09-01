#include "Student.h"
#include <iostream>
#include <algorithm>
void Student_management_system::add_student(int id, float score, std::string name)
{
    students_.emplace_back(id, score, name);
}

void Student_management_system::print_all_student()
{
    std::cout << "--------------------------------------------------" << std::endl;
    for (const auto& [id, score, name] : students_)
    {
        std::cout << "id: " << id << '\n' << "name: " << name << '\n' << "score: " << score << std::endl;
    }
    std::cout << "--------------------------------------------------" << std::endl;
}

void Student_management_system::find_student(int id)
{
    auto it = std::find_if(students_.begin(), students_.end(), [id](const Student& s)
    {
        if (s.id_ == id) return true;
        return false;
    });
    if (it == students_.end())
    {
        std::cout << "no found" << std::endl;
    }
    else
    {
        const auto& [id, score, name] = *it;
        std::cout << "id: " << id << '\n' << "name: " << name << '\n' << "score: " << score << std::endl;
    }
}