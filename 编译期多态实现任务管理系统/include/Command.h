#pragma once

#include "TaskManager.h"
#include <string>
#include <rsync_log.h>

class CommandAdd
{
  public:
    CommandAdd(TaskManager& manager) : manager_{manager} {}

    void execute(const std::string& str)
    {
        manager_.add_task(str);
        INFO("add: {}", str);
    }

  private:
    TaskManager& manager_;
};
class CommandDelete
{
  public:
    CommandDelete(TaskManager& manager) : manager_{manager} {}

    void execute(int id)
    {
        manager_.delete_task(id);
        INFO("delete: {}", id);
    }

  private:
    TaskManager& manager_;
};
class CommandList
{
  public:
    CommandList(TaskManager& manager) : manager_{manager} {}

    void execute()
    {
        manager_.list_task();
        INFO("list: ");
    }

  private:
    TaskManager& manager_;
};
class CommandUpdate
{
  public:
    CommandUpdate(TaskManager& manager) : manager_{manager} {}

    void execute(int id, const std::string& str)
    {
        manager_.update_task(id, str);
        INFO("update: {} {}", id, str);
    }

  private:
    TaskManager& manager_;
};
class CommandExit
{
  public:
    CommandExit(TaskManager& manager) : manager_{manager} {}

    void execute(bool& is_exit)
    {
        is_exit = true;
    }

  private:
    TaskManager& manager_;
};