#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <memory>
#include <string>
#include <cstring>

// 创建一个简单的MyString类，支持拷贝构造，默认构造，有参构造，支持输出和比较等。
namespace my
{
class string
{
  public:
    // 默认构造
    string() : size_{0}, data_{std::make_unique<char[]>(1)} {}
    // c风格字符串构造
    string(const char* str) : size_(std::strlen(str)), data_{std::make_unique<char[]>(size_ + 1)}
    {
        std::strcpy(data_.get(), str);
    }
    // 移动构造
    string(string&& other) noexcept : size_{other.size_}, data_{std::move(other.data_)}
    {
        other.size_ = 0;
        // other.data_ = std::make_unique<char[]>(1);
    }
    // 移动赋值
    string& operator=(string&& other) noexcept
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
    string(const string& other) : size_{other.size_}, data_{std::make_unique<char[]>(size_ + 1)}
    {
        std::strcpy(data_.get(), other.c_str());
    }
    // 拷贝赋值
    string& operator=(const string& other)
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

        string tmp(other);

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
    friend std::ostream& operator<<(std::ostream& os, const my::string& str);

    // size()
    uint64_t size() const
    {
        return size_;
    }
    // 比较str是否相等
    bool operator==(const string& str) const
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
    string operator+(const string& str) const
    {
        uint64_t new_str_size = size_ + str.size_ + 1;
        std::unique_ptr<char[]> new_str = std::make_unique<char[]>(new_str_size);
        std::strcpy(new_str.get(), c_str());
        std::strcpy(new_str.get() + size_, str.c_str());

        return string{new_str.get()};
    }
    // 析构
    ~string() = default;

  private:
    uint64_t size_{};
    std::unique_ptr<char[]> data_;
};
std::ostream& operator<<(std::ostream& os, const my::string& str)
{
    os << str.c_str();
    return os;
}
} // namespace my

int main()
{
    // 默认构造
    my::string s1;
    std::cout << s1 << std::endl;
    // c风格构造
    my::string s2("hello");
    std::cout << "size: " << s2.size() << " " << "data: " << s2.c_str() << std::endl;
    // 拷贝构造
    // 原始字符串 basic str
    my::string origin_str("aaa");
    my::string s3(origin_str);
    std::cout << "size: " << s3.size() << " " << "data: " << s3.c_str() << std::endl;

    // 拷贝赋值
    my::string origin_str1("bbb");
    s3 = origin_str1;
    std::cout << "size: " << s3.size() << " " << "data: " << s3.c_str() << std::endl;

    {
        // 移动构造
        my::string apple("apple");
        my::string str(std::move(apple));
        std::cout << "size: " << apple.size() << " " << "data: " << apple.c_str() << std::endl;
        std::cout << "size: " << str.size() << " " << "data: " << str.c_str() << std::endl;
    }
    {
        // 移动赋值
        my::string bob("bob");
        my::string cat("cat");
        cat = std::move(bob);
        std::cout << "size: " << bob.size() << " " << "data: " << bob.c_str() << std::endl;
        std::cout << "size: " << cat.size() << " " << "data: " << cat.c_str() << std::endl;
    }

    {
        // 判断相等
        my::string a("apple");
        my::string b("apple");

        if (a == b)
        {
            std::cout << "equal" << std::endl;
        }
    }

    {
        // 字符串追加
        my::string a{"abc"};
        my::string b{"def"};
        std::cout << a + b << std::endl;
    }
}