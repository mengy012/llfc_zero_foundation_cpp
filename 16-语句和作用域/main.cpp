#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <cstdint>

std::vector<uint64_t> fib(int count)
{
    if (count <= 0)
    {
        return std::vector<uint64_t>{};
    }

    if (count == 1)
    {
        return std::vector<uint64_t>{0};
    }

    std::vector<uint64_t> result{0, 1};
    for (int i = 0; i + 2 < count; ++i)
    {
        result.push_back(result[i] + result[i + 1]);
    }
    return result;
}

int main()
{
    uint64_t value{};
    uint64_t i{};
    for (const auto& v : fib(1000))
    {
        ++i;
        if (value > v)
        {
            std::cout << "i: " << i << std::endl;
            break;
        }
        value = v;
        std::cout << v << ' ';
    }
}
