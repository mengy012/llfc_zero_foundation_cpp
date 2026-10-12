#include "simple_sharedptr.hpp"
#include <iostream>
#include <vector>

void thread_func_copy(XsharedPtr<Test> sptr, int thread_id)
{
    std::cout << "Thread " << thread_id << " is copying shared_ptr." << std::endl;
    XsharedPtr<Test> local_sptr = sptr;
    std::cout << "Thread " << thread_id << " copied shared_ptr, use_count = " << local_sptr.use_count() << std::endl;
    local_sptr->show();
}

void thread_func_reset(XsharedPtr<Test>& sptr, int new_val, int thread_id)
{
    std::cout << "Thread " << thread_id << " is resetting shared_ptr." << std::endl;
    sptr.reset(new Test(new_val));
    std::cout << "Thread " << thread_id << " reset shared_ptr, use_count = " << sptr.use_count() << std::endl;
    sptr->show();
}

int main()
{
    std::cout << "Creating XsharedPtr with Test(100)." << std::endl;
    XsharedPtr<Test> sptr(new Test(100));
    std::cout << "Initial use_count: " << sptr.use_count() << std::endl;

    // 创建多个线程进行拷贝操作
    const int num_threads = 5;
    std::vector<std::thread> threads_copy;

    for (int i = 0; i < num_threads; ++i)
    {
        threads_copy.emplace_back(thread_func_copy, sptr, i);
    }

    for (auto& t : threads_copy)
    {
        t.join();
    }

    std::cout << "After copy threads, use_count: " << sptr.use_count() << std::endl;

    // 创建多个线程进行 reset 操作
    std::vector<std::thread> threads_reset;

    for (int i = 0; i < num_threads; ++i)
    {
        threads_reset.emplace_back(thread_func_reset, std::ref(sptr), 200 + i, i);
    }

    for (auto& t : threads_reset)
    {
        t.join();
    }

    std::cout << "After reset threads, final use_count: " << sptr.use_count() << std::endl;

    std::cout << "Exiting main." << std::endl;
}