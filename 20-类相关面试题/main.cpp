// // #include <iostream>

// // int main()
// // {
// //     std::cout << "hello world" << std::endl;
// // }

// #include <thread>
// #include <iostream>
// #include <memory>
// #include <utility>
// #include <cstdlib>
// #include <string>
// #include <cstring>

// class JoiningThread
// {
//   public:
//     JoiningThread() : _i(0) {}
//     JoiningThread(int i) : _i{i} {}
//     int GetIndex() const
//     {
//         return _i;
//     }
//     int Geta() const
//     {
//         return _a;
//     }

//   private:
//     std::thread _t;
//     int _i;
//     int _a{99};
// };

// class Base_a
// {
//   private:
//     /* data */
//   public:
//     Base_a(/* args */)
//     {
//         std::cout << "Base_a()" << std::endl;
//     }
//     virtual ~Base_a()
//     {
//         std::cout << "~Base_a()" << std::endl;
//     }

//     virtual void show()
//     {
//         std::cout << "Base_a::show()" << std::endl;
//     }
//     virtual void f()
//     {
//         std::cout << "Base_a::f()" << std::endl;
//     }
//     virtual void g()
//     {
//         std::cout << "Base_a::g()" << std::endl;
//     }
// };
// class Base_b
// {
//   private:
//     /* data */
//   public:
//     Base_b(/* args */)
//     {
//         std::cout << "Base_b()" << std::endl;
//     }
//     virtual ~Base_b()
//     {
//         std::cout << "~Base_b()" << std::endl;
//     }

//     virtual void show()
//     {
//         std::cout << "Base_b::show()" << std::endl;
//     }
//     virtual void f()
//     {
//         std::cout << "Base_b::f()" << std::endl;
//     }
//     virtual void g()
//     {
//         std::cout << "Base_b::g()" << std::endl;
//     }
// };

// class Derived : public Base_a , public Base_b
// {
//   private:
//     /* data */
//   public:
//     Derived(/* args */)
//     {
//         std::cout << "Derived()" << std::endl;
//     }
//     ~Derived()
//     {
//         std::cout << "~Derived()" << std::endl;
//     }
// };

// class MyClass
// {

//   public:
//     int x;
//     int y;
//     MyClass() : MyClass(0, 0) {} // 委托构造函数

//     MyClass(int a, int b) : x(a), y(b) {}
// };

// int main()
// {
//     //     JoiningThread js;
//     //     std::cout << "member _i is : " << js.GetIndex() << std::endl;
//     //     std::cout << "member _a is : " << js.Geta() << std::endl;

//     //     JoiningThread js1(42);
//     //     std::cout << "member _i is : " << js1.GetIndex() << std::endl;

//     //     int a{2};
//     //     int& ra = a;
//     //     int& rra = ra;
//     //     std::cout << (long long)&a << std::endl;
//     //     std::cout << (long long)&ra << std::endl;
//     //     std::cout << (long long)&rra << std::endl;

//     // Derived derived;
//     // Base* base_p = &derived;

//     // Base* base_p = new Derived;

//     // delete base_p;

//     // {
//     //     MyClass o;
//     //     std::cout << o.x << ' ' << o.y << std::endl;
//     //     MyClass o1(9, 9);
//     //     std::cout << o1.x << ' ' << o1.y << std::endl;
//     // }
//     // std::copy((int*)1, (int*)2);

//     // memcpy((int*)1, (int*)2, 99);

//     {
//         // using Vptr = void**;
//         using Vtable = void*;
//         using funp = void (*)(Base_a*);

//         Base_a base_a;

//         Vtable table = nullptr;
//         std::memcpy(&table, &base_a, sizeof(table));

//         // ((funp)((unsigned long long*)table)[0])(&base_a);
//         // ((funp)((unsigned long long*)table)[1])(&base_a);
//         ((funp)((unsigned long long*)table)[2])(&base_a);
//         ((funp)((unsigned long long*)table)[3])(&base_a);
//         ((funp)((unsigned long long*)table)[4])(&base_a);

//         // std::cout << (((unsigned long long*)table)[-2]) << std::endl;
//     }
// }

// #include <iostream>
// #include <string>

// // 基类 Device
// class Device
// {
//   public:
//     std::string brand;

//     Device(const std::string& brand_) : brand(brand_) {}

//     void showBrand() const
//     {
//         std::cout << "Brand: " << brand << std::endl;
//     }
// };

// // 派生类 Laptop，虚继承 Device
// class Laptop : virtual public Device
// {
//   public:
//     Laptop(const std::string& brand_) : Device(brand_) {}
// };

// // 派生类 Tablet，虚继承 Device
// class Tablet : virtual public Device
// {
//   public:
//     Tablet(const std::string& brand_) : Device(brand_) {}
// };

// // 派生类 Convertible
// class Convertible : public Laptop, public Tablet
// {
//   public:
//     Convertible(const std::string& brand_) : Device(brand_), Laptop(brand_), Tablet(brand_) {}
// };

// int main()
// {
//     Convertible c("TechBrand");
//     c.showBrand();

//     Laptop l("laptop");
//     l.showBrand();
//     Tablet t("tablet");
//     t.showBrand();
//     return 0;
// }

#include <iostream>

// 基类
class Base
{
  public:
    virtual Base* clone() const
    {
        std::cout << "Base cloned." << std::endl;
        return new Base(*this);
    }

    virtual ~Base() {}
};

// 派生类
class Derived : public Base
{
  public:
    Derived* clone() const override
    { // 协变返回类型
        std::cout << "Derived cloned." << std::endl;
        return new Derived(*this);
    }
};

int main()
{
    Base* b = new Base();
    Base* d = new Derived();

    Base* bClone = b->clone(); // 输出: Base cloned.
    Base* dClone = d->clone(); // 输出: Derived cloned.

    delete b;
    delete d;
    delete bClone;
    delete dClone;

    return 0;
}