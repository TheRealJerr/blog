#include "../headFile.h"

class Solution {
private:
    int Sum = 0;
    
public:
    void dfs(vector<int>& nums,int pos,int sum)
    {
        if(pos == (int)nums.size()) return;
        
        for(int i = pos; i < (int)nums.size(); i++)
        {
            Sum += sum ^ nums[i];
            dfs(nums,i + 1,sum ^ nums[i]);
            // 这里sum是传值，不用通过回溯来keep 
        }
        return;
    }
    int subsetXORSum(vector<int>& nums) {
        // 这道题和求子集很像
        dfs(nums,0,0);
        return Sum;
    }
    void test()
    {
        std::vector<int> arr = { 1, 2 };
        auto ret = subsetXORSum(arr);
        std::cout << "Sum: " << ret << std::endl; 
    }
};