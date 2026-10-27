#include <iostream>
#include <variant>
#include <unordered_map>
#include <string>
#include "Command.h"

int main()
{
    DataStore data_store("./tasks.txt");
    TaskManager task_manager(data_store);

    CommandAdd command_add(task_manager);
    CommandDelete command_delete(task_manager);
    CommandUpdate command_update(task_manager);
    CommandList command_list(task_manager);
    CommandExit command_exit(task_manager);

    bool is_exit{false};

    std::unordered_map<std::string, std::variant<CommandAdd, CommandDelete, CommandUpdate, CommandList, CommandExit>> commands;

    commands.emplace("add", command_add);
    commands.emplace("delete", command_delete);
    commands.emplace("update", command_update);
    commands.emplace("list", command_list);
    commands.emplace("exit", command_exit);

    std::cout << "欢迎使用任务管理系统！" << std::endl;
    std::cout << "可用命令: add, delete, list, update, exit" << std::endl;

    while (!is_exit)
    {
        std::cout << "> " << std::flush;

        std::string line;
        if (!std::getline(std::cin, line))
        {
            break;
        }

        auto pos = line.find(' ');
        std::string command = line.substr(0, pos);

        auto it = commands.find(command);
        if (it != commands.end())
        {
            std::string data = line.substr(pos + 1);

            std::visit([&data, &is_exit](auto&& v)
            {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, CommandAdd>)
                {
                    v.execute(data);
                }
                else if constexpr (std::is_same_v<T, CommandDelete>)
                {
                    int id{};
                    auto res = std::from_chars(data.data(), data.data() + data.size(), id);
                    if (res.ec == std::error_code{} && res.ptr == data.data() + data.size())
                    {
                        v.execute(id);
                    }
                }
                else if constexpr (std::is_same_v<T, CommandUpdate>)
                {
                    std::string tmp(std::move(data));
                    size_t pos{};

                    std::string id_str;
                    int id{};
                    pos = tmp.find(',');
                    if (pos != tmp.npos)
                    {
                        id_str = tmp.substr(0, pos);
                        auto res = std::from_chars(id_str.data(), id_str.data() + id_str.size(), id);
                        if (res.ec == std::error_code{} && res.ptr == id_str.data() + id_str.size())
                        {
                            v.execute(id, tmp.substr(pos + 1));
                        }
                    }
                }
                else if constexpr (std::is_same_v<T, CommandList>)
                {
                    v.execute();
                }
                else if constexpr (std::is_same_v<T, CommandExit>)
                {
                    v.execute(is_exit);
                }
            }, (*it).second);
        }
        else
        {
            ERROR("unknown command\n");
        }
    }
}