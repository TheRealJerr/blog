// create by hrj
// Current time: 2025-03-13 13:44:27.751
#include "/home/hrj/leetcode/headFile.h"

class Solution {
public:
    int isAlphabet(std::string str)
    {
        if(str.size() == 1)
        {
            if(str[0] <= '9' && str[0] >= '1') return 1;
            else return 0;
        }
        else if(str.size() == 2)
        {
            int tmp = std::stoi(str);
            if(tmp >= 10 && tmp <= 26) return 1;
            else return 0;
        }
        else return 0;
    }
    int numDecodings(string s)
    {
        // 解码方法
        // 通过dp进行动态规划
        std::vector<int> dp(s.size(),0);
        dp[0] = isAlphabet(s.substr(0,1));
        if(s.size() == 1) return dp[0];
        
        // 初始化
        if(dp[0]) 
            if(isAlphabet(s.substr(1,1))) dp[1] += dp[0];
        dp[1] += isAlphabet(s.substr(0,2));
        
        // 遍历
        for(int k = 2;k < s.size();k++)
        {
            if(dp[k - 1]) 
                if(isAlphabet(s.substr(k,1))) 
                    dp[k] += dp[k - 1];
            if(dp[k - 2])
                if(isAlphabet(s.substr(k - 1,2)))
                    dp[k] += dp[k - 2];
        }
        return dp.back();
    }
};