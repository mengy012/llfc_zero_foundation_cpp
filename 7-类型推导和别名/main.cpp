#include <iostream>
#include <cstdint>

int main()
{
    int i{0};
    int& ri = i;
    auto ai = ri;
    decltype(ri) rri = ri;

    const int* const cpc = &i;
    auto ap = cpc;
    decltype(cpc) dp = cpc;

    {
        int* ip = &i;
        int& ri = *ip;
        std::cout << (uint64_t)ip << std::endl;
        std::cout << (uint64_t)&ri << std::endl;
    }
    {
        // decltype的结果可以是引用各类型
        int i = 42, *p = &i, &r = i;
        // 正确，假发的结果是int，因此b是一个未初始化的int
        decltype(r + 0) b;
        // 错误，c是int&，必须初始化
        //  decltype(*p) c;
    }
    {
        int i{};
        // decltype((i)) a;
    }
}