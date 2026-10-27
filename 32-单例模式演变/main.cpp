#include <iostream>
#include <utility>
#include <type_traits>
#include <string>
#include <functional>
#include <mutex>
#include <memory>
#include <functional>
#include <variant>
#include <any>
#include <map>

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

class Base
{
  public:
    virtual void show() = 0;
    virtual ~Base() = default;
};

template <typename T>
class Fruit_Base : public Base
{
  public:
    void show() override
    {
        static_cast<T*>(this)->impl_show();
    }
};

class Derived_apple : public Fruit_Base<Derived_apple>
{
  public:
    friend class Fruit_Base<Derived_apple>;
    void impl_show()
    {
        std::cout << "Derived_apple" << std::endl;
    }
};

class Derived_banana : public Fruit_Base<Derived_banana>
{
  public:
    friend class Fruit_Base<Derived_banana>;
    void impl_show()
    {
        std::cout << "Derived_banana" << std::endl;
    }
};

template <typename T>
void show(T& obj)
{
    static_cast<Fruit_Base<T>*>(&obj)->show();
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
        // show(apple);
        // show(banana);

        // Base* p = &apple;
        // p->show();

        // p = &banana;
        // p->show();
    }
    {
        Derived_apple apple;
        Derived_banana banana;

        std::unordered_map<std::string, std::variant<Derived_apple, Derived_banana>> m;
        m["apple"] = apple;
        m["banana"] = banana;

        std::visit([](auto&& v) { v.impl_show(); }, m["apple"]);
        std::visit([](auto&& v) { v.impl_show(); }, m["banana"]);
    }
}