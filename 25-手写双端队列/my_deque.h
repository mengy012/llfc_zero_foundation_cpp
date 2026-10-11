#pragma once

#include <algorithm>
#include <cstdint>
#include <utility>
#include <exception>
#include <stdexcept>
#include <iterator>

template <typename T>
class Deque
{
  public:
    Deque(size_t initial_capacity = 8) : capacity_{(initial_capacity) ? initial_capacity : 8}
    {
        buffer_ = new T[capacity_];
    }

    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;

    bool empty() const
    {
        return cur_count_ == 0;
    }
    size_t size() const
    {
        return cur_count_;
    }

    // 在前面插入元素
    void push_front(const T& value)
    {
        T saved = value;
        if (cur_count_ == capacity_)
        {
            resize(capacity_ * 2);
        }

        front_idx_ = (front_idx_ == 0) ? capacity_ - 1 : front_idx_ - 1;
        buffer_[front_idx_] = saved;
        ++cur_count_;
    }

    // 在后面插入元素
    void push_back(const T& value)
    {
        T saved = value;
        if (cur_count_ == capacity_)
        {
            resize(capacity_ * 2);
        }

        buffer_[back_idx_] = saved;
        back_idx_ = (back_idx_ + 1) % capacity_;
        ++cur_count_;
    }

    // 从前面删除元素
    void pop_front()
    {
        if (!empty())
        {
            front_idx_ = (front_idx_ + 1) % capacity_;
            --cur_count_;
        }
    }

    // 从后面删除元素
    void pop_back()
    {
        if (!empty())
        {
            back_idx_ = (back_idx_ == 0) ? capacity_ - 1 : back_idx_ - 1;
            --cur_count_;
        }
    }

    // 获取前端元素
    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("Deque is empty");
        }
        return buffer_[front_idx_];
    }

    // 获取后端元素
    T& back()
    {
        if (empty())
        {
            throw std::out_of_range("Deque is empty");
        }
        return buffer_[(back_idx_ == 0) ? capacity_ - 1 : back_idx_ - 1];
    }

    class Iterator
    {
      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Deque<T>* deque_ptr, size_t pos) : deque_ptr_{deque_ptr}, pos_{pos} {}

        // 解引用操作
        reference operator*() const
        {
            size_t real_index = (deque_ptr_->front_idx_ + pos_) % deque_ptr_->capacity_;
            return deque_ptr_->buffer_[real_index];
        }

        pointer operator->()
        {
            return &operator*();
        }

        // 前置递增 ++i
        Iterator& operator++()
        {
            ++pos_;
            return *this;
        }

        // i++
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++pos_;
            return tmp;
        }

        // --i
        Iterator& operator--()
        {
            --pos_;
            return *this;
        }
        // i--
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --pos_;
            return tmp;
        }

        // 比较操作
        bool operator==(const Iterator& other) const
        {
            return (deque_ptr_ == other.deque_ptr_) && (pos_ == other.pos_);
        }

        bool operator!=(const Iterator& other) const
        {
            return !operator==(other);
        }

      private:
        Deque<T>* deque_ptr_;
        // size_t index_;
        size_t pos_;
    };

    Iterator begin()
    {
        return {this, 0};
    }
    Iterator end()
    {
        return {this, cur_count_};
    }

    ~Deque()
    {
        delete[] buffer_;
    }

  private:
    T* buffer_{nullptr};
    size_t capacity_{};
    size_t front_idx_{};
    size_t back_idx_{};
    size_t cur_count_{};

    void resize(size_t new_capacity)
    {
        T* new_buffer = new T[new_capacity];

        for (size_t i = 0; i < cur_count_; ++i)
        {
            new_buffer[i] = buffer_[(front_idx_ + i) % capacity_];
        }

        delete[] buffer_;

        buffer_ = new_buffer;
        capacity_ = new_capacity;
        front_idx_ = 0;
        back_idx_ = cur_count_;
    }
};
