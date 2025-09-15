#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include <boost/regex.hpp>

// 判断一个vector<string>中符合正则表达式的元素集合
std::vector<std::string> filter_by_regex(const std::vector<std::string>& vec, const std::string& regex_str)
{
    std::vector<std::string> result;
    boost::regex regex(regex_str);
    for (const auto& str : vec)
    {
        if (boost::regex_match(str, regex))
        {
            result.push_back(str);
        }
    }
    return result;
}
auto main() -> int 
{
    std::vector<std::string> vec = {"hello", "world", "redis", "cpp", "mysql"};
    std::string regex_str = ".*redis.*";
    auto result = filter_by_regex(vec, regex_str);
    for (const auto& str : result)
    {
        std::cout << str << std::endl;
    }
    return 0;
}