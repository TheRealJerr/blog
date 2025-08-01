// create by hrj
// 2025-02-10 17:29:01.336

#include "../headFile.h"
// class Solution {
//     bool isSymmetry(const std::string& str)  // 检验是否平衡
//     {
//         if(str.empty()) return true;
//         int left = 0, right = str.size() - 1;
//         while(left < right)
//         {
//             if(str[left] == str[right]) return false;
//             left++;
//             right--;
//         }
//         return true;
//     }
    
// public:
//     std::pair<std::vector<std::string>,std::vector<bool>> dfs(int n)
//     {
//         std::pair<std::vector<std::string>,std::vector<bool>> ret;
//         if(n == 1)
//         {
//             ret.first.push_back("()");
//             ret.second.push_back(true);
//             return ret;
//         } 

//         auto last = dfs(n - 1);
//         for(int i = 0; i < last.first.size(); i++)
//         {
//             if(last.second[i] == true)
//             {
//                 // 平衡的话
//                 ret.first.push_back("(" + last.first[i] + ")");
//                 ret.second.push_back(true);

//                 // 平衡就没有() + str && str + () 只有 () 
//                 std::string buffer = "()" + last.first[i];
//                 ret.second.push_back(isSymmetry(buffer));
//                 ret.first.push_back(std::move(buffer));
//             }
//             else
//             {

//             }
//         }
//     }
//     vector<string> generateParenthesisgenerateParenthesis(int n) {
        
//     }
// };

// class Solution
// {
// public:
//     std::unordered_set<std::string> dfs(int n)
//     {
//         std::unordered_set<std::string> ret;
//         if(n == 1) 
//         {
//             ret.insert("()");
//             return ret;
//         }

//         auto last = dfs(n - 1);
//         for(auto& str : last)
//         {
//             ret.insert(str + "()");
//             ret.insert("()" + str);
//             ret.insert("(" + str + ")");
//         }
//         return ret;
//     }
//     vector<string> generateParenthesis(int n)
//     {
//         auto ret = dfs(n);
//         return std::vector<std::string>(ret.begin(),ret.end());
//     }
//     void test()
//     {
//         auto ret = generateParenthesis(3);
//         for(auto& str : ret)
//             std::cout << str << std::endl;
//     }
//     void newtest()
//     {
//         std::unordered_set<std::string> n1 = { "()(())()","(())()()","(((())))","()()(())","()((()))","((())())","(()(()))","(()()())","()()()()","((()()))","((()))()","()(()())","(()())()" };
//         std::vector<std::string> n2 = { "(((())))","((()()))","((())())","((()))()","(()(()))","(()()())","(()())()","(())(())","(())()()","()((()))","()(()())","()(())()","()()(())","()()()()" };
//         for(auto& str : n2)
//             if(n1.count(str) == false) std::cout << str << std::endl;
//     }
// };
// // ["()(())()","(())()()","(((())))","()()(())","()((()))","((())())","(()(()))","(()()())","()()()()","((()()))","((()))()","()(()())","(()())()"]
// // ["(((())))","((()()))","((())())","((()))()","(()(()))","(()()())","(()())()","(())(())","(())()()","()((()))","()(()())","()(())()","()()(())","()()()()"]
// // ()
// // (())  ()()
// // ["((()))","(()())","(())()","()(())","()()()"]
// // (((()))) ((()())) 

class Solution
{
    std::string path;
    std::vector<std::string> ret;
public:
    void dfs(int left,int right)
    {
        if(left == right && left == 0) ret.push_back(path);
        if(left > right) return; // jianzhi

        if(left > 0)
        {
            path.push_back('(');
            dfs(left - 1,right);
            path.pop_back();
        }

        if(right > 0)
        {
            path.push_back(')');
            dfs(left,right - 1);
            path.pop_back();
        }
    }
    vector<std::string> generateParenthesis(int n)
    {
        dfs(n,n);
        return ret;
    }
    void test()
    {
        auto ret = generateParenthesis(4);
        for(auto& mem : ret)
            std::cout << mem << std::endl;
        std::cout << "[size]" << ret.size() << std::endl;
    }
};