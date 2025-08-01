// 全排列
// 2025/2/9
#include "../headFile.h"
class Solution
{
private:
    std::vector<std::vector<int>> ret;
    std::vector<int> path;
    bool status[7] = { false };
public:

    void dfs(std::vector<int>& nums)
    {
        if(nums.size() == path.size()) 
        {
            ret.push_back(path);
            return;
        }
        else
        {
            for(size_t i = 0; i < nums.size(); i++)
            {
                if(status[i] == true) continue;
                
                path.push_back(nums[i]);
                status[i] = true;
                dfs(nums);
                // 回溯 -> 回复现场
                path.pop_back();
                status[i] = false;
            }
            return;
        }
    }

    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        dfs(nums);
        return ret;
    }
    void test()
    {
        std::vector<int> nums = { 1, 2, 3, 4 };
        auto ret = permute(nums);
        std::cout << "[" << std::endl;
        for(auto& e : ret)
        {
            std::cout << "[";
            for(auto i : e)
                std::cout << i << " ";
            std::cout << "]";
        }
        std::cout << "]" << std::endl;
    }
};