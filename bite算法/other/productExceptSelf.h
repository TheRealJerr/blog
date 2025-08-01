//
// Created by jerry on 2024/9/7.
//
//leetcode 238. 除自身以外数组的乘积
#include "headFile.h"
#ifndef LEETCODE_PRODUCTEXCEPTSELF_H
#define LEETCODE_PRODUCTEXCEPTSELF_H
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> answer(nums.size(),0);

    vector<int> prefix(nums.size(),0);
    vector<int> suffix(nums.size(),0);
    int leftSum = 1;
    for(int i = 0;i < nums.size();i++)
    {
        leftSum *= nums[i];
        prefix[i] = leftSum;
    }
    int rightSum = 1;
    for(int i = nums.size() - 1;i >= 0;i--){
        rightSum *= nums[i];
        suffix[i] = rightSum;
    }
    for(int i = 0;i < nums.size();i++)
    {
        int left = (i == 0 ? 1 : prefix[i - 1]);
        int right = (i == (nums.size() - 1) ? 1 : suffix[i + 1]);
        answer[i] = left * right;
    }
    return answer;
}
void test()
{
    vector<int> arr = {1,2,3,4};
    vector<int> ret = productExceptSelf(arr);
}
#endif //LEETCODE_PRODUCTEXCEPTSELF_H
