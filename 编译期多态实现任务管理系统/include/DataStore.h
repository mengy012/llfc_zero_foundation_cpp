#pragma once

#include <fstream>
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

class DataStore
{
  public:
    DataStore(const char* str) : file_path_{str} {}

    std::optional<std::string> read()
    {
        std::fstream file_(file_path_, std::ios::in | std::ios::out | std::ios::binary);
        if (file_)
        {
            file_.seekg(0, std::ios::end);
            auto file_size = file_.tellg();
            file_.seekg(0, std::ios::beg);

            std::string buf(static_cast<size_t>(file_size), ' ');
            file_.read(buf.data(), static_cast<std::streamsize>(file_size));

            return buf;
        }
        return std::nullopt;
    }

    void write(const std::string& data)
    {
        std::fstream file_ = std::fstream(file_path_, std::ios::out | std::ios::trunc);
        if (file_)
        {
            file_ << data;
        }
    }

  private:
    fs::path file_path_;
};
