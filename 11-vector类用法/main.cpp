#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <execution>

// 定义学生结构体
struct Student
{
    int id;
    std::string name;
    float grade;
};

int main()
{
    // {
    //     // 默认初始化
    //     std::vector<int> vec1;

    //     // 指定大小和默认值
    //     std::vector<int> vec2(5, 10);

    //     // 使用初始化列表
    //     std::vector<int> vec3 = {1, 2, 3, 4, 5};

    //     // 拷贝构造
    //     std::vector<int> vec4(vec3);

    //     // 移动构造
    //     std::vector<int> vec5(std::move(vec4));

    //     // 输出vec2
    //     std::cout << "vec2: ";
    //     for (auto num : vec2)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;

    //     // 输出vec3
    //     std::cout << "vec3: ";
    //     for (auto num : vec3)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;

    //     // 输出vec5
    //     std::cout << "vec5: ";
    //     for (auto num : vec5)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // {

    //     std::vector<int> vec = {1, 2, 3};

    //     std::cout << "Size: " << vec.size() << std::endl;         // 输出: 3
    //     std::cout << "Capacity: " << vec.capacity() << std::endl; // 输出: 3（或更大，取决于实现）

    //     std::cout << "Is empty? " << (vec.empty() ? "Yes" : "No") << std::endl; // 输出: No

    //     vec.reserve(10);                                                             // 预留容量
    //     std::cout << "After reserve(10), Capacity: " << vec.capacity() << std::endl; // 输出: 10

    //     vec.shrink_to_fit();                                                             // 收缩到适合大小
    //     std::cout << "After shrink_to_fit(), Capacity: " << vec.capacity() << std::endl; // 输出: 3
    // }

    // {
    //     std::vector<int> vec;

    //     // 使用push_back添加元素
    //     vec.push_back(10);
    //     vec.push_back(20);
    //     vec.push_back(30);

    //     std::cout << "After push_back: ";
    //     for (auto num : vec)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl; // 输出: 10 20 30

    //     // 使用pop_back移除最后一个元素
    //     vec.pop_back();

    //     std::cout << "After pop_back: ";
    //     for (auto num : vec)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl; // 输出: 10 20

    //     // 在第二个位置插入25
    //     vec.insert(vec.begin() + 1, 25);

    //     std::cout << "After insert: ";
    //     for (auto num : vec)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl; // 输出: 10 25 20

    //     // 删除第二个元素（25）
    //     vec.erase(vec.begin() + 1);

    //     std::cout << "After erase: ";
    //     for (auto num : vec)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl; // 输出: 10 20

    //     // 清空向量
    //     vec.clear();
    //     std::cout << "After clear, size: " << vec.size() << std::endl; // 输出: 0
    // }

    // {
    //     std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};

    //     // 使用operator[]访问元素
    //     std::cout << "First fruit: " << fruits[0] << std::endl; // 输出: Apple

    //     // 使用at()访问元素
    //     try
    //     {
    //         std::cout << "Second fruit: " << fruits.at(1) << std::endl;  // 输出: Banana
    //         std::cout << "Invalid fruit: " << fruits.at(5) << std::endl; // 抛出异常
    //     }
    //     catch (const std::out_of_range& e)
    //     {
    //         std::cerr << "Exception: " << e.what() << std::endl;
    //     }

    //     // 使用front()和back()
    //     std::cout << "Front: " << fruits.front() << std::endl; // 输出: Apple
    //     std::cout << "Back: " << fruits.back() << std::endl;   // 输出: Cherry
    // }
    // {
    //     std::vector<int> numbers = {1, 2, 3, 4, 5};

    //     // 使用范围 for 循环
    //     std::cout << "Using range-based for loop: ";
    //     for (auto num : numbers)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;

    //     // 使用传统 for 循环
    //     std::cout << "Using traditional for loop: ";
    //     for (size_t i = 0; i < numbers.size(); ++i)
    //     {
    //         std::cout << numbers[i] << " ";
    //     }
    //     std::cout << std::endl;

    //     // 使用迭代器
    //     std::cout << "Using iterators: ";
    //     for (auto it = numbers.begin(); it != numbers.end(); ++it)
    //     {
    //         std::cout << *it << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // {
    //     std::vector<int> vec = {10, 20, 30, 40, 50};

    //     // 通过索引修改元素
    //     vec[2] = 35;

    //     // 使用 at() 修改元素
    //     vec.at(4) = 55;

    //     // 使用迭代器修改元素
    //     for (auto it = vec.begin(); it != vec.end(); ++it)
    //     {
    //         if (*it == 20)
    //         {
    //             *it = 25;
    //         }
    //     }

    //     // 输出修改后的向量
    //     std::cout << "Modified vector: ";
    //     for (auto num : vec)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl; // 输出: 10 25 35 40 55
    // }

    // {
    //     // 定义一个3x4的二维向量，初始化为0
    //     std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));

    //     // 填充矩阵
    //     for (int i = 0; i < 3; ++i)
    //     {
    //         for (int j = 0; j < 4; ++j)
    //         {
    //             matrix[i][j] = i * 4 + j + 1;
    //         }
    //     }

    //     // 输出矩阵
    //     std::cout << "Matrix:" << std::endl;
    //     for (auto row : matrix)
    //     {
    //         for (auto elem : row)
    //         {
    //             std::cout << elem << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    // }

    // {
    //     // 定义一个学生向量
    //     std::vector<Student> students;

    //     // 添加学生
    //     students.push_back({1001, "Alice", 89.5});
    //     students.push_back({1002, "Bob", 92.0});
    //     students.push_back({1003, "Charlie", 85.0});

    //     // 遍历并输出学生信息
    //     for (const auto& student : students)
    //     {
    //         std::cout << "ID: " << student.id << ", Name: " << student.name << ", Grade: " << student.grade << std::endl;
    //     }
    // }
    // {
    //     std::vector<int> vec = {10, 20, 30, 40, 50};

    //     // 使用迭代器遍历并修改元素
    //     for (auto it = vec.begin(); it != vec.end(); ++it)
    //     {
    //         *it += 5;
    //     }

    //     // 输出修改后的向量
    //     std::cout << "After modifying: ";
    //     for (auto it = vec.begin(); it != vec.end(); ++it)
    //     {
    //         std::cout << *it << " ";
    //     }
    //     std::cout << std::endl; // 输出: 15 25 35 45 55
    // }

    // {
    //     std::vector<int> numbers = {50, 20, 40, 10, 30};

    //     // 排序前
    //     std::cout << "Before sorting: ";
    //     for (auto num : numbers)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;

    //     // 使用sort()排序
    //     // std::sort(numbers.begin(), numbers.end());
    //     std::sort(std::execution::par_unseq, numbers.begin(), numbers.end(), std::less{});

    //     // 排序后
    //     std::cout << "After sorting: ";
    //     for (auto num : numbers)
    //     {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // {
    //     std::vector<char> letters = {'A', 'B', 'C', 'D', 'E'};

    //     std::cout << "Before reversing: ";
    //     for (auto c : letters)
    //     {
    //         std::cout << c << " ";
    //     }
    //     std::cout << std::endl;

    //     // 反转向量
    //     std::reverse(letters.begin(), letters.end());

    //     std::cout << "After reversing: ";
    //     for (auto c : letters)
    //     {
    //         std::cout << c << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // {
    //     std::vector<std::string> fruits = {"Apple", "Banana", "Cherry", "Date"};
    //     std::string target = "Cherry";

    //     // 使用find()查找元素
    //     auto it = std::find(std::execution::par, fruits.begin(), fruits.end(), target);

    //     if (it != fruits.end())
    //     {
    //         std::cout << target << " found at position " << std::distance(fruits.begin(), it) << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << target << " not found." << std::endl;
    //     }
    // }
    {
        std::vector<int> vec;

        // 预留空间
        vec.reserve(1000);
        std::cout << "Capacity after reserve(1000): " << vec.capacity() << std::endl;

        // 添加元素
        for (int i = 0; i < 1000; ++i)
        {
            vec.push_back(i);
        }

        std::cout << "Size after adding elements: " << vec.size() << std::endl;
        std::cout << "Capacity after adding elements: " << vec.capacity() << std::endl;

        // 删除一半元素
        vec.erase(std::remove_if(vec.begin(), vec.end(), [](int n) { return n > 499; }), vec.end());

        std::cout << "Size after adding elements: " << vec.size() << std::endl;
        std::cout << "Capacity after adding elements: " << vec.capacity() << std::endl;

        // 减少内存占用
        vec.shrink_to_fit();
        
        std::cout << "Size after adding elements: " << vec.size() << std::endl;
        std::cout << "Capacity after adding elements: " << vec.capacity() << std::endl;
    }
}