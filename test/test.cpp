// 尝试学习一下类型萃取
#include <iostream>
#include <type_traits>

// 测试基本的类型检测
template <class T>
void test1(T val)
{
    if constexpr (std::is_integral<T>::value)
        std::cout << "int" << std::endl;
    else if constexpr(std::is_floating_point<T>::value)
        std::cout << "float" << std::endl;
    else 
        std::cout << "Unkown type" << std::endl;
}

auto main() -> int
{
    test1(1);
    test1(1.1);
    test1("string");
    
    return 0;
}

