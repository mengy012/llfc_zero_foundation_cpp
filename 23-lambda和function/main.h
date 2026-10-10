#pragma once

// #include <bits/stdc++.h>
// #include <linux/kernel.h>
#include <utility>

void file_info();

int test(int, int);

void show_begin();

template <typename T>
void show_info(const T& val)
{
    std::cout << '\t' << val << std::endl;
}

void show_end();