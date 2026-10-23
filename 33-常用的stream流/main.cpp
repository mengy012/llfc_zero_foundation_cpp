#include <iostream>
#include <format>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <numeric>
#include <map>

int main()
{
    {
        int age = 25;
        std::cout << "Hello, World!" << std::endl;
        std::cout << "I am " << age << " years old." << std::endl;
    }
    {
        std::cout << std::format("{{ hellowrld }}{}", "test") << std::endl;
    }

    {
        double value = 12345678.0;
        std::cout << value << std::endl;
        std::cout << std::fixed << std::setprecision(4);
        std::cout << value << std::endl;
        std::cout << std::defaultfloat << std::setprecision(4);
        std::cout << value << std::endl;

        double pi = 3.141592653589793;
        int num = 42;

        // 设置浮点数的显示精度
        std::cout << "Pi with default precision: " << pi << std::endl;
        std::cout << "Pi with 4 decimal places: " << std::fixed << std::setprecision(4) << pi << std::endl;

        // 设置字段宽度和对齐方式
        std::cout << std::setfill('*');
        std::cout << "Number with width 5: |" << std::setw(5) << num << "|" << std::endl;
        std::cout << "Number with width 5 (left aligned): |" << std::left << std::setw(5) << num << "|" << std::endl;
    }

    {
        // 创建一个ofstream对象，并打开文件 "output.txt"
        std::ofstream outfile("output.txt", std::ios::binary);

        // 检查文件是否成功打开
        if (!outfile)
        {
            std::cerr << "无法打开文件进行写入。" << std::endl;
            return 1;
        }

        // 向文件中写入数据
        outfile << "这是第一行。\n";
        outfile << "这是第二行，数字：" << 100 << std::endl;
        outfile << "浮点数：" << 3.14159 << std::endl;

        // 关闭文件
        // outfile.close();
        outfile = std::ofstream("1.txt", std::ios::binary);
        outfile << "这是第一行。\n";
        outfile << "这是第二行，数字：" << 100 << std::endl;
        outfile << "浮点数：" << 3.14159 << std::endl;

        std::cout << "数据已成功写入 output.txt 文件。" << std::endl;
    }
    {
        // 创建一个ifstream对象，并打开文件 "output.txt"
        std::ifstream infile("output.txt");

        // 检查文件是否成功打开
        if (!infile)
        {
            std::cerr << "无法打开文件进行读取。" << std::endl;
            return 1;
        }

        std::string line;

        int loop_count{};
        // 逐行读取文件内容
        while (std::getline(infile, line))
        {
            std::cout << line << std::endl;
            ++loop_count;
        }

        std::cout << loop_count << std::endl;
        // 关闭文件
        infile.close();
    }

    {
        // 创建一个 fstream 对象，并以读写模式打开文件 "data.txt"
        std::fstream file("data.txt", std::ios::in | std::ios::out | std::ios::app);

        // 检查文件是否成功打开
        if (!file)
        {
            std::cerr << "无法打开文件进行读写。" << std::endl;
            return 1;
        }

        // 向文件追加新内容
        // file << "追加的一行内容。\n";

        // 将文件指针移动到文件开头以读取内容
        file.seekg(0, std::ios::beg);

        std::string line;

        std::cout << "文件内容如下：" << std::endl;

        // 读取文件内容并输出
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }

        // 关闭文件
        file.close();
    }

    {
        int id = 101;
        std::string name = "Alice";
        double score = 95.5;

        std::stringstream ss;
        ss << "ID: " << id << ", Name: " << name << ", Score: " << score;

        std::string result = ss.str();
        std::cout << result << std::endl;
    }
    {
        std::string data = "2023 JohnDoe 85.6";
        int year;
        std::string name;
        double grade;

        std::stringstream ss(data);
        ss >> year >> name >> grade;

        std::cout << "Year: " << year << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Grade: " << grade << std::endl;
    }

    { // 字符串转换为整数和浮点数
        std::string numStr = "12345";
        std::string floatStr = "98.76";
        int number;
        double decimal;

        std::stringstream ss1(numStr);
        ss1 >> number;

        std::stringstream ss2(floatStr);
        ss2 >> decimal;

        std::cout << "字符串 \"" << numStr << "\" 转换为整数：" << number << std::endl;
        std::cout << "字符串 \"" << floatStr << "\" 转换为浮点数：" << decimal << std::endl;

        // 数字转换为字符串
        int num = 6789;
        double dec = 12.34;
        std::stringstream ss3;
        ss3 << num << " and " << dec;

        std::string combinedStr = ss3.str();
        std::cout << "数字转换为字符串：" << combinedStr << std::endl;
    }

    {
        // 使用 std::istringstream 读取数据
        std::string input = "2023 Bob 75.5";
        int year;
        std::string name;
        double score;

        std::istringstream iss(input);
        iss >> year >> name >> score;

        std::cout << "Parsed Data:" << std::endl;
        std::cout << "Year: " << year << ", Name: " << name << ", Score: " << score << std::endl;

        // 使用 std::ostringstream 构建字符串
        std::ostringstream oss;
        oss << "Year: " << year << ", Name: " << name << ", Score: " << score;

        std::string output = oss.str();
        std::cout << "Formatted String: " << output << std::endl;
    }
    {
        std::string csvData = "John,25,80.5";
        std::string name;
        int age;
        double score;

        std::stringstream ss(csvData);
        std::getline(ss, name, ','); // 使用逗号作为分隔符
        ss >> age;
        ss.ignore(1); // 忽略逗号
        ss >> score;

        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Score: " << score << std::endl;

        ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        static_assert(sizeof(long) == 8);
    }

    {
        std::ifstream infile("output.txt");
        if (!infile)
        {
            std::cerr << "无法打开文件。" << std::endl;
            return 1;
        }

        std::string word;
        std::cout << "逐词读取文件内容：" << std::endl;
        while (infile >> word)
        {
            std::cout << word << std::endl;
        }

        infile.close();
    }
    {
        // 以二进制模式写入数据
        std::ofstream outfile("binary.dat", std::ios::binary);
        if (!outfile)
        {
            std::cerr << "无法打开二进制文件。" << std::endl;
            return 1;
        }

        int number = 12345;
        outfile.write(reinterpret_cast<char*>(&number), sizeof(number));
        outfile.close();

        // 以二进制模式读取数据
        std::ifstream infile("binary.dat", std::ios::binary);
        if (!infile)
        {
            std::cerr << "无法打开二进制文件进行读取。" << std::endl;
            return 1;
        }

        int readNumber;
        infile.read(reinterpret_cast<char*>(&readNumber), sizeof(readNumber));
        std::cout << "读取的数字是：" << readNumber << std::endl;

        infile.close();
    }
    {
        std::ifstream infile("input.txt");
        if (!infile)
        {
            std::cerr << "无法打开 input.txt 进行读取。" << std::endl;
            return 1;
        }

        std::map<std::string, int> wordCount;
        std::string word;

        // 逐词读取并统计
        while (infile >> word)
        {
            // 可以添加更多的处理，如去除标点符号、转换为小写等
            wordCount[word]++;
        }

        infile.close();

        std::ofstream outfile("word_count.txt");
        if (!outfile)
        {
            std::cerr << "无法打开 word_count.txt 进行写入。" << std::endl;
            return 1;
        }

        // 写入统计结果
        for (const auto& pair : wordCount)
        {
            outfile << pair.first << ": " << pair.second << std::endl;
        }

        outfile.close();

        std::cout << "单词统计已完成，结果保存在 word_count.txt 中。" << std::endl;
    }

    {
        std::string data("apple banana carrot 1 2 3 apple apple");
        std::stringstream ss(data);
    }
}