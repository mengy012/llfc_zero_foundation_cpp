#pragma once

// 实现简单的unique ptr
template <typename T>
class XuniquePtr
{
  public:
    // 删除拷贝构造，拷贝赋值
    XuniquePtr(const XuniquePtr&) = delete;
    XuniquePtr& operator=(const XuniquePtr&) = delete;

    // 构造函数
    // 默认构造
    XuniquePtr() {}

    // 参数构造 指针 不允许隐式构造
    explicit XuniquePtr(T* data) : data_{data} {}

    // 移动构造
    XuniquePtr(XuniquePtr&& other) noexcept : data_{other.data_}
    {
        other.data_ = nullptr;
    }
    // 移动赋值
    XuniquePtr& operator=(XuniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete data_;

            data_ = other.data_;

            other.data_ = nullptr;
        }
        return *this;
    }

    // 辅助函数get,内部所有 解引用 操作 指向资源的指针 都必须使用该函数
    T* get() const
    {
        return data_ ? data_ : nullptr;
    }

    // 重载 (*p)
    T& operator*() const
    {
        return *get();
    }
    // 重载 (p->)
    T* operator->() const
    {
        return get();
    }

    // 释放所有权
    T* release()
    {
        T* tmp = get();
        data_ = nullptr;
        return tmp;
    }
    // 重新设定指针
    void reset(T* data = nullptr)
    {
        delete data_;
        data_ = data;
    }
    // 析构函数
    ~XuniquePtr()
    {
        delete data_;
    }

  private:
    // 指向资源的指针
    T* data_{nullptr};
};

