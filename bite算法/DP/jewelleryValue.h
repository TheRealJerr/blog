// create by hrj
// Current time: 2025-03-17 15:15:04.730
#include "/home/hrj/leetcode/headFile.h"
// 珠宝的最高价值
class Solution {
public:
    using ll = long long int;
    int jewelleryValue(vector<vector<int>>& frame) {
        // frame根本没有任何珠宝
        if(frame.size() == 0 || frame[0].size() == 0) return 0;
        // 创建dp表
        int m = frame.size(), n = frame[0].size();
        vector<vector<ll>> dp(m,vector<ll>(n,0));
        // dp[i][j]表示的是到达某个位置所能拿到的最高价值的珠宝
        for(int i = 1;i <= m;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                
            }

        }
    }
};
