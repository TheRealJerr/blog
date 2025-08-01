// 子集 
// 2025/2/9
#include "../headFile.h"












class Solution {
private:
    std::vector<std::vector<int>> ret;
    
    std::vector<int> path;
public:

    void dfs(std::vector<int>& nums,int cur)
    {
        if(nums.size() == path.size()) return; // 走到了尽头

        for(int i = cur; i < nums.size();i++)
        {
            path.push_back(nums[i]);
            ret.push_back(path);
            dfs(nums,i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) 
    {
        ret.push_back(vector<int>());
        dfs(nums,0);
        return ret;
    }
    
    void test()
    {
        std::vector<int> nums = { 1, 2, 3};
        auto ret = subsets(nums);
        std::cout << "[" << std::endl;
        for(auto& e : ret)
        {
            std::cout << "[";
            for(auto i : e)
                std::cout << i << " ";
            std::cout << "]";
        }
        std::cout << "]" << std::endl;
        std::cout << "[size]:" << ret.size() << std::endl;
    }
};