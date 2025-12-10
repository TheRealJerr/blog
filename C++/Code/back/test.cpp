#include <iostream>

#include <mutex>


constexpr void function(int a)
{
    std::cout << "a = " << a << std::endl;
}

int main()
{
    std::recursive_mutex mtx;

    function(10);


    return 0;
}