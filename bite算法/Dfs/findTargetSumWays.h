// create by hrj
// Current time: 2025-02-13 20:34:26.089
#include "/home/hrj/leetcode/headFile.h"
class Solution {
    int count = 0;
    int sum = 0;
public:
    void dfs(vector<int>& nums,int pos,int target)
    {
        if(pos == nums.size()) 
        {
            if(sum == target) count++;
            return;
        }

        // 
        sum += (+nums[pos]);
        dfs(nums,pos + 1,target);
        sum -= (2 * nums[pos]);
        dfs(nums,pos + 1,target);
        sum += nums[pos];
    }    
    int findTargetSumWays(vector<int>& nums, int target) {
        dfs(nums,0,target);
        return count;
    }
    void test()
    {
        vector<int> nums = { 1, 1, 1, 1, 1 };
        int ret = findTargetSumWays(nums,3);
        std::cout << "[count]" << ret << std::endl;
    }
};