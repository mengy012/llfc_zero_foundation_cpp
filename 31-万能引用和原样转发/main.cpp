#include <cassert>
#include <iostream>
#include <filesystem>
#include <utility>
#include <string>
#include <type_traits>

namespace fs = std::filesystem;

class A
{
  public:
    void show()
    {
        std::cout << "from class A" << std::endl;
    }

    A* get_this()
    {
        return this;
    }
};

float Q_rsqrt(float number)
{
    int i{};
    float x2 = number * 0.5f, y = number;
    i = *(int*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (x2 * y * y));
    return y;
}

void func(int& x)
{
    std::cout << "func(int&)" << std::endl;
}

void func(int&& x)
{
    std::cout << "func(int&&)" << std::endl;
}

template <typename T>
void check_reference(T&& x)
{
    std::cout << std::boolalpha;
    std::cout << "T is lvalue reference: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T is rvalue reference: " << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "T is rvalue : " << std::is_rvalue_reference<T&&>::value << std::endl;
    std::cout << "x is lvalue reference: " << std::is_lvalue_reference<decltype(x)>::value << std::endl;
    std::cout << "x is rvalue reference: " << std::is_rvalue_reference<decltype(x)>::value << std::endl;
}

// 目标函数，分别有左值和右值的重载
void process(int& x)
{
    std::cout << "process(int&)" << std::endl;
}

void process(int&& x)
{
    std::cout << "process(int&&)" << std::endl;
}

// 通用的包装函数，使用转发引用
template <typename T>
void wrapper(T&& arg)
{
    process(std::forward<T>(arg)); // 原样转发
}

template <typename T>
void deduce_type(T&&)
{
    std::cout << std::boolalpha;
    std::cout << "Is T an lvalue reference? " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "Is T an rvalue reference? " << std::is_rvalue_reference<T>::value << std::endl;
}

template <typename T>
void display_type(T&& param)
{
    std::cout << "Type of T: " << (std::is_lvalue_reference<T>::value ? "lvalue reference" : "rvalue reference") << ", "
              << (std::is_integral<typename std::remove_reference<T>::type>::value ? "Integral" : "Non-Integral") << std::endl;
}

class Person
{
  public:
    std::string name_{};
    int age_{};

    Person(const std::string& name = std::string{}, const int& age = int{}) : name_{name}, age_{age}
    {
        std::cout << "lvalue function" << std::endl;
    }
    Person(std::string&& name, int&& age) : name_{std::move(name)}, age_{age}
    {
        std::cout << "rvalue function" << std::endl;
    }

    void show()
    {
        std::cout << "name: " << name_ << ' ' << "age: " << age_ << std::endl;
    }
};

template <typename T, typename... Args>
T create(Args&&... args)
{
    return T(std::forward<Args>(args)...);
}

constexpr int compute()
{
    return 42;
}

template <typename T>
T&& my_forward(typename std::remove_reference_t<T>& v) noexcept
{
    return static_cast<T&&>(v);
}

template <typename T, typename... Args>
T my_create(Args&&... args)
{
    return T(my_forward<Args>(args)...);
}

int main()
{
    {
        fs::path dir = "data";
        fs::path file = dir / "logs" / "app.txt";

        std::cout << file << std::endl;
        std::cout << file.filename() << std::endl;
        std::cout << file.stem() << std::endl;
        std::cout << file.extension() << std::endl;
        std::cout << file.parent_path() << std::endl;

        std::cout << file.string() << std::endl;

        std::cout << fs::current_path() << std::endl;

        for (auto& entry : fs::recursive_directory_iterator(fs::current_path()))
        {
            std::cout << entry.path() << std::endl;
        }
    }
    {
        std::cout << Q_rsqrt(4) * 4.f << std::endl;
        std::cout << Q_rsqrt(1) * 1.f << std::endl;
        std::cout << Q_rsqrt(100) * 100.f << std::endl;
    }

    {
        int a = 10;    // a是一个左值
        int& b = a;    // b是a的左值引用
        int&& c = 20;  // c是一个右值引用，绑定到临时右值20
        int d = a + 5; // (a + 5)是一个纯右值

        std::string s1 = "Hello";              // s1是一个左值
        std::string s2 = std::string("World"); // std::string("World")是一个纯右值

        std::cout << "a: " << a << ", d: " << d << std::endl;
        std::cout << "s1: " << s1 << ", s2: " << s2 << std::endl;

        // 检查类型
        std::cout << std::boolalpha;
        // 使用 decltype((a)) 获取 a 的类型，包括引用
        // `(a)` 是一个左值表达式，所以 decltype((a)) 是 `int&`
        std::cout << "a 是左值: " << std::is_lvalue_reference<decltype((a))>::value << std::endl;
        std::cout << "c 是右值引用: " << std::is_rvalue_reference<decltype(c)>::value << std::endl;
    }

    {
        int a = 5;
        const int& ref = a;

        // 判断类型
        std::cout << std::boolalpha;
        // 使用 decltype((a)) 获取 a 的类型，包括引用
        // `(a)` 是一个左值表达式，所以 decltype((a)) 是 `int&`
        std::cout << "a 是左值: " << std::is_lvalue_reference<decltype((a))>::value << std::endl;
        std::cout << "ref 是左值引用: " << std::is_lvalue_reference<decltype(ref)>::value << std::endl;

        // 调用函数
        func(a);  // 调用func(int&)
        func(10); // 调用func(int&&)
    }
    {
        int a = 10;
        // check_reference(a);  // T被推导为 int&， 因此 T&& -> int& && -> int&
        // check_reference(20); // T被推导为 int，  T&& -> int&&

        int&& c = 10;
        check_reference(c);
        check_reference(std::move(c));
    }
    {
        int a = 10;
        wrapper(a);  // 传递左值，调用process(int&)
        wrapper(20); // 传递右值，调用process(int&&)
    }
    {
        const int a = 10;
        const volatile int c = 11;
        // wrapper(a);
        auto& b = a;
        // wrapper(c);
        auto&& d = c;
    }
    {
        int a = 1;
        std::cout << std::is_lvalue_reference_v<decltype(a++)> << std::endl;
        std::cout << std::is_lvalue_reference_v<decltype(++a)> << std::endl;
    }

    {
        int a = 5;
        const int& ref = a;

        deduce_type(a);            // T被推导为 int&
        deduce_type(10);           // T被推导为 int
        deduce_type(ref);          // T被推导为 const int&
        deduce_type(std::move(a)); // T被推导为 int
    }

    {
        int x = 10;
        const int& y = x;
        display_type(x);            // T被推导为 int&
        display_type(20);           // T被推导为 int&&
        display_type(y);            // T被推导为 const int&
        display_type(std::move(x)); // T被推导为 int&&
    }
    {
        std::string name = "bob";

        Person p1 = create<Person>(name, 28);
        p1.show();

        Person p2 = create<Person>("alice", 10);
        p2.show();

        Person p3 = create<Person>(std::string("tom"), 10);
    }
    {
        int a = compute();
        auto b = compute();
        auto&& c = compute();
    }

    {
        std::string name = "bob";

        Person p1 = my_create<Person>(name, 28);
        p1.show();

        Person p2 = my_create<Person>("alice", 10);
        p2.show();

        Person p3 = my_create<Person>(std::string("tom"), 10);
    }
}