#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 14 . 最长的公共前缀
// AC 2025/2/6
// 这里的时间复杂度尾n * log(k) n 字符串个数 ， k 是
class Solution {
public:
    std::string merge(std::vector<std::string>& strs,int left,int right)
    {
        if(left > right) return ""; // 这个应该是用不上的
        else if(left == right) return strs[left];

        int mid = (left + right) >> 1;
        std::string left_prefix = merge(strs,left,mid);
        std::string right_prefix = merge(strs,mid + 1,right);
        // 这里可以出现隐藏的bug
        // std::string& l = left_prefix.size() > right_prefix.size() ? left_prefix : right_prefix;
        // std::string& r = left_prefix.size() < right_prefix.size() ? right_prefix : left_prefix;
        // // int i = 0;
        // for(i = 0;i < r.size();i++)
        //     if(r[i] != l[i]) break;
        // return r.substr(0,i);
        int curl = 0, curr = 0;
        for(curl = 0,curr = 0;curl < left_prefix.size() && curr < right_prefix.size();curl++,curr++)
            if(left_prefix[curl] != right_prefix[curr]) break;
        
        return left_prefix.substr(0,curr);
    }
    string longestCommonPrefix(vector<string>& strs) {
        // 通过归并的方式进行两两比较
        return merge(strs,0,strs.size() - 1);
    }
    void test()
    {
        std::vector<std::string> strs = { "flower" , "flow" , "fl" };
        std::cout << longestCommonPrefix(strs) << std::endl;
    }
};
