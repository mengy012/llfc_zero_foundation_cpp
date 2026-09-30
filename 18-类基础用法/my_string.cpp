#include "my_string.h"

class ImplString
{
  public:
    // 默认构造
    ImplString() : size_{0}, data_{std::make_unique<char[]>(1)} {}
    // c风格字符串构造
    ImplString(const char* str)
    {
        if (!str)
        {
            return;
        }
        size_ = std::strlen(str);
        data_ = std::make_unique<char[]>(size_ + 1);
        std::strcpy(data_.get(), str);
    }
    // 移动构造
    ImplString(ImplString&& other) noexcept : size_{other.size_}, data_{std::move(other.data_)}
    {
        other.size_ = 0;
        // other.data_ = std::make_unique<char[]>(1);
    }
    // 移动赋值
    ImplString& operator=(ImplString&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        // data_.reset();

        size_ = other.size_;
        data_ = std::move(other.data_);

        other.size_ = 0;
        // other.data_ = std::make_unique<char[]>(1);
        return *this;
    }
    // 拷贝构造
    ImplString(const ImplString& other) : size_{other.size_}, data_{std::make_unique<char[]>(size_ + 1)}
    {
        std::strcpy(data_.get(), other.c_str());
    }
    // 拷贝赋值
    ImplString& operator=(const ImplString& other)
    {
        if (this == &other)
        {
            return *this;
        }

        // data_.reset();

        // size_ = other.size_;
        // data_ = std::make_unique<char[]>(size_ + 1);

        // std::strcpy(data_.get(), other.data_.get());
        // return *this;

        ImplString tmp(other);

        size_ = tmp.size_;
        data_ = std::move(tmp.data_);

        return *this;
    }
    // c_str
    const char* c_str() const
    {
        return data_.get() ? data_.get() : "";
    }
    // 友元 重载operator<<输出
    friend std::ostream& operator<<(std::ostream& os, const ImplString& str);

    // size()
    uint64_t size() const
    {
        return size_;
    }
    // 比较str是否相等
    bool operator==(const ImplString& str) const
    {
        if (size_ != str.size_)
        {
            return false;
        }

        if (!std::strcmp(c_str(), str.c_str()))
        {
            return true;
        }
        return false;
    }
    // 合并两个str
    ImplString operator+(const ImplString& str) const
    {
        uint64_t new_str_size = size_ + str.size_ + 1;
        std::unique_ptr<char[]> new_str = std::make_unique<char[]>(new_str_size);
        std::strcpy(new_str.get(), c_str());
        std::strcpy(new_str.get() + size_, str.c_str());

        return ImplString{new_str.get()};
    }
    // 析构
    ~ImplString() = default;

  private:
    uint64_t size_{};
    std::unique_ptr<char[]> data_;
};
std::ostream& operator<<(std::ostream& os, const ImplString& str)
{
    os << str.c_str();
    return os;
}

namespace my
{
std::ostream& operator<<(std::ostream& os, const my::string& str)
{
    os << str.c_str();
    return os;
}

} // namespace my

my::string::string() : impl{std::make_unique<ImplString>()} {}

my::string::string(const char* str) : impl{std::make_unique<ImplString>(str)} {}

my::string::string(string&& other) noexcept : impl{std::move(other.impl)} {}

my::string& my::string::operator=(string&& other) noexcept
{
    if (this != &other)
    {
        impl = std::move(other.impl);
    }
    return *this;
}

my::string::string(const string& other) : impl{std::make_unique<ImplString>(other.c_str())} {}

my::string& my::string::operator=(const string& other)
{
    if (this != &other)
    {
        impl = std::make_unique<ImplString>(other.c_str());
    }
    return *this;
}

const char* my::string::c_str() const
{
    return impl ? impl->c_str() : "";
}

uint64_t my::string::size() const
{
    return impl ? impl->size() : 0;
}

bool my::string::operator==(const string& str) const
{
    return size() == str.size() && std::strcmp(c_str(), str.c_str()) == 0;
}

my::string my::string::operator+(const string& str) const
{
    if (!impl) return string{str};
    if (!str.impl) return *this;
    return string{impl->operator+(*str.impl).c_str()};
}

my::string::~string() {}
