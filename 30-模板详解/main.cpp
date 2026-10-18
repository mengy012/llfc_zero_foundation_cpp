#include <string>
#include <iostream>
#include <type_traits>
#include <vector>
#include <cstdint>
#include <array>
#include <stack>

#define STR(x) #x

template <typename T>
T max_value(T a, T b)
{
    return (a > b) ? a : b;
}

template <>
std::string max_value<std::string>(std::string a, std::string b)
{
    std::cout << STR(T max_value<std::string>(T a, T b)) << std::endl;
    return "default";
}

template <typename T_1, typename T_2>
class pair
{
  public:
    T_1 first_;
    T_2 second_;
    pair(T_1 first = T_1{}, T_2 second = T_2{}) : first_{first}, second_{second} {}

  private:
};

template <>
class pair<float, float>
{
  public:
    pair()
    {
        std::cout << "pair<float,float>" << std::endl;
    }
};
template <typename T>
class pair<T, double>
{
  public:
    pair()
    {
        std::cout << "pair<" STR(T) ",double>" << std::endl;
    }
};

template <typename T, size_t size>
class fixed_array
{
  public:
    T arr[size];

    fixed_array(T v = T{})
    {
        for (int i = 0; i < size; ++i)
        {
            arr[i] = v;
        }
    }

    T& operator[](size_t index)
    {
        return arr[index];
    }

    void print()
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << arr[i] << std::endl;
        }
    }
};

template <template <typename, size_t> typename fixed_array, typename T, size_t size>
class container
{
  public:
    void print(fixed_array<T, size> arr)
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << arr[i] << std::endl;
        }
    }
};

template <typename T>
using func = T (*)(T, T);
template <typename T, func<T> f, T a, T b>
class bind_max_value
{
  public:
    bind_max_value()
    {
        std::cout << f(a, b) << std::endl;
    }
};

// void print_all()
// {

// }

// template <typename T, typename... Args>
// void print_all(const T& first, const Args&... args)
// {
//     std::cout << first << std::endl;
//     print_all(args...);
// }
template <typename... Args>
void print_all(const Args&... args)
{
    ((std::cout << args << ' '), ...) << std::endl;
}

template <typename... Args>
auto sub(Args... args) -> decltype((... - args))
{
    return (... - args);
}
template <typename... Args>
auto sub_right(Args... args) -> decltype((args - ...))
{
    return (args - ...);
}

// void log(const std::string& msg)
// {
//     std::cout << msg << std::endl;
// }

// template <typename T, typename... Args>
// void log(const std::string& msg, const T& first, const Args&... args)
// {
//     std::cout << msg << " : " << first << ' ';
//     log("", args...);
// }

// // 基础情况：无参数
// void log(const std::string& msg)
// {
//     std::cout << msg << std::endl;
// }

// // 递归情况：至少一个参数
// template <typename T, typename... Args>
// void log(const std::string& msg, const T& first, const Args&... args)
// {
//     std::cout << msg << ": " << first << " ";
//     log("", args...); // 递归调用，省略消息前缀
// }

template <typename T, typename... Args>
void log(const T& first, Args... args)
{
    std::cout << first << ": ";
    print_all(args...);
}

template <typename... Args>
auto complexFold(const Args&... args)
{
    return (args + ...) * (args + ...);
}

template <typename T, typename... Args>
T maxAll(T first, Args... args)
{
    ((first = std::max(first, args)), ...);
    return first;
}

// 适用于整数类型
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type print_type(T value)
{
    std::cout << "Integral type: " << value << std::endl;
}

// 适用于浮点类型
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type print_type(T value)
{
    std::cout << "Floating point type: " << value << std::endl;
}

struct WithValueType
{
    using value_type = int;
};

struct WithoutValueType
{
};

struct WithVoidValueType
{
    using value_type = void;
};
template <typename T>
    requires(!std::is_void_v<typename T::value_type>)
void type_printer()
{
    std::cout << typeid(typename T::value_type).name() << std::endl;
}

template <typename T>
class Logger
{
  public:
    static void log(const T& m)
    {
        std::cout << "general: " << m << std::endl;
    }
};

template <typename T>
concept Pointer = std::is_pointer_v<T>;

template <Pointer T>
class Logger<T>
{
  public:
    static void log(const T& p)
    {
        if (p)
        {
            std::cout << *p << std::endl;
        }
        else
        {
            std::cout << STR(nullptr) << std::endl;
        }
    }
};

template <typename T>
concept String = std::same_as<T, std::string>;

template <String T>
class Logger<T>
{
  public:
    static void log(const T& s)
    {
        std::cout << "string: " << s << std::endl;
    }
};

template <typename... Args>
void MultiLogger(Args... args)
{
    ((std::cout << args << ' '), ...);
    std::cout << std::endl;
}

template <typename T>
concept has_size = requires(const T& obj) {
    { obj.size() } -> std::same_as<std::size_t>;
};

template <has_size T>
void print_size(const T& c)
{
    std::cout << c.size() << std::endl;
}

