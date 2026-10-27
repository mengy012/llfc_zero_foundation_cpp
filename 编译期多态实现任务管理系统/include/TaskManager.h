#pragma once

#include "Task.h"
#include "DataStore.h"
#include "rsync_log.h"
#include <string>
#include <chrono>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <charconv>
#include <optional>

using namespace std::chrono_literals;
using sys_clock = std::chrono::system_clock;
using sys_clock_time_point = std::chrono::system_clock::time_point;

class TaskManager
{
  public:
    void sort()
    {
        std::sort(tasks_.begin(), tasks_.end(), [](const TaskData& a, const TaskData& b) { return a.priority_ > b.priority_; });
    }

    std::optional<TaskData> create_task(const std::string& input)
    {
        std::string tmp;
        size_t l{}, r{};

        std::vector<std::string> info;
        while (true)
        {
            r = input.find(',', l);
            info.push_back(input.substr(l, r - l));
            if (r == input.npos) break;
            l = r + 1;
        }
        if (info.size() != 4)
        {
            ERROR("格式错误, 格式: id,description,priority,deadline");
            return std::nullopt;
        }

        int id{}, priority{};
        auto id_res = std::from_chars(info[0].data(), info[0].data() + info[0].size(), id);
        auto priority_res = std::from_chars(info[2].data(), info[2].data() + info[2].size(), priority);
        if (id_res.ec == std::error_code{} && id_res.ptr == info[0].data() + info[0].size() && priority_res.ec == std::error_code{} && priority_res.ptr == info[2].data() + info[2].size())
        {
            return TaskData(id, priority, info[1], info[3]);
        }
        return std::nullopt;
    }
    void add_task(const std::string& input)
    {
        std::string tmp(std::to_string(id_) + ',' + input);
        auto res = create_task(tmp);
        if (res)
        {
            tasks_.push_back(*res);
            ++id_;
            sort();
        }
    }

    void delete_task(int id)
    {
        auto it = std::find_if(tasks_.begin(), tasks_.end(), [id](const TaskData& d) { return id == d.id_; });
        if (it != tasks_.end())
        {
            tasks_.erase(it);
        }
    }

    void list_task()
    {
        std::for_each(tasks_.begin(), tasks_.end(),
                      [](const TaskData& d) { std::cout << "id: " << d.id_ << " 描述: " << d.description_ << " 优先级: " << d.priority_ << " 截止日期: " << d.deadline_ << std::endl; });
    }

    void update_task(int id, const std::string& new_data)
    {
        auto it = std::find_if(tasks_.begin(), tasks_.end(), [id](const TaskData& d) { return id == d.id_; });
        if (it != tasks_.end())
        {

            std::string tmp(std::to_string(id) + ',' + new_data);
            auto res = create_task(tmp);
            if (res)
            {
                (*it) = *res;
            }

            sort();
        }
    }

    TaskManager(DataStore& ds) : ds_{ds}
    {
        auto data = ds_.read();
        if (data)
        {
            std::istringstream iss(*data);
            std::string tmp;
            while (std::getline(iss, tmp))
            {
                if (tmp.empty()) continue;

                auto res = create_task(tmp);
                if (res)
                {
                    tasks_.push_back(*res);
                }
            }

            std::for_each(tasks_.begin(), tasks_.end(), [this](const TaskData& v) { id_ = std::max(id_, v.id_ + 1); });
        }
    }

    ~TaskManager()
    {
        std::string data;
        for (auto& ele : tasks_)
        {
            std::string task;
            task += std::to_string(ele.id_) + ',' + ele.description_ + ',' + std::to_string(ele.priority_) + ',' + ele.deadline_;
            data += task + '\n';
        }
        ds_.write(data);
    }

  private:
    DataStore& ds_;
    std::vector<TaskData> tasks_;
    int id_{};
};