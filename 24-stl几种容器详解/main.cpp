// #include <iostream>

// class MyClass
// {
//   public:
//     int a{};
//     int b{};
//     int c{};
// };

// #define MY_OFFSETOF(T, M) (unsigned long long)(&((T*)0)->M)

// int main()
// {
//     std::cout << "hello world" << std::endl;

//     std::cout << MY_OFFSETOF(MyClass, MyClass::b) << std::endl;
// }

// #include <iostream>
// #include <vector>

// int main()
// {
//     // 创建一个空的整数vector
//     std::vector<int> numbers;

//     // 向vector末尾添加元素
//     numbers.push_back(10);
//     numbers.push_back(20);
//     numbers.push_back(30);

//     // 通过索引访问元素
//     std::cout << "第一个元素: " << numbers[0] << std::endl;

//     // 遍历vector
//     std::cout << "所有元素: ";
//     for (auto it = numbers.begin(); it != numbers.end(); ++it)
//     {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;

//     // 删除最后一个元素
//     numbers.pop_back();

//     // 打印删除后的vector
//     std::cout << "删除最后一个元素后: ";
//     for (auto num : numbers)
//     {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }

#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <iterator>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>

template <typename T>
class Node
{
  public:
    Node(const T& data = T()) : data_(data) {}

    T data_;
    Node* prev_{nullptr};
    Node* next_{nullptr};
};

template <typename T>
class List;

template <typename T>
class Iterator
{
  public:
    using self_type = Iterator<T>;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using test = int;

    Iterator(Node<T>* ptr = nullptr) : node_ptr_{ptr} {}

    reference operator*() const
    {
        return node_ptr_->data_;
    }
    pointer operator->() const
    {
        return &(node_ptr_->data_);
    }

    // eg: ++i
    self_type& operator++()
    {
        if (node_ptr_)
        {
            node_ptr_ = node_ptr_->next_;
        }
        return *this;
    }

    // eg: i++
    self_type operator++(int)
    {
        self_type tmp = *this;

        if (node_ptr_)
        {
            node_ptr_ = node_ptr_->next_;
        }
        return tmp;
    }

    // eg: --i
    self_type& operator--()
    {
        if (node_ptr_)
        {
            node_ptr_ = node_ptr_->prev_;
        }
        return *this;
    }

    // eg: i--
    self_type operator--(int)
    {
        self_type tmp = *this;

        if (node_ptr_)
        {
            node_ptr_ = node_ptr_->prev_;
        }
        return tmp;
    }

    bool operator==(const self_type& other) const
    {
        return node_ptr_ == other.node_ptr_;
    }

    bool operator!=(const self_type& other) const
    {
        return node_ptr_ != other.node_ptr_;
    }

  private:
    Node<T>* node_ptr_;

    friend class List<T>;
};

template <typename T>
class List
{
  public:
    using iterator = Iterator<T>;
    // using const_iterator = Iterator<T>;

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    iterator insert(iterator pos, const T& value)
    {
        Node<T>* new_node = new Node<T>();

        Node<T>* current_node = pos.node_ptr_;
        Node<T>* prev_node = pos.node_ptr_->prev_;

        prev_node->next_ = new_node;
        new_node->next_ = current_node;

        current_node->prev_ = new_node;
        new_node->prev_ = prev_node;

        new_node->data_ = value;
        return iterator{new_node};
    }

    // 删除迭代器指向的元素
    iterator erase(iterator pos)
    {
        Node<T>* current_node = pos.node_ptr_;
        if (current_node == head || current_node == tail)
        {
            return pos;
        }

        Node<T>* next_node = current_node->next_;
        std::exchange(current_node->prev_->next_, current_node->next_);
        std::exchange(current_node->next_->prev_, current_node->prev_);

        delete current_node;

        return iterator{next_node};
    }

    iterator begin()
    {
        return iterator{head->next_};
    }
    iterator end()
    {
        return iterator{tail};
    }

    bool empty() const
    {
        return head->next_ == tail;
    }

    // 在头部插入元素
    void push_front(const T& val)
    {
        insert(begin(), val);
    }
    // 在尾部插入元素
    void push_back(const T& val)
    {
        insert(end(), val);
    }

    // 在头部删除元素
    void pop_front()
    {
        if (!empty())
        {
            auto beg = begin();
            erase(beg);
        }
    }

    // 在尾部删除元素
    void pop_back()
    {
        if (!empty())
        {
            auto end = this->end();
            --end;
            erase(end);
        }
    }