template <unsigned long long N>
struct factorial
{
    static constexpr decltype(N) value = N * factorial<N - 1>::value;
};

template <>
struct factorial<1>
{
    static constexpr unsigned long long value = 1;
};
template <>
struct factorial<2>
{
    static constexpr unsigned long long value = 2;
};

template <uint64_t N>
struct fib
{
    inline static constexpr uint64_t value = fib<N - 1>::value + fib<N - 2>::value;
};

template <>
struct fib<0>
{
    inline static constexpr uint64_t value = 0;
};
template <>
struct fib<1>
{
    inline static constexpr uint64_t value = 1;
};

template <typename T>
concept addable = requires(T a, T b) { a + b; };

template <typename T>
consteval bool is_addable()
{
    return addable<T>;
}

template <uint64_t... Ns>
struct Sum
{
    inline static constexpr int64_t value = (uint64_t(0) + ... + Ns);
};

template <uint64_t... Ns>
inline static constexpr uint64_t Sum_v = Sum<Ns...>::value;

template <typename... Ts>
struct TypeList
{
};

template <typename List>
struct LengthOf;

template <>
struct LengthOf<TypeList<>>
{
    static constexpr size_t length = 0;
};

template <typename Head, typename... tail>
struct LengthOf<TypeList<Head, tail...>>
{
    static constexpr size_t length = 1 + LengthOf<TypeList<tail...>>::length;
};

template <typename List, size_t N>
struct TypeAt;

template <typename Head, typename... tail>
struct TypeAt<TypeList<Head, tail...>, 0>
{
    using type = Head;
};

template <typename Head, typename... tail, size_t N>
struct TypeAt<TypeList<Head, tail...>, N>
{
    using type = typename TypeAt<TypeList<tail...>, N - 1>::type;
};

template <std::movable T>
void Swap(T& a, T& b)
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template <typename T>
    requires std::default_initializable<T>
struct Triple
{
    T first_{};
    T second_{};
    T third_{};

    T& get(size_t index)
    {
        switch (index)
        {
        case 0:
            return first_;
            break;
        case 1:
            return second_;
            break;
        case 2:
            return third_;
            break;

        default:
            break;
        }
    }
};

template <Pointer T>
struct pointer
{
    T ptr{nullptr};
    pointer(T p) : ptr{p} {}
    void print()
    {
        std::cout << "general pointer: " << *ptr << std::endl;
    }
};
template <>
struct pointer<bool*>
{
    bool* ptr{nullptr};
    pointer(bool* p) : ptr{p} {}
    void print()
    {
        std::cout << "Boolean Printer: " << *ptr << std::endl;
    }
};

template <typename first, typename... Ts>
void logmessages(first f, Ts... vs);

void logmessages()
{
    std::cout << std::endl;
};

template <typename first, typename... Ts>
void logmessages(first f, Ts... vs)
{
    std::cout << f << ' ';
    logmessages(vs...);
}

template <typename T>
typename std::enable_if<has_size<T>, void>::type enableIfExample(const T& c)
{
    std::cout << c.size() << std::endl;
}

template <std::integral T>
bool isEven(const T& v)
{
    return v % 2 == 0;
}

template <typename T, size_t N>
struct FixedStack
{
    std::array<T, N> stack_{};

    size_t top_idx{};
    size_t base_idx{};

    bool empty()
    {
        return top_idx - base_idx == 0;
    }

    T& top()
    {
        if (!empty())
        {
            return stack_[top_idx - 1];
        }
    }

    void push(const T& v)
    {
        if (top_idx < N)
        {
            stack_[top_idx] = v;
            ++top_idx;
        }
    }

    void pop()
    {
        if (!empty())
        {
            --top_idx;
        }
    }
};

template <typename T>
struct TypeIdentity
{
    using type = T;
};

