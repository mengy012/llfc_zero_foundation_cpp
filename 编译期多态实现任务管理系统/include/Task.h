#pragma once

#include <string>
#include <chrono>
#include <fmt/format.h>
#include <fmt/chrono.h>

using namespace std::chrono_literals;

struct TaskData
{
    int id_{};
    int priority_{};            // 优先级 越大优先级越高
    std::string description_{}; // 任务描述
    std::string deadline_{};    // 截止日期

    TaskData() = default;
    TaskData(int id, int priority, const std::string& description, const std::string& deadline) : id_{id}, priority_{priority}, description_{description}, deadline_{deadline} {}
};
