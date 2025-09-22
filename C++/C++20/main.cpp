#include <iostream>
#include <vector>
#include <spdlog/spdlog.h>
#include <thread>
#include <functional>
#include <chrono>


enum { END_SIZE = 100 };

void func(int i)
{
    for(int j = 0;j < END_SIZE;j++)
        spdlog::info("thread {}: {}", i, j);
    
    
}


int main()
{
    
    return 0;
}