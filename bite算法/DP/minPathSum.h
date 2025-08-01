// create by hrj
// Current time: 2025-03-13 15:38:42.861
#include "/home/hrj/leetcode/headFile.h"

// 最小路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) 
    {
        int m = grid.size(), n = grid[0].size();
        // dp[i][j] 表示走到 i j 需要的最小路径和
        vector<vector<int>> dp(m + 1,vector<int>(n + 1,0)); 
        
        for(int i = 2;i <= m;i++) dp[i][0] = INT32_MAX;
        for(int i = 2;i <= n;i++) dp[0][i] = INT32_MAX;

        for(int i = 1;i <= m;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                dp[i][j] = std::min(dp[i][j - 1],dp[i - 1][j]) + grid[i - 1][j - 1];
            }
        }
        return dp[m][n];
    }
};