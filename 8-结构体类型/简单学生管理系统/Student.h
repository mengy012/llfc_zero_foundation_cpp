#pragma once

#include <string>
#include <utility>
#include <vector>

class Student
{

  public:
    Student(int id, float score, std::string name) : id_(id), score_(score), name_(std::move(name)) {}
    ~Student() = default;

    int id_;
    float score_;
    std::string name_;
};

class Student_management_system
{
  private:
    std::vector<Student> students_;

  public:
    void add_student(int id, float score, std::string name);
    void print_all_student();
    void find_student(int id);
};