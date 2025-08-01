#include "../headFile.h"

// 最长的摆动数列
enum class Tendency // 趋势
{
    UP,
    DOWN,
    NOT_KOWN,
}; 
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        // 直接使用贪心选择拐点
        // 统计处所有的波峰以及波谷
        Tendency tend_left = Tendency::NOT_KOWN;
        int n = nums.size();
        int count = 0;
        
        for(int i = 0;i < n;i++)
        {
            // 算算当前右边的状态
            Tendency tend_right;
            if(i + 1 == n || nums[i + 1] == nums[i])
                tend_right = Tendency::NOT_KOWN;
            else if(nums[i + 1] > nums[i]) tend_right = Tendency::UP;

            else tend_right = Tendency::DOWN;
        }
    }
};