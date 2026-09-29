#include <iostream>
#include <vector>
#include <string>

// 定义一个基类 Vehicle，包含以下内容：

// ● 公共成员函数：
//   ○ 构造函数：输出 "Vehicle constructed."
//   ○ 析构函数：输出 "Vehicle destructed."

class Vehicle
{
  public:
    Vehicle()
    {
        std::cout << "Vehicle constructed" << std::endl;
    }

    ~Vehicle()
    {
        std::cout << "Vehicle destructed" << std::endl;
    }
};

// 然后，定义一个派生类 Car，继承自 Vehicle，并添加以下内容：
class Car : public Vehicle
{
  public:
    Car()
    {
        std::cout << "Car constructed." << std::endl;
    }
    ~Car()
    {
        std::cout << "Car destructed." << std::endl;
    }
};
// ● 公共成员函数：
//   ○ 构造函数：输出 "Car constructed."
//   ○ 析构函数：输出 "Car destructed."

// 要求：

// ● 在 main 函数中，创建一个 Car 对象，并观察构造和析构的调用顺序。

int main()
{
    Car car;
}