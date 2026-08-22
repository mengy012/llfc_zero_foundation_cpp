#include <iostream>
#include <utility>

union int_byte
{
    int int_val;
    char char_val[4];
};

void func(const int& v)
{
    std::cout << "lvalue!!!" << std::endl;
}
void func(int&& v)
{
    std::cout << "rvalue" << std::endl;
}

template <typename T>
void perfect_forwarding(T&& v)
{
    func(std::forward<T>(v));
}


int main()
{
    // int_byte a;
    // a.int_val = 0x12345699;
    // for (int i = 0; i < 4; ++i)
    // {
    //     std::cout << std::hex << (int)(unsigned char)a.char_val[i] << '\n';
    // }

    // int a{42};
    // int& r_a{a};
    // std::cout << (long long)&a << '\n' << (long long)&r_a << std::endl;

    int a{33};
    // 左值
    func(a);
    // 右值
    func(42);

    perfect_forwarding(a);
    perfect_forwarding(42);
}