#include "my_deque.h"

#include <iostream>

int main()
{
    {
        Deque<std::string> dq;

        // 在后面插入元素
        dq.push_back("Apple");
        dq.push_back("Banana");
        dq.push_back("Cherry");

        // 在前面插入元素
        dq.push_front("Date");
        dq.push_front("Elderberry");

        // 显示队列大小
        std::cout << "Deque 大小: " << dq.size() << std::endl;

        // 使用迭代器进行遍历
        std::cout << "Deque 元素: ";
        for (auto it = dq.begin(); it != dq.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // 访问前端和后端元素
        std::cout << "前端元素: " << dq.front() << std::endl;
        std::cout << "后端元素: " << dq.back() << std::endl;

        // 删除元素
        dq.pop_front();
        dq.pop_back();

        // 再次遍历
        std::cout << "删除元素后的 Deque: ";
        for (auto it = dq.begin(); it != dq.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}