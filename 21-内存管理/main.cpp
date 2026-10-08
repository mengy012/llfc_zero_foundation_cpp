#include "xunique_ptr.h"

#include <iostream>
#include <utility>
#include <memory>

struct ControlBlock
{
    size_t ref_count_{};

    ControlBlock() : ref_count_{1} {}
};

template <typename T>
class XsharedPtr
{
  public:
    // 默认构造
    XsharedPtr() = default;

    // 参数构造 指针 不允许隐式转换
    explicit XsharedPtr(T* data) : data_{data}
    {
        if (data)
        {
            ctl_ = new ControlBlock;
        }
    }

    // 辅助函数 用于控制计数，当计数归零释放 data_ 和 clt_
    void release()
    {
        if (ctl_)
        {
            ctl_->ref_count_--;

            if (ctl_->ref_count_ == 0)
            {
                delete ctl_;
                delete data_;
            }
        }
        ctl_ = nullptr;
        data_ = nullptr;
    }

    // 拷贝相关
    // 拷贝构造
    XsharedPtr(const XsharedPtr& other) : data_{other.data_}, ctl_{other.ctl_}
    {
        if (ctl_)
        {
            ++ctl_->ref_count_;
        }
    }
    // 拷贝赋值
    XsharedPtr& operator=(const XsharedPtr& other)
    {
        if (this == &other)
        {
            return *this;
        }

        release();

        data_ = other.data_;
        ctl_ = other.ctl_;
        if (ctl_)
        {
            ++ctl_->ref_count_;
        }
        return *this;
    }

    // 移动相关
    // 移动构造
    XsharedPtr(XsharedPtr&& other) : data_{other.data_}, ctl_{other.ctl_}
    {
        other.data_ = nullptr;
        other.ctl_ = nullptr;
    }
    // 移动赋值
    XsharedPtr& operator=(XsharedPtr&& other)
    {
        if (this != &other)
        {
            release();

            data_ = other.data_;
            ctl_ = other.ctl_;

            other.data_ = nullptr;
            other.ctl_ = nullptr;
        }
        return *this;
    }

    // 重载*
    T& operator*() const
    {
        return *data_;
    }

    // 重载->
    T* operator->() const
    {
        return data_;
    }

    // 获取当前引用计数
    size_t use_count() const
    {
        return ctl_ ? ctl_->ref_count_ : 0;
    }
    // 获取裸指针
    T* get() const
    {
        return data_;
    }
    // 重置指针
    void reset(T* data = nullptr)
    {
        if (data)
        {
            release();

            data_ = data;
            ctl_ = new ControlBlock;
        }
        else
        {
            *this = XsharedPtr();
        }
    }

    ~XsharedPtr()
    {
        release();
    }

  private:
    T* data_{nullptr};
    ControlBlock* ctl_{nullptr};
};

// 测试类
class Test
{
  public:
    Test(int val) : value(val)
    {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test()
    {
        std::cout << "Test Destructor: " << value << std::endl;
    }
    void show() const
    {
        std::cout << "Value: " << value << std::endl;
    }

  private:
    int value;
};


int main()
{
    // XsharedPtr<Test> ptr1(new Test(42));
    // ptr1->show();
    // auto p = ptr1.operator->();
    // ptr1.operator->()->show();
    // (*ptr1).show();

    {
        // 创建一个 SimpleUniquePtr
        XuniquePtr<Test> ptr1(new Test(1));
        ptr1->show();
        (*ptr1).show();

        // 移动所有权到 ptr2
        XuniquePtr<Test> ptr2 = std::move(ptr1);
        if (ptr1.get() == nullptr)
        {
            std::cout << "ptr1 is now nullptr after move." << std::endl;
        }
        ptr2->show();

        // 释放所有权
        Test* rawPtr = ptr2.release();
        if (ptr2.get() == nullptr)
        {
            std::cout << "ptr2 is now nullptr after release." << std::endl;
        }
        rawPtr->show();
        delete rawPtr; // 手动删除

        // 使用 reset
        ptr2.reset(new Test(2));
        ptr2->show();

        ptr2.reset(); // 自动删除
        if (ptr2.get() == nullptr)
        {
            std::cout << "ptr2 is now nullptr after reset." << std::endl;
        }
    }
}