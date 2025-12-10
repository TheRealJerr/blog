#include <iostream>

// 检测某个类型是否含有某个接口

template <class T,class ...Args>
class HasFunc
{
public:
    template <class U = T, typename = std::void_t<decltype(std::declval<U>().func(std::declval<Args>()...))>>
    static std::true_type test(int) { return {}; }

    template <class U = T, typename = std::void_t<>>
    static std::false_type test(...) { return {}; }

    static constexpr bool value = decltype(test(0))::value;
};

template <class T,class ...Args>
inline constexpr bool has_func_t = HasFunc<T,Args...>::value;



