#include <iostream>
#include <utility>
#include <type_traits>
#include <string>

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
}