#include "../headFile.h"
// create by hrj 2025/2/9
class Solution {
private:
     // 去重hash
    std::vector<int> path;
    std::vector<std::vector<int>> ret;
    bool status[10] = { false };
public:
    void dfs(std::vector<int>& nums)
    {
        std::unordered_set<int> hash;
        if(path.size() == nums.size()) 
        {
            ret.push_back(path);
            return;
        }
        
        for(int i = 0; i < nums.size();i++)
        {
            if(status[i] == true || hash.count(nums[i])) continue;

            path.push_back(nums[i]);
            status[i] = true;
            hash.insert(nums[i]);
            dfs(nums);
            path.pop_back();
            status[i] = false;
        }

    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
      
        dfs(nums);
        return ret;
    }
    void test()
    {
        std::vector<int> arr = { 1, 1, 3};
        auto ret = permuteUnique(arr);
        for(auto& ar : ret)
        {
            for(auto e : ar)
                std::cout << e << " ";
            std::cout << std::endl;
        }
    }
};