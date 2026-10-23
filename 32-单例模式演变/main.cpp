#include <iostream>
#include <utility>
#include <type_traits>
#include <string>
#include <functional>
#include <mutex>

template <typename T>
class Single
{
  public:
    Single(const Single&) = delete;
    Single& operator=(const Single&) = delete;
    Single(Single&&) = delete;
    Single& operator=(Single&&) = delete;

    static T& instance()
    {
        static T value;
        return value;
    }

  protected:
    Single() = default;
    ~Single() = default;
};

class A final : public Single<A>
{
  private:
    friend class Single<A>;
    A() = default;
    ~A() = default;

  public:
    A* get_p()
    {
        return this;
    }
};

template <typename T>
class Base
{
  public:
    void show()
    {
        static_cast<T*>(this)->show();
    }
};

class Derived_apple : public Base<Derived_apple>
{
    friend class Base<Derived_apple>;
    void show()
    {
        std::cout << "Derived_apple" << std::endl;
    }
};

class Derived_banana : public Base<Derived_banana>
{
    friend class Base<Derived_banana>;
    void show()
    {
        std::cout << "Derived_banana" << std::endl;
    }
};

template <typename T>
void show(T& obj)
{
    static_cast<Base<T>*>(&obj)->show();
}

int main()
{
    {
        std::cout << "hello world" << std::endl;
    }

    {
        int&& a = 10;
        std::cout << std::is_rvalue_reference_v<decltype(std::forward<decltype(a)>(a))> << std::endl;
    }
    {
        std::cout << A::instance().get_p() << std::endl;
        std::cout << A::instance().get_p() << std::endl;
        std::cout << A::instance().get_p() << std::endl;
    }

    {
        Derived_apple apple;
        Derived_banana banana;
        show(apple);
        show(banana);
    }
}