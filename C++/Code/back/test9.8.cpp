#include <iostream>
#include <type_traits>
#include <vector>
#include <thread>
thread_local int num = 0;
auto main() -> int
{
    auto handler = [](int id) -> void
    {
        for(int i = 0;i < 10;i++)
            std::cout << "thread id : " << id << " " << num++ << std::endl;
    };
    std::vector<std::thread> threads(4);
    int count = 0;
    for(auto& thread : threads)
        thread = std::thread(handler, count++);
    // 进行线程回收
    for(auto& thread : threads)
        if(thread.joinable()) thread.join();
    
    return 0;
}


#include <iostream>

template <class Derive>
class Base
{
public:
    void func()
    {
        static_cast<Derive*>(this)->func();
    }
    
private:    
};

class Derive : public Base<Derive>
{
public:
    void func()
    {
        std::cout << "this is Derive" << std::endl;
    }
};