int main()
{
    // std::cout << STR(hello world) << std::endl;
    // std::cout << "hello world" << std::endl;
    {
        std::cout << max_value(1, 2) << std::endl;
        std::cout << max_value(3.14, 2.72) << std::endl; // double 类型
        std::cout << max_value('a', 'z') << std::endl;   // char 类型
        std::cout << max_value('A', 'Z') << std::endl;   // char 类型
    }

    {
        pair p(1, 2);
        pair p1("str1", "str2");
        pair<int, std::string> p3(67, "6767");
        std::cout << p.first_ << ' ' << p.second_ << std::endl;
        std::cout << p1.first_ << ' ' << p1.second_ << std::endl;
        std::cout << p3.first_ << ' ' << p3.second_ << std::endl;
    }

    {
        fixed_array<int, 2> arr;
        arr[0] = 1;
        arr[1] = 2;
        arr.print();
    }

    {
        fixed_array<int, 3> arr3(3);
        container<fixed_array, int, 3> instance;

        void (container<fixed_array, int, 3>::*ptr)(fixed_array<int, 3>) = &container<fixed_array, int, 3>::print;
        (instance.*ptr)(arr3);
    }

    {
        pair<int, int> pp;
        pair<float, float> p;
    }

    {
        bind_max_value<int, max_value<int>, 1, 9>();
    }

    {
        pair<std::string, double>();
    }

    {
        std::string a("a");
        std::string b("b");
        max_value<std::string>(a, b);
    }

    {
        print_all("a", 99, 3.14);
    }

    {
        // 1,2,3,4
        std::cout << sub(1, 2, 3, 4) << std::endl;
        std::cout << sub_right(1, 2, 3, 4) << std::endl;
    }

    {
        log("Error", 404, "Not Found");
        log("Sum", 10, 20, 30);
    }

    {
        std::cout << complexFold(1, 2, 3) << std::endl;
    }

    {
        std::cout << maxAll(1, 2, 3, 4) << std::endl;
    }

    {
        type_printer<WithValueType>();
        // type_printer<WithoutValueType>();
        // type_printer<WithVoidValueType>();
    }

    {
        int a = 10;
        double b = 3.14;
        std::string s = "Hello, World!";
        int* ptr = &a;
        double* pNull = nullptr;

        Logger<int>::log(a);
        Logger<double>::log(b);
        Logger<std::string>::log(s);
        Logger<int*>::log(ptr);
        Logger<double*>::log(pNull);

        MultiLogger(a, b, s, ptr, pNull);

        std::cout << ptr << std::endl;

        const char* text = "hello";

        std::cout << text << '\n';                           // hello
        std::cout << static_cast<const void*>(text) << '\n'; // 地址
    }

    {
        std::vector<int> vec = {1, 2, 3};
        std::string str = "Hello";
        int num = 42;

        print_size(vec);
        print_size(str);
        // print_size(num);
    }

    {
        std::cout << &factorial<1>::value << std::endl;
        std::cout << &factorial<2>::value << std::endl;
        std::cout << &factorial<3>::value << std::endl;
        std::cout << &factorial<4>::value << std::endl;
    }

    {
        std::cout << fib<0>::value << std::endl;
        std::cout << fib<1>::value << std::endl;
        std::cout << fib<2>::value << std::endl;
        std::cout << fib<3>::value << std::endl;
        std::cout << fib<4>::value << std::endl;
        std::cout << fib<5>::value << std::endl;
        std::cout << fib<20>::value << std::endl;
    }

    {
        std::cout << is_addable<int>() << std::endl;
        std::cout << is_addable<void>() << std::endl;

        std::cout << addable<int> << std::endl;
        std::cout << addable<void> << std::endl;
    }

    {

        std::cout << Sum<1>::value << std::endl;
        std::cout << Sum_v<1, 2> << std::endl;
        std::cout << Sum_v<1, 2, 3> << std::endl;
        std::cout << Sum_v<1, 2, 3, 4> << std::endl;
    }

    {
        using list = TypeList<char, int, long, float, double>;
        using type = TypeAt<list, 1>::type;
    }

    {
        int i1 = 1, i2 = 2;
        double d1 = .1, d2 = .2;
        std::string s1("s1"), s2("s2");
        Swap(i1, i2);
        Swap(d1, d2);
        Swap(s1, s2);

        std::cout << i1 << ' ' << i2 << std::endl;
        std::cout << d1 << ' ' << d2 << std::endl;
        std::cout << s1 << ' ' << s2 << std::endl;
    }

    {
        Triple<int> ti = {1, 2, 3};
        std::cout << ti.get(1) << std::endl;

        Triple<std::string> ts = {"a", "b", "c"};
        std::cout << ts.get(1) << std::endl;
    }

    {
        int a = 99;
        bool b = true;
        pointer<int*> ap(&a);
        ap.print();

        pointer<bool*> bp(&b);
        bp.print();
    }

    {
        logmessages(1, 2, 3, .1, .9, "aaa", "bbb");
    }
    {
        static_assert(Pointer<int*>, "int* is a pointer");
        static_assert(!Pointer<int>, "int is not a pointer");
    }
    {
        enableIfExample(std::vector<int>{1, 2, 3});
        // enableIfExample(1);
    }

    {
        std::cout << isEven(1) << std::endl;
        std::cout << isEven(2) << std::endl;
        // std::cout << isEven(.3) << std::endl;
    }
    {
        FixedStack<int, 3> s;
        std::cout << s.empty() << std::endl;

        s.push(1);
        s.push(2);
        s.push(3);
        s.push(4);

        std::cout << s.top() << std::endl;
        s.pop();
        std::cout << s.top() << std::endl;
        s.pop();
        std::cout << s.top() << std::endl;
        s.pop();

        std::cout << s.empty() << std::endl;
        // std::cout << s.top() << std::endl;
        // s.pop();
    }

    {
        static_assert(std::is_same<TypeIdentity<int>::type, int>::value, "TypeIdentity<int> should be int");
    }

    {
        using list = TypeList<char, int, long, float, double>;
        constexpr size_t value = LengthOf<list>::length;
    }
}