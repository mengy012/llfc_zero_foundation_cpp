#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <algorithm>

class Complex
{
  private:
    double real_;
    double imag_;

  public:
    Complex(double real = 0, double imag = 0) : real_{real}, imag_{imag} {}

    // +
    Complex operator+(const Complex& other)
    {
        return {real_ + other.real_, imag_ + other.imag_};
    }
    // -
    Complex operator-(const Complex& other)
    {
        return {real_ - other.real_, imag_ - other.imag_};
    }
    // *
    Complex operator*(const Complex& other)
    {
        return {(real_ * other.real_ - imag_ * other.imag_), (real_ * other.imag_ + imag_ * other.real_)};
    }
    // /
    Complex operator/(const Complex& other)
    {
        double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
        if (denominator == 0)
        {
            throw std::invalid_argument("denominator == 0");
        }

        return {((real_ * other.real_ + imag_ * other.imag_) / denominator), ((imag_ * other.real_ - real_ * other.imag_) / denominator)};
    }

    // +=
    Complex& operator+=(const Complex& other)
    {
        *this = operator+(other);
        return *this;
    }
    // -=
    Complex& operator-=(const Complex& other)
    {
        *this = operator-(other);
        return *this;
    }

    // *=
    Complex& operator*=(const Complex& other)
    {
        *this = operator*(other);
        return *this;
    }

    // /=
    Complex& operator/=(const Complex& other)
    {
        *this = operator/(other);
        return *this;
    }

    // ++i
    Complex& operator++()
    {
        real_++;
        imag_++;
        return *this;
    }
    // i++
    Complex operator++(int)
    {
        Complex tmp = *this;
        operator++();
        return tmp;
    }

    // --i
    Complex& operator--()
    {
        real_--;
        imag_--;
        return *this;
    }

    // i--
    Complex operator--(int)
    {
        Complex tmp = *this;
        operator--();
        return tmp;
    }

    // bool()
    operator bool()
    {
        return imag_ != 0;
    }

    // ==
    bool operator==(const Complex& other)
    {
        return (real_ == other.real_) && (imag_ == other.imag_);
    }
    // !=
    bool operator!=(const Complex& other)
    {
        return !operator==(other);
    }

    // >
    friend bool operator>(const Complex& a, const Complex& b);

    // >=
    // <
    // <=

    // <<
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    // >>
    friend std::istream& operator>>(std::istream& is, Complex& c);

    // []
    const double& operator[](int index) const
    {
        int real_index = std::clamp(index, 0, 1);

        switch (real_index)
        {
        case 0:
            return real_;
            break;
        case 1:
            return imag_;
            break;
        }
    }
    // ()
    double operator()(const std::string& part)
    {
        if (part == "real")
        {
            return real_;
        }
        else if (part == "imag")
        {
            return imag_;
        }
    }
};

bool operator>(const Complex& a, const Complex& b)
{
    double mod_a = sqrt(a.real_ * a.real_ + a.imag_ * a.imag_);
    double mod_b = sqrt(b.real_ * b.real_ + b.imag_ * b.imag_);
    return mod_a > mod_b;
}
std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << c.real_ << " + " << c.imag_ << 'i';
    return os;
}
std::istream& operator>>(std::istream& is, Complex& c)
{
    is >> c.real_ >> c.imag_;
    return is;
}
bool operator<(const Complex& a, const Complex& b)
{
    return b > a;
}
bool operator>=(const Complex& a, const Complex& b)
{
    return !(a < b);
}
bool operator<=(const Complex& a, const Complex& b)
{
    return !(a > b);
}

class Logger
{
  private:
    std::string message_;

  public:
    Logger(const std::string& message) : message_{message}
    {
        std::cout << (unsigned long long)message_.c_str() << std::endl;
    }

    Logger operator,(const Logger& log)
    {
        return message_ + ", " + log.message_;
    }

    const char* get_str() const
    {
        return message_.c_str();
    }
    friend std::ostream& operator<<(std::ostream& os, const Logger& log);
};

std::ostream& operator<<(std::ostream& os, const Logger& log)
{
    os << log.message_;
    return os;
}

int main()
{
    // {
    //     Complex c1(3.0, 4.0);
    //     Complex c2(1.5, -2.5);
    //     Complex c3;

    //     // 赋值运算
    //     c3 = c1;
    //     std::cout << "c3 = " << c3 << std::endl;

    //     // 加法
    //     Complex c4 = c1 + c2;
    //     std::cout << "c1 + c2 = " << c4 << std::endl;

    //     // 减法
    //     Complex c5 = c1 - c2;
    //     std::cout << "c1 - c2 = " << c5 << std::endl;

    //     // 乘法
    //     Complex c6 = c1 * c2;
    //     std::cout << "c1 * c2 = " << c6 << std::endl;

    //     // 除法
    //     try
    //     {
    //         Complex c7 = c1 / c2;
    //         std::cout << "c1 / c2 = " << c7 << std::endl;
    //     }
    //     catch (const std::invalid_argument& e)
    //     {
    //         std::cerr << "错误: " << e.what() << std::endl;
    //     }

    //     // 比较运算
    //     if (c1 > c2)
    //         std::cout << "c1 的模长大于 c2" << std::endl;
    //     else
    //         std::cout << "c1 的模长不大于 c2" << std::endl;

    //     // 逻辑非运算
    //     Complex c_zero;
    //     if (!c1)
    //         std::cout << "c1 是零复数" << std::endl;
    //     else
    //         std::cout << "c1 不是零复数" << std::endl;

    //     if (!c_zero)
    //         std::cout << "c_zero 是零复数" << std::endl;
    //     else
    //         std::cout << "c_zero 不是零复数" << std::endl;

    //     // 取反运算
    //     Complex c_neg = ~c1;
    //     std::cout << "~c1 = " << c_neg << std::endl;

    //     // 下标运算
    //     try
    //     {
    //         std::cout << "c1[0] (real) = " << c1[0] << std::endl;
    //         std::cout << "c1[1] (imag) = " << c1[1] << std::endl;
    //         // std::cout << "c1[2] = " << c1[2] << std::endl; // 会抛出异常
    //     }
    //     catch (const std::out_of_range& e)
    //     {
    //         std::cerr << "错误: " << e.what() << std::endl;
    //     }

    //     // 自增自减运算符
    //     std::cout << "c1 = " << c1 << std::endl;
    //     std::cout << "++c1 = " << ++c1 << std::endl;
    //     std::cout << "c1++ = " << c1++ << std::endl;
    //     std::cout << "c1 = " << c1 << std::endl;
    //     std::cout << "--c1 = " << --c1 << std::endl;
    //     std::cout << "c1-- = " << c1-- << std::endl;
    //     std::cout << "c1 = " << c1 << std::endl;

    //     // 函数调用运算符
    //     std::cout << "c1 的实部: " << c1("real") << std::endl;
    //     std::cout << "c1 的虚部: " << c1("imag") << std::endl;

    //     // 输入运算
    //     std::cout << "请输入一个复数的实部和虚部，以空格分隔: ";
    //     Complex c_input;
    //     std::cin >> c_input;
    //     std::cout << "您输入的复数是: " << c_input << std::endl;
    // }

    {
        Logger log1("info 1");
        Logger log2("info 2");
        Logger log3("info 3");

        Logger mix = (log1, log2, log3);

        std::cout << (unsigned long long)mix.get_str() << std::endl;
    }
}