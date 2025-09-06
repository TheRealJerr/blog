#include <unistd.h>
#include <iostream>
#include <sw/redis++/redis++.h>
#include <set>
#include <thread>
// Redis-plus-plus的作者, 可以直接展开这个命名空间
using namespace sw;

void handler(int num)
{
    for(int i = 0;i < num;i++)
        std::cout << i << std::endl;
}
auto main() -> int
{
    sw::redis::Redis redis_client("tcp://localhost:6379");
    std::thread(handler, 5).join();
    std::cout << std::this_thread::get_id()
    return 0;    
}