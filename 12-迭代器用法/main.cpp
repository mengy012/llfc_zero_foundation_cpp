#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // {
    //     std::string s("some string");
    //     // 确保s非空
    //     if (s.begin() != s.end())
    //     {
    //         // 第一个字母改为大写
    //         auto it = s.begin();
    //         *it = toupper(*it);
    //     }
    //     std::cout << s << std::endl;
    // }
    // {
    //     // 测试空字符串
    //     std::string s("");
    //     auto it = s.begin();
    //     std::cout << *it << std::endl;

    //     it = s.end();
    //     std::cout << *it << std::endl;
    // }
    // {
    //     std::string s2 = "another string";
    //     for (auto it = s2.begin(); it != s2.end() && !isspace(*it); ++it)
    //     {
    //         *it = toupper(*it);
    //     }
    //     std::cout << s2 << std::endl;
    // }

    // {
    //     // 迭代器it, it能读写vector<int>的元素
    //     std::vector<int>::iterator it;
    //     // it2能读写string对象的字符
    //     std::string::iterator it2;
    //     // it3只能读元素，不能写元素
    //     std::vector<int>::const_iterator it3;
    //     // it4只能读字符,不能写字符
    //     std::string::const_iterator it4;
    // }

    // {
    //     std::vector<int> numbers = {1, 2, 3, 4, 5};

    //     // 使用 const_iterator 遍历
    //     std::vector<int>::const_iterator it;
    //     for (it = numbers.cbegin(); it != numbers.cend(); ++it)
    //     {
    //         std::cout << *it << " "; // 读取元素值
    //     }
    //     std::cout << std::endl;
    // }

    // {
    //     std::vector<int> v;
    //     const std::vector<int> cv;
    //     // it1是 vector<int>的迭代器，
    //     auto it1 = v.begin();
    //     // it2是const vector<int>的迭代器
    //     auto it2 = cv.begin();
    // }

    // {
    //     std::vector<std::string> vs = {"hello", "world"};
    //     for (auto it = vs.begin(); it != vs.end(); ++it)
    //     {
    //         //(*it)解引用获取string对象，再次调用empty()方法判断为空
    //         if ((*it).empty())
    //         {
    //             std::cout << "empty string" << std::endl;
    //         }
    //     }
    // }

    // {
    //     // 依次输出text的每一行直到遇到第一个空行为止
    //     std::vector<std::string> text = {
    //         "hello",
    //         "",
    //         "world",
    //     };
    //     for (auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it)
    //     {
    //         std::cout << *it << std::endl;
    //     }
    // }

    // {
    //     // 注意下面逻辑错误，在for循环中push元素导致死循环
    //     std::vector<int> numbers = {1, 2, 3, 4, 5};
    //     for (auto i = 0; i < numbers.size(); ++i)
    //     {
    //         numbers.push_back(i);
    //     }

    //     // 注意下面逻辑错误，在for循环中push元素导致迭代器失效,也会导致死循环
    //     for (auto it = numbers.begin(); it != numbers.end(); ++it)
    //     {
    //         numbers.push_back(1);
    //     }

    //     // 删除第一个元素
    //     numbers.erase(numbers.begin());
    // }

    // {
    //     // vector容器存储了一系列数字，在循环中遍历每一个元素，并且删除其中的奇数，要求循环结束，vector元素为偶数，要求时间复杂度o(n)
    //     std::vector<int> numbers = {1, 2, 3, 4, 5};

    //     numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 1; }), numbers.end());
    //     for (auto n : numbers)
    //     {
    //         std::cout << n << std::endl;
    //     }
    // }

    // {
    //     std::vector<int> numbers = {1, 2, 3, 4, 5};
    //     // 中间位置的迭代器
    //     auto mid = numbers.begin() + numbers.size() / 2;
    //     // 判断迭代器是否有效
    //     if (mid != numbers.end())
    //     {
    //         std::cout << *mid << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "mid is end" << std::endl;
    //     }
    // }

    // {
    //     std::vector<int> numbers;
    //     for (int i = 1; i <= 100; ++i)
    //     {
    //         numbers.push_back(i);
    //     }
    //     // 使用迭代器运算的一个经典算法是二分搜索。二分搜索从有序序列中寻找某个给定的值。
    //     // 二分搜索从序列中间的位置开始搜索，如果中间位置的元素正好就是要找的元素，搜索完成；
    //     // 如果不是，假如该元素小于要找的元素，则在序列的后半部分继续搜素；
    //     // 假如该元素大于要找的元素，则在序列的前半部分继续搜索。
    //     // 在缩小的范围中计算一个新的中间元素并重复之前的过程，直至最终找到目标或者没有元素可供继续搜索。

    //     auto left{numbers.begin()}, right{numbers.end()};
    //     auto mid{numbers.begin() + numbers.size() / 2};
    //     auto found{numbers.end()};
    //     int target{99};

    //     while (left != right)
    //     {
    //         if (target < *mid)
    //         {
    //             right = mid;
    //             mid = left + (right - left) / 2;
    //         }
    //         else if (target > *mid)
    //         {
    //             left = mid + 1;
    //             mid = left + (right - left) / 2;
    //         }
    //         else
    //         {
    //             found = mid;
    //             break;
    //         }
    //     }

    //     if (found != numbers.end())
    //     {
    //         std::cout << *found << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "no found" << std::endl;
    //     }
    // }

    // {
    //     // 编写一个程序，读取一组整数到一个 std::vector 中，并打印每对相邻元素的和。例如，给定输入 1 2 3 4，输出应为 3 5 7。
    //     std::vector<int> numbers = {1, 2, 3, 4};
    //     std::vector<int> result{};

    //     for (auto it = numbers.begin(); it != numbers.end(); ++it)
    //     {
    //         if ((it + 1) != numbers.end())
    //         {
    //             result.push_back(*it + *(it + 1));
    //         }
    //     }

    //     for (auto n : result)
    //     {
    //         std::cout << n << std::endl;
    //     }
    // }

    // {
    //     //  编写一个程序，从用户输入一组整数到一个 std::vector 中，然后使用迭代器反向打印这些元素。

    //     std::vector<int> numbers{};
    //     for (int i = 0; i < 10; ++i)
    //     {
    //         numbers.push_back(i);
    //     }

    //     for (auto rit = numbers.rbegin(); rit != numbers.rend(); ++rit)
    //         std::cout << *rit << std::endl;
    // }

    {
        // 编写一个程序，创建两个 std::vector，从用户输入填充它们。使用迭代器将这两个 vector 合并为一个新 vector。
        std::vector<int> vec1{1, 3, 5, 7, 9};
        std::vector<int> vec2{2, 4, 6, 8, 10, 11, 12, 999, 1111};

        std::vector<int> result{};

        for (auto it1 = vec1.begin(), it2 = vec2.begin(); it1 != vec1.end() || it2 != vec2.end();)
        {
            if (it1 != vec1.end())
            {
                result.push_back(*it1);
                ++it1;
            }

            if (it2 != vec2.end())
            {
                result.push_back(*it2);
                ++it2;
            }
        }
        for (auto n : result)
        {
            std::cout << n << std::endl;
        }
    }

    {
        std::vector<int> data1 = {1, 2, 3, 4};
        std::vector<int> data2 = {9, 10, 8};

        {
            std::vector<int> result;
            result.insert(result.begin(), data1.begin(), data1.end());
            result.insert(result.begin() + data1.size(), data2.begin(), data2.end());

            for (const auto& it : result)
            {
                std::cout << it << " ";
            }
        }
    }
}