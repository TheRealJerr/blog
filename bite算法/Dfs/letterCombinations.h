#include "../headFile.h"

class Solution
{
private:
    std::unordered_map<char,std::string> map = 
    {
        {'2',"abc"},
        {'3',"def"},
        {'4',"ghi"},
        {'5',"jkl"},
        {'6', "mno"},
        {'7',"pqrs"},
        {'8',"tuv"},
        {'9',"wxyz"},
        
    };
    std::string Map(char a)
    {
        return map[a];
    }
    std::vector<std::string> ret;
    std::string path;
public:
    void dfs(std::string & digits,int pos)
    {
        if(path.size() == digits.size())
        {
            ret.push_back(path);
            return;
        }

        std::string buffer = Map(digits[pos]);
        for(auto i : buffer)
        {
            path.push_back(i);
            dfs(digits,pos + 1);
            path.pop_back();
        }

    }
    vector<string> letterCombinations(string digits)
    {
        dfs(digits,0);
        return ret;
    }
    void test()
    {
        std::string test = "23";
        auto ret = letterCombinations(test);
        for(auto& str : ret)
            std::cout << "[" << str << "]" << std::endl;
        
    }
    void testMap()
    {
        std::cout << Map('1') << std::endl;
        std::cout << Map('2') << std::endl;
        std::cout << Map('9') << std::endl;
    }
};