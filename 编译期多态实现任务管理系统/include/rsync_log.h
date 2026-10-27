#pragma once

#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <utility>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <condition_variable>

namespace fs = std::filesystem;
using namespace std::chrono_literals;

enum class Log_level
{
    DEBUG,
    INFO,
    ERROR
};

class Logger
{
  private:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& get_logger()
    {
        static Logger logger;
        return logger;
    }

    Logger()
    {
        output_thread_ = std::thread([this]()
        {
            std::ostream* os = &std::cout;
            std::ofstream ofs(out_file_path_, std::ios::app);
            if (write_into_file_)
            {
                os = &ofs;
            }
            while (true)
            {

                std::queue<std::string> pending;
                bool should_exit = false;

                {
                    std::unique_lock<std::mutex> locked(mtx_);
                    cv_.wait(locked, [this]() { return !msg_queue_.empty() || exit_flag_; });
                    pending.swap(msg_queue_);
                    should_exit = exit_flag_;
                }
                while (!pending.empty())
                {

                    *os << pending.front();
                    pending.pop();
                }
                os->flush();
                if (should_exit)
                {
                    return;
                }
            }
        });
    }
    ~Logger()
    {
        {
            std::scoped_lock locked(mtx_);
            exit_flag_ = true;
        }
        cv_.notify_all();
        output_thread_.join();
    }

    std::string get_current_time()
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(now + 8h);
        auto time_str = fmt::format("{:%Y-%m-%d %H:%M:%S}", time);
        // X_X
        // std::cout << time_str << std::endl;
        return time_str;
    }

    bool exit_flag_{false};
    bool write_into_file_{false};
    fs::path out_file_path_{"./log.txt"};
    std::thread output_thread_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<std::string> msg_queue_;

  public:
    inline static Logger& logger = get_logger();

    template <typename... Args>
    void log(Log_level level, fmt::format_string<Args...> format_str, Args&&... args)
    {
        std::string msg(get_current_time());
        if (!write_into_file_)
        {
            switch (level)
            {
            case Log_level::DEBUG:
                msg.insert(0, fmt::format(fmt::emphasis::bold | fg(fmt::color::gold), "{} ", "[DEBUG]"));
                break;
            case Log_level::INFO:
                msg.insert(0, fmt::format(fmt::emphasis::bold | fg(fmt::color::green), "{} ", "[INFO]"));
                break;
            case Log_level::ERROR:
                msg.insert(0, fmt::format(fmt::emphasis::bold | fg(fmt::color::red), "{} ", "[ERROR]"));
                break;

            default:
                throw std::invalid_argument("invalid level");
            }

            msg += ' ' + fmt::format(fmt::emphasis::bold | fg(fmt::color::white_smoke), format_str, std::forward<Args>(args)...);
        }
        else
        {
            switch (level)
            {
            case Log_level::DEBUG:
                msg.insert(0, "[DEBUG] ");
                break;
            case Log_level::INFO:
                msg.insert(0, "[INFO] ");
                break;
            case Log_level::ERROR:
                msg.insert(0, "[ERROR] ");
                break;

            default:
                throw std::invalid_argument("invalid level");
            }

            msg += ' ' + fmt::format(format_str, std::forward<Args>(args)...);
        }
        // X_X
        // std::cout << msg << std::endl;

        msg += '\n';

        {
            std::scoped_lock<std::mutex> locked(mtx_);
            msg_queue_.push(std::move(msg));
        }
        cv_.notify_one();
    }
};

#define logger Logger::logger

#define DEBUG(fmt_str, ...) logger.log(Log_level::DEBUG, fmt_str __VA_OPT__(,) __VA_ARGS__)
#define INFO(fmt_str, ...) logger.log(Log_level::INFO, fmt_str __VA_OPT__(,)__VA_ARGS__)
#define ERROR(fmt_str, ...) logger.log(Log_level::ERROR,fmt_str __VA_OPT__(,) __VA_ARGS__)
