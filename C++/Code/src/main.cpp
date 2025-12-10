// 第一我们这里C++的配置项目
#include <iostream>
#include <string>

namespace Config
{
    enum class CXX_VERSION
    {
        CXX11,
        CXX14,
        CXX17,
    };

    // 记录的我们这里C++的标准
    inline constexpr CXX_VERSION VERSION = CXX_VERSION::CXX17;


    
};

namespace Project
{
    
    std::string getStringBUffer()
    {
        // 11的版本
       if constexpr (Config::VERSION == Config::CXX_VERSION::CXX11)
       {

       }
       // 14的版本
       else if constexpr (Config::VERSION == Config::CXX_VERSION::CXX14)
       {

       }
       // 17的版本
       else if constexpr (Config::VERSION == Config::CXX_VERSION::CXX17)
       {

       }
    }

}