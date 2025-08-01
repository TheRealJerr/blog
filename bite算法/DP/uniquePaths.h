// create by hrj
// Current time: 2025-03-13 14:31:09.123
#include "/home/hrj/leetcode/headFile.h"

// 不同路径
class Solution
{
public:
    int uniquePaths(int m, int n) 
    {
        vector<vector<int>> dp(m + 1,vector<int>(n + 1, 0));
        // 0 1 0 0 0 0 0
        // 0
        // 0
        // 0 
        dp[0][1] = 1;
        for(int i = 1;i <= m;i++)
            for(int j = 1;j <= n;j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp[m][n];           
    }
};