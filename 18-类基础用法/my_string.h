#pragma once

#include <algorithm>
#include <utility>
#include <cstdint>
#include <memory>
#include <string>
#include <cstring>

// 创建一个简单的MyString类，支持拷贝构造，默认构造，有参构造，支持输出和比较等。
class ImplString;
namespace my
{

class string
{
  public:
    string();
    string(const char* str);
    string(string&& other) noexcept;
    string& operator=(string&& other) noexcept;
    string(const string& other);
    string& operator=(const string& other);

    const char* c_str() const;

    friend std::ostream& operator<<(std::ostream& os, const my::string& str);

    uint64_t size() const;
    bool operator==(const string& str) const;
    string operator+(const string& str) const;

    ~string();

  private:
    std::unique_ptr<ImplString> impl;
};

} // namespace my
