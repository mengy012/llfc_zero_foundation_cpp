#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>




/* 
当前状态：各线程操作各自实例时，引用计数安全；各线程同时修改同一实例时，不安全；被管理对象的数据也需要单独同步
不太完美

 */




struct ControlBlock
{
    std::atomic<size_t> ref_count_{};

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

        {

            if (ctl_ && (ctl_->ref_count_.fetch_sub(1, std::memory_order_acq_rel) == 1))
            {
                delete ctl_;
                delete data_;
            }
            ctl_ = nullptr;
            data_ = nullptr;
        }
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
        std::lock_guard<std::mutex> lock(mtx);
        return *data_;
    }

    // 重载->
    T* operator->() const
    {
        std::lock_guard<std::mutex> lock(mtx);
        return data_;
    }

    // 获取当前引用计数
    size_t use_count() const
    {
        std::lock_guard<std::mutex> lock(mtx);
        return ctl_ ? ctl_->ref_count_.load() : 0;
    }
    // 获取裸指针
    T* get() const
    {
        std::lock_guard<std::mutex> lock(mtx);
        return data_;
    }
    // 重置指针
    void reset(T* data = nullptr)
    {
        std::lock_guard<std::mutex> lock(mtx);
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
    mutable std::mutex mtx;

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
