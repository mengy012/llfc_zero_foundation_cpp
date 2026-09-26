// #include <iostream>

// // 整数加法函数
// int add(int a, int b)
// {
//     return a + b;
// }

// int main()
// {
//     std::cout << "hello" << std::endl;
// }

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <execution>
#include <functional>

class Person
{
  public:
    std::string name;
    int age;

    Person(std::string n, int a) : name(n), age(a) {}
    Person(Person&& other) : name(std::move(other.name)), age(other.age) {}
};

Person createPerson(std::string name, int age)
{
    Person p(name, age);
    return p; // 返回对象
}

template <long long N>
constexpr long long factorial()
{
    if constexpr (N == 0 || N == 1)
    {
        return 1;
    }
    else
    {
        return N * factorial<N - 1>();
    }
}

template <long long N>
constexpr long long fb()
{
    if constexpr (N <= 0)
    {
        return 0;
    }
    else if constexpr (N == 1)
    {
        return 1;
    }
    else
    {
        return fb<N - 1>() + fb<N - 2>();
    }
}

class EventSystem
{

  public:
    using callback = std::function<int(int)>;
    EventSystem() = default;
    ~EventSystem() = default;

    void regist_callback(const callback& cb)
    {
        callbacks_.push_back(cb);
    }

    void call_callbacks(int data)
    {
        for (auto& cb : callbacks_)
        {
            std::cout << cb(data) << ' ';
        }
        std::cout << '\n';
    }

  private:
    std::vector<EventSystem::callback> callbacks_;
};

int display(int a)
{
    return a;
}

int main()
{
    // {
    //     Person person = createPerson("Alice", 25);
    //     std::cout << "Name: " << person.name << ", Age: " << person.age << std::endl;
    //     return 0;
    // }

    // {
    //     std::cout << factorial<4>() << std::endl;
    // }

    {
        std::cout << fb<0>() << std::endl;
        std::cout << fb<1>() << std::endl;
        std::cout << fb<2>() << std::endl;
        std::cout << fb<3>() << std::endl;
        std::cout << fb<4>() << std::endl;
        std::cout << fb<10>() << std::endl;
    }

    {
        // std::vector<std::string> fruits = {"apple", "banana", "kiwi", "strawberry", "grape", "pineapple"};
        std::vector<std::string> fruits = {"grape", "apple", "banana", "kiwi", "strawberry", "pineapple"};

        std::sort(std::execution::par_unseq, fruits.begin(), fruits.end(), [](const std::string& s1, const std::string& s2) { return s1.size() < s2.size(); });

        std::for_each(fruits.begin(), fruits.end(), [](const std::string& s) { std::cout << s << ' '; });
        // kiwi grape apple banana pineapple strawberry
        std::cout << std::endl;
    }

    {
        std::cout << "_____________________________________" << std::endl;

        int a = 42;
        EventSystem sys;
        sys.regist_callback(display);
        sys.regist_callback([a](int v) { return a + v; });
        sys.regist_callback([](int v) { return v * v; });

        sys.call_callbacks(2); // 2 44 4

        std::cout << "_____________________________________" << std::endl;
    }
}