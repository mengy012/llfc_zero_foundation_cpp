#include "rsync_log.h"
#include <iostream>
#include <random>

int main()
{

    auto seed = std::random_device{}();
    auto rd = std::mt19937_64(seed);
    auto dis = std::uniform_real_distribution(.0, 1.);
    for (int i = 0; i < 100; ++i)
    {

        auto result = dis(rd);

        if (result < 0.3)
        {
            DEBUG("test {}", 1);
        }
        else if (result < 0.9)
        {
            INFO("test {}", 2);
        }
        else
        {
            ERROR("test {}", 3);
        }
    }
}