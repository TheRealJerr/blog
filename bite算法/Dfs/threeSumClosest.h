// create by hrj
// Current time: 2025-02-17 00:05:15.127
#include "/home/hrj/leetcode/headFile.h"
#include <ctype.h>
class Solution {
    int ret = INT32_MAX;
    int level;
    int sum;
public:
    void dfs(vector<int>& nums,int pos,int target)
    {
        
        for(int i = pos; i < nums.size(); i++)
        {
            sum += nums[i];
            level++;
            if(level == 3)
            {
                ret = (abs(sum - target) < abs(ret - target) ? sum : ret); // ret的更新
            }
            else dfs(nums, i + 1,target);
            level--;
            sum -= nums[i];
        }
    }
    int threeSumClosest(vector<int>& nums, int target) {
        dfs(nums,0,target);
        return ret;
    }
    void test()
    {
        vector<int> arr = {-1,2,1,-4};
        auto re = threeSumClosest(arr,1);
        std::cout << re << std::endl;
    }
};