    // 清空链表
    void clear()
    {
        if (!empty())
        {
            auto beg = begin();
            auto end = this->end();
            while (beg != end)
            {
                beg = erase(beg);
            }

            head->next_ = tail;
            tail->prev_ = head;
        }
    }

    // 打印链表（辅助函数）
    void print()
    {
        if (!empty())
        {
            auto beg = begin();
            auto end = this->end();
            while (beg != end)
            {
                std::cout << *beg << ' ';
                ++beg;
            }
            std::cout << std::endl;
        }
    }

    // 获取头元素引用
    T& front()
    {
        return head->next_->data_;
    }
    // 获取尾元素引用
    T& back()
    {
        return tail->prev_->data_;
    }

    List()
    {
        head = new Node<T>();
        tail = new Node<T>();
        head->next_ = tail;
        tail->prev_ = head;
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }

  private:
    Node<T>* head;
    Node<T>* tail;
};

int main()
{
    // // 创建一个空的整数list
    // std::list<int> numbers;

    // // 向list末尾添加元素
    // numbers.push_back(100);
    // numbers.push_back(200);
    // numbers.push_back(300);

    // // 向list前端添加元素
    // numbers.push_front(50);

    // // 遍历list
    // std::cout << "所有元素: ";
    // for (auto it = numbers.begin(); it != numbers.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl; // 50 100 200 300

    // // 插入元素
    // auto it = numbers.begin();
    // ++it;                    // 指向第二个元素
    // numbers.insert(it, 150); // 50 150 100 200 300

    // // 打印插入后的list
    // std::cout << "插入元素后: ";
    // for (auto num : numbers)
    // {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    // // 删除元素
    // numbers.remove(200); // 50 150 100  300

    // // 打印删除后的list
    // std::cout << "删除元素后: ";
    // for (auto num : numbers)
    // {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    {
        List<int> lst;

        // 插入元素
        lst.push_back(10);            // 链表: 10
        lst.push_front(5);            // 链表: 5, 10
        lst.push_back(15);            // 链表: 5, 10, 15
        lst.insert(++lst.begin(), 7); // 链表: 5, 7, 10, 15

        // 打印链表
        std::cout << "链表内容: ";
        lst.print(); // 输出: 5 7 10 15

        // 删除元素
        lst.pop_front(); // 链表: 7, 10, 15
        lst.pop_back();  // 链表: 7, 10

        // 打印链表
        std::cout << "删除头尾后链表内容: ";
        lst.print(); // 输出: 7 10

        // 插入和删除
        auto it = lst.begin();
        it = lst.insert(it, 3); // 链表: 3, 7, 10
        lst.erase(++it);        // 链表: 3, 10

        // 打印链表
        std::cout << "插入和删除后链表内容: ";
        lst.print(); // 输出: 3 10

        // 清空链表
        lst.clear();
        std::cout << "清空后，链表是否为空: " << (lst.empty() ? "是" : "否") << std::endl;
    }

    {
        // 创建一个空的deque
        std::deque<std::string> dq;

        // 在末尾添加元素
        dq.push_back("End1");
        dq.push_back("End2");

        // 在前端添加元素
        dq.push_front("Front1");
        dq.push_front("Front2");

        // 遍历deque
        std::cout << "deque中的元素: ";
        for (auto it = dq.begin(); it != dq.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // 访问首尾元素
        std::cout << "首元素: " << dq.front() << std::endl;
        std::cout << "尾元素: " << dq.back() << std::endl;

        // 删除首元素
        dq.pop_front();

        // 删除尾元素
        dq.pop_back();

        // 打印删除后的deque
        std::cout << "删除首尾元素后: ";
        for (auto num : dq)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    {
        // 创建一个空的map，键为string，值为int
        std::map<std::string, int> ageMap;

        // 插入键值对
        ageMap["Alice"] = 30;
        ageMap["Bob"] = 25;
        ageMap["Charlie"] = 35;

        // 查找元素
        std::string name = "Bob";
        if (ageMap.find(name) != ageMap.end())
        {
            std::cout << name << " 的年龄是 " << ageMap[name] << std::endl;
        }
        else
        {
            std::cout << "未找到 " << name << std::endl;
        }

        // 遍历map
        std::cout << "所有人员和年龄: " << std::endl;
        for (auto it = ageMap.begin(); it != ageMap.end(); ++it)
        {
            std::cout << it->first << " : " << it->second << std::endl;
        }

        // 删除元素
        ageMap.erase("Alice");

        // 打印删除后的map
        std::cout << "删除Alice后: " << std::endl;
        for (auto& [key, value] : ageMap)
        {
            std::cout << key << " : " << value << std::endl;
        }
    }
    {
        // 创建一个空的unordered_map，键为string，值为double
        std::unordered_map<std::string, double> priceMap;

        // 插入键值对
        priceMap["Apple"] = 1.2;
        priceMap["Banana"] = 0.5;
        priceMap["Orange"] = 0.8;

        // 查找元素
        std::string fruit = "Banana";
        if (priceMap.find(fruit) != priceMap.end())
        {
            std::cout << fruit << " 的价格是 $" << priceMap[fruit] << std::endl;
        }
        else
        {
            std::cout << "未找到 " << fruit << std::endl;
        }

        // 遍历unordered_map
        std::cout << "所有水果和价格: " << std::endl;
        for (auto& [key, value] : priceMap)
        {
            std::cout << key << " : $" << value << std::endl;
        }

        // 删除元素
        priceMap.erase("Apple");

        // 打印删除后的unordered_map
        std::cout << "删除Apple后: " << std::endl;
        for (auto& [key, value] : priceMap)
        {
            std::cout << key << " : $" << value << std::endl;
        }
    }

    {
        // 创建一个空的整数set
        std::set<int> numbers;

        // 插入元素
        numbers.insert(10);
        numbers.insert(20);
        numbers.insert(30);
        numbers.insert(20); // 重复元素，不会被插入

        // 遍历set
        std::cout << "set中的元素: ";
        for (auto it = numbers.begin(); it != numbers.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // 查找元素
        int key = 20;
        if (numbers.find(key) != numbers.end())
        {
            std::cout << key << " 在set中存在。" << std::endl;
        }
        else
        {
            std::cout << key << " 不在set中。" << std::endl;
        }

        // 删除元素
        numbers.erase(10);

        // 打印删除后的set
        std::cout << "删除10后set中的元素: ";
        for (auto num : numbers)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    {
        // 创建一个空的unordered_set
        std::unordered_set<int> numbers;

        // 插入元素
        numbers.insert(10);
        numbers.insert(20);
        numbers.insert(30);
        numbers.insert(20); // 重复元素，不会被插入

        // 遍历unordered_set
        std::cout << "unordered_set中的元素: ";
        for (auto it = numbers.begin(); it != numbers.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // 查找元素
        int key = 20;
        if (numbers.find(key) != numbers.end())
        {
            std::cout << key << " 在unordered_set中存在。" << std::endl;
        }
        else
        {
            std::cout << key << " 不在unordered_set中。" << std::endl;
        }

        // 删除元素
        numbers.erase(10);

        // 打印删除后的unordered_set
        std::cout << "删除10后unordered_set中的元素: ";
        for (auto num : numbers)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    {
        // 创建一个空的stack，底层使用vector
        std::stack<int> s;

        // 压入元素
        s.push(1);
        s.push(2);
        s.push(3);

        // 访问栈顶元素
        std::cout << "栈顶元素: " << s.top() << std::endl;

        // 弹出元素
        s.pop();
        std::cout << "弹出一个元素后，新的栈顶: " << s.top() << std::endl;

        // 判断栈是否为空
        if (!s.empty())
        {
            std::cout << "栈不为空，元素数量: " << s.size() << std::endl;
        }
    }

    {
        // 创建一个空的queue，底层使用deque
        std::queue<std::string> q;

        // 入队元素
        q.push("First");
        q.push("Second");
        q.push("Third");

        // 访问队首元素
        std::cout << "队首元素: " << q.front() << std::endl;

        // 访问队尾元素
        std::cout << "队尾元素: " << q.back() << std::endl;

        // 出队元素
        q.pop();
        std::cout << "出队后新的队首: " << q.front() << std::endl;

        // 判断队列是否为空
        if (!q.empty())
        {
            std::cout << "队列不为空，元素数量: " << q.size() << std::endl;
        }
    }

    {
        // 创建一个空的priority_queue，默认是最大堆
        std::priority_queue<int> pq;

        // 插入元素
        pq.push(30);
        pq.push(10);
        pq.push(20);
        pq.push(40);

        // 访问堆顶元素
        std::cout << "优先级最高的元素: " << pq.top() << std::endl;

        // 弹出元素
        pq.pop();
        std::cout << "弹出一个元素后，新的堆顶: " << pq.top() << std::endl;

        // 遍历priority_queue（需要复制，因为无法直接遍历）
        std::priority_queue<int> copy = pq;
        std::cout << "剩余的元素: ";
        while (!copy.empty())
        {
            std::cout << copy.top() << " ";
            copy.pop();
        }
        std::cout << std::endl;
    }
    return 0;
}