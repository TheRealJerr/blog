// 通过模版实现特化
#include <iostream>
#include <type_traits>

// 判断某个类是否含有Append这个接口

template <class T,typename = void>
class has_append_func : public std::false_type {};

// 偏特化检测
template <class T>
class has_append_func<T,std::void_t<decltype(std::declval<T>().append())>> : public std::true_type {};

//
template <class T>
inline constexpr bool has_append_func_t = has_append_func<T>::value;


 


class Tmp
{
public:
    void append() {};
};
void test()
{
    if constexpr(has_append_func_t<int>)
        std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;

    if constexpr(has_append_func_t<Tmp>)
        std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;
}

// 更加复杂的设计


#include <utility>

template <class T, class... Args>
class has_size_mem
{
private:
    // 修正：使用统一的模板参数
    template <class U = T>
    static auto check(int) -> decltype(std::declval<U>().size(std::declval<Args>()...), std::true_type{});
    
    template <class U = T>
    static std::false_type check(...);
    
public:
    // 修正：不需要传递模板参数，使用默认参数
    inline static constexpr bool value = decltype(check<T>(0))::value;
};

template <class T, class... Args>
inline constexpr bool has_size_mem_t = has_size_mem<T, Args...>::value;

class Object
{
public:
    void size(int x) {};
};

void test_2()
{
    if constexpr(has_size_mem<Object, int>::value) 
        std::cout << "true" << std::endl;
    else 
        std::cout << "false" << std::endl;
}

int main() {
    test_2();  // 现在会输出 "true"
    return 0;
}