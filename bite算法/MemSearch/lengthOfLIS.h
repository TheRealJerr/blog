// create by hrj
// Current time: 2025-02-24 20:58:01.075
#include "/home/hrj/leetcode/headFile.h"

// 最长的递增子序列
// 记忆化搜索

class Solution
{
    int n;
    vector<int> mem;
public:
    void Init(int size)
    {
        n = size;
        mem.resize(n,0);
    }

    int lenthOfLIS(vector<int>& nums)
    {
        Init(nums.size());
        for(int i = n - 1;i >= 0;i--)
        {
            int max_size = 1;
            for(int j = i + 1;j < n;j++)
            {
                if(nums[i] < nums[j]) max_size = std::max(max_size,1 + mem[j]);
            }
            mem[i] = max_size;
        }
        int ret = 0;
        for(auto i : mem)
            ret = std::max(i,ret);
        return ret;
    }
};