#pragma once

#include <atomic>
#include <cstddef>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <utility>

// 教学实现：单对象、默认 delete，不支持数组、weak_ptr 或自定义删除器。
// 1. instance_mutex_ 保护某个智能指针实例的控制块指针。
// 2. ControlBlock::object_mutex 由所有副本共享，保护被管理对象。
// 3. Access 持有一份引用和对象锁，保证访问期间对象不会销毁。
// 智能指针实例本身的析构不能与对该实例的访问并发。
template <typename T>
class ThreadSafeSharedPtr
{
    struct ControlBlock
    {
        explicit ControlBlock(T* value) : data(value) {}

        std::atomic<std::size_t> count{1};
        std::mutex object_mutex;
        T* data;
    };

    static void retain(ControlBlock* block) noexcept
    {
        if (block) block->count.fetch_add(1, std::memory_order_relaxed);
    }

    static void release_ref(ControlBlock* block) noexcept
    {
        if (block && block->count.fetch_sub(1, std::memory_order_acq_rel) == 1)
        {
            // 调用用户析构函数时不持有实例锁或对象锁。
            delete block->data;
            delete block;
        }
    }

    ControlBlock* acquire_snapshot() const
    {
        std::lock_guard<std::mutex> lock(instance_mutex_);
        retain(block_); // 必须在实例锁内增加引用，避免 reset 提前释放控制块。
        return block_;
    }

  public:
    class Access
    {
        friend class ThreadSafeSharedPtr;

        explicit Access(ControlBlock* block) : block_(block)
        {
            if (!block_) throw std::logic_error("access to empty ThreadSafeSharedPtr");
            try
            {
                lock_ = std::unique_lock<std::mutex>(block_->object_mutex);
            }
            catch (...)
            {
                release_ref(block_);
                throw;
            }
        }

      public:
        Access(const Access&) = delete;
        Access& operator=(const Access&) = delete;
        Access(Access&&) = delete;
        Access& operator=(Access&&) = delete;

        ~Access()
        {
            lock_.unlock();
            release_ref(block_);
        }

        T* operator->() const noexcept
        {
            return block_->data;
        }
        T& operator*() const noexcept
        {
            return *block_->data;
        }

      private:
        ControlBlock* block_;
        std::unique_lock<std::mutex> lock_;
    };

    ThreadSafeSharedPtr() = default;

    // 接管一个独占的 new T 指针；不能重复接管已被管理的裸指针。
    explicit ThreadSafeSharedPtr(T* data)
    {
        std::unique_ptr<T> owner(data);
        if (data) block_ = new ControlBlock(data);
        owner.release(); // 控制块分配失败时，owner 自动删除 data。
    }

    ThreadSafeSharedPtr(const ThreadSafeSharedPtr& other) : block_(other.acquire_snapshot()) {}

    ThreadSafeSharedPtr(ThreadSafeSharedPtr&& other)
    {
        std::lock_guard<std::mutex> lock(other.instance_mutex_);
        block_ = std::exchange(other.block_, nullptr);
    }

    ThreadSafeSharedPtr& operator=(const ThreadSafeSharedPtr& other)
    {
        if (this != &other)
        {
            ThreadSafeSharedPtr temporary(other);
            swap(temporary);
        } // temporary 在锁外释放旧对象。
        return *this;
    }

    ThreadSafeSharedPtr& operator=(ThreadSafeSharedPtr&& other)
    {
        if (this != &other)
        {
            ControlBlock* old;
            {
                std::scoped_lock lock(instance_mutex_, other.instance_mutex_);
                old = block_;
                block_ = std::exchange(other.block_, nullptr);
            }
            release_ref(old);
        }
        return *this;
    }

    void swap(ThreadSafeSharedPtr& other)
    {
        if (this == &other) return;
        std::scoped_lock lock(instance_mutex_, other.instance_mutex_);
        std::swap(block_, other.block_);
    }

    void reset(T* data = nullptr)
    {
        ThreadSafeSharedPtr temporary(data);
        swap(temporary); // 先分配再替换：分配失败保留原对象。
    }

    std::size_t use_count() const
    {
        std::lock_guard<std::mutex> lock(instance_mutex_);
        return block_ ? block_->count.load(std::memory_order_relaxed) : 0;
    }

    explicit operator bool() const
    {
        std::lock_guard<std::mutex> lock(instance_mutex_);
        return block_ != nullptr;
    }

    // auto access = ptr.lock(); access->method(); ++(*access);
    // 多步操作共用同一个 Access，才能保证整个操作期间持锁。
    [[nodiscard]] Access lock() const
    {
        return Access(acquire_snapshot());
    }

    // ptr->method()：临时 Access 存活到完整表达式结束，而非返回裸指针时结束。
    [[nodiscard]] Access operator->() const
    {
        return lock();
    }

    // 不提供直接返回裸指针的 get() 或直接返回 T& 的 operator*()。
    // 通过 Access 得到的指针/引用不能逃逸到 Access 生命周期之外使用。
    // 对象方法返回的引用也遵循同一规则；所有对象读写必须经过 Access。
    // object_mutex 非递归：持有 Access 时，不要再次 lock 同一对象的任一副本。
    // 涉及多个对象时，调用方还需约定一致的对象加锁顺序。
    // bool/use_count 是瞬时快照；先判断非空再访问不能阻止并发 reset。
    // Access 也计入 use_count；若快照为空，lock/operator-> 抛 logic_error。

    ~ThreadSafeSharedPtr()
    {
        release_ref(block_);
    }

  private:
    mutable std::mutex instance_mutex_;
    ControlBlock* block_{nullptr};
};